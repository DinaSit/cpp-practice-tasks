#ifndef STRING_HPP
#define STRING_HPP

#include <cstddef>
#include <cstring>
#include <iostream>
#include <fstream>
#include <utility>

class String {
    char* str_;
    size_t size_;
    size_t capacity_;

public:
    String();
    String(const char* c_str); // NOLINT
    String(const char* c_str, size_t size);
    String(size_t size, char symbol);

    // правило пяти
    String(const String& other);
    String(String&& other) noexcept;
    String& operator=(const String& other) noexcept;
    String& operator=(String&& other) noexcept;
    ~String();

    // индексирование
    const char& operator[](size_t i) const {
        return str_[i];
    }

    char& operator[](size_t i) {
        return str_[i];
    }

    // front/back
    char& Front() { return str_[0]; }
    const char& Front() const { return str_[0]; }
    char& Back() { return str_[size_ - 1]; }
    const char& Back() const { return str_[size_ - 1]; }

    // Методы для доступа к строке
    char* CStr() { return str_; }
    const char* CStr() const { return str_; }
    char* Data() { return str_; }
    const char* Data() const { return str_; }
    bool Empty() const { return size_ == 0; }
    size_t Size() const { return size_; }
    size_t Length() const { return size_; }
    size_t Capacity() const { return capacity_; }

    // модификаторы
    void Clear();
    void Swap(String& other);

    void PopBack();
    void PushBack(char symbol);

    String& operator+=(const String& rhs);

    void Resize(size_t new_size, char symbol = '\0');
    void Reserve(size_t new_capacity);
    void ShrinkToFit();
};

// конкатенация
String operator+(const String& a, const String& b);

// лексикографические сравнения
bool operator==(const String& a, const String& b);
bool operator!=(const String& a, const String& b);
bool operator<(const String& a, const String& b);
bool operator>(const String& a, const String& b);
bool operator<=(const String& a, const String& b);
bool operator>=(const String& a, const String& b);

// ввод/вывод
std::ostream& operator<<(std::ostream& out, const String& s);
std::istream& operator>>(std::istream& in, String& s);

#endif
