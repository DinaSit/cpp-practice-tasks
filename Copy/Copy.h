#ifndef COPY_H
#define COPY_H

template <class T1, class T2>
T2* Copy(const T1* src_begin, const T1* src_end, T2* dest) {
    while (src_begin != src_end) {
        *dest = *src_begin;
        ++src_begin;
        ++dest;
    }
    return dest;
}

template <class T1, class T2>
T2* CopyBackward(const T1* src_begin, const T1* src_end, T2* dest) {
    while (src_end != src_begin) {
        --src_end;
        --dest;
        *dest = *src_end;
    }
    return dest;
}

#endif
