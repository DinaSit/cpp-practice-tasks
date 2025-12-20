#ifndef UNIQUE_PTR_HPP
#define UNIQUE_PTR_HPP

#define MAKE_UNIQUE_IMPLEMENTED

#include <utility>

template <class T>
class UniquePtr {
    T* ptr_;


public:
    // конструктор по умолчанию
    UniquePtr() : ptr_(nullptr) {}
    // конструктор от указателя
    explicit UniquePtr(T* pointer) : ptr_(pointer) {}

    // ПРАВИЛО ПЯТИ
    // конструктор копирования
    UniquePtr(const UniquePtr& other) = delete;
    // копирующее присваивание
    UniquePtr& operator=(const UniquePtr& other) = delete;
    // конструктор перемещения (noexcept)
    UniquePtr(UniquePtr&& other) noexcept : ptr_(other.ptr_) { 
        other.ptr_ = nullptr; 
    }
    // перемещающее присваивание (noexcept)
    UniquePtr& operator=(UniquePtr&& other) noexcept {
        if (this != &other) {
            delete ptr_;
            ptr_ = other.ptr_;
            other.ptr_ = nullptr;
        }
        return *this;
    }
    // деструктор
    ~UniquePtr() { 
        delete ptr_; 
    }

    // Метод Release(), который отлучает класс от владения текущим ресурсом и возвращает указатель на него;
    T* Release() noexcept {
        T* tmp = ptr_;
        ptr_ = nullptr;
        return tmp;
    }

    // Метод Reset(T* ptr = nullptr), меняет указатель, которым владеет объект (старый ресурс удаляется);
    void Reset(T* p = nullptr) noexcept {
        if (ptr_ != p) {
            delete ptr_;
            ptr_ = p;
        }
    }

    // Метод Swap(UniquePtr<T>&);
    void Swap(UniquePtr& other) noexcept {
        std::swap(ptr_, other.ptr_);
    }

    // Метод Get(), возвращающий указатель на объект;
    T* Get() const noexcept {
        return ptr_;
    }

    // Оператор разыменовывания operator*
    T& operator*() const {
        return *ptr_;
    }
    // Оператор "стрелочка" operator-> (унарная операция)
    T* operator->() const {
        return ptr_;
    }

    // Явный оператор приведения к bool (operator bool).
    explicit operator bool() const noexcept {
        return ptr_ != nullptr;
    }
};

template <class T, class... Args> // пак типов произвольной длины
UniquePtr<T> MakeUnique(Args&&... args) { // пак параметров функции: любое количество аргументов любых типов.
    return UniquePtr<T>(new T(std::forward<Args>(args)...)); // распаковка пачки аргументов и типов (lvalue/rvalue)
}

#endif // UNIQUE_PTR_HPP
