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

#include <TIM.h>

Timer Timer::TIM1;
Timer Timer::TIM2;
Timer Timer::TIM3;
Timer Timer::TIM4;
Timer Timer::TIM5;
Timer Timer::TIM6;
Timer Timer::TIM7;
Timer Timer::TIM8;
Timer Timer::TIM9;
Timer Timer::TIM10;
Timer Timer::TIM11;
Timer Timer::TIM12;
Timer Timer::TIM13;
Timer Timer::TIM14;
Timer Timer::TIM15;
Timer Timer::TIM16;
Timer Timer::TIM17;

void Timer::TIM_CR1_VALUES( Timer *const tim, CALLBACK(TIM_CR1_CALLBACK) ) {
	TIM_CR1_CALLBACK( tim->CR1.registerPeriph().c_str()
		, tim->CR1.registerName().c_str()
		, tim->CR1.registerValue()
		, tim->CR1.registerOpStr().c_str()
		);
}

void Timer::TIM_CR2_VALUES( Timer *const tim, CALLBACK(TIM_CR2_CALLBACK) ) {
	TIM_CR2_CALLBACK( tim->CR2.registerPeriph().c_str()
		, tim->CR2.registerName().c_str()
		, tim->CR2.registerValue()
		, tim->CR2.registerOpStr().c_str()
		);
}

void Timer::TIM_SMCR_VALUES( Timer *const tim, CALLBACK(TIM_SMCR_CALLBACK) ) {
	TIM_SMCR_CALLBACK( tim->SMCR.registerPeriph().c_str()
		, tim->SMCR.registerName().c_str()
		, tim->SMCR.registerValue()
		, tim->SMCR.registerOpStr().c_str()
		);
}

void Timer::TIM_DIER_VALUES( Timer *const tim, CALLBACK(TIM_DIER_CALLBACK) ) {
	TIM_DIER_CALLBACK( tim->DIER.registerPeriph().c_str()
		, tim->DIER.registerName().c_str()
		, tim->DIER.registerValue()
		, tim->DIER.registerOpStr().c_str()
		);
}

void Timer::TIM_CCMR1_VALUES( Timer *const tim, CALLBACK(TIM_CCMR1_CALLBACK) ) {
	TIM_CCMR1_CALLBACK( tim->CCMR1.registerPeriph().c_str()
		, tim->CCMR1.registerName().c_str()
		, tim->CCMR1.registerValue()
		, tim->CCMR1.registerOpStr().c_str()
		);
}

void Timer::TIM_CCMR2_VALUES( Timer *const tim, CALLBACK(TIM_CCMR2_CALLBACK) ) {
	TIM_CCMR2_CALLBACK( tim->CCMR2.registerPeriph().c_str()
		, tim->CCMR2.registerName().c_str()
		, tim->CCMR2.registerValue()
		, tim->CCMR2.registerOpStr().c_str()
		);
}

void Timer::TIM_CCER_VALUES( Timer *const tim, CALLBACK(TIM_CCER_CALLBACK) ) {
	TIM_CCER_CALLBACK( tim->CCER.registerPeriph().c_str()
		, tim->CCER.registerName().c_str()
		, tim->CCER.registerValue()
		, tim->CCER.registerOpStr().c_str()
		);
}

void Timer::TIM_BDTR_VALUES( Timer *const tim, CALLBACK(TIM_BDTR_CALLBACK) ) {
	TIM_BDTR_CALLBACK( tim->BDTR.registerPeriph().c_str()
		, tim->BDTR.registerName().c_str()
		, tim->BDTR.registerValue()
		, tim->BDTR.registerOpStr().c_str()
		);
}

void Timer::TIM_PSC_VALUES( Timer *const tim, CALLBACK(TIM_PSC_CALLBACK) ) {
	TIM_PSC_CALLBACK( tim->PSC.registerPeriph().c_str()
		, tim->PSC.registerName().c_str()
		, tim->PSC.registerValue()
		, tim->PSC.registerOpStr().c_str()
		);
}

void Timer::TIM_ARR_VALUES( Timer *const tim, CALLBACK(TIM_ARR_CALLBACK) ) {
	TIM_ARR_CALLBACK( tim->ARR.registerPeriph().c_str()
		, tim->ARR.registerName().c_str()
		, tim->ARR.registerValue()
		, tim->ARR.registerOpStr().c_str()
		);
}

void Timer::TIM_CCR1_VALUES( Timer *const tim, CALLBACK(TIM_CCR1_CALLBACK) ) {
	TIM_CCR1_CALLBACK( tim->CCR1.registerPeriph().c_str()
		, tim->CCR1.registerName().c_str()
		, tim->CCR1.registerValue()
		, tim->CCR1.registerOpStr().c_str()
		);
}

void Timer::TIM_CCR2_VALUES( Timer *const tim, CALLBACK(TIM_CCR2_CALLBACK) ) {
	TIM_CCR2_CALLBACK( tim->CCR2.registerPeriph().c_str()
		, tim->CCR2.registerName().c_str()
		, tim->CCR2.registerValue()
		, tim->CCR2.registerOpStr().c_str()
		);
}

void Timer::TIM_CCR3_VALUES( Timer *const tim, CALLBACK(TIM_CCR3_CALLBACK) ) {
	TIM_CCR3_CALLBACK( tim->CCR3.registerPeriph().c_str()
		, tim->CCR3.registerName().c_str()
		, tim->CCR3.registerValue()
		, tim->CCR3.registerOpStr().c_str()
		);
}

void Timer::TIM_CCR4_VALUES( Timer *const tim, CALLBACK(TIM_CCR4_CALLBACK) ) {
	TIM_CCR4_CALLBACK( tim->CCR4.registerPeriph().c_str()
		, tim->CCR4.registerName().c_str()
		, tim->CCR4.registerValue()
		, tim->CCR4.registerOpStr().c_str()
		);
}
