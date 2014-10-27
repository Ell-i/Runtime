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

#include <RCC.h>

ResetClockControl ResetClockControl::RCC;

void ResetClockControl::RCC_CR_VALUES( ResetClockControl *const rcc, CALLBACK(RCC_CR_CALLBACK) ) {
	RCC_CR_CALLBACK( rcc->CR.registerPeriph().c_str()
		, rcc->CR.registerName().c_str()
		, rcc->CR.registerValue()
		, rcc->CR.registerOpStr().c_str()
		);
}

#if defined(__STM32F407__)
void ResetClockControl::RCC_PLLCFGR_VALUES( ResetClockControl *const rcc, CALLBACK(RCC_PLLCFGR_CALLBACK) ) {
	RCC_PLLCFGR_CALLBACK( rcc->PLLCFGR.registerPeriph().c_str()
		, rcc->PLLCFGR.registerName().c_str()
		, rcc->PLLCFGR.registerValue()
		, rcc->PLLCFGR.registerOpStr().c_str()
		);
}
#endif

void ResetClockControl::RCC_CFGR_VALUES( ResetClockControl *const rcc, CALLBACK(RCC_CFGR_CALLBACK) ) {
	RCC_CFGR_CALLBACK( rcc->CFGR.registerPeriph().c_str()
		, rcc->CFGR.registerName().c_str()
		, rcc->CFGR.registerValue()
		, rcc->CFGR.registerOpStr().c_str()
		);
}

void ResetClockControl::RCC_CIR_VALUES( ResetClockControl *const rcc, CALLBACK(RCC_CIR_CALLBACK) ) {
	RCC_CIR_CALLBACK( rcc->CIR.registerPeriph().c_str()
		, rcc->CIR.registerName().c_str()
		, rcc->CIR.registerValue()
		, rcc->CIR.registerOpStr().c_str()
		);
}

void ResetClockControl::RCC_APB1RSTR_VALUES( ResetClockControl *const rcc, CALLBACK(RCC_APB1RSTR_CALLBACK) ) {
	RCC_APB1RSTR_CALLBACK( rcc->APB1RSTR.registerPeriph().c_str()
		, rcc->APB1RSTR.registerName().c_str()
		, rcc->APB1RSTR.registerValue()
		, rcc->APB1RSTR.registerOpStr().c_str()
		);
}

#if defined(__STM32F407__)
void ResetClockControl::RCC_AHB1ENR_VALUES( ResetClockControl *const rcc, CALLBACK(RCC_AHB1ENR_CALLBACK) ) {
	RCC_AHB1ENR_CALLBACK( rcc->AHB1ENR.registerPeriph().c_str()
		, rcc->AHB1ENR.registerName().c_str()
		, rcc->AHB1ENR.registerValue()
		, rcc->AHB1ENR.registerOpStr().c_str()
		);
}
#elif defined(__STM32F051__) || defined(__STM32F334__)
void ResetClockControl::RCC_AHBENR_VALUES( ResetClockControl *const rcc, CALLBACK(RCC_AHBENR_CALLBACK) ) {
	RCC_AHBENR_CALLBACK( rcc->AHBENR.registerPeriph().c_str()
		, rcc->AHBENR.registerName().c_str()
		, rcc->AHBENR.registerValue()
		, rcc->AHBENR.registerOpStr().c_str()
		);
}
#else
# error "Unknown MCU die.  Please define."
#endif

void ResetClockControl::RCC_APB2ENR_VALUES( ResetClockControl *const rcc, CALLBACK(RCC_APB2ENR_CALLBACK) ) {
	RCC_APB2ENR_CALLBACK( rcc->APB2ENR.registerPeriph().c_str()
		, rcc->APB2ENR.registerName().c_str()
		, rcc->APB2ENR.registerValue()
		, rcc->APB2ENR.registerOpStr().c_str()
		);
}

void ResetClockControl::RCC_APB1ENR_VALUES( ResetClockControl *const rcc, CALLBACK(RCC_APB1ENR_CALLBACK) ) {
	RCC_APB1ENR_CALLBACK( rcc->APB1ENR.registerPeriph().c_str()
		, rcc->APB1ENR.registerName().c_str()
		, rcc->APB1ENR.registerValue()
		, rcc->APB1ENR.registerOpStr().c_str()
		);
}

void ResetClockControl::RCC_APB2RSTR_VALUES( ResetClockControl *const rcc, CALLBACK(RCC_APB2RSTR_CALLBACK) ) {
	RCC_APB2RSTR_CALLBACK( rcc->APB2RSTR.registerPeriph().c_str()
		, rcc->APB2RSTR.registerName().c_str()
		, rcc->APB2RSTR.registerValue()
		, rcc->APB2RSTR.registerOpStr().c_str()
		);
}

void ResetClockControl::RCC_BDCR_VALUES( ResetClockControl *const rcc, CALLBACK(RCC_BDCR_CALLBACK) ) {
	RCC_BDCR_CALLBACK( rcc->BDCR.registerPeriph().c_str()
		, rcc->BDCR.registerName().c_str()
		, rcc->BDCR.registerValue()
		, rcc->BDCR.registerOpStr().c_str()
		);
}

void ResetClockControl::RCC_CSR_VALUES( ResetClockControl *const rcc, CALLBACK(RCC_CSR_CALLBACK) ) {
	RCC_CSR_CALLBACK( rcc->CSR.registerPeriph().c_str()
		, rcc->CSR.registerName().c_str()
		, rcc->CSR.registerValue()
		, rcc->CSR.registerOpStr().c_str()
		);
}

void ResetClockControl::RCC_AHBRSTR_VALUES( ResetClockControl *const rcc, CALLBACK(RCC_AHBRSTR_CALLBACK) ) {
	RCC_AHBRSTR_CALLBACK( rcc->AHBRSTR.registerPeriph().c_str()
		, rcc->AHBRSTR.registerName().c_str()
		, rcc->AHBRSTR.registerValue()
		, rcc->AHBRSTR.registerOpStr().c_str()
		);
}

void ResetClockControl::RCC_CFGR2_VALUES( ResetClockControl *const rcc, CALLBACK(RCC_CFGR2_CALLBACK) ) {
	RCC_CFGR2_CALLBACK( rcc->CFGR2.registerPeriph().c_str()
		, rcc->CFGR2.registerName().c_str()
		, rcc->CFGR2.registerValue()
		, rcc->CFGR2.registerOpStr().c_str()
		);
}

void ResetClockControl::RCC_CFGR3_VALUES( ResetClockControl *const rcc, CALLBACK(RCC_CFGR3_CALLBACK) ) {
	RCC_CFGR3_CALLBACK( rcc->CFGR3.registerPeriph().c_str()
		, rcc->CFGR3.registerName().c_str()
		, rcc->CFGR3.registerValue()
		, rcc->CFGR3.registerOpStr().c_str()
		);
}

void ResetClockControl::RCC_CR2_VALUES( ResetClockControl *const rcc, CALLBACK(RCC_CR2_CALLBACK) ) {
	RCC_CR2_CALLBACK( rcc->CR2.registerPeriph().c_str()
		, rcc->CR2.registerName().c_str()
		, rcc->CR2.registerValue()
		, rcc->CR2.registerOpStr().c_str()
		);
}
