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

#ifndef _ETHERNET_ARCH_ENC28J60CLASS_H
#define _ETHERNET_ARCH_ENC28J60CLASS_H

#include <spiStruct.h>
#include <ellduino_spi.h>    // XXX To be placed into the variant.h!
#include <enc28j60-conf.h>

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

    
private:
    void    spi_begin() const;
    uint8_t spi_command(uint8_t cmd, uint8_t value, bool third_byte) const;
    void    spi_transfer(uint8_t *buffer, uint16_t len) const;

    void    set_bank(int bank) const;   //XXX to prevent casting differnt enums enc_bank_t
    int     phy_get(enc_reg_t reg) const;
    void    phy_set(enc_reg_t reg, int value, bool nowait) const;

    int     reg_get(enc_reg_t reg) const;
    void    reg_set(enc_reg_t reg, int value) const;
    void    reg_bitop(enc_spi_op_t op, enc_reg_t reg, int mask) const;

};

inline void
ENC28J60Class::spi_begin() const {
    spi_master_begin(&ENC28J60_SPI, ss_pin_);
}

inline void
ENC28J60Class::spi_transfer(uint8_t *buffer, uint16_t len) const {
    // XXX This needs to be modified, because the current
    //     SPI implementation always writes over the buffer
    ::spi_transfer(&ENC28J60_SPI, ss_pin_, spiCR1value, buffer, len, 1);
}

#endif//_ETHERNET_ARCH_ENC28J60CLASS_H
