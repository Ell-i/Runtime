/*
 * Copyright (c) 2014 ELL-i co-operative
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
 * @brief SPI interface for STM32F
 */

#include <SPI/spiAPI.h>

/**
 * Transmit, don't read.
 */
// XXX Refactor the dummy reads out, if possible.  If not, document.
size_t /*inline*/ spi_transfer_write(
    const struct SPI *const spi, uint8_t data[], const size_t len) {

    /* Get a handle for writing and reading 8-bit data */
    volatile uint8_t *const DR8 = (volatile uint8_t *const)&spi->spi_->DR;

    int dummy __attribute__((unused));
# if 0
    /* Read any pertaining data from the FIFO and throw it away */
    dummy = spi->spi_->DR;
# endif

    if (len == 0) return 0;

# if defined(STM32F0XX)
    for(size_t count = 0; count < len; count++) {
        *DR8 = data[count];
        while (!(spi->spi_->SR & SPI_SR_FRLVL))
            ;
        dummy = *DR8;
    }
# elif defined(STM32F40_41xxx)
#  warning STM32F4 SPI not implemented yet.  Will not work!
# else
#  error "Unsupported MCU."
# endif

# ifdef notyet // XXX doesn't work correctly, please debug.
    if (len == 1) {
        *DR8 = data[0];           /* Write the only byte */
    } else {
        register uint16_t *wp;
        wp = (uint16_t *)data;

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

            dummy = spi->spi_->DR;  /* Read the previous two bytes */
        }

        if (len % 1) {
            *DR8 = data[len-1];     /* Write the last byte, if any */
        }

        /* Again, ensure we have received at least 2 bytes. */
        while (!(spi->spi_->SR & SPI_SR_FRLVL_1))
            ; /* XXX.  Let other threads run. */
        dummy = spi->spi_->DR;      /* Read the final two bytes */
    }

    /* Wait until the transmission is done */
    while (spi->spi_->SR & SPI_SR_BSY)
        ; /* XXX.  Let other threads run. */

    if (len % 1) {
        dummy = *DR8;     /* Read the last byte, if any */
    }

#endif

    return len;
}

/**
 * Transmit and read
 */
size_t /*inline*/ spi_transfer_read(
    const struct SPI *const spi, uint8_t data[], const size_t len) {
    /* Get a handle for writing and reading 8-bit data */
    volatile uint8_t *const DR8 = (volatile uint8_t *const)&spi->spi_->DR;

# if 0
    /* Read any pertaining data from the FIFO and throw it away */
    int dummy __attribute__((unused));
    dummy = spi->spi_->DR;
# endif

    if (len == 0) return 0;

# if defined(STM32F0XX)
    for(size_t count = 0; count < len; count++) {
        *DR8 = data[count];
        while (!(spi->spi_->SR & SPI_SR_FRLVL))
            ;
        data[count] = *DR8;
    }
# elif defined(STM32F40_41xxx)
#  warning STM32F4 SPI not implemented yet.  Will not work!
# else
#  error "Unsupported MCU."
# endif

# ifdef notyet // XXX doesn't work correctly, please debug.
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

#endif

    return len;
}

