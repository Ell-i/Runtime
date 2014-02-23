/*
 * Copyright (c) 2014 ELL-i co-operative.
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

/**
 * @author: Pekka Nikander <pekka.nikander@ell-i.org>  2014
 */

#ifndef _TINY_MAP_H_
# define _TINY_MAP_H_

# include <stdlib.h>

/**
 * A templated class for tiny (linear) associative arrays.
 *
 * This template creates associative arrays that use little or no
 * extra memory in addition to the actual keys and values.  The keys
 * and values are stored in separate, potentially statically allocated
 * tables, making sure that alignment doesn't unnecessarily increase
 * the table sizes.  The constructor is a constexpr, allowing fully
 * static allocation by the compiler.  The only operation supported is
 * the array operator[], returning a reference to the value at the
 * key.
 *
 * If statically allocate,d uses sizeof(KEY)*(size+1) +
 * sizeof(VALUE)*(size+2) bytes of RAM.
 *
 * The zero key is implicitly used as the default key, and space is
 * always allocated for the <0,value> key; this is the reason for the
 * +1 in the sizes above.  If a key doesn't have a value associated
 * with it yet, a new key-value pair is taken into use.  To
 * accommodate overflows, another extra VALUE is also allocated, so
 * that if the table gets full, a reference to that extra VALUE is
 * always returned (hence +2 instead of +1).
 *
 * There is no way to delete keys.
 *
 * At the moment, this class is used as a helper class in a number of
 * Arduino API emulation classes that associate pins with various
 * items.  For example, to statically allocate a <pin->uint32_t>
 * array that can hold 7+1 items, use
 *
 *     TinyMap<pint_t, uint32_t, 7>
 *
 * An even better solution would be to use a compile-time allocated
 * key array, but the current Arduino APIs don't allow for that.
 */

template <typename KEY, typename VALUE, size_t size>
class TinyMap {
public:
    constexpr TinyMap() {}

    VALUE& operator[] (KEY key) {
        for (size_t i = 0; i < size_; i++) {
            if (keys_[i] == key)
                return values_[i];
        }
        /* First key is always zero. */
        for (size_t i = 1; i < size_; i++) {
            if (keys_[i] == 0) {
                keys_[i] = key;
                return values_[i];
            }
        }
        /* Overflow.  As embedded, simply subsume the error. */
        return values_[size_];
    }
private:
    static const size_t size_ = size+1; /* Accomodate zero key */
    KEY   keys_  [size_];
    VALUE values_[size_+1]; /* Accomodate overflow */
};

# ifdef UNIT_TEST

#include <stdint.h>
#include <assert.h>
#include <iostream>
#include <iomanip>

TinyMap<uint8_t, uint32_t, 3> a;

int main(void) {

    for (int i = 3; i >= 0; i--) {
        a[i] = i;
    }
    for (int i = 0; i < 4; i++) {
        std::cout << i << ":" << a[i] << '\n';
        assert(a[i] == i);
    }
}
# endif

#endif//_TINY_MAP_H_
