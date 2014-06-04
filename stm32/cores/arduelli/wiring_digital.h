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

#ifndef _WIRING_DIGITAL_H_
# define _WIRING_DIGITAL_H_

#include "arduelli_gpio.h"
#include "ellduino_gpio.h" // XXX replace with variant_gpio.h

/**************************************
 * Arduino APIs
 */

#include "wiring_digital_pinMode.h"

extern "C" {
 int digitalRead(pin_t pin) {
    return GPIOPIN[pin].gpio_port->IDR & GPIOPIN[pin].gpio_mask? 1: 0;
}
}

extern "C" {
   void  digitalWrite(pin_t pin, uint32_t val) {
    if (val)
        GPIOPIN[pin].gpio_port->BSRR = GPIOPIN[pin].gpio_mask;
    else
        GPIOPIN[pin].gpio_port->BRR  = GPIOPIN[pin].gpio_mask;
}
}

#endif//_WIRING_DIGITAL_H_
