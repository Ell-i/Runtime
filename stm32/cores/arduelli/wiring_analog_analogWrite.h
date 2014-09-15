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
 * @author Pekka Nikander <pekka.nikander@ell-i.org>  2014
 */

#include "arduelli_gpio.h"
#include "arduelli_timer.h"

// XXX FIXME: The pin numbering in this file is wrong, see issue #18

static inline
void analogWrite(pin_t pin, uint32_t value) {

    const uint32_t pin_shift = (GPIOPIN[pin].gpio_pin * 2);

    /* Place the GPIO in the Alternate Function mode.  Idempotent. */
    GPIOPIN[pin].gpio_port->MODER &= ~(GPIO_MODER_MODER0_0 << pin_shift);
    GPIOPIN[pin].gpio_port->MODER |=  (GPIO_MODER_MODER0_1 << pin_shift);

    /* Channel counter value */
    *(PWMPIN[pin].pwm_ccr) = value;
}

static inline
void noAnalogWrite(pin_t pin) {

    const uint32_t pin_shift = (GPIOPIN[pin].gpio_pin * 2);

    /* Place the GPIO back to the default mode. */
    GPIOPIN[pin].gpio_port->MODER &= ~(GPIO_MODER_MODER0 << pin_shift);
}


