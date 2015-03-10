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

#ifndef _SCB_H_
#define _SCB_H_

#include <Register.h>
#if defined(__STM32F407__) || defined(__STM32F334__)
# include <Register_SCB_CPUID.h>
# include <Register_SCB_ICSR.h>
# include <Register_SCB_VTOR.h>
#endif

class SystemControlBlock {
public:
#if defined(__STM32F407__) || defined(__STM32F334__)
    /* XXX Set to reset value */
    //DEFINE_REGISTER(32, SCB, CPUID,    0x410FC241);
    //DEFINE_REGISTER(32, SCB, ICSR,     0x00000000);
    //DEFINE_REGISTER(32, SCB, VTOR,     0x00000000);
    Register_SCB_CPUID CPUID;
    Register_SCB_ICSR ICSR;
    Register_SCB_VTOR VTOR;
#endif
protected:
    SystemControlBlock()
#if defined(__STM32F407__) || defined(__STM32F334__)
    	: CPUID(0x410FC241)
    	, ICSR(0x00000000)
    	, VTOR(0x00000000)
#endif
    	{}
public:
    static SystemControlBlock SCB;
#if defined(__STM32F407__) || defined(__STM32F334__)
    void SCB_CPUID_VALUES( SystemControlBlock *const scb, CALLBACK(SCB_CPUID_CALLBACK) );
    void SCB_ICSR_VALUES( SystemControlBlock *const scb, CALLBACK(SCB_ICSR_CALLBACK) );
    void SCB_VTOR_VALUES( SystemControlBlock *const scb, CALLBACK(SCB_VTOR_CALLBACK) );
#endif
};

SystemControlBlock *const SCB = &SystemControlBlock::SCB;

#endif //_SCB_H_
