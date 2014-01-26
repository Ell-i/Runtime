/*
 * Copyright (c) 2014 ELL-i co-operative
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
 * @author Pekka Nikander <pekka.nikander@ell-i.org>  2014
 *
 * @brief The Arduino Stream class
 */

#include <stddef.h>
#include "Arduino_String.h"

class Stream {
    void setTimeout(unsigned long timeout) const;

    bool find(char *target) const;
    bool find(char *target, size_t length) const;
    bool findUntil(char *target, char *terminator) const;
    bool findUntil(char *target, size_t targetLen, char *terminator, size_t termLen) const;

    long  parseInt() const;
    float parseFloat() const;

    size_t readBytes(char *buffer, size_t length) const;
    size_t readBytesUntil(int terminator, char *buffer, size_t length) const;

    String readString() const;
    String readStringUntil(int terminator) const;

    /* Print functions */
    size_t println(void) const;
    size_t print(unsigned long value, enum base base=DEC, bool u = 1) const;
    size_t print(double value, int decimals=2) const;
    size_t print(unsigned char value, enum base base=DEC) const;
    size_t print(unsigned int  value, enum base base=DEC) const;
    size_t print(int           value, enum base base=DEC) const;
    size_t print(long          value, enum base base=DEC) const;

    size_t print(const char c)     const;
    size_t print(const char s[])   const;
    size_t print(const String &s)  const;

    size_t println(unsigned long value, enum base base=DEC, unsigned u = 1);
    size_t println(double value) const;

    size_t println(unsigned char value, enum base base=DEC) const;
    size_t println(unsigned int  value, enum base base=DEC) const;

    size_t println(int           value, enum base base=DEC) const;
    size_t println(long          value, enum base base=DEC) const;

    size_t println(const char c)       const;
    size_t println(const char s[])     const;
    size_t println(const String &s)    const;
};
