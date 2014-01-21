/*
 * Copyright (c) 2014 ELL-i co-operative.
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
 *
 * @brief  Macros and data types for USARTs
 */

#ifndef _ARDUELLI_USART_H_
# define _ARDUELLI_USART_H_

# include <stm32f0xx.h>
# include <stm32f0xx_extra.h>
# include <system_init.h>

/***************************
 *
 * Static, compile-time-only records for boot-time initialisation
 * of USARTs.
 *
 * For each of the ports, we set the corresponding Enable bit in the
 * RCC AHBENR register.  Other than that, the factory defaults are
 * good enough for us.
 *
 * Note that the actual record is placed at the SYSTEM_INIT_SECTION
 * linker section, causing the boot-time initialisation code called from main() to
 * initialise the usart.  If the usart is not used, the record won't be
 * placed at the .init.default section, and the usart won't be enabled.
 */

/**
 * Declares USART init records so that they are externally
 * visible.
 */
#  define USART_INIT_DEFAULT(usart) \
    extern const SystemInitRecordArray USART ## usart ## _INIT, USART ## usart ## _RCC_INIT

/**
 * Defines an USART init record and makes it visible through the
 * @see SYSTEM_INIT_SECTION.
 * @param port The usart as a single numbr
 *
 * See the corresponding definitions in <variant>_usart.c
 *
 * XXX (later): At the moment these are NOT declared as static, to
 * make sure that the compiler does *not* optimise these away.  It
 * would be good for someone to see if the definitions work also if
 * they are static, as they don't need to pollute the name space.
 */

#define DEFINE_USART(apbus, usart, init_records)                        \
    const SystemInitRecordOnesOnly                                      \
      USART ## usart ## _RCC_INIT_DefaultRecords[] = {                  \
        {                                                               \
            IF(init_r_address) &RCC->APB ## apbus ## ENR,               \
            IF(init_r_ones)    RCC_APB ## apbus ## ENR_USART ## usart ## EN, \
        },                                                              \
    };                                                                  \
    const SystemInitRecordArray                                         \
      USART ## usart ## _RCC_INIT                                       \
       __attribute__((section(SYSTEM_INIT_SECTION(USART ## usart))))    \
        = {                                                             \
        IF(init_record_type)   ONES_ONLY,                               \
        IF(init_record_number) COUNT_OF(USART ## usart ##_RCC_INIT_DefaultRecords), \
        { IF(init_record_offset) 0 },                                   \
        { IF(init_records_ones_only) USART ## usart ## _RCC_INIT_DefaultRecords, }, \
    };                                                                  \
    const SystemInitRecordArray                                         \
      USART ## usart ## _INIT                                           \
       __attribute__((section(SYSTEM_INIT_SECTION(USART ## usart))))    \
        = {                                                             \
        IF(init_record_type)   DATA32_NO_ADDRESS,                       \
        IF(init_record_number) COUNT_OF(init_records2),                 \
        { IF(init_record_address32) &USART ## usart->CR1 },             \
        { IF(init_records_data32_no_address) init_records, },           \
    }

/**
 * A minimal base class for an Arduino compatible Serial class, describing an USART.
 */

class SerialBase {
public: /* XXX FIXME Use POD until C++1 constexpr is available */
#ifdef EMULATOR
    UniversalSynchronousAsynchronousReceiverTransmitter *const
                                  usart_; /* Representation of the emulator USART */
#else
    USART_TypeDef *const          usart_; /* Pointer to the USART registers */
#endif
};

/**
 * Defines a pin in a compact way.  This macro simply expands into a
 * struct initialisation.
 *
 * Used in the <variant>/<variant>_usart.h, to define a static const array of
 * pins.  The array is then optimised away by the compiler.
 *
 * @see struct PWM
 */
#define DEFINE_SERIAL(usart) {           \
    IF(usart_)   USART ## usart,         \
}

#define DEFINE_PWM_PIN_NONE { 0, 0 }

#endif//_ARDUELLI_PWM_H_
