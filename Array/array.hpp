#ifndef ARRAY_H
#define ARRAY_H
#define ARRAY_TRAITS_IMPLEMENTED

#include <cstddef>
#include <utility>

template <class T, size_t N>
struct Array {
    T buffer[N];

    const T& Front() const { return buffer[0]; }
    const T& Back() const { return buffer[N - 1]; }

    T& Front() { return buffer[0]; }
    T& Back() { return buffer[N - 1]; }

    size_t Size() const { return N; }
    bool Empty() const { return N == 0; }

    const T* Data() const { return buffer; } // перегрузка операций
    T* Data() { return buffer; }

    void Fill(const T& value) {
      for (size_t i = 0; i < N; ++i) { buffer[i] = value; }
    }

    void Swap(Array<T, N>& other) {
      for (size_t i = 0; i < N; ++i) { std::swap(buffer[i], other.buffer[i]); }
    }

    const T& operator[](size_t i) const { return buffer[i]; }
    T& operator[](size_t i) { return buffer[i]; }
};

// GetSize — возвращает размер массива, если это C-массив
template <typename T, size_t N>
size_t GetSize(const T (&)[N]) { return N; }

template <typename T>
size_t GetSize(const T&) { return 0; }

// GetRank — число координат многомерного массива array
template <typename T>
size_t GetRank(const T&) {
    return 0; // не массив
}
template <typename T, size_t N>
size_t GetRank(const T (&arr)[N]) {
    // один уровень массива + глубина вложенного
    return 1 + GetRank(arr[0]);
}

// GetNumElements — общее число элементов в многомерном массиве array
template <typename T>
size_t GetNumElements(const T&) {
    return 1; // не массив — один элемент
}
template <typename T, size_t N>
size_t GetNumElements(const T (&arr)[N]) {
    // количество элементов в этом уровне * количество во вложенном
    return N * GetNumElements(arr[0]);
}

#endif
