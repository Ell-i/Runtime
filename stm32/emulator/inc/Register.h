/*
 * Copyright (c) 2013-2014 ELL-i co-operative.
 *
 * This is part of ELL-i software.
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

#ifndef _REGISTER_H_
#define _REGISTER_H_

#include <iostream>
#include <iomanip>
#include <string>
#include <stdint.h>

class Register {
protected:
    uint32_t          value_;
    const std::string periph_;
    const std::string name_;
    uint8_t           size_;

    Register(std::string periph, std::string name,
             uint8_t size, uint32_t value)
        : value_(value)
        , periph_(periph)
        , name_(name)
        , size_(size)
        {};

public:
    uint32_t  operator |= (uint32_t);
    uint32_t  operator &= (uint32_t);
    uint32_t  operator =  (uint32_t);
    uint32_t  operator =  (uint32_t) volatile;
    uint32_t  operator &  (uint32_t) const;
    operator uint32_t () volatile { return value_; }

protected:
    void printout(const std::string opStr, uint32_t result) const;
};

#define DEFINE_REGISTER(size, periph, name, value)            \
class Class ## name : public Register {                       \
public:                                                       \
    Class ## name() : Register(# periph, # name, size, value) {}; \
    uint32_t operator=(uint32_t arg) {                        \
        printout("=", arg);                                   \
        return value_ = arg;                                  \
    }                                                         \
} name

#endif /* _REGISTER_H_ */
