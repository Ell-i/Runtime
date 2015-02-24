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

/**
 * @author Asif Sardar <engr.asif.sardar@gmail.com>  2014
 */

#ifndef _REGISTER_PWR_CR_H_
#define _REGISTER_PWR_CR_H_

#include <Register.h>

class Register_PWR_CR : public Register {
public:
    Register_PWR_CR(uint32_t val) : Register("PWR", "CR", 32, val) {}

    uint32_t operator = (uint32_t arg);
};

#endif //_REGISTER_PWR_CR_H_
