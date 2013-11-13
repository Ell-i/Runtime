/*
 * Copyright (c) 2013 ELL-i co-operative.
 */

#include "arduelli_gpio.h"

/**
 * Arduino pinMode
 *
 * Configuration records each GPIO pin as input or output, with the desired pullups.
 */

/*
 * With the current Arduino API, it is not possible to reliably
 * determine at compile time which GPIO ports are used and which are
 * not.  Hence, the only viable option at the moment is to explicitly
 * refer to the GPIO system init records, by creating explicit
 * references to them.  With the -fdata-sections gcc options, the
 * __GPIOx names below will be deleted during link time, leaving only
 * the referenced and explicitly kept GPIOx_INIT records into the
 * linked code (due to the corresponding linker KEEP directive.)
 *
 * Another option would be to create an explicit references from the
 * code, but that is even worse since it would generate runtime code.
 */

const void * __GPIOA = &GPIOA_INIT;
const void * __GPIOB = &GPIOB_INIT;
const void * __GPIOC = &GPIOC_INIT;
const void * __GPIOD = &GPIOD_INIT;
const void * __GPIOF = &GPIOF_INIT;

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
            .init_r_address = (volatile uint32_t *const)(               \
                (volatile char *const)GPIO[pin].gpio_port               \
                + ((char *const)&GPIOA->MODER - (char *const)GPIOA)),   \
            .init_r_mask    = ~(GPIO_MODER_MODER ## pin),               \
            .init_r_value   = GPIO_pin_mode_moder_values[mode],         \
        }, {                                                            \
            .init_r_address = (volatile uint32_t *const)(               \
                (volatile char *const)GPIO[pin].gpio_port               \
                + ((char *const)&GPIOA->PUPDR - (char *const)GPIOA)),   \
            .init_r_mask   = ~(GPIO_PUPDR_PUPDR ## pin),                \
            .init_r_value  = GPIO_pin_mode_pupdr_values[mode],          \
        }                                                               \
    }

#  define INIT_pinMode(pin, mode)                                       \
    StaticInitMaskAndValue(COUNT_OF(GPIO_PIN_MODE_Records),             \
                     GPIO_PIN_MODE_Records)

#  define pinMode(pin, mode) {                                          \
        DEFINE_pinMode(pin, mode);                                      \
        INIT_pinMode(pin, mode);                                        \
    } while (0)

#else

/*
 * Dynamic, sequential, inlined version of the Arduiono pinMode() API.
 *
 * With GCC, generates fair but not optimal code.
 */
static inline
void pinMode(pin_t pin, const enum pin_mode mode) {

    const uint32_t pin_shift = (GPIO[pin].gpio_pin * 2);

    switch (mode) {
    case INPUT:
        /* High impedance: push up/down register bits zero */
        GPIO[pin].gpio_port->PUPDR &= ~(GPIO_PUPDR_PUPDR0   << pin_shift);
        break;
    case INPUT_PULLUP:
        /* Pull-up: push up/down register bits 01 */
        GPIO[pin].gpio_port->PUPDR |= ~(GPIO_PUPDR_PUPDR0_0 << pin_shift);
        GPIO[pin].gpio_port->PUPDR &= ~(GPIO_PUPDR_PUPDR0_1 << pin_shift);
        break;
    case INPUT_PULLDOWN:
        /* Pull-down: push up/down register bits 10 */
        GPIO[pin].gpio_port->PUPDR &= ~(GPIO_PUPDR_PUPDR0_0 << pin_shift);
        GPIO[pin].gpio_port->PUPDR |= ~(GPIO_PUPDR_PUPDR0_1 << pin_shift);
        break;
    case OUTPUT:
        break;
    }

    switch (mode) {
    case OUTPUT:
        /* Output mode:  mode register bits 01 */
        GPIO[pin].gpio_port->MODER |=  (GPIO_MODER_MODER0_0 << pin_shift);
        GPIO[pin].gpio_port->MODER &= ~(GPIO_MODER_MODER0_1 << pin_shift);
        break;
    case INPUT:
    case INPUT_PULLUP:
    case INPUT_PULLDOWN:
        /* Input mode: mode register bits zero */
        GPIO[pin].gpio_port->MODER &= ~(GPIO_MODER_MODER0   << pin_shift);
    }
}

#endif
