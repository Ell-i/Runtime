/*
 * This file is part of ELL-i software.
 * ELL-i software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * ELL-i software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with ELL-i software.  If not, see <http://www.gnu.org/licenses/>.
 *
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
