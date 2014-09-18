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

#ifndef _REGISTER_GPIO_ODR_H_
#define _REGISTER_GPIO_ODR_H_

#include <Register.h>

class Register_GPIO_IDR;
class Register_GPIO_BSRR;
class Register_GPIO_BRR;

class Register_GPIO_ODR : public Register {
    Register_GPIO_IDR & idr_;
public:
    Register_GPIO_ODR(Register_GPIO_IDR &idr)
        : Register("GPIO", "ODR", 32, 0)
        , idr_(idr)
        {}
    uint32_t  operator = (uint32_t arg);
private:
    friend class Register_GPIO_BSRR;
    friend class Register_GPIO_BRR;
    void assign(uint32_t arg);
};

#endif//_REGISTER_GPIO_ODR_H_
