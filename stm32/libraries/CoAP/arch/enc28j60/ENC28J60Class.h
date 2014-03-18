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

    static const struct enc28j60_register_init_static_8bit enc28j60_init[];
    static const size_t enc28j60_init_size;
    static enc_rx_packet_header_t rx_header;
    
private:

    void    spi_begin() const;
    void    spi_activate() const;
    void    spi_deactivate()  const;
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

#include <enc28j60_reg.h>
#include <enc28j60_packet.h>

inline void
ENC28J60Class::spi_activate() const {
    digitalWrite(ss_pin_, 0);
}

inline void
ENC28J60Class::spi_deactivate() const {
    digitalWrite(ss_pin_, 1);
}

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
ENC28J60Class::spi_transfer(uint8_t *buffer, uint16_t len) const {
    // XXX This needs to be modified, because the current
    //     SPI implementation always writes over the buffer
    ::spi_transfer(&ENC28J60_SPI, ss_pin_, spiCR1value, buffer, len, 1);
}

inline void 
ENC28J60Class::begin() const {
    const device_register_init_static_8bit_t *p;
    
    spi_begin();

    // XXX reset the device

    while ((reg_get(E_STAT) & E_STAT_CLOCK_READY) == 0) {
        ;
    }

    // XXX CHECK ORDER!
    reg_set(MAC_ADR0, mac_address_[5]);
    reg_set(MAC_ADR1, mac_address_[4]);
    reg_set(MAC_ADR2, mac_address_[3]);
    reg_set(MAC_ADR3, mac_address_[2]);
    reg_set(MAC_ADR4, mac_address_[1]);
    reg_set(MAC_ADR5, mac_address_[0]);

    for (p = enc28j60_init;
         p < enc28j60_init + enc28j60_init_size;
         p++) {
        reg_set(p->reg, p->value);
    }

    while (reg_get(PHY_CON1) & PHY_CON1_PRST)
        ;

    reg_set(PHY_CON2, PHY_CON2_HDLDIS);

    enc_buf_value_t b[2] = { ENC_SPI_WRITE_MEM, 0 };

    spi_transfer(b, sizeof(b));
    
}

// XXX For debugging purposes
inline bool 
ENC28J60Class::checkBegin(const uint8_t mac_address[ETH_ADDRESS_LEN]) const {
    const device_register_init_static_8bit_t *p;

    if(reg_get(MAC_ADR0) != mac_address[5]) return false;
    if(reg_get(MAC_ADR1) != mac_address[4]) return false;
    if(reg_get(MAC_ADR2) != mac_address[3]) return false;
    if(reg_get(MAC_ADR3) != mac_address[2]) return false;
    if(reg_get(MAC_ADR4) != mac_address[1]) return false;
    if(reg_get(MAC_ADR5) != mac_address[0]) return false;

    for (p = enc28j60_init + 14;                          //skip buffer pointers
         p < enc28j60_init + enc28j60_init_size - 1; //skip ECON1
         p++) {
        if (reg_get(p->reg) != p->value) return false;
    }

    return true;
}

#endif//_ETHERNET_ARCH_ENC28J60CLASS_H
