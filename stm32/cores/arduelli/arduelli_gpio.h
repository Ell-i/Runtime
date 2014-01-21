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
# define _ARDUELLI_GPIO_H_

# include <stm32f0xx.h>
# include <stm32f0xx_extra.h>
# include <system_init.h>

/***************************
 *
 * Static, compile-time-only records for boot-time initialisation
 * of GPIO ports.
 *
 * For each of the ports, we set the corresponding Enable bit in the
 * RCC AHBENR register.  Other than that, the factory defaults are
 * good enough for us.
 *
 * Note that the actual record is placed at the SYSTEM_INIT_SECTION
 * linker section, causing the boot-time initialisation code called from main() to
 * initialise the GPIO.  If the GPIO is not used, the record won't be
 * placed at the .init.default section, and the GPIO won't be enabled.
 */

/**
 * Declares an GPIO init record so that they are externally
 * visible.
 */

#  define GPIO_INIT_DEFAULT(port) \
    extern const SystemInitRecordArray GPIO ## port ## _INIT

/**
 * Defines an GPIO init record and makes it visible through the
 * @see SYSTEM_INIT_SECTION.
 * @param port The GPIO port as a single letter
 *
 * See the corresponding definitions in <variant>_gpio.c
 *
 * XXX (later): At the moment these are NOT declared as static, to
 * make sure that the compiler does *not* optimise these away.  It
 * would be good for someone to see if the definitions work also if
 * they are static, as they don't need to pollute the name space.
 */

#define DEFINE_GPIO_PORT(port)                                          \
    const SystemInitRecordOnesOnly                                      \
    GPIO ## port ## _INIT_DefaultRecords[] = {                          \
        {                                                               \
            IF(init_r_address) &RCC->AHBENR,                            \
            IF(init_r_ones)    RCC_AHBENR_GPIO ## port ## EN,           \
        },                                                              \
    };                                                                  \
    const SystemInitRecordArray                                         \
      GPIO ## port ## _INIT                                             \
       __attribute__((section(SYSTEM_INIT_SECTION(GPIO ## port))))      \
        = {                                                             \
        IF(init_record_type)   ONES_ONLY,                                     \
        IF(init_record_number) COUNT_OF(GPIO ## port ##_INIT_DefaultRecords), \
        { IF(init_record_offset) 0 },                                   \
        { IF(init_records_ones_only) GPIO ## port ## _INIT_DefaultRecords, }, \
    }

/**
 * A const data structure describing each Arduino-compatible GPIO pin
 * in the target boards.  Each variant defines an array of these data
 * structures.  The Arduino PIN numbers act as indices to the array.
 *
 * In the typical case, the GPIO pins are described as a static const
 * array, arranged in such a way that the compiler is able to optimise
 * the array completely away, generating code that accesses the GPIO
 * registers directly.
 *
 * @member gpio_port  A pointer to the GPIO port register bank
 * @member gpio_mask  Mask for BSRR / BRR register access
 * @member gpio_pin   Pin number
 *
 * @see DEFINE_GPIO_PIN
 */

struct GPIO {
#ifdef EMULATOR
    GeneralPurposeInputOutput *const
                                  gpio_port; /* Representation of the emulator GPIO port */
#else
    GPIO_TypeDef *const           gpio_port; /* Pointer to the GPIO registers */
#endif
    const uint32_t                gpio_mask; /* GPIO pin mask for BSRR / BRR register */
    const uint8_t                 gpio_pin;  /* GPIO pin number, as an integer */
};

/**
 * Defines a pin in a compact way.  This macro simply expands into a
 * struct initialisation.
 *
 * Used in the <variant>/gpio_<variant>.h, to define a static const array of
 * pins.  The array is then optimised away by the compiler.
 *
 * @see struct GPIO
 */
#define DEFINE_GPIO_PIN(port, pin)         \
{                                          \
    IF(gpio_port) GPIO ## port,            \
    IF(gpio_mask) GPIO_ODR_ ## pin,        \
    IF(gpio_pin)  pin,                     \
}


/*********************************************************************************
 *
 * Arduino-compatible GPIO data structures and interfaces
 *
 */

/**
 * Arduino GPIO pin mode.
 */
enum pin_mode {
    INPUT          = 0,
    INPUT_PULLUP   = 1,
    INPUT_PULLDOWN = 2,         /* ELL-i extension */
    OUTPUT         = 3,
};

#define PIN_MODE_NUMBER (OUTPUT+1)

/*
 * STM32F GPIO MODER register values for the particular pin mode,
 * @see RM0091 Reference manual Section 8.4.1, page 129.
 */
static const uint32_t GPIO_pin_mode_moder_values[PIN_MODE_NUMBER] = {
    0, 0, 0, GPIO_MODER_MODER0_0,
};
/* STM32F GPIO PUPDR register values for the particular pin mode,
 * @see RM0091 Reference manual Section 8.4.4, page 130.
 */
static const uint32_t GPIO_pin_mode_pupdr_values[PIN_MODE_NUMBER] = {
    0, GPIO_PUPDR_PUPDR0_0, GPIO_PUPDR_PUPDR0_1, 0,
};

/*
 * They type for Arduino pins, i.e., basically an index
 * to the pin description table, defined below.
 *
 * XXX: Try to replace with an explicit class that has an explicit
 *      constructor from an integer.  Probably generates worse code,
 *      but is worth trying with a good compiler (LLVM?).
 */
typedef const uint32_t pin_t;

#endif//_ARDUELLI_GPIO_H_
