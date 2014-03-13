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
 * XXX (later) This code is based on the assumption that the C++ version of 
 * the D32 macro will be used. Although it cuould be removed and use the direct
 * value, it is still used to keep homogeneity.
 */

#ifdef __cplusplus
# define D32(p, r, v) { v }
#else
# ifndef offsetof
#  define offsetof(st, m) ((uint32_t)(&((st *)0)->m))
# endif
# define D32(p, r, v) [offsetof(p, r)/sizeof(uint32_t)] = { v }
#endif

/**
 * Declares an GPIO init record so that they are externally
 * visible.
 */

#  define GPIO_INIT_DEFAULT(port)                                       \
    extern const SystemInitRecordArray GPIO ## port ## _INIT1,          \
        GPIO ## port ## _INIT2, GPIO ## port ## _RCC_INIT

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

#define DEFINE_GPIO_PORT(port, init_records1, init_records2)            \
    const SystemInitRecordAddrAndOnes                                   \
    GPIO ## port ## _RCC_INIT_DefaultRecords[] = {                      \
        {                                                               \
            IF(init_r_address) &RCC->AHBENR,                            \
            IF(init_r_ones)    RCC_AHBENR_GPIO ## port ## EN,           \
        },                                                              \
    };                                                                  \
    const SystemInitRecordArray                                         \
      GPIO ## port ## _RCC_INIT                                         \
        __attribute__((section(SYSTEM_INIT_SECTION(RCC, GPIO ## port))))\
        = {                                                             \
        IF(init_record_type)   ADDR_AND_ONES,                           \
        IF(init_record_number) COUNT_OF(GPIO ## port ## _RCC_INIT_DefaultRecords), \
        IF(init_record_reserved) 0,                                     \
        { IF(init_record_offset) 0 },                                   \
        { IF(init_records_addr_and_ones) GPIO ## port ## _RCC_INIT_DefaultRecords, }, \
    };                                                                  \
    const SystemInitRecordArray                                         \
      GPIO ## port ## _INIT1                                            \
       __attribute__((section(SYSTEM_INIT_SECTION(1, GPIO ## port))))   \
        = {                                                             \
        IF(init_record_type)   DATA32_ONLY,                             \
        IF(init_record_number) COUNT_OF(init_records1),                 \
        IF(init_record_reserved) 0,                                     \
        { IF(init_record_address32) &GPIO ## port->MODER },             \
        { IF(init_records_data32_only) init_records1, },                \
    };                                                                  \
    const SystemInitRecordArray                                         \
      GPIO ## port ## _INIT2                                            \
       __attribute__((section(SYSTEM_INIT_SECTION(2, GPIO ## port))))   \
        = {                                                             \
        IF(init_record_type)   DATA32_ONLY,                             \
        IF(init_record_number) COUNT_OF(init_records2),                 \
        IF(init_record_reserved) 0,                                     \
        { IF(init_record_address32) &GPIO ## port->AFR[0] },            \
        { IF(init_records_data32_only) init_records2, },                \
    }


#define DEFINE_GPIO_PIN_INIT(port, pin, mode, type, speed, pupd, af)    \
    static const uint32_t __GPIO ## port ## _PIN ## pin ## _MODE =      \
        GPIO_MODER_MODER0_ ## mode<< (pin * 2);                         \
    static const uint32_t __GPIO ## port ## _PIN ## pin ## _TYPE =      \
        GPIO_OTYPER_OT_0_ ## type<< (pin * 1);                          \
    static const uint32_t __GPIO ## port ## _PIN ## pin ## _SPEED =     \
        GPIO_OSPEEDR_OSPEEDR0_ ## speed<< (pin * 2);                    \
    static const uint32_t __GPIO ## port ## _PIN ## pin ## _PUPD =      \
        GPIO_PUPDR_PUPDR0_ ## pupd<< (pin * 2);                         \
    static const uint32_t __GPIO ## port ## _PIN ## pin ## _AF =        \
        GPIO_AFRx_AFRx0_AF ## af<< ((pin % 8) * 4)


#define DEFINE_GPIO_INIT_RECORD(port)                                   \
const SystemInitRecordData32Only GPIO ## port ## _INIT_DefaultRecords[] = { \
    D32(GPIO_TypeDef, MODER,                                            \
        0                                                               \
        | __GPIO ## port ## _PIN0_MODE                                  \
        | __GPIO ## port ## _PIN1_MODE                                  \
        | __GPIO ## port ## _PIN2_MODE                                  \
        | __GPIO ## port ## _PIN3_MODE                                  \
        | __GPIO ## port ## _PIN4_MODE                                  \
        | __GPIO ## port ## _PIN5_MODE                                  \
        | __GPIO ## port ## _PIN6_MODE                                  \
        | __GPIO ## port ## _PIN7_MODE                                  \
        | __GPIO ## port ## _PIN8_MODE                                  \
        | __GPIO ## port ## _PIN9_MODE                                  \
        | __GPIO ## port ## _PIN10_MODE                                 \
        | __GPIO ## port ## _PIN11_MODE                                 \
        | __GPIO ## port ## _PIN12_MODE                                 \
        | __GPIO ## port ## _PIN13_MODE                                 \
        | __GPIO ## port ## _PIN14_MODE                                 \
        | __GPIO ## port ## _PIN15_MODE                                 \
        ),                                                              \
    D32(GPIO_TypeDef, OTYPER,                                           \
        0                                                               \
        | __GPIO ## port ## _PIN0_TYPE                                  \
        | __GPIO ## port ## _PIN1_TYPE                                  \
        | __GPIO ## port ## _PIN2_TYPE                                  \
        | __GPIO ## port ## _PIN3_TYPE                                  \
        | __GPIO ## port ## _PIN4_TYPE                                  \
        | __GPIO ## port ## _PIN5_TYPE                                  \
        | __GPIO ## port ## _PIN6_TYPE                                  \
        | __GPIO ## port ## _PIN7_TYPE                                  \
        | __GPIO ## port ## _PIN8_TYPE                                  \
        | __GPIO ## port ## _PIN9_TYPE                                  \
        | __GPIO ## port ## _PIN10_TYPE                                 \
        | __GPIO ## port ## _PIN11_TYPE                                 \
        | __GPIO ## port ## _PIN12_TYPE                                 \
        | __GPIO ## port ## _PIN13_TYPE                                 \
        | __GPIO ## port ## _PIN14_TYPE                                 \
        | __GPIO ## port ## _PIN15_TYPE                                 \
        ),                                                              \
    D32(GPIO_TypeDef, OSPEEDR,                                          \
        0                                                               \
        | __GPIO ## port ## _PIN0_SPEED                                 \
        | __GPIO ## port ## _PIN1_SPEED                                 \
        | __GPIO ## port ## _PIN2_SPEED                                 \
        | __GPIO ## port ## _PIN3_SPEED                                 \
        | __GPIO ## port ## _PIN4_SPEED                                 \
        | __GPIO ## port ## _PIN5_SPEED                                 \
        | __GPIO ## port ## _PIN6_SPEED                                 \
        | __GPIO ## port ## _PIN7_SPEED                                 \
        | __GPIO ## port ## _PIN8_SPEED                                 \
        | __GPIO ## port ## _PIN9_SPEED                                 \
        | __GPIO ## port ## _PIN10_SPEED                                \
        | __GPIO ## port ## _PIN11_SPEED                                \
        | __GPIO ## port ## _PIN12_SPEED                                \
        | __GPIO ## port ## _PIN13_SPEED                                \
        | __GPIO ## port ## _PIN14_SPEED                                \
        | __GPIO ## port ## _PIN15_SPEED                                \
        ),                                                              \
    D32(GPIO_TypeDef, PUPDR,                                            \
        0                                                               \
        | __GPIO ## port ## _PIN0_PUPD                                  \
        | __GPIO ## port ## _PIN1_PUPD                                  \
        | __GPIO ## port ## _PIN2_PUPD                                  \
        | __GPIO ## port ## _PIN3_PUPD                                  \
        | __GPIO ## port ## _PIN4_PUPD                                  \
        | __GPIO ## port ## _PIN5_PUPD                                  \
        | __GPIO ## port ## _PIN6_PUPD                                  \
        | __GPIO ## port ## _PIN7_PUPD                                  \
        | __GPIO ## port ## _PIN8_PUPD                                  \
        | __GPIO ## port ## _PIN9_PUPD                                  \
        | __GPIO ## port ## _PIN10_PUPD                                 \
        | __GPIO ## port ## _PIN11_PUPD                                 \
        | __GPIO ## port ## _PIN12_PUPD                                 \
        | __GPIO ## port ## _PIN13_PUPD                                 \
        | __GPIO ## port ## _PIN14_PUPD                                 \
        | __GPIO ## port ## _PIN15_PUPD                                 \
        ),                                                              \
};                                                                      \
const SystemInitRecordData32Only GPIO ## port ## _INIT_AltFunctRecords[] = { \
    D32(GPIO_TypeDef, AFR[0],                                           \
        0                                                               \
        | __GPIO ## port ## _PIN0_AF                                    \
        | __GPIO ## port ## _PIN1_AF                                    \
        | __GPIO ## port ## _PIN2_AF                                    \
        | __GPIO ## port ## _PIN3_AF                                    \
        | __GPIO ## port ## _PIN4_AF                                    \
        | __GPIO ## port ## _PIN5_AF                                    \
        | __GPIO ## port ## _PIN6_AF                                    \
        | __GPIO ## port ## _PIN7_AF                                    \
        ),                                                              \
    D32(GPIO_TypeDef, AFR[1],                                           \
        0                                                               \
        | __GPIO ## port ## _PIN8_AF                                    \
        | __GPIO ## port ## _PIN9_AF                                    \
        | __GPIO ## port ## _PIN10_AF                                   \
        | __GPIO ## port ## _PIN11_AF                                   \
        | __GPIO ## port ## _PIN12_AF                                   \
        | __GPIO ## port ## _PIN13_AF                                   \
        | __GPIO ## port ## _PIN14_AF                                   \
        | __GPIO ## port ## _PIN15_AF                                   \
        ),                                                              \
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
