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
# include <arduelli_pin_functions.h>

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
 * initialise the usart.  If the USART is not used, the record shouldn't be
 * placed at the .init.default section, and the usart wouldn't be enabled.
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
 * @param port The usart as a single number
 *
 * See the corresponding definitions in <variant>_usart.c
 *
 * XXX (later): At the moment these are NOT declared as static, to
 * make sure that the compiler does *not* optimise these away.  It
 * would be good for someone to see if the definitions work also if
 * they are static, as they don't need to pollute the name space.
 */

#define DEFINE_USART_DEVICE(usart, apbus, init_records)                 \
    const SystemInitRecordOnesOnly                                      \
      USART ## usart ## _RCC_INIT_DefaultRecords[] = {                  \
        {                                                               \
            IF(init_r_address) &RCC->APB ## apbus ## ENR,               \
            IF(init_r_ones)    RCC_APB ## apbus ## ENR_USART ## usart ## EN, \
        },                                                              \
    };                                                                  \
    const SystemInitRecordArray                                         \
      USART ## usart ## _RCC_INIT                                       \
       __attribute__((section(SYSTEM_INIT_SECTION(RCC, USART ## usart))))\
        = {                                                             \
        IF(init_record_type)   ONES_ONLY,                               \
        IF(init_record_number) COUNT_OF(USART ## usart ##_RCC_INIT_DefaultRecords), \
        { IF(init_record_offset) 0 },                                   \
        { IF(init_records_ones_only) USART ## usart ## _RCC_INIT_DefaultRecords, }, \
    };                                                                  \
    const SystemInitRecordArray                                         \
      USART ## usart ## _INIT                                           \
       __attribute__((section(SYSTEM_INIT_SECTION(1, USART ## usart)))) \
        = {                                                             \
        IF(init_record_type)   DATA32_NO_ADDRESS,                       \
        IF(init_record_number) COUNT_OF(init_records),                  \
        { IF(init_record_address32) &USART ## usart->CR1 },             \
        { IF(init_records_data32_no_address) init_records, },           \
    }

/**
 * A minimal base class for an Arduino compatible Serial class, describing an USART.
 */

struct USART {
# ifdef EMULATOR
    UniversalSynchronousAsynchronousReceiverTransmitter *const
                                  usart_; /* Representation of the emulator USART */
# else
    USART_TypeDef *const          usart_; /* Pointer to the USART registers */
# endif
    const struct PinFunction      usart_tx_function_;
    const struct PinFunction      usart_rx_function_;
};

// XXX assumes tx pin is first and rx pin immediately after
#define DEFINE_USART_STRUCT(usart_number, tx_port, tx_pin, tx_af, rx_port, rx_pin, rx_af) \
    {                                                                       \
        IF(usart_)             USART ## usart_number,                       \
        IF(usart_tx_function_) DEFINE_PIN_FUNCTION(tx_port, tx_pin, tx_af), \
        IF(usart_rx_function_) DEFINE_PIN_FUNCTION(rx_port, rx_pin, rx_af)  \
    }

#endif//_ARDUELLI_USART_H_
