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
 *
 * In the Arduelli runtime, an SPI device is represented as a
 * three-layer structure:
 *      +--------------+------------------------+
 *      | SPIClass     | Arduino SPI APIs       |
 *      +--------------+------------------------+
 *      | SPI + SS pin | C-level APIs           |
 *      +--------------+------------------------+
 *      | struct SPI   | Compile time constants |
 *      +--------------+------------------------+
 *
 * The compile time constants are defined in spiStruct.[ch]
 * The C-level API is defined in spiAPI.h
 * The Arduino SPI class is defined in SPIClass.h
 */

#ifndef  _SPISTRUCT_H_
# define _SPISTRUCT_H_

# include <system_init.h>
# include <arduelli_pin_functions.h> // XXX Replace with non-core specific?

/***************************
 * Static, compile-time-only records for boot-time initialisation.
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

#define DEFINE_SPI_DEVICE(spi, apbus, init_records_data, init_records_offsets, init_records_count) \
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
        IF(init_record_reserved) 0,                                     \
        { IF(init_record_offset) 0 },                                   \
        { IF(init_records_addr_and_ones) SPI ## spi ## _RCC_INIT_DefaultRecords, }, \
    };                                                                  \
    const SystemInitRecordArray                                         \
    SPI ## spi ## _INIT                                                 \
    __attribute__((section(SYSTEM_INIT_SECTION(1, SPI ## spi))))        \
        = {                                                             \
        IF(init_record_type)   DATA16_WITH_OFFSETS,                     \
        IF(init_record_number) init_records_count,                      \
        IF(init_record_reserved) 0,                                     \
        { IF(init_record_address16) &SPI ## spi->CR1 },                 \
        { IF(init_records_data16_only) init_records_data, },            \
        { IF(init_records_register_offsets) init_records_offsets },     \
    }

/**
 * A struct describing a single external SPI slave.  Each slave is
 * associated with a GPIO pin acting as the slave select pin, and the
 * value of the CR1 register, allowing different slaves to have
 * different clock speeds and other parameters.
 *
 * XXX CHECK IF USED.  REMOVE IF NOT.
 */
struct SPIslave {
    pin_t    spi_slave_pin_;
    uint32_t spi_slave_cr1_;
};

/**
 * XXX
 */
struct SPIdynamicFields {
    uint8_t   spi_dyn_outstanding_begin_calls_;
};

/**
 * A const struct describing and SPI peripheral and pointers to the 
 * associated slave devices.
 */
struct SPI {
# ifdef EMULATOR
    SerialPeripheralInterface *const
                                   spi_; /* Representation of the emulator SPI */
# else
    SPI_TypeDef *const             spi_; /* Pointer to the SPI registers */
# endif
    const struct PinFunction       spi_ss_function_;  // Only used for slave!
    const struct PinFunction       spi_miso_function_;
    const struct PinFunction       spi_mosi_function_;
    const struct PinFunction       spi_clk_function_;
    struct SPIdynamicFields *const spi_dynamic_;
};

#define DEFINE_SPI_STRUCT(spi_number, ss_port, ss_pin, ss_af, miso_port, miso_pin, miso_af, mosi_port, mosi_pin, mosi_af, clk_port, clk_pin, clk_af, dynamicFields) \
    static const struct SPI SPI ## spi_number ## struct = {                        \
        IF(spi_)                SPI ## spi_number,                                 \
        IF(spi_ss_function_)    DEFINE_PIN_FUNCTION(ss_port, ss_pin, ss_af),       \
        IF(spi_miso_function_)  DEFINE_PIN_FUNCTION(miso_port, miso_pin, miso_af), \
        IF(spi_mosi_function_)  DEFINE_PIN_FUNCTION(mosi_port, mosi_pin, mosi_af), \
        IF(spi_clk_function_)   DEFINE_PIN_FUNCTION(clk_port, clk_pin, clk_af),    \
        IF(spi_dynamic_)        dynamicFields,                                     \
    }

/**
 * Constant boot-time initialisation structures, defined in SPIInitSTM32F0cpp
 */

extern const SystemInitRecordData16Only     SPI_INIT_STM32F0_DefaultRecordsData[];
extern const SystemInitRecordRegisterOffset SPI_INIT_STM32F0_DefaultRecordsOffsets[];
extern const uint8_t                        SPI_INIT_STM32F0_DefaultRecordsCount;

#endif //_SPISTRUCT_H_
