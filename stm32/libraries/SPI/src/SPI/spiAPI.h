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

#ifndef  _SPIAPI_H_
# define _SPIAPI_H_

# include <stdlib.h> // define size_t
# include <arduelli_pin_functions.h> // XXX Replace with non-core specific?
# include <SPI/spiStruct.h>
# include <wiring_digital.h>

/****************************************
 * C-level SPI API functions
 *
 * XXX document
 */


# ifdef __cplusplus
extern "C" {
# endif

/**
 * Connect an SPI peripheral to the given pins as a master.
 *
 * In the current ELL-i runtime we pre-configure the used SPI
 * peripherals as masters using the system_init.[ch] functions.
 * Hence, to activate an SPI as a master it is enough to connect the
 * SPI to the right output pins. 
 */
static inline void spi_master_begin(const struct SPI *const spi, const pin_t ss_pin) {
    digitalWrite(ss_pin, 1); /* Avoid glitch */
    pinMode(ss_pin, OUTPUT);
    if (0 == spi->spi_dynamic_->spi_dyn_outstanding_begin_calls_++) {
        PinFunctionActivate(&spi->spi_miso_function_);
        PinFunctionActivate(&spi->spi_mosi_function_);
        PinFunctionActivate(&spi->spi_clk_function_);
    }
}

static inline void spi_master_activate  (const pin_t ss_pin) __attribute__((always_inline));
static inline void spi_master_activate  (const pin_t ss_pin) { digitalWrite(ss_pin, 0); }
static inline void spi_master_deactivate(const pin_t ss_pin) __attribute__((always_inline));
static inline void spi_master_deactivate(const pin_t ss_pin) { digitalWrite(ss_pin, 1); }

/**
 * XXX
 */
static inline void spi_master_end  (const struct SPI *const spi, const pin_t ss_pin) {
    pinMode(ss_pin, INPUT /* XXX DEFAULT */);
    if (0 == --spi->spi_dynamic_->spi_dyn_outstanding_begin_calls_) {
        PinFunctionDeactivate(&spi->spi_miso_function_);
        PinFunctionDeactivate(&spi->spi_mosi_function_);
        PinFunctionDeactivate(&spi->spi_clk_function_);
    }
}

extern size_t spi_transfer_write(
    const struct SPI *const spi, uint8_t data[], const size_t len);

extern size_t spi_transfer_read(
    const struct SPI *const spi, uint8_t data[], const size_t len);

/**
 * XXX
 */

static inline size_t spi_transfer_raw(
    const struct SPI *const spi, const uint32_t cr1, 
    uint8_t data[], size_t len, uint8_t read) __attribute__((always_inline));
static inline size_t spi_transfer_raw(
    const struct SPI *const spi, const uint32_t cr1, 
    uint8_t data[], size_t len, uint8_t read) {

    /* Set the bitorder, speed, and mode according to the pin */
    spi->spi_->CR1 = cr1;

    if (read)
        len = spi_transfer_read(spi, data, len);
    else
        len = spi_transfer_write(spi, data, len);

    return len;
}

/**
 * XXX
 */

static inline size_t spi_transfer(
    const struct SPI *const spi, const pin_t ss_pin, const uint32_t cr1, 
    uint8_t data[], size_t len, uint8_t read) __attribute__((always_inline));
static inline size_t spi_transfer(
    const struct SPI *const spi, const pin_t ss_pin, const uint32_t cr1, 
    uint8_t data[], size_t len, uint8_t read) {

    // Lower slave select
    digitalWrite(ss_pin, 0);

    len = spi_transfer_raw(spi, cr1, data, len, read);

    // Rise slave select
    digitalWrite(ss_pin, 1);
    
    return len;
}



# ifdef __cplusplus
}
# endif

#endif //_SPIAPI_H_
