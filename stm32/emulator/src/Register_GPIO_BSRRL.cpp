/*
 * Copyright (c) 2014 ELL-i co-operative.
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

#include <Register_GPIO_BSRRL.h>
#include <Register_GPIO_IDR.h>
#include <Register_GPIO_ODR.h>

uint32_t  Register_GPIO_BSRRL::operator = (uint32_t arg) {
    printout("=", 0);

    uint32_t value = odr_.value_;
    value &= ~(arg >> 16);
    value |=  (arg & 0xffff);
    odr_.assign(value);

    return 0; // See STM32F4xx Refence Manual RM0090 Doc ID 018909 Rev 7 page 281.
    		  // See STM32F334xx Refence Manual RM0364 Doc ID 025177 Rev 1 page 156.
}

