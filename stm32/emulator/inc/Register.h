/*
 * Copyright (c) 2013 ELL-i co-operative
 */

#ifndef _REGISTER_H_
#define _REGISTER_H_

#include <iostream>
#include <iomanip>
#include <string>
#include <stdint.h>

class Register {
protected:
    const std::string periph_;
    const std::string name_;
    uint32_t    value_;
    Register(std::string periph, std::string name, uint32_t value)
        : periph_(periph)
        , name_(name)
        , value_(value)
        {};
public:
    uint32_t operator =  (uint32_t);
    uint32_t operator |= (uint32_t);
    uint32_t operator &= (uint32_t);
    uint32_t operator &  (uint32_t);
};

#define DEFINE_REGISTER(periph, name, value)                  \
class Class ## name : public Register {                       \
public:                                                       \
    Class ## name() : Register(# periph, # name, value) {};   \
    uint32_t operator=(uint32_t arg) {                        \
        std::cout << periph_ << ":" << name_ << ":" << "=" << arg << '\n'; \
        return value_ = arg;                                  \
    }                                                         \
} name

#endif /* _REGISTER_H_ */
