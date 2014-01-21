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

#ifndef _RCC_H_
#define _RCC_H_

#include <Register.h>

class ResetClockControl {
public:
    DEFINE_REGISTER(RCC, CR,       0x0200FF83); // PLL set for SetSysClock
    DEFINE_REGISTER(RCC, CFGR,     0x00000008); // PLL set for SetSysClock
    DEFINE_REGISTER(RCC, CIR,      0x00000000);
    DEFINE_REGISTER(RCC, APB1RSTR, 0x00000000);
    DEFINE_REGISTER(RCC, AHBENR,   0x00000014);
    DEFINE_REGISTER(RCC, APB2ENR,  0x00000000);
    DEFINE_REGISTER(RCC, APB1ENR,  0x00000000);
    DEFINE_REGISTER(RCC, APB2RSTR, 0x00000000);
    DEFINE_REGISTER(RCC, BDCR,     0x00000018);
    DEFINE_REGISTER(RCC, CSR,      0x0C000000);
    DEFINE_REGISTER(RCC, AHBRSTR,  0x00000000);
    DEFINE_REGISTER(RCC, CFGR2,    0x00000000);
    DEFINE_REGISTER(RCC, CFGR3,    0x00000000);
    DEFINE_REGISTER(RCC, CR2,      0x0000FF80);
protected:
    ResetClockControl() {}
public:
    static ResetClockControl RCC;
};

ResetClockControl *const RCC = &ResetClockControl::RCC;

#endif //_RCC_H_
