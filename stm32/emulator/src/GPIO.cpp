/*
 * Copyright (c) 2014 ELL-i co-operative
 *
 * This file is part of ELL-i software.
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
 * @author Pekka Nikander <pekka.nikander@ell-i.org>  2013-2014
 *
 * @brief Emulated STM32F0/STM32F4 GPIO registers
 */

#include <GPIO.h>

GeneralPurposeInputOutput GeneralPurposeInputOutput::GPIOA;
GeneralPurposeInputOutput GeneralPurposeInputOutput::GPIOB;
GeneralPurposeInputOutput GeneralPurposeInputOutput::GPIOC;
GeneralPurposeInputOutput GeneralPurposeInputOutput::GPIOD;
GeneralPurposeInputOutput GeneralPurposeInputOutput::GPIOE;
GeneralPurposeInputOutput GeneralPurposeInputOutput::GPIOF;
GeneralPurposeInputOutput GeneralPurposeInputOutput::GPIOG;
GeneralPurposeInputOutput GeneralPurposeInputOutput::GPIOH;
GeneralPurposeInputOutput GeneralPurposeInputOutput::GPIOI;

/*
Implement here a generic fiunction, which initiate callbacks according to the port e.g. GPIOA, GPIOB, GPIOC etc
*/

void GeneralPurposeInputOutput::GPIO_MODER_VALUES( GeneralPurposeInputOutput *const gpioPort
	, CALLBACK(GPIO_MODER_CALLBACK) ) {
	GPIO_MODER_CALLBACK( gpioPort->MODER.registerPeriph().c_str()
		, gpioPort->MODER.registerName().c_str()
		, gpioPort->MODER.registerValue()
		);
}

void GeneralPurposeInputOutput::GPIO_PUPDR_VALUES( GeneralPurposeInputOutput *const gpioPort
	, CALLBACK(GPIO_PUPDR_CALLBACK) ) {
	GPIO_PUPDR_CALLBACK( gpioPort->PUPDR.registerPeriph().c_str()
		, gpioPort->PUPDR.registerName().c_str()
		, gpioPort->PUPDR.registerValue()
		);
}

void GeneralPurposeInputOutput::GPIO_ODR_VALUES( GeneralPurposeInputOutput *const gpioPort
	, CALLBACK(GPIO_ODR_CALLBACK) ) {
	GPIO_ODR_CALLBACK( gpioPort->ODR.registerPeriph().c_str()
		, gpioPort->ODR.registerName().c_str()
		, gpioPort->ODR.registerValue()
		);
}

void GeneralPurposeInputOutput::GPIO_IDR_VALUES( GeneralPurposeInputOutput *const gpioPort
	, CALLBACK(GPIO_IDR_CALLBACK) ) {
	GPIO_IDR_CALLBACK( gpioPort->IDR.registerPeriph().c_str()
		, gpioPort->IDR.registerName().c_str()
		, gpioPort->IDR.registerValue()
		);
}
#if defined(__STM32F407__) || defined(__STM32F334__)
void GeneralPurposeInputOutput::GPIO_BSRRL_VALUES( GeneralPurposeInputOutput *const gpioPort
	, CALLBACK(GPIO_BSRRL_CALLBACK) ) {
	GPIO_BSRRL_CALLBACK( gpioPort->BSRRL.registerPeriph().c_str()
		, gpioPort->BSRRL.registerName().c_str()
		, gpioPort->BSRRL.registerValue()
		);
}

void GeneralPurposeInputOutput::GPIO_AFR_VALUES( GeneralPurposeInputOutput *const gpioPort
	, CALLBACK(GPIO_AFR_CALLBACK) ) {
	GPIO_AFR_CALLBACK( gpioPort->AFR[0].registerPeriph().c_str()
		, gpioPort->AFR[0].registerName().c_str()
		, gpioPort->AFR[0].registerValue()
		);
	GPIO_AFR_CALLBACK( gpioPort->AFR[1].registerPeriph().c_str()
		, gpioPort->AFR[1].registerName().c_str()
		, gpioPort->AFR[1].registerValue()
		);
}

void GeneralPurposeInputOutput::GPIO_BSRRH_VALUES( GeneralPurposeInputOutput *const gpioPort
	, CALLBACK(GPIO_BSRRH_CALLBACK) ) {
	GPIO_BSRRH_CALLBACK( gpioPort->BSRRH.registerPeriph().c_str()
		, gpioPort->BSRRH.registerName().c_str()
		, gpioPort->BSRRH.registerValue()
		);
}
#elif defined(__STM32F051__)
void GeneralPurposeInputOutput::GPIO_BSRR_VALUES( GeneralPurposeInputOutput *const gpioPort
	, CALLBACK(GPIO_BSRR_CALLBACK) ) {
	GPIO_BSRR_CALLBACK( gpioPort->BSRR.registerPeriph().c_str()
		, gpioPort->BSRR.registerName().c_str()
		, gpioPort->BSRR.registerValue()
		);
}

void GeneralPurposeInputOutput::GPIO_AFR_VALUES( GeneralPurposeInputOutput *const gpioPort
	, CALLBACK(GPIO_AFR_CALLBACK) ) {
	GPIO_AFR_CALLBACK( gpioPort->AFR[0].registerPeriph().c_str()
		, gpioPort->AFR[0].registerName().c_str()
		, gpioPort->AFR[0].registerValue()
		);
	GPIO_AFR_CALLBACK( gpioPort->AFR[1].registerPeriph().c_str()
		, gpioPort->AFR[1].registerName().c_str()
		, gpioPort->AFR[1].registerValue()
		);
}

void GeneralPurposeInputOutput::GPIO_BRR_VALUES( GeneralPurposeInputOutput *const gpioPort
	, CALLBACK(GPIO_BRR_CALLBACK) ) {
	GPIO_BRR_CALLBACK( gpioPort->BRR.registerPeriph().c_str()
		, gpioPort->BRR.registerName().c_str()
		, gpioPort->BRR.registerValue()
		);
}
#else
# error "Unknown MCU die.  Please define."
#endif

/*
void GeneralPurposeInputOutput::GPIO_MODER_VALUES( const std::string &port, CALLBACK(GPIO_MODER_CALLBACK) ) {
#if defined(__STM32F407__) || defined(__STM32F334__)
	if (port == "A") {
		GPIO_MODER_CALLBACK(GPIOA.MODER.registerPeriph().c_str(), GPIOA.MODER.registerName().c_str(), GPIOA.MODER.registerValue());
	}
	else if (port == "B") {
		GPIO_MODER_CALLBACK(GPIOB.MODER.registerPeriph().c_str(), GPIOB.MODER.registerName().c_str(), GPIOB.MODER.registerValue());
	}
	else if (port == "C") {
		GPIO_MODER_CALLBACK(GPIOC.MODER.registerPeriph().c_str(), GPIOC.MODER.registerName().c_str(), GPIOC.MODER.registerValue());
	}
	else {

	}
#elif defined(__STM32F051__)
	if (port == "A") {
		GPIO_MODER_CALLBACK(GPIOA.MODER.registerPeriph().c_str(), GPIOA.MODER.registerName().c_str(), GPIOA.MODER.registerValue());
	}
	else if (port == "B") {
		GPIO_MODER_CALLBACK(GPIOB.MODER.registerPeriph().c_str(), GPIOB.MODER.registerName().c_str(), GPIOB.MODER.registerValue());
	}
	else if (port == "C") {
		GPIO_MODER_CALLBACK(GPIOC.MODER.registerPeriph().c_str(), GPIOC.MODER.registerName().c_str(), GPIOC.MODER.registerValue());
	}
	else if (port == "D") {
		GPIO_MODER_CALLBACK(GPIOD.MODER.registerPeriph().c_str(), GPIOD.MODER.registerName().c_str(), GPIOD.MODER.registerValue());
	}
	else if (port == "F") {
		GPIO_MODER_CALLBACK(GPIOF.MODER.registerPeriph().c_str(), GPIOF.MODER.registerName().c_str(), GPIOF.MODER.registerValue());
	}
	else {

	}
#else
# error "Unknown MCU die.  Please define."
#endif
}
*/
