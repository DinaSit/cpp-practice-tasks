#include "string.hpp"

// Конструктор по умолчанию;
String::String() : str_(nullptr), size_(0), capacity_(0) {
}

// Конструктор, принимающий size и symbol, — создает строку длины size, заполненную символами symbol;
String::String(size_t size, char symbol) : str_(nullptr), size_(0), capacity_(0) {
    if (size == 0) { return; }
    str_ = new char[size + 1];
    size_ = capacity_ = size;
    for (size_t i = 0; i < size; ++i) {
        str_[i] = symbol;
    }
    str_[size] = '\0';
}

// Конструктор, принимающий массив char (const char*) и количество первых символов (size), которые нужно скопировать;
String::String(const char* c_str, size_t size) : str_(nullptr), size_(0), capacity_(0) {
    if (size == 0) { return; }
    str_ = new char[size + 1];
    std::strncpy(str_, c_str, size);
    str_[size] = '\0';
    size_ = capacity_ = size;
}
// Done
// Конструктор, принимающий С-style строку (const char*) и создающий на ее основе строку
String::String(const char* c_str) : String(c_str, std::strlen(c_str)) { // NOLINT
}

// Правило пяти
// Конструктор копирования
String::String(const String& other) : String(other.str_, other.size_) {
}
// Конструктор перемещения
String::String(String&& other) noexcept : str_(other.str_), size_(other.size_), capacity_(other.capacity_) {
    other.str_ = nullptr;
    other.size_ = other.capacity_ = 0;
}
// Копирующее присваивание
String& String::operator=(const String& other) noexcept {
    if (this != &other) {
        auto copy = other;
        Swap(copy);
    }
    return *this;
}
// Перемещающее присваивание
String& String::operator=(String&& other) noexcept {
    auto copy = std::move(other);
    Swap(copy);
    return *this;
}
// Деструктор
String::~String() {
    delete[] str_;
}

// модификаторы
void String::Clear() {
    size_ = 0;
    if (str_) { str_[size_] = '\0'; }
}

void String::Swap(String& other) {
    std::swap(str_, other.str_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
}

void String::PopBack() {
    if (size_ == 0) { return; }
    --size_;
    if (str_) { str_[size_] = '\0'; }
}

// Метод PushBack(symbol) — добавляет символ symbol в конец строки (при необходимости строка расширяется);
void String::PushBack(char symbol) {
    if (size_ + 1 > capacity_) {
        Reserve(capacity_ == 0 ? 1 : capacity_ * 2);
    }
    str_[size_] = symbol;
    str_[size_ + 1] = '\0';
    ++size_;
}
// принимает другую строку (String) и приписывает ее в конец текущей;
String& String::operator+=(const String& rhs) {
    if (rhs.size_ == 0) { return *this; }

    size_t n = size_ + rhs.size_;
    while (n >= capacity_) {
        Reserve(capacity_ == 0 ? 1 : capacity_ * 2);
    }

    if (this == &rhs) {
        const size_t old = size_;
        for (size_t i = 0; i < old; ++i) {
            str_[old + i] = str_[i];
        }
        size_ += old;
    } else {
        for (size_t i = 0; i < rhs.size_; ++i) {
            str_[size_ + i] = rhs.str_[i];
        }
        size_ += rhs.size_;
    }
    str_[size_] = '\0';

    return *this;
}

// изменяет размер на new_size. Если вместимость не позволяет хранить столько символов, 
// то выделяется новый буфер с вместимостью new_size. 
// В случае new_size > size заполняет недостающие символы значением symbol;
void String::Resize(size_t new_size, char symbol) {
    if (new_size > capacity_) {
        capacity_ = new_size;
    }
    auto new_str = new char[capacity_ + 1];
    for (size_t i = 0; i < size_; ++i) {
        new_str[i] = str_[i];
    }
    new_str[size_] = '\0';
    delete[] str_;
    str_ = new_str;

    for (size_t i = size_; i < new_size; ++i) {
        str_[i] = symbol;
    }
    size_ = new_size; 
    str_[size_] = '\0';
}
// изменяет вместимость на max(new_capacity, текущая вместимость). Размер при этом не изменяется;
void String::Reserve(size_t new_capacity) {
    if (new_capacity <= capacity_) { return; }
    auto new_str = new char[new_capacity + 1];
    for (size_t i = 0; i < size_; ++i) {
        new_str[i] = str_[i];
    } 
    new_str[size_] = '\0';
    delete[] str_;
    str_ = new_str;
    capacity_ = new_capacity;
}
// уменьшает capacity до size (убирает излишек);
void String::ShrinkToFit() {
    // if (capacity_ < size_ + 1) { return; }
    // if (size_ == 0) {
    //     size_ = 0;
    //     capacity_ = 0;
    //     delete[] str_;
    //     str_ = nullptr;
    //     return;
    // }
    auto new_str = new char[size_ + 1];
    for (size_t i = 0; i < size_; ++i) {
        new_str[i] = str_[i];
    } 
    new_str[size_] = '\0';
    delete[] str_;
    str_ = new_str;
    capacity_ = size_;
}

// конкатенация
String operator+(const String& a, const String& b) {
    String res;
    if (a.Size() + b.Size() > 0) {
        res.Reserve(a.Size() + b.Size());
        res += a;
        res += b;
    }
    return res;
}

// лексикографические сравнения
bool operator==(const String& a, const String& b) {
    if (a.Size() != b.Size()) { return false; }
    for (size_t i = 0; i < a.Size(); ++i) {
        if (a[i] != b[i]) {
            return false;
        }
    }
    return true;
}
bool operator!=(const String& a, const String& b) {
    return !(a == b);
}
bool operator<(const String& a, const String& b) {
    size_t size = (a.Size() < b.Size() ? a.Size() : b.Size());
    for (size_t i = 0; i < size; ++i) {
        if (a[i] < b[i]) { return true; }
        if (a[i] > b[i]) { return false; }
    }
    return a.Size() < b.Size();
}
bool operator>(const String& a, const String& b) {
    return b < a;
}
bool operator<=(const String& a, const String& b) {
    return !(b < a);
}
bool operator>=(const String& a, const String& b) {
    return !(a < b);
}

// вывод
std::ostream& operator<<(std::ostream& out, const String& s) {
    for (size_t i = 0; i < s.Size(); ++i) {
        out.put(s[i]);
    }
    return out;
}
// ввод
std::istream& operator>>(std::istream& in, String& s) {
    s.Clear();
    char ch = 0;
    // пропускаем ведущие пробелы
    while (in.get(ch)) {
        if (!std::isspace(static_cast<unsigned char>(ch))) {
            s.PushBack(ch);
            break;
        }
    }
    // если поток закончился до первого непробельного
    if (!in) { return in; }
    // читаем до первого встреченного пробельного символа/конца потока
    while (in.get(ch)) {
        if (std::isspace(static_cast<unsigned char>(ch))) {
            break;
        }
        s.PushBack(ch);
    }
    return in;
}
