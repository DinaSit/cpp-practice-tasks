#ifndef MERGE_H
#define MERGE_H

template <class T1, class T2, class OUT>
OUT* Merge(const T1* first_begin, const T1* first_end, const T2* second_begin, const T2* second_end, OUT* out) {
    while (first_begin != first_end && second_begin != second_end) {
        if (*second_begin < *first_begin) {
            *out = *second_begin;
            ++second_begin;
        } else {
            *out = *first_begin;
            ++first_begin;
        }
        ++out;
    }

    while (first_begin != first_end) {
        *out++ = *first_begin++;
    }
    while (second_begin != second_end) {
        *out++ = *second_begin++;
    }
    return out;
}

#endif
