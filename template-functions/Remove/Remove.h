#ifndef REMOVE_H
#define REMOVE_H

template <class T>
T* Remove(T* src_begin, T* src_end, const T& value) {
    T* write = src_begin;
    while (src_begin < src_end) {
        if (*src_begin != value) { *write = *src_begin; ++write; }
        ++src_begin;
    }
    return write;
}

#endif
