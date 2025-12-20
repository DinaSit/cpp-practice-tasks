#ifndef SHARED_PTR_HPP
#define SHARED_PTR_HPP

#define WEAK_PTR_IMPLEMENTED

#include <stdexcept>

class BadWeakPtr : std::runtime_error {
 public:
  BadWeakPtr() : std::runtime_error("BadWeakPtr") {
  }
};

struct Counter {
    size_t strong; // счетчик обычных (сильных) ссылок strong_count
    size_t weak; // поле weak_count для подсчета количества слабых указателей
};

template <class T>
class SharedPtr;

template <class T>
class WeakPtr;

template <class T>
class SharedPtr {
    T* ptr_;
    Counter* cnt_;

    void Unlink() {
      if (!cnt_) {
        ptr_ = nullptr;
        return;
      }

      Counter* c = cnt_;
      T* p = ptr_;
      cnt_ = nullptr;
      ptr_ = nullptr;

      if (--c->strong == 0) {
        if (c->weak == 0) {
            delete p;
            delete c;
        } else {
            delete p;
        }
      }
    }

public:
  template <class A>
  friend class WeakPtr;

  // Конструктор по умолчанию (создает нулевой указатель);
  SharedPtr() :ptr_(nullptr), cnt_(nullptr) {}

  // Конструктор от указателя (сохраняет указатель на владеемый объект);
  explicit SharedPtr(T* pointer) : ptr_(pointer), cnt_(nullptr) {
    if (pointer != nullptr) {
        cnt_ = new Counter{1, 0};
    }
  }

  // copy&swap idiom
  SharedPtr& operator=(SharedPtr&& other) noexcept {
    auto copy = std::move(other);
    Swap(copy);
    return *this;
  }

  SharedPtr(const SharedPtr& other) : ptr_(other.ptr_), cnt_(other.cnt_) {
    if (cnt_ != nullptr) {
      cnt_->strong += 1;
    }
  }

  SharedPtr(SharedPtr&& other) noexcept : ptr_(other.ptr_), cnt_(other.cnt_) {
    other.ptr_ = nullptr;
    other.cnt_ = nullptr;
  }

  SharedPtr& operator=(const SharedPtr& other) {
    if (this != &other) {
      auto copy = other;
      Swap(copy);
    }
    return *this;
  }

  SharedPtr& operator=(std::nullptr_t) noexcept {
    Reset();
    return *this;
  }

  ~SharedPtr() {
    Unlink();
  }

  // Метод Reset(T* ptr = nullptr), меняет указатель, которым владеет объект;
  void Reset(T* pointer = nullptr) {
    Unlink();
    if (pointer != nullptr) {
      ptr_ = pointer;
      cnt_ = new Counter{1, 0};
    } else {
      ptr_ = nullptr;
      cnt_ = nullptr;
    }
  }

  // Метод Swap(SharedPtr<T>&);
  void Swap(SharedPtr& other) {
    std::swap(ptr_, other.ptr_);
    std::swap(cnt_, other.cnt_);
  }

  // Метод Get(), возвращающий указатель на владеемый объект;
  T* Get() const noexcept {
    return ptr_;
  }

  // Метод UseCount(), возвращающий число "сильных" ссылок на объект;
  std::size_t UseCount() const noexcept {
    return cnt_ ? cnt_->strong : 0;
  }

  // Операцию разыменовывания operator*;
  T& operator*() const {
    return *ptr_;
  }

  // Операцию "стрелочка" operator->;
  T* operator->() const {
    return ptr_;
  }

  // Явную операцию приведения к bool (operator bool).
  explicit operator bool() const noexcept {
    return ptr_ != nullptr;
  }

  // В SharedPtr необходимо добавить конструктор от WeakPtr, который работает аналогично методу Lock(), 
  // но в случае Expired() == true должно бросаться исключение BadWeakPtr.
  explicit SharedPtr(const WeakPtr<T>& weak) : ptr_(nullptr), cnt_(nullptr) {
    if (weak.Expired()) {
      throw BadWeakPtr();
    }
    ptr_ = weak.ptr_;
    cnt_ = weak.cnt_;
    cnt_->strong += 1;
  }
};

// шаблон WeakPtr — аналог std::weak_ptr,
template <class T>
class WeakPtr {
  T* ptr_;
  Counter* cnt_;

  void Unlink() {
    if (!cnt_) {
      ptr_ = nullptr;
      return;
    }

    Counter* c = cnt_;
    cnt_ = nullptr;
    ptr_ = nullptr;

    if (--c->weak == 0 && c->strong == 0) {
      delete c;
    }
  }

public:
  template <class A>
  friend class SharedPtr;

  WeakPtr() : ptr_(nullptr), cnt_(nullptr) {
  }

  // Конструктор от SharedPtr (увеличивает число "слабых" ссылок);
  explicit WeakPtr(const SharedPtr<T>& shared) : ptr_(shared.ptr_), cnt_(shared.cnt_) {
    if (cnt_ != nullptr) {
      cnt_->weak += 1;
    }
  }

  WeakPtr(const WeakPtr& other) noexcept : ptr_(other.ptr_), cnt_(other.cnt_) {
    if (cnt_ != nullptr) {
      cnt_->weak += 1;
    }
  }

  WeakPtr(WeakPtr&& other) noexcept : ptr_(other.ptr_), cnt_(other.cnt_) {
    other.ptr_ = nullptr;
    other.cnt_ = nullptr;
  }

  WeakPtr& operator=(const WeakPtr& other) noexcept {
    if (this != &other) {
      auto copy = other;
      Swap(copy);
    }
    return *this;
  }

  WeakPtr& operator=(WeakPtr&& other) {
    auto copy = std::move(other);
    Swap(copy);
    return *this;
  }

  WeakPtr& operator=(const SharedPtr<T>& shared) noexcept {
    Reset();
    ptr_ = shared.ptr_;
    cnt_ = shared.cnt_;
    if (cnt_ != nullptr) {
      cnt_->weak += 1;
    }
    return *this;
  }

  // Метод Swap(WeakPtr<T>&);
  void Swap(WeakPtr& other) noexcept {
    std::swap(ptr_, other.ptr_);
    std::swap(cnt_, other.cnt_);
  }

  // Метод Reset(), отвязывающего указатель от объекта;
  void Reset() {
    Unlink();
  }

  // Метод UseCount(), возвращающего число "сильных" ссылок на объект;
  std::size_t UseCount() const noexcept {
    return cnt_ ? cnt_->strong : 0;
  }

  // Метод Expired(), возвращающий true, если сильных ссылок на объект уже нет (объект удален);
  bool Expired() const noexcept {
    return UseCount() == 0;
  }

  // Метод Lock(), возвращающий SharedPtr на объект (если Expired() == true, то возвращается пустой указатель);
  SharedPtr<T> Lock() const {
    SharedPtr<T> shared;
    shared.ptr_ = ptr_;
    shared.cnt_ = cnt_;
    if (cnt_ != nullptr) {
      cnt_->strong += 1;
    }
    return shared;
  }

  ~WeakPtr() {
    Unlink();
  }
};

template <class T, class... Args>
SharedPtr<T> MakeShared(Args&&... args) {
    return SharedPtr<T>(new T(std::forward<Args>(args)...));
};

#endif // SHARED_PTR_HPP
