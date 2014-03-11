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

#include <SPI.h>
#include <enc28j60-conf.h>

class ENC28J60Class {
public:
    const SPIClass &spi_;
    const uint8_t pin_; // Arduino board pin
    constexpr ENC28J60Class(const SPIClass &spi, const uint8_t pin) 
        : spi_(spi)
        , pin_(pin)
    {};
    void begin(const uint8_t mac_address[ETH_ADDRESS_LEN]) const;
    void end(void) const {
        spiEnd();
    }

    int  availablePackets(void) const;

    //XXX check real default value
    int  receivePacket(uint8_t *buffer, size_t maxlen = 2048) const; 
    
    void sendPacket(uint8_t *buffer, size_t len) const;

    // XXX For debugging purposes
    bool checkBegin(const uint8_t mac_address[ETH_ADDRESS_LEN]) const;
    void getHeader(enc_rx_packet_header_t *rx_header) const;

    
private:
    void    spiBegin(uint32_t hertz = 6000000) const;
    uint8_t spiCmd(uint8_t cmd, uint8_t value, bool third_byte) const;
    void    spiBuffer(uint8_t *buffer, uint16_t len, bool read = true) const;
    void    spiEnd(void) const;

    void    set_bank(int bank) const;   //XXX to prevent casting differnt enums enc_bank_t
    int     phy_get(enc_reg_t reg) const;
    void    phy_set(enc_reg_t reg, int value, bool nowait) const;

    int     enc_reg_get(enc_reg_t reg) const;
    void    enc_reg_set(enc_reg_t reg, int value) const;
    void    enc_reg_bitop(enc_spi_op_t op, enc_reg_t reg, int mask) const;

};

#endif//_ETHERNET_ARCH_ENC28J60CLASS_H
