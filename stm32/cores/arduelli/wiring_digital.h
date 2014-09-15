/*
 * Copyright (c) 2013-2014 ELL-i co-operative
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
 */

#ifndef  _WIRING_DIGITAL_H_
# define _WIRING_DIGITAL_H_

# include "arduelli_api_definitions.h"
# include "arduelli_pin_functions.h"
# include "arduelli_gpio.h"

# if defined(ELLI_STM32F051_ELLDUINO)
#  include "ellduino_gpio.h"  // XXX replace with variant_gpio.h
# elif defined(ELLI_STM32F407_DISCOVERY)
#  include "stm32f4discovery_gpio.h" // XXX To be placed into the variant.h!
# elif defined(ELLI_STM32F334_NUCLEO)
#  include "stm32f334nucleo_gpio.h" // XXX To be placed into the variant.h!
# else
#  error "Unknown board.  Please define."
# endif

/**************************************
 * Arduino APIs
 */

# include "wiring_digital_pinMode.h"

static inline
int digitalRead(pin_t pin) {
    return GPIOPIN[pin].gpio_port->IDR & GPIOPIN[pin].gpio_mask? 1: 0;
}

static inline
void  digitalWrite(pin_t pin, uint32_t val) {
// TODO: Check if the following ifdefs are really needed, or could we
// use BSRRL also in Cortex-M0 without too much overhead
# if defined(STM32F40_41xxx) || defined(STM32F334x8)
    if (val) // Set
        GPIOPIN[pin].gpio_port->BSRRL = GPIOPIN[pin].gpio_mask;
    else    // Reset
        GPIOPIN[pin].gpio_port->BSRRH = GPIOPIN[pin].gpio_mask;
# elif defined(STM32F0XX)
    if (val) // Set
        GPIOPIN[pin].gpio_port->BSRR  = GPIOPIN[pin].gpio_mask;
    else    // Reset
        GPIOPIN[pin].gpio_port->BRR   = GPIOPIN[pin].gpio_mask;
# else
#  error "Unknown board.  Please define."
# endif
}

#endif//_WIRING_DIGITAL_H_
