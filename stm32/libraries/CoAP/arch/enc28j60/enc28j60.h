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

#ifndef _ETHERNET_ARCH_ENC28J60_H
#define _ETHERNET_ARCH_ENC28J60_H

#include <SPI.h>

class ENC28J60Class {
public:
    const SPIClass spi_;
    const uint8_t pin_; // Arduino board pin
    constexpr ENC28J60Class(const SPIClass &spi, const uint8_t pin) 
        : spi_(spi)
        , pin_(pin)
    {};
private:
    void spiBegin();
    int  spiCmd(XXX cmd, XXX value, int third_byte);
    void spiBuffer(XXX cmd, XXX *buffer, uint16_t len, bool read = false);
    void spiEnd();
}

#endif//_ETHERNET_ARCH_ENC28J60_H
