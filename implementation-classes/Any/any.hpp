#ifndef ANY_HPP
#define ANY_HPP

#include <stdexcept>
#include <memory>

class BadAnyCast : public std::bad_cast {
 public:
  [[nodiscard]] const char* what() const noexcept override {
    return "BadAnyCast error";
  }
};

struct IHolder {
  virtual ~IHolder() = default;
  virtual std::unique_ptr<IHolder> Clone() const = 0;
};

// структурка, хранящая в себе любой тип данных
template <class T>
struct AnyHolder : public IHolder {
  T value;

  explicit AnyHolder(const T& x) : value(x) {
  }

  std::unique_ptr<IHolder> Clone() const override {
    return std::make_unique<AnyHolder<T>>(value);
  }
};

class Any {
  std::unique_ptr<IHolder> ptr_ = std::unique_ptr<IHolder>();

public:
  Any() = default;

  // копирующий конструктор
  Any(const Any& other) : ptr_(other.ptr_ ? other.ptr_->Clone() : nullptr) {
  }

  // перемещающий конструктор
  Any(Any&& other) noexcept = default;

  // шаблонный конструктор от произвольного типа
  Any(const T& value) : ptr_(std::make_unique<AnyHolder<T>>(value)) { // NOLINT
  }

  // копирующее присваивание
  Any& operator=(const Any& other) {
    if (this != &other) {
      ptr_ = other.ptr_ ? other.ptr_->Clone() : nullptr;
    }
    return *this;
  }

  // перемещающее присваивание
  Any& operator=(Any&& other) noexcept = default;

  // шаблонный оператор присваивания
  Any& operator=(const T& value) {
    ptr_ = std::make_unique<AnyHolder<T>>(value);
    return *this;
  }

  ~Any() = default;

  void Swap(Any& other) noexcept {
    ptr_.swap(other.ptr_);
  }

  void Reset() noexcept {
    ptr_.reset();
  }

  bool HasValue() const noexcept {
    return ptr_ != nullptr;
  }

  friend T AnyCast(const Any& any);
};

// Внешняя шаблонная функция, которая возвращает значение, в случае, если IHolder указывает на AnyHolder<T> и бросает BadAnyCast в противном случае
template <class T> 
T AnyCast(const Any& any) {
  auto* anyholder_ptr = dynamic_cast<AnyHolder<T>*>(any.ptr_.get());
  if (anyholder_ptr != nullptr) {
    return anyholder_ptr->value;
  }
  throw BadAnyCast{};
};

#endif // ANY_HPP
