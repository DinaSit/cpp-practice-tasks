#ifndef UNIQUE_H
#define UNIQUE_H

template <class T>
T* Unique(T* first, T* last) {
    if (!first || !last) { return last; }
    if (first == last) { return last; }

    T* write = first + 1;
    for (T* read = first + 1; read != last; ++read) {
        if (*(write - 1) < *read) {
            *write = *read;
            ++write;
        }
    }
    return write;
}

#endif
