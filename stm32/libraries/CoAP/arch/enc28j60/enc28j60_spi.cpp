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

#include <SPI.h>
#include <ENC28J60Class.h>

void
ENC28J60Class::spiBegin(uint32_t hertz) const {
    spi_.begin(pin_);
    spi_.setClock(pin_,hertz);
}

uint8_t
ENC28J60Class::spiXferCmd(uint8_t cmd, uint8_t value, bool third_byte) const {
    uint8_t buffer[4];
    size_t  len;

    buffer[0] = cmd;
    buffer[1] = value;

    len = 2;
    if(third_byte) len = 3;

    spi_.transfer(pin_, buffer, len);

    if(third_byte) return buffer[2];
    else           return buffer[1];
}

void
ENC28J60Class::spiXferBuffer(uint8_t *buffer, uint16_t len, bool read) const {
	// XXX This needs to be modified, because the current
	//     SPI implementation always writes over the buffer
	spi_.transfer(pin_, buffer, len);
}

void
ENC28J60Class::spiEnd(void) const {
	spi_.end();
}
