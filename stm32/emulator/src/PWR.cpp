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

#include <PWR.h>

PowerController PowerController::PWR;

#if defined(__STM32F407__)
void PowerController::PWR_CR_VALUES( PowerController *const pwr, CALLBACK(PWR_CR_CALLBACK) ) {
	PWR_CR_CALLBACK( pwr->CR.registerPeriph().c_str()
		, pwr->CR.registerName().c_str()
		, pwr->CR.registerValue()
		, pwr->CR.registerOpStr().c_str()
		);
}
#endif