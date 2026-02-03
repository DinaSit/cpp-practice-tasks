#include "CString.hpp"

static bool InSet(char c, const char* set) {
    while (*set) {
        if (*set++ == c) { return true; }
    }
    return false;
}

// Returns the length of the C string str
size_t Strlen(const char* str) {
    if (!str) return 0;
    const char* last = str;
    while (*last) ++last;
    return static_cast<size_t>(last - str);
}

// Compares the C string first to the C string second
int Strcmp(const char* first, const char* second) {
    if (!first || !second) {
        if (first == second) return 0;
        return first ? 1 : -1;
    }
    while (*first && *second && *first == *second) { ++first; ++second; }
    return static_cast<unsigned char>(*first) - static_cast<unsigned char>(*second);
}

// Compares up to count characters of the C string first to those of the C string second
int Strncmp(const char* first, const char* second, size_t count) {
    if (count == 0) { return 0; }
    if (!first || !second) {
        if (first == second) return 0;
        return first ? 1 : -1;
    }

    while (count && *first && *second && (*first == *second)) {
        ++first;
        ++second;
        --count;
    }

    if (count == 0) return 0;
    return static_cast<unsigned char>(*first) - static_cast<unsigned char>(*second);
}

// Returns a pointer to the first occurrence of symbol in the C string str
const char* Strchr(const char* str, char symbol) {
    while (*str) {
        if (*str == symbol) { return str; }
        str++;
    }
    return (symbol == '\0') ? str : nullptr;
}

// Returns a pointer to the last occurrence of symbol in the C string str
const char* Strrchr(const char* str, char symbol) {
    const char* last = nullptr;
    while (*str) {
        if (*str == symbol) { last = str; }
        str++;
    }
    return (symbol == '\0') ? str : last;
}

// Returns the length of the initial portion of dest which consists only of characters that are part of src
size_t Strspn(const char* dest, const char* src) {
    const char* p = dest;
    while (*p && InSet(*p, src)) { ++p; }
    return static_cast<size_t>(p - dest);
}

// Scans dest for the first occurrence of any of the characters that are part of src, returning the number of characters of dest read before this first occurrence
size_t Strcspn(const char* dest, const char* src) {
    const char* p = dest;
    while (*p && !InSet(*p, src)) { ++p; }
    return static_cast<size_t>(p - dest);
}

// Returns a pointer to the first occurrence in dest of any of the characters that are part of breakset, or a null pointer if there are no matches
const char* Strpbrk(const char* dest, const char* breakset) {
    while (*dest) {
        if (InSet(*dest, breakset)) { return dest; }
        dest++;
    }
    return nullptr;
}

// Returns a pointer to the first occurrence of pattern in str, or a null pointer if pattern is not part of str
const char* Strstr(const char* str, const char* pattern) {
    if (*pattern == '\0') { return str; }
    for (const char* h = str; *h; ++h) {
        if (*h != *pattern) { continue; }
        const char* p = h;
        const char* q = pattern;
        while (*p && *q && (*p == *q)) { ++p; ++q; }
        if (*q == '\0') { return h; }
    }
    return nullptr;
}

// Copies the C string pointed by src into the array pointed by dest, including the terminating null character (and stopping at that point)
char* Strcpy(char* dest, const char* src) {
    char* d = dest;
    while ((*d++ = *src++) != '\0') { }
    return dest;
}

// Copies the first count characters of src to dest. If the end of the src C string (which is signaled by a null-character) 
// is found before count characters have been copied, dest is padded with zeros until a total of count characters have been written to it
char* Strncpy(char* dest, const char* src, size_t count) {
    char* d = dest;
    while (count && (*src)) { *d++ = *src++; --count; }
    while (count) { *d++ = '\0'; --count; } // pad with zeros
    return dest;
}

// Appends a copy of the src string to the dest string
char* Strcat(char* dest, const char* src) {
    char* d = dest;
    while (*d) { ++d; } // go to '\0'
    while ((*d++ = *src++) != '\0') { }
    return dest;
}

// Appends the first count characters of src to dest, plus a terminating null-character
char* Strncat(char* dest, const char* src, size_t count) {
    char* d = dest;
    while (*d) { ++d; }
    while (count && *src) { *d++ = *src++; --count; }
    *d = '\0';
    return dest;
}
