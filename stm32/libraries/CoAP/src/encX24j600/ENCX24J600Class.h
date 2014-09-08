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
 * ENCX24J600 interface through the Arduino SPI library
 *
 * @author: Pekka Nikander <pekka.nikander@ell-i.org>  2014
 */

#ifndef  _ENCX24J600_CLASS_H_
# define _ENCX24J600_CLASS_H_

# include <SPI/spiStruct.h>
# include <SPI/spiAPI.h>
# include <SPI/ellduino_spi.h>    // XXX To be placed into the variant.h!
# include <encX24J600/encX24J600_conf.h>

class ENCX24J600Class {
public:
    const static pin_t ss_pin_ = 2; // XXX Must allow constant propagration, make in constructor!

    const static uint32_t spiCR1value =
        0
        | ! SPI_CR1_CPHA       /* Data at first edge */
        | ! SPI_CR1_CPOL       /* Clock low when idle */
        |   SPI_CR1_MSTR       /* Master mode */
        |   SPI_CR1_BR_1       /* Clock divider 8: 72 MHz / 8 = 9 MHz < 14 MHz */
        |   SPI_CR1_SPE        /* SPI enabled */
        | ! SPI_CR1_LSBFIRST   /* MSB first */

        |   SPI_CR1_SSI        /* Internal NSS high, needed for master mode */
        |   SPI_CR1_SSM        /* Software Slave management enabled */
        | ! SPI_CR1_RXONLY     /* 0: Full duplex */
        | ! SPI_CR1_CRCL       /* 0: N/A (8-bit CRC length) */
        | ! SPI_CR1_CRCNEXT    /* 0: Transmit TX buffer, not CERC */
        | ! SPI_CR1_CRCEN      /* 0: CRC disabled */
        |   SPI_CR1_BIDIOE     /* 1: Output enabled */
        | ! SPI_CR1_BIDIMODE   /* 0: 2-Line (uni)directional data */
        ;

    constexpr ENCX24J600Class(
        const struct SPI &spi_dummy, // XXX FIXME define the SPI device here
        pin_t ss_pin_dummy)              // XXX FIXME define the SPI slave select pin here
        // : ss_pin_(ss_pin), ...  XXX FIXME add variable initialisation here
        {};

    void begin() const;
    int  availablePackets(void) const;

    int  receivePacket(uint8_t *buffer, size_t len) const;
    void sendPacket   (uint8_t *buffer, size_t len) const;

    static const struct encX24j600_register_init_static_16bit encX24j600_init[];
    static const size_t encX24j600_init_size;
    /// XXX FIXME do we need this: static enc_rx_packet_header_t rx_header;

private:

    void    spi_send_single_byte(enc_spi_op_t op) const
        __attribute__((always_inline));
    uint8_t  spi_transfer_3bytes(uint8_t cmd, uint8_t address,  uint8_t value) const;
    uint16_t spi_transfer_4bytes(uint8_t cmd, uint8_t address, uint16_t value) const;
    void    spi_transfer_send(uint8_t *buffer, uint16_t len) const
        __attribute__((always_inline));
    void    spi_transfer     (uint8_t *buffer, uint16_t len) const /// XXX rename
        __attribute__((always_inline));

    int     phy_get(uint8_t reg) const;
    void    phy_set(uint8_t reg, int value, bool nowait) const;

    int     reg_get(enc_reg_t reg)                const __attribute__((always_inline));
    void    reg_set(enc_reg_t reg, int value)     const __attribute__((always_inline));
    void    reg_clr_bits(enc_reg_t reg, int mask) const __attribute__((always_inline));
    void    reg_set_bits(enc_reg_t reg, int mask) const __attribute__((always_inline));

};

inline void
ENCX24J600Class::spi_send_single_byte(enc_spi_op_t cmd) const {
    uint8_t buffer[1];
    buffer[0] = cmd;
    spi_transfer(buffer, 1);
}

inline uint8_t
ENCX24J600Class::spi_transfer_3bytes(uint8_t cmd, uint8_t address, uint8_t value) const {
    uint8_t buffer[3];

    buffer[0] = cmd;
    buffer[1] = address;
    buffer[2] = value;

    spi_transfer(buffer, 3);

    return buffer[2];
}

inline uint16_t
ENCX24J600Class::spi_transfer_4bytes(uint8_t cmd, uint8_t address, uint16_t value) const {
    uint8_t buffer[4];

    buffer[0] = cmd;
    buffer[1] = address;
    buffer[2] = value; // NB.  C/C++ truncates by default
    buffer[3] = value >> 8;

    spi_transfer(buffer, 4);

    return buffer[2] | (buffer[3] << 8);
}

inline void
ENCX24J600Class::spi_transfer_send(uint8_t *buffer, uint16_t len) const {
    spi_master_activate(ss_pin_);
    ::spi_transfer_raw(&ENCX24J600_SPI, spiCR1value, buffer, len, 0);
    spi_master_deactivate(ss_pin_);
}

inline void
ENCX24J600Class::spi_transfer(uint8_t *buffer, uint16_t len) const {
    spi_master_activate(ss_pin_);
    ::spi_transfer_raw(&ENCX24J600_SPI, spiCR1value, buffer, len, 1);
    spi_master_deactivate(ss_pin_);
}

# include <encX24J600/encX24J600_reg.h>
# include <encX24J600/encX24J600_begin.h>
//# include <encX24J600/encX24J600_packet.h>

#endif//_ENCX24J600_CLASS_H_
