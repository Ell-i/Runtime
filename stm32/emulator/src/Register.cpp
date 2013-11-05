/*
 * Copyright (c) 2013 ELL-i co-operative
 */

#include <Register.h>

uint32_t Register::operator |= (uint32_t arg) {
    // XXX move setbase to a better location
    std::cout << std::setbase(16) << periph_ << ":" << name_ << ":" << value_ << "|=" << arg << '\n';
    return value_ |= arg;
}

uint32_t Register::operator &= (uint32_t arg) {
    std::cout << periph_ << ":" << name_ << ":" << value_ << "&=" << arg << '\n';
    return value_ &= arg;
}

uint32_t Register::operator &  (uint32_t arg) {
    std::cout << periph_ << ":" << name_ << ":" << value_ << "&" << arg << '\n';
    return value_ & arg;
}
