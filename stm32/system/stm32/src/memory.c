/*
 * Copyright (c) 2013-2014 ELL-i co-operative.
 *
 * This file is part of ELL-i software.
 *
 * ELL-i software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ELL-i software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ELL-i software.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <string.h>

inline
void *memcpy(void *dst, const void *src, size_t size) {
    char *d = (char *)dst;
    const char *s = (const char *)src;
    while (size--) {
        *d++ = *s++;
    }
    return dst;
}

inline
void *memset(void *dst, int c, size_t size) {
    char *d = (char *)dst;
    while (size--) {
       *d++ = c;
    }
    return dst;
}

inline
int memcmp(const void *str1, const void *str2, size_t size) {
    const char *s1 = (const char *)str1;
    const char *s2 = (const char *)str2;

    while (size--) {
        int d = *s1++ - *s2++;
        if (d != 0)
            return d;
    }
    return 0;
}
