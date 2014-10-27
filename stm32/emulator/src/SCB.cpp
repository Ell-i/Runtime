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

#include <SCB.h>

SystemControlBlock SystemControlBlock::SCB;

#if defined(__STM32F407__) || defined(__STM32F334__)
void SystemControlBlock::SCB_CPUID_VALUES( SystemControlBlock *const scb, CALLBACK(SCB_CPUID_CALLBACK) ) {
	SCB_CPUID_CALLBACK( scb->CPUID.registerPeriph().c_str()
		, scb->CPUID.registerName().c_str()
		, scb->CPUID.registerValue()
		, scb->CPUID.registerOpStr().c_str()
		);
}

void SystemControlBlock::SCB_ICSR_VALUES( SystemControlBlock *const scb, CALLBACK(SCB_ICSR_CALLBACK) ) {
	SCB_ICSR_CALLBACK( scb->ICSR.registerPeriph().c_str()
		, scb->ICSR.registerName().c_str()
		, scb->ICSR.registerValue()
		, scb->ICSR.registerOpStr().c_str()
		);
}

void SystemControlBlock::SCB_VTOR_VALUES( SystemControlBlock *const scb, CALLBACK(SCB_VTOR_CALLBACK) ) {
	SCB_VTOR_CALLBACK( scb->VTOR.registerPeriph().c_str()
		, scb->VTOR.registerName().c_str()
		, scb->VTOR.registerValue()
		, scb->VTOR.registerOpStr().c_str()
		);
}
#endif
