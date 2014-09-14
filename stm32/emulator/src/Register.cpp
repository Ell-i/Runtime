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

#include <Register.h>

void Register::printout(const std::string opStr, uint32_t result) const {
    std::cout << std::setbase(16)
              << periph_ << ':'
              << name_   << ':'
              << "value=" << value_
              << "->" << opStr << result
              << std::endl;
}

uint32_t Register::operator = (uint32_t arg) volatile {
    ((Register *)this)->printout("=", arg);
    return *(const_cast<Register*>(this)) = arg;
}

uint32_t Register::operator  = (uint32_t arg) {
    printout("=", arg);
    return value_  = arg;
}

uint32_t Register::operator |= (uint32_t arg) {
    printout("|=", value_ | arg);
    return value_ |= arg;
}

uint32_t Register::operator &= (uint32_t arg) {
    printout("&=", value_ & arg);
    return value_ &= arg;
}

uint32_t Register::operator &  (uint32_t arg) const {
    printout("&", value_ & arg);
    return value_ &  arg;
}

uint16_t Register::operator &  (uint16_t arg) const {
    printout("&(16b)", value_ & arg);
    return value_ &  arg;
}
