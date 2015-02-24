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

#include <FLASH.h>

Flash Flash::FLASH;

void Flash::FLASH_ACR_VALUES( Flash *const flash, CALLBACK(FLASH_ACR_CALLBACK) ) {
	FLASH_ACR_CALLBACK( flash->ACR.registerPeriph().c_str()
		, flash->ACR.registerName().c_str()
		, flash->ACR.registerValue()
		, flash->ACR.registerOpStr().c_str()
		);
}

void Flash::FLASH_KEYR_VALUES( Flash *const flash, CALLBACK(FLASH_KEYR_CALLBACK) ) {
	FLASH_KEYR_CALLBACK( flash->KEYR.registerPeriph().c_str()
		, flash->KEYR.registerName().c_str()
		, flash->KEYR.registerValue()
		, flash->KEYR.registerOpStr().c_str()
		);
}

void Flash::FLASH_OPTKEYR_VALUES( Flash *const flash, CALLBACK(FLASH_OPTKEYR_CALLBACK) ) {
	FLASH_OPTKEYR_CALLBACK( flash->OPTKEYR.registerPeriph().c_str()
		, flash->OPTKEYR.registerName().c_str()
		, flash->OPTKEYR.registerValue()
		, flash->OPTKEYR.registerOpStr().c_str()
		);
}

void Flash::FLASH_SR_VALUES( Flash *const flash, CALLBACK(FLASH_SR_CALLBACK) ) {
	FLASH_SR_CALLBACK( flash->SR.registerPeriph().c_str()
		, flash->SR.registerName().c_str()
		, flash->SR.registerValue()
		, flash->SR.registerOpStr().c_str()
		);
}

void Flash::FLASH_CR_VALUES( Flash *const flash, CALLBACK(FLASH_CR_CALLBACK) ) {
	FLASH_CR_CALLBACK( flash->CR.registerPeriph().c_str()
		, flash->CR.registerName().c_str()
		, flash->CR.registerValue()
		, flash->CR.registerOpStr().c_str()
		);
}
