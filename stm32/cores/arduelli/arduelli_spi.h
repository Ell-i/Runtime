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
 * @brief  Macros and data types for SPIs
 */

#ifndef _ARDUELLI_SPI_H_
# define _ARDUELLI_SPI_H_

# include <stm32f0xx.h>
# include <stm32f0xx_extra.h>
# include <system_init.h>
# include <arduelli_pin_functions.h>

/***************************
 *
 * Static, compile-time-only records for boot-time initialisation
 * of SPIs.
 *
 * For each of the ports, we set the corresponding Enable bit in the
 * RCC AHBENR register.
 *
 * Note that the actual record is placed at the SYSTEM_INIT_SECTION
 * linker section, causing the boot-time initialisation code called from main() to
 * initialise the spi.  If the spi is not used, the record shouldnt't be
 * placed at the .init.default section, and the spi wouldn't be enabled.
 */

/**
 * Declares SPI init records so that they are externally
 * visible.
 */
#  define SPI_INIT_DEFAULT(spi) \
    extern const SystemInitRecordArray SPI ## spi ## _INIT, SPI ## spi ## _RCC_INIT

/**
 * Defines an SPI init record and makes it visible through the
 * @see SYSTEM_INIT_SECTION.
 * @param port The spi as a single number
 *
 * See the corresponding definitions in <variant>_spi.c
 */

#define DEFINE_SPI_DEVICE(spi, apbus, init_records_data, init_records_offsets) \
    const SystemInitRecordAddrAndOnes                                   \
    SPI ## spi ## _RCC_INIT_DefaultRecords[] = {                        \
        {                                                               \
            IF(init_r_address) &RCC->APB ## apbus ## ENR,               \
            IF(init_r_ones)    RCC_APB ## apbus ## ENR_SPI ## spi ## EN,\
        },                                                              \
    };                                                                  \
    const SystemInitRecordArray                                         \
    SPI ## spi ## _RCC_INIT                                             \
    __attribute__((section(SYSTEM_INIT_SECTION(RCC, SPI ## spi))))      \
        = {                                                             \
        IF(init_record_type)   ADDR_AND_ONES,                           \
        IF(init_record_number) COUNT_OF(SPI ## spi ##_RCC_INIT_DefaultRecords), \
        { IF(init_record_offset) 0 },                                   \
        { IF(init_records_addr_and_ones) SPI ## spi ## _RCC_INIT_DefaultRecords, }, \
    };                                                                  \
    const SystemInitRecordArray                                         \
    SPI ## spi ## _INIT                                                 \
    __attribute__((section(SYSTEM_INIT_SECTION(1, SPI ## spi))))        \
        = {                                                             \
        IF(init_record_type)   DATA16_WITH_OFFSETS,                     \
        IF(init_record_number) COUNT_OF(init_records_data),             \
        { IF(init_record_address16) &SPI ## spi->CR1 },                 \
        { IF(init_records_data16_only) init_records_data, },            \
        { IF(init_records_register_offsets) init_records_offsets },     \
    }

/**
 * A minimal struct for an SPI.
 */

struct SPI {
# ifdef EMULATOR
    SerialPeripheralInterface *const
                                  spi_; /* Representation of the emulator SPI */
# else
    SPI_TypeDef *const            spi_; /* Pointer to the SPI registers */
# endif
    const struct PinFunction      spi_ss_function_;
    const struct PinFunction      spi_miso_function_;
    const struct PinFunction      spi_mosi_function_;
    const struct PinFunction      spi_clk_function_;
};

// XXX assumes tx pin is first and rx pin immediately after
#define DEFINE_SPI_STRUCT(spi_number, ss_port, ss_pin, ss_af, miso_port, miso_pin, miso_af, mosi_port, mosi_pin, mosi_af, clk_port, clk_pin, clk_af) \
    {                                                                             \
        IF(spi_)               SPI ## spi_number,                                 \
        IF(spi_ss_function_)   DEFINE_PIN_FUNCTION(ss_port, ss_pin, ss_af),       \
        IF(spi_miso_function_) DEFINE_PIN_FUNCTION(miso_port, miso_pin, miso_af), \
        IF(spi_mosi_function_) DEFINE_PIN_FUNCTION(mosi_port, mosi_pin, mosi_af), \
        IF(spi_clk_function_)  DEFINE_PIN_FUNCTION(clk_port, clk_pin, clk_af),    \
    }

#endif//_ARDUELLI_SPI_H_
