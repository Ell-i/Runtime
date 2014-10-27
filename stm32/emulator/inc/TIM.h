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
#include <Register_TIM_CR1.h>
#include <Register_TIM_CR2.h>
#include <Register_TIM_SMCR.h>
#include <Register_TIM_DIER.h>
#include <Register_TIM_CCMR1.h>
#include <Register_TIM_CCMR2.h>
#include <Register_TIM_CCER.h>
#include <Register_TIM_BDTR.h>
#include <Register_TIM_PSC.h>
#include <Register_TIM_ARR.h>
#include <Register_TIM_CCR1.h>
#include <Register_TIM_CCR2.h>
#include <Register_TIM_CCR3.h>
#include <Register_TIM_CCR4.h>

class Timer {
public:
    //DEFINE_REGISTER(16, TIM, CR1,   0x00000000);
    //DEFINE_REGISTER(16, TIM, CR2,   0x00000000);
    //DEFINE_REGISTER(16, TIM, SMCR,  0x00000000);
    //DEFINE_REGISTER(16, TIM, DIER,  0x00000000);
    //DEFINE_REGISTER(16, TIM, CCMR1, 0x00000000);
    //DEFINE_REGISTER(16, TIM, CCMR2, 0x00000000);
    //DEFINE_REGISTER(16, TIM, CCER,  0x00000000);
    //DEFINE_REGISTER(16, TIM, BDTR,  0x00000000);
    //DEFINE_REGISTER(16, TIM, PSC,   0x00000000);
    //DEFINE_REGISTER(32, TIM, ARR,   0x00000000);
    //DEFINE_REGISTER(32, TIM, CCR1,  0x00000000);
    //DEFINE_REGISTER(32, TIM, CCR2,  0x00000000);
    //DEFINE_REGISTER(32, TIM, CCR3,  0x00000000);
    //DEFINE_REGISTER(32, TIM, CCR4,  0x00000000);
    Register_TIM_CR1 CR1;
    Register_TIM_CR2 CR2;
    Register_TIM_SMCR SMCR;
    Register_TIM_DIER DIER;
    Register_TIM_CCMR1 CCMR1;
    Register_TIM_CCMR2 CCMR2;
    Register_TIM_CCER CCER;
    Register_TIM_BDTR BDTR;
    Register_TIM_PSC PSC;
    Register_TIM_ARR ARR;
    Register_TIM_CCR1 CCR1;
    Register_TIM_CCR2 CCR2;
    Register_TIM_CCR3 CCR3;
    Register_TIM_CCR4 CCR4;

protected:
    Timer() {}
public:
    static Timer TIM1;
    static Timer TIM2;
    static Timer TIM3;
    static Timer TIM4;
    static Timer TIM5;
    static Timer TIM6;
    static Timer TIM7;
    static Timer TIM8;
    static Timer TIM9;
    static Timer TIM10;
    static Timer TIM11;
    static Timer TIM12;
    static Timer TIM13;
    static Timer TIM14;
    static Timer TIM15;
    static Timer TIM16;
    static Timer TIM17;

    void TIM_CR1_VALUES( Timer *const tim, CALLBACK(TIM_CR1_CALLBACK) );
    void TIM_CR2_VALUES( Timer *const tim, CALLBACK(TIM_CR2_CALLBACK) );
    void TIM_SMCR_VALUES( Timer *const tim, CALLBACK(TIM_SMCR_CALLBACK) );
    void TIM_DIER_VALUES( Timer *const tim, CALLBACK(TIM_DIER_CALLBACK) );
    void TIM_CCMR1_VALUES( Timer *const tim, CALLBACK(TIM_CCMR1_CALLBACK) );
    void TIM_CCMR2_VALUES( Timer *const tim, CALLBACK(TIM_CCMR2_CALLBACK) );
    void TIM_CCER_VALUES( Timer *const tim, CALLBACK(TIM_CCER_CALLBACK) );
    void TIM_BDTR_VALUES( Timer *const tim, CALLBACK(TIM_BDTR_CALLBACK) );
    void TIM_PSC_VALUES( Timer *const tim, CALLBACK(TIM_PSC_CALLBACK) );
    void TIM_ARR_VALUES( Timer *const tim, CALLBACK(TIM_ARR_CALLBACK) );
    void TIM_CCR1_VALUES( Timer *const tim, CALLBACK(TIM_CCR1_CALLBACK) );
    void TIM_CCR2_VALUES( Timer *const tim, CALLBACK(TIM_CCR2_CALLBACK) );
    void TIM_CCR3_VALUES( Timer *const tim, CALLBACK(TIM_CCR3_CALLBACK) );
    void TIM_CCR4_VALUES( Timer *const tim, CALLBACK(TIM_CCR4_CALLBACK) );
};

Timer *const TIM1  = &Timer::TIM1;
Timer *const TIM2  = &Timer::TIM2;
Timer *const TIM3  = &Timer::TIM3;
Timer *const TIM4  = &Timer::TIM4;
Timer *const TIM5  = &Timer::TIM5;
Timer *const TIM6  = &Timer::TIM6;
Timer *const TIM7  = &Timer::TIM7;
Timer *const TIM8  = &Timer::TIM8;
Timer *const TIM9  = &Timer::TIM9;
Timer *const TIM10 = &Timer::TIM10;
Timer *const TIM11 = &Timer::TIM11;
Timer *const TIM12 = &Timer::TIM12;
Timer *const TIM13 = &Timer::TIM13;
Timer *const TIM14 = &Timer::TIM14;
Timer *const TIM15 = &Timer::TIM15;
Timer *const TIM16 = &Timer::TIM16;
Timer *const TIM17 = &Timer::TIM17;

Timer *const TIM[] = { TIM1
    , TIM2
    , TIM3
    , TIM4
    , TIM5
    , TIM6
    , TIM7
    , TIM8
    , TIM9
    , TIM10
    , TIM11
    , TIM12
    , TIM13
    , TIM14
    , TIM15
    , TIM16
    , TIM17
};


#endif //_TIM_H_
