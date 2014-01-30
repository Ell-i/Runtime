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
    volatile uint32_t *const      gpio_afr_;       // GPIO AFR for setting the pin alternate function
    const uint32_t                gpio_afr_mask_;  // Bits to clear in the GPIO AFR
    const uint32_t                gpio_afr_ones_;  // Bits to set in the GPIO AFR
    volatile uint32_t *const      gpio_moder_;
    const uint32_t                gpio_moder_mask_;
    const uint32_t                gpio_moder_ones_;
};

// XXX assumes tx pin is first and rx pin immediately after
#define DEFINE_USART_STRUCT(usart_number, gpio_letter, tx_pin, af)      \
    {                                                                   \
    IF(usart_)           USART ## usart_number,                         \
    IF(gpio_afr_)        &GPIO ## gpio_letter->AFR[tx_pin / 8],         \
    IF(gpio_afr_mask_)   (GPIO_AFRL_AFRL0 | GPIO_AFRL_AFRL1) << ((tx_pin % 8) * 4), \
    IF(gpio_afr_ones_)   (af              | af << 4        ) << ((tx_pin % 8) * 4), \
    IF(gpio_moder_)      &GPIO ## gpio_letter->MODER,                   \
    IF(gpio_moder_mask_) (GPIO_MODER_MODER0  | GPIO_MODER_MODER1  ) << (tx_pin * 2), \
    IF(gpio_moder_ones_) (GPIO_MODER_MODER0_1| GPIO_MODER_MODER1_1) << (tx_pin * 2), \
    }

#endif//_ARDUELLI_USART_H_
