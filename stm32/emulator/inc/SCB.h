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

#ifndef _SCB_H_
#define _SCB_H_

#include <Register.h>

class SystemControlBlock {
public:
#if defined(__STM32F407__)
    /* XXX Set to reset value */
    DEFINE_REGISTER(32, SCB, CPUID,    0x410FC241);
    DEFINE_REGISTER(32, SCB, ICSR,     0x00000000);
    DEFINE_REGISTER(32, SCB, VTOR,     0x00000000);
#endif
protected:
    SystemControlBlock() {}
public:
    static SystemControlBlock SCB;
};

SystemControlBlock *const SCB = &SystemControlBlock::SCB;

#endif //_SCB_H_
