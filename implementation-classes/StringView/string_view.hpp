#ifndef STRING_VIEW_HPP
#define STRING_VIEW_HPP

#include <cstddef>
#include <cstring>
#include <stdexcept>

struct StringViewOutOfRange : public std::out_of_range {
    explicit StringViewOutOfRange(const char* msg) : std::out_of_range(msg) {} 
};

class StringView {
private:
    const char* str_;
    size_t size_;

public:
    // Конструктор по умолчанию (nullptr строка)
    StringView() : str_(nullptr), size_(0) {}

    // Неявный конструктор от const char*
    StringView(const char* c_str) : str_(c_str), size_(c_str ? std::strlen(c_str) : 0) {} // NOLINT

    // Конструктор от const char* и size_t (длина передается вторым параметром)
    StringView(const char* c_str, size_t size) : str_(c_str), size_(size) {}

    // operator[]
    const char& operator[](size_t i) const {
        return str_[i];
    }

    // Методы Front(), Back(), Size(), Length(), Empty(), Data()
    const char& Front() const { return str_[0]; }
    const char& Back()  const { return str_[size_ - 1]; }
    size_t Size() const { return size_; }
    size_t Length() const { return size_; }
    bool Empty() const { return size_ == 0; }
    const char* Data() const { return str_; }

    void Swap(StringView& other) {
        const char* tmp_ptr = str_;
        str_ = other.str_;
        other.str_ = tmp_ptr;

        size_t tmp_size = size_;
        size_ = other.size_;
        other.size_ = tmp_size;
    }

    void RemovePrefix(size_t prefix_size) {
        if (prefix_size > size_) { prefix_size = size_; }
        if (prefix_size == 0) { return; }
        if (str_) { str_ += prefix_size; }
        size_ -= prefix_size;
    }

    void RemoveSuffix(size_t suffix_size) {
        if (suffix_size > size_) { suffix_size = size_; }
        size_ -= suffix_size;
    }

    StringView Substr(size_t pos, size_t count = static_cast<size_t>(-1)) const {
        if (pos > size_) {
            throw StringViewOutOfRange("Position is out of range");
        }
        size_t len = (count < size_ - pos) ? count : size_ - pos;
        if (len == 0) {
            return str_ ? StringView(str_ + pos, 0) : StringView();
        }
        return { str_ ? (str_ + pos) : str_, len };
    }
};

#endif
