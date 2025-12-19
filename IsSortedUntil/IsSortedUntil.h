// Returns pointer to first element that breaks non-decreasing order in [first, last).
// If sorted, returns last. Uses only operator<. Complexity: O(n) time, O(1) memory.

#ifndef ISSORTEDUNTIL_H
#define ISSORTEDUNTIL_H

template <class T>
const T* IsSortedUntil(const T* first, const T* last) {
    if (first == last) { return last; }
    const T* next = first;
    ++next;
    while (next != last) {
        if (*next < *first) { return next; }
        ++first; ++next;
    }
    return last;
}

#endif
