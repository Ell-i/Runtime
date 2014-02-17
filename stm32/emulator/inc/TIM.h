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

#ifndef _TIM_H_
#define _TIM_H_

#include <Register.h>

class Timer {
public:
    DEFINE_REGISTER(16, TIM, CR1,   0x00000000);
    DEFINE_REGISTER(16, TIM, CR2,   0x00000000);
    DEFINE_REGISTER(16, TIM, SMCR,  0x00000000);
    DEFINE_REGISTER(16, TIM, DIER,  0x00000000);
    DEFINE_REGISTER(16, TIM, CCMR1, 0x00000000);
    DEFINE_REGISTER(16, TIM, CCMR2, 0x00000000);
    DEFINE_REGISTER(16, TIM, CCER,  0x00000000);
    DEFINE_REGISTER(16, TIM, BDTR,  0x00000000);
    DEFINE_REGISTER(16, TIM, PSC,   0x00000000);
    DEFINE_REGISTER(32, TIM, ARR,   0x00000000);
    DEFINE_REGISTER(32, TIM, CCR1,  0x00000000);
    DEFINE_REGISTER(32, TIM, CCR2,  0x00000000);
    DEFINE_REGISTER(32, TIM, CCR3,  0x00000000);
    DEFINE_REGISTER(32, TIM, CCR4,  0x00000000);
protected:
    Timer() {}
public:
    static Timer TIM1;
    static Timer TIM2;
    static Timer TIM3;
    static Timer TIM14;
    static Timer TIM15;
    static Timer TIM16;
    static Timer TIM17;
};

Timer *const TIM1  = &Timer::TIM1;
Timer *const TIM2  = &Timer::TIM2;
Timer *const TIM3  = &Timer::TIM3;
Timer *const TIM14 = &Timer::TIM14;
Timer *const TIM15 = &Timer::TIM15;
Timer *const TIM16 = &Timer::TIM16;
Timer *const TIM17 = &Timer::TIM17;

#endif //_TIM_H_
