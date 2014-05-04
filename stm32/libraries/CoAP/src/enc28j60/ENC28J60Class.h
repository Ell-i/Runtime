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
 * ENC28J60 interface through the Arduino SPI library
 *
 * @author: Pekka Nikander <pekka.nikander@ell-i.org>  2014
 */

#ifndef  _ENC28J60_CLASS_H_
# define _ENC28J60_CLASS_H_

# include <SPI/spiStruct.h>
# include <SPI/spiAPI.h>
# include <SPI/ellduino_spi.h>    // XXX To be placed into the variant.h!
# include <enc28j60/enc28j60_conf.h>

class ENC28J60Class {
public:
    const static pin_t ss_pin_ = 40; // Must allow constant propagration!

    const uint8_t *const mac_address_;

    const static uint32_t spiCR1value = 
        // XXX Check the clock divider!
        0
        | ! SPI_CR1_CPHA       /* Data at first edge */
        | ! SPI_CR1_CPOL       /* Clock low when idle */
        |   SPI_CR1_MSTR       /* Master mode */
        |   SPI_CR1_BR_1       /* Clock divider 8 XXX CHECK! */
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

    constexpr ENC28J60Class(
        pin_t ss_pin_dummy, 
        const uint8_t mac_address[ETH_ADDRESS_LEN])
        : 
          mac_address_(mac_address)
    {};

    void begin() const;
    int  availablePackets(void) const;

    int  receivePacket(uint8_t *buffer, size_t len) const; 
    void sendPacket   (uint8_t *buffer, size_t len) const;

    // XXX For debugging purposes
    bool checkBegin(const uint8_t mac_address[ETH_ADDRESS_LEN]) const;
    void getHeader(enc_rx_packet_header_t *rx_header) const;

    static const struct enc28j60_register_init_static_8bit enc28j60_init[];
    static const size_t enc28j60_init_size;
    static enc_rx_packet_header_t rx_header;
    
private:

    uint8_t spi_command(uint8_t cmd, uint8_t value, bool third_byte) const;
    void    spi_transfer_send(uint8_t *buffer, uint16_t len) const __attribute__((always_inline));
    void    spi_transfer     (uint8_t *buffer, uint16_t len) const __attribute__((always_inline));

    void    set_bank(int bank) const;   //XXX to prevent casting differnt enums enc_bank_t
    int     phy_get(enc_reg_t reg) const;
    void    phy_set(enc_reg_t reg, int value, bool nowait) const;

    int     reg_get(enc_reg_t reg) const __attribute__((always_inline));
    void    reg_set(enc_reg_t reg, int value) const __attribute__((always_inline));
    void    reg_set_inner(enc_reg_t reg, int value) const;
    void    reg_bitop(enc_spi_op_t op, enc_reg_t reg, int mask) const __attribute__((always_inline));

};

inline uint8_t
ENC28J60Class::spi_command(uint8_t cmd, uint8_t value, bool third_byte) const {
    uint8_t buffer[4];
    size_t  len;

    buffer[0] = cmd;
    buffer[1] = value;

    len = 2;
    if (third_byte) len = 3;

    spi_transfer(buffer, len);

    return (third_byte)? buffer[2]: buffer[1];
}

inline void
ENC28J60Class::spi_transfer_send(uint8_t *buffer, uint16_t len) const {
    spi_master_activate(ss_pin_);
    ::spi_transfer_raw(&ENC28J60_SPI, spiCR1value, buffer, len, 0);
    spi_master_deactivate(ss_pin_);
}

inline void
ENC28J60Class::spi_transfer(uint8_t *buffer, uint16_t len) const {
    spi_master_activate(ss_pin_);
    ::spi_transfer_raw(&ENC28J60_SPI, spiCR1value, buffer, len, 1);
    spi_master_deactivate(ss_pin_);
}

# include <enc28j60/enc28j60_reg.h>
# include <enc28j60/enc28j60_init.h>
# include <enc28j60/enc28j60_packet.h>

#endif//_ENC28J60_CLASS_H_
