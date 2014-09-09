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
#include <Register_RCC_CFGR.h>

class ResetClockControl {
public:

#if defined(__STM32F407__) || defined(__STM32F334__)
    DEFINE_REGISTER(32, RCC, CR,       0x0202FF83); // HSERDY set for SetSysClock
#elif defined(__STM32F051__) || defined(__STM32F334__)
    DEFINE_REGISTER(32, RCC, CR,       0x0200FF83); // PLL set for SetSysClock
#else
# error "Unknown MCU die.  Please define."
#endif
#if defined(__STM32F407__)
    DEFINE_REGISTER(32, RCC, PLLCFGR,  0x24003010); // XXX Check, set to reset value
#endif
#if defined(__STM32F407__)
    RegisterRCC_CFGR CFGR;
#elif defined(__STM32F051__) || defined(__STM32F334__)
    DEFINE_REGISTER(32, RCC, CFGR,     0x00000008); // PLL set for SetSysClock
#else
# error "Unknown MCU die.  Please define."
#endif
    DEFINE_REGISTER(32, RCC, CIR,      0x00000000);
    DEFINE_REGISTER(32, RCC, APB1RSTR, 0x00000000);
#if defined(__STM32F407__)
    DEFINE_REGISTER(32, RCC, AHB1ENR,  0x00000014 /* XXX CHECK ME */);
#elif defined(__STM32F051__) || defined(__STM32F334__)
    DEFINE_REGISTER(32, RCC, AHBENR,   0x00000014);
#else
# error "Unknown MCU die.  Please define."
#endif
    DEFINE_REGISTER(32, RCC, APB2ENR,  0x00000000);
    DEFINE_REGISTER(32, RCC, APB1ENR,  0x00000000);
    DEFINE_REGISTER(32, RCC, APB2RSTR, 0x00000000);
    DEFINE_REGISTER(32, RCC, BDCR,     0x00000018);
    DEFINE_REGISTER(32, RCC, CSR,      0x0C000000);
    DEFINE_REGISTER(32, RCC, AHBRSTR,  0x00000000);
    DEFINE_REGISTER(32, RCC, CFGR2,    0x00000000);
    DEFINE_REGISTER(32, RCC, CFGR3,    0x00000000);
    DEFINE_REGISTER(32, RCC, CR2,      0x0000FF80);
protected:
    ResetClockControl() {}
public:
    static ResetClockControl RCC;
};

ResetClockControl *const RCC = &ResetClockControl::RCC;

#endif //_RCC_H_
