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

#ifndef  _SPISTRUCT_H_
# define _SPISTRUCT_H_

# include <system_init.h>
# include <arduelli_pin_functions.h> // XXX Replace with non-core specific?
# include <stdlib.h> // define size_t

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
    const struct PinFunction      spi_ss_function_;  // Only used for slave!
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

/****************************************
 * Inlined SPI functions
 ****************************************/

# ifdef __cplusplus
extern "C" {
# endif

/**
 * XXX
 */

extern void spi_master_begin(const struct SPI *const spi);
extern void spi_master_end  (const struct SPI *const spi);

/**
 * XXX
 */

/**
 * XXX
 *
 * We inline this to allow the special case of len == 1 being handled efficiently.
 * In most other cases the compiler most probably won't inline, as the resulting
 * function is rather big.  However, LLVM may to do partial application,
 * inlining some part of the code.
 */



size_t inline
spi_transfer(const struct SPI *const spi, const uint32_t cr1, uint8_t data[], const size_t len) {
    /* Get a handle for writing and reading 8-bit data */
    volatile uint8_t *const DR8 = (volatile uint8_t *const)&spi->spi_->DR;

# if 0
    /* Read any pertaining data from the FIFO and throw it away */
    int dummy __attribute__((unused));
    dummy = spi->spi_->DR;
# endif

    /* Set the bitorder, speed, and mode according to the pin */
    spi->spi_->CR1 = cr1;

    if (len == 0) return 0;

    if (len == 1) {
        *DR8 = data[0];           /* Write the only byte */
    } else {
        register uint16_t *wp, *rp;
        wp = rp = (uint16_t *)data;

        /*
         * Try to keep the SPI busy until the buffer has been transferred.
         *
         * We first seed the transmit FIFO with two bytes, then keep
         * writing two more bytes and reading two bytes, until we come
         * to the last byte(s).  This should keep the transmit buffer
         * non-empty all the time.
         */

        spi->spi_->DR = *wp++; /* Fill the transmit fifo with two bytes */

        for (size_t count = (len / 2) - 1; count > 0; count--) {
            spi->spi_->DR = *wp++;  /* Write the next two bytes */

            /* Ensure we have at least 2 bytes in the input FIFO */
            while (!(spi->spi_->SR & SPI_SR_FRLVL_1))
                ; /* XXX.  Let other threads run. */

            *rp++ = spi->spi_->DR;  /* Read the previous two bytes */
        }

        if (len % 1) {
            *DR8 = data[len-1];     /* Write the last byte, if any */
        }

        /* Again, ensure we have received at least 2 bytes. */
        while (!(spi->spi_->SR & SPI_SR_FRLVL_1))
            ; /* XXX.  Let other threads run. */
        *rp++ = spi->spi_->DR;      /* Read the final two bytes */
    }

    /* Wait until the transmission is done */
    while (spi->spi_->SR & SPI_SR_BSY)
        ; /* XXX.  Let other threads run. */

    if (len % 1) {
        data[len-1] = *DR8;     /* Read the last byte, if any */
    }

    return len;
}

# ifdef __cplusplus
}
# endif

#endif //_SPISTRUCT_H_
