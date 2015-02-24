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
 * @author Pekka Nikander <pekka.nikander@ell-i.org>  2014
 */

#ifndef _RCC_H_
#define _RCC_H_

#include <Register.h>
#include <Register_RCC_CR.h>
#if defined(__STM32F407__)
# include <Register_RCC_PLLCFGR.h>
#endif
#include <Register_RCC_CFGR.h>
#include <Register_RCC_CIR.h>
#include <Register_RCC_APB1RSTR.h>
#if defined(__STM32F407__)
# include <Register_RCC_AHB1ENR.h>
#elif defined(__STM32F051__) || defined(__STM32F334__)
# include <Register_RCC_AHBENR.h>
#else
# error "Unknown MCU die.  Please define."
#endif
#include <Register_RCC_APB2ENR.h>
#include <Register_RCC_APB1ENR.h>
#include <Register_RCC_APB2RSTR.h>
#include <Register_RCC_BDCR.h>
#include <Register_RCC_CSR.h>
#include <Register_RCC_AHBRSTR.h>
#include <Register_RCC_CFGR2.h>
#include <Register_RCC_CFGR3.h>
#include <Register_RCC_CR2.h>

class ResetClockControl {
public:

/*
#if defined(__STM32F407__) || defined(__STM32F334__)
    //DEFINE_REGISTER(32, RCC, CR,       0x0202FF83); // HSERDY set for SetSysClock
#elif defined(__STM32F051__) || defined(__STM32F334__)
    //DEFINE_REGISTER(32, RCC, CR,       0x0200FF83); // PLL set for SetSysClock
#else
# error "Unknown MCU die.  Please define."
#endif
#if defined(__STM32F407__)
    //DEFINE_REGISTER(32, RCC, PLLCFGR,  0x24003010); // XXX Check, set to reset value
#endif
#if defined(__STM32F407__)
    //Register_RCC_CFGR CFGR;
#elif defined(__STM32F051__) || defined(__STM32F334__)
    //DEFINE_REGISTER(32, RCC, CFGR,     0x00000008); // PLL set for SetSysClock
#else
# error "Unknown MCU die.  Please define."
#endif
    //DEFINE_REGISTER(32, RCC, CIR,      0x00000000);
    //DEFINE_REGISTER(32, RCC, APB1RSTR, 0x00000000);
#if defined(__STM32F407__)
    //DEFINE_REGISTER(32, RCC, AHB1ENR,  0x00000014 /* XXX CHECK ME /);
#elif defined(__STM32F051__) || defined(__STM32F334__)
    //DEFINE_REGISTER(32, RCC, AHBENR,   0x00000014);
#else
# error "Unknown MCU die.  Please define."
#endif
    //DEFINE_REGISTER(32, RCC, APB2ENR,  0x00000000);
    //DEFINE_REGISTER(32, RCC, APB1ENR,  0x00000000);
    //DEFINE_REGISTER(32, RCC, APB2RSTR, 0x00000000);
    //DEFINE_REGISTER(32, RCC, BDCR,     0x00000018);
    //DEFINE_REGISTER(32, RCC, CSR,      0x0C000000);
    //DEFINE_REGISTER(32, RCC, AHBRSTR,  0x00000000);
    //DEFINE_REGISTER(32, RCC, CFGR2,    0x00000000);
    //DEFINE_REGISTER(32, RCC, CFGR3,    0x00000000);
    //DEFINE_REGISTER(32, RCC, CR2,      0x0000FF80);
//########################################
*/
    Register_RCC_CR CR;
#if defined(__STM32F407__)
    Register_RCC_PLLCFGR PLLCFGR;
#endif
    Register_RCC_CFGR CFGR;
    Register_RCC_CIR CIR;
    Register_RCC_APB1RSTR APB1RSTR;
#if defined(__STM32F407__)
    Register_RCC_AHB1ENR AHB1ENR;
#elif defined(__STM32F051__) || defined(__STM32F334__)
    Register_RCC_AHBENR AHBENR;
#else
# error "Unknown MCU die.  Please define."
#endif
    Register_RCC_APB2ENR APB2ENR;
    Register_RCC_APB1ENR APB1ENR;
    Register_RCC_APB2RSTR APB2RSTR;
    Register_RCC_BDCR BDCR;
    Register_RCC_CSR CSR;
    Register_RCC_AHBRSTR AHBRSTR;
    Register_RCC_CFGR2 CFGR2;
    Register_RCC_CFGR3 CFGR3;
    Register_RCC_CR2 CR2;
protected:
    ResetClockControl()
#if defined(__STM32F407__) || defined(__STM32F334__)
    : CR(0x0202FF83) // HSERDY set for SetSysClock
#elif defined(__STM32F051__) || defined(__STM32F334__)
    : CR(0x0200FF83) // PLL set for SetSysClock
#else
# error "Unknown MCU die.  Please define."
#endif
#if defined(__STM32F407__)
    , PLLCFGR(0x24003010) // XXX Check, set to reset value
#endif
#if defined(__STM32F407__)
    , CFGR(0)
#elif defined(__STM32F051__) || defined(__STM32F334__)
    , CFGR(0x00000008) // PLL set for SetSysClock
#else
# error "Unknown MCU die.  Please define."
#endif
#if defined(__STM32F407__)
    , AHB1ENR(0x00000014 /* XXX CHECK ME */)
#elif defined(__STM32F051__) || defined(__STM32F334__)
    , AHBENR(0x00000014)
#else
# error "Unknown MCU die.  Please define."
#endif
    , BDCR(0x0C000000)
    , CSR(0x0C000000)
    , CR2(0x0000FF80)
    {}
public:
    static ResetClockControl RCC;

    void RCC_CR_VALUES( ResetClockControl *const rcc, CALLBACK(RCC_CR_CALLBACK) );
#if defined(__STM32F407__)
    void RCC_PLLCFGR_VALUES( ResetClockControl *const rcc, CALLBACK(RCC_PLLCFGR_CALLBACK) );
#endif
    void RCC_CFGR_VALUES( ResetClockControl *const rcc, CALLBACK(RCC_CFGR_CALLBACK) );
    void RCC_CIR_VALUES( ResetClockControl *const rcc, CALLBACK(RCC_CIR_CALLBACK) );
    void RCC_APB1RSTR_VALUES( ResetClockControl *const rcc, CALLBACK(RCC_APB1RSTR_CALLBACK) );
#if defined(__STM32F407__)
    void RCC_AHB1ENR_VALUES( ResetClockControl *const rcc, CALLBACK(RCC_AHB1ENR_CALLBACK) );
#elif defined(__STM32F051__) || defined(__STM32F334__)
    void RCC_AHBENR_VALUES( ResetClockControl *const rcc, CALLBACK(RCC_AHBENR_CALLBACK) );
#else
# error "Unknown MCU die.  Please define."
#endif
    void RCC_APB2ENR_VALUES( ResetClockControl *const rcc, CALLBACK(RCC_APB2ENR_CALLBACK) );
    void RCC_APB1ENR_VALUES( ResetClockControl *const rcc, CALLBACK(RCC_APB1ENR_CALLBACK) );
    void RCC_APB2RSTR_VALUES( ResetClockControl *const rcc, CALLBACK(RCC_APB2RSTR_CALLBACK) );
    void RCC_BDCR_VALUES( ResetClockControl *const rcc, CALLBACK(RCC_BDCR_CALLBACK) );
    void RCC_CSR_VALUES( ResetClockControl *const rcc, CALLBACK(RCC_CSR_CALLBACK) );
    void RCC_AHBRSTR_VALUES( ResetClockControl *const rcc, CALLBACK(RCC_AHBRSTR_CALLBACK) );
    void RCC_CFGR2_VALUES( ResetClockControl *const rcc, CALLBACK(RCC_CFGR2_CALLBACK) );
    void RCC_CFGR3_VALUES( ResetClockControl *const rcc, CALLBACK(RCC_CFGR3_CALLBACK) );
    void RCC_CR2_VALUES( ResetClockControl *const rcc, CALLBACK(RCC_CR2_CALLBACK) );
};

ResetClockControl *const RCC = &ResetClockControl::RCC;

#endif //_RCC_H_
