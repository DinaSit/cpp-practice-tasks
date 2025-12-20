#ifndef REVERSE_H
#define REVERSE_H

template <class T>
void Reverse(T* src_begin, T* src_end) {
    while (src_begin < src_end) {
        --src_end;
        if (src_begin >= src_end) { break; }

        T temp = *src_begin;
        *src_begin = *src_end;
        *src_end = temp;
        ++src_begin;
    }
}

template <class T>
void Rotate(T* begin, T* mid, T* end) {
    if (begin == mid || mid == end) { return; }

    Reverse(begin, mid);
    Reverse(mid, end);
    Reverse(begin, end);
}
// Example for Rotate:
// [1, 2, 3, | 4, 5]  mid=4  
// -> Reverse(first part):     [3, 2, 1, | 4, 5]
// -> Reverse(second part):    [3, 2, 1, | 5, 4]
// -> Reverse(all):            [4, 5, 1, 2, 3]

#endif
