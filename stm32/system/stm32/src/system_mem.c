// #include <stddef.h> // for size_t
#include <system_init.h>

void *memcpy(void *dst, const void *src, size_t size) {
    char *d = dst;
    const char *s = src;
    while (size--) {
        *d++ = *s++;
    }
    return dst;
}

void *memset(void *dst, int c, size_t size) {
    char *d = dst;
    while (size--) {
       *d++ = c;
    }
    return dst;
}