#ifndef BINARY_H
#define BINARY_H

template <class T>
const T* LowerBound(const T* begin, const T* end, const T& value) {
    if (!begin || !end) return end; 

    while (begin < end) {
        const T* mid = begin + (end - begin) / 2;
        if (*mid < value) {
            begin = mid + 1;
        } else { end = mid; }
    }
    return begin;
}

template <class T>
const T* UpperBound(const T* begin, const T* end, const T& value) {
    if (!begin || !end) return end;

    while (begin < end) {
        const T* mid = begin + (end - begin) / 2;
        if (!(value < *mid)) {
            begin = mid + 1;
        } else { end = mid; }
    }
    return begin;
}

template <class T>
bool BinarySearch(const T* begin, const T* end, const T& value) {
    if (begin == end) return false;
    if (!begin || !end) return false; 

    const T* it = LowerBound(begin, end, value);
    return (it != end) && !(*it < value) && !(value < *it);
}

#endif
