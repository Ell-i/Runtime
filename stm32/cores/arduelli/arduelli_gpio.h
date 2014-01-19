/*
 * Copyright (c) 2013-2014 ELL-i co-operative.
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
 * @brief  Macros and data types for GPIO ports.
 */

#ifndef _ARDUELLI_GPIO_H_
#define _ARDUELLI_GPIO_H_

#include <stm32f0xx.h>
#include <system_init.h>

/*
 * Static, compile-time-only records for reset-time initialisation GPIO ports A-D and F.
 *
 * For each of the ports, we set the corresponding ENable bit in the RCC AHBENR register.
 * Other than that, the factory defaults are good enough for us.
 *
 * Note that the actual record is placed at the .init.default linker section, causing
 * the reset-time code called from main() to initialise the GPIO.  If the GPIO is not
 * used, the record won't be placed at the .init.default section, and the GPIO won't
 * be enabled.
 */

#define GPIO_INIT_DEFAULT(port) \
    extern const SystemInitRecord GPIO ## port ## _INIT

GPIO_INIT_DEFAULT(A);
GPIO_INIT_DEFAULT(B);
GPIO_INIT_DEFAULT(C);
GPIO_INIT_DEFAULT(D);
GPIO_INIT_DEFAULT(F);

#define GPIO_INIT_DEFAULT_DEFINITION(port)                              \
    const SystemInitRecordMaskOnly                                      \
    GPIO ## port ## _INIT_DefaultRecords[] = {                          \
        {                                                               \
            .init_r_address = &RCC->AHBENR,                             \
            .init_r_mask = RCC_AHBENR_GPIO ## port ## EN,               \
        },                                                              \
    };                                                                  \
    const SystemInitRecord                                              \
      GPIO ## port ## _INIT                                             \
      __attribute__((section(".peripheral.default.GPIO" # port))) = {   \
        .init_record_type   = MASK_ONLY,                                \
        .init_record_number = COUNT_OF(GPIO ## port ##_INIT_DefaultRecords), \
        .init_records_mask_only = GPIO ## port ## _INIT_DefaultRecords, \
    }

/* Corresponding definitions in <variant>_gpio.c */

/*********************************************************************************/

/*
 * Mode
 */

enum pin_mode {
    INPUT          = 0,
    INPUT_PULLUP   = 1,
    INPUT_PULLDOWN = 2,         /* ELL-i extension */
    OUTPUT         = 3,
};

#define PIN_MODES (OUTPUT+1)


static const uint32_t GPIO_pin_mode_moder_values[PIN_MODES] = {
    0, 0, 0, GPIO_MODER_MODER0_0,
};
static const uint32_t GPIO_pin_mode_pupdr_values[PIN_MODES] = {
    0, GPIO_PUPDR_PUPDR0_0, GPIO_PUPDR_PUPDR0_1, 0,
};


/*********************************************************************************/

/*
 * Define a type for an Arduino pin, i.e. basically an index
 * to the pin description table, defined below.
 *
 * XXX: Try to replace with an explicit class that has an explicit
 *      constructor from an integer.  Probably generates worse code,
 *      but is worth trying with a good compiler (LLVM?).
 */
typedef const uint32_t pin_t;

/*
 * A const data structure for describing each Arduino-compatible GPIO pin
 * in the target boards.  Each variant defines an array of these
 * data structures.  The Arduino PIN numbers act as indices to the array.
 *
 * XXX define data structure contents
 */

struct GPIO {
    GPIO_TypeDef *const           gpio_port; /* Pointer to the GPIO registers */
    const uint32_t                gpio_mask; /* GPIO pin mask for BSRR / BRR register */
    const uint8_t                 gpio_pin;  /* GPIO pin number, as an integer */
};

/*
 * A macro, used in the variant/gpio_xxx.h, for defining the pins in a compact way.
 * This macro simply expands into a struct initialisation.
 */
#define DEFINE_GPIO(port, pin)             \
{                                          \
    .gpio_port = GPIO ## port,             \
    .gpio_mask = GPIO_ODR_ ## pin,         \
    .gpio_pin  = pin,                      \
}

#endif//_ARDUELLI_GPIO_H_
