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

/**
 * Arduino pinMode
 *
 * Configuration records each GPIO pin as input or output, with the desired pullups.
 */

#if defined(ARDUELLI_FEATURE_STATIC_PINMODE)

/*
 * Static, data driven version of the Arduino pinMode() API.
 *
 * This version attempts to cut the amount of generated code through
 * assembling couple a static data structures and then calling
 * SystemInitMaskAndValue() with the static data structures as the
 * argument.  The rationale is that if the compiler is smart enough,
 * it is able to compute the static data structure contents at compile
 * time and assemble the data structures at compile time.
 *
 * Unfortunately, GCC 4.7.1 is not quite smart enough.  It manages to
 * use constant propagation to compute all of the initialisation
 * values at compile time, but it still fails to generate the actual
 * structs at compile time.  Instead, it generates explicit code that
 * initialises the data structures at run time.  Hence, with gcc (and
 * therefore by default) we don't use this version.
 *
 * XXX Test with LLVM to see if it manages to do it right.
 */
#  define DEFINE_pinMode(pin, mode)                                     \
    static const                                                        \
    SystemInitRecordMaskAndValue GPIO_PIN_MODE_Records[] = {            \
        {                                                               \
            .init_r_address = (volatile preg32_t *const)(               \
                (volatile char *const)GPIOPIN[pin].gpio_port            \
                + ((char *const)&GPIOA->MODER - (char *const)GPIOA)),   \
            .init_r_mask    = ~(GPIO_MODER_MODER ## pin),               \
            .init_r_value   = GPIO_pin_mode_moder_values[mode],         \
        }, {                                                            \
            .init_r_address = (volatile preg32_t *const)(               \
                (volatile char *const)GPIOPIN[pin].gpio_port            \
                + ((char *const)&GPIOA->PUPDR - (char *const)GPIOA)),   \
            .init_r_mask    = ~(GPIO_PUPDR_PUPDR ## pin),               \
            .init_r_value   = GPIO_pin_mode_pupdr_values[mode],         \
        }                                                               \
    }

#  define INIT_pinMode(pin, mode)                                       \
    StaticInitMaskAndValue(COUNT_OF(GPIO_PIN_MODE_Records),             \
                     GPIO_PIN_MODE_Records)

/**
 * XXX TBD
 */

#  define pinMode(pin, mode) {                                          \
        DEFINE_pinMode(pin, mode);                                      \
        INIT_pinMode(pin, mode);                                        \
    } while (0)

#else

/**
 * Arduino pinMode API.
 * @param pin   Pin whose mode to change.
 * @param mode  The new mode for pin.
 *
 * Dynamic, sequential, inlined version of the Arduiono pinMode() API.
 *
 * With GCC, generates fair but not optimal code.
 */
/*
#ifdef __cplusplus
extern "C"
#endif
*/
extern "C" {
	void pinMode(pin_t pin, const enum pin_mode mode) {

    const uint32_t pin_shift = (GPIOPIN[pin].gpio_pin * 2);

    switch (mode) {
    case INPUT:
        /* High impedance: push up/down register bits zero */
        GPIOPIN[pin].gpio_port->PUPDR &= ~(GPIO_PUPDR_PUPDR0 << pin_shift);
        break;
    case INPUT_PULLUP: {
        /* Pull-up: push up/down register bits 01 */
        register uint32_t pupdr = GPIOPIN[pin].gpio_port->PUPDR;
        pupdr |=  (GPIO_PUPDR_PUPDR0_0 << pin_shift);
        pupdr &= ~(GPIO_PUPDR_PUPDR0_1 << pin_shift);
        GPIOPIN[pin].gpio_port->PUPDR = pupdr;
        break;
    }
    case INPUT_PULLDOWN: {
        /* Pull-down: push up/down register bits 10 */
        register uint32_t pupdr = GPIOPIN[pin].gpio_port->PUPDR;
        pupdr &= ~(GPIO_PUPDR_PUPDR0_0 << pin_shift);
        pupdr |=  (GPIO_PUPDR_PUPDR0_1 << pin_shift);
        GPIOPIN[pin].gpio_port->PUPDR = pupdr;
        break;
    }
    case OUTPUT:
        break;
    }

    switch (mode) {
    case OUTPUT: {
        /* Output mode:  mode register bits 01 */
        register uint32_t moder = GPIOPIN[pin].gpio_port->MODER;
        moder |=  (GPIO_MODER_MODER0_0 << pin_shift);
        moder &= ~(GPIO_MODER_MODER0_1 << pin_shift);
        GPIOPIN[pin].gpio_port->MODER = moder;
        break;
    }
    case INPUT:
    case INPUT_PULLUP:
    case INPUT_PULLDOWN:
        /* Input mode: mode register bits zero */
        GPIOPIN[pin].gpio_port->MODER &= ~(GPIO_MODER_MODER0 << pin_shift);
    }
}
}
#endif
