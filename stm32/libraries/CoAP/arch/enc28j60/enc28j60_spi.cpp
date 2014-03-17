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
 * @author: Pekka Nikander <pekka.nikander@ell-i.org>  2014
 * @author Ivan Raul <ivan.raul@ell-i.org> 2014
 *
 * @brief ENC28J60 ethernet interface
 */

#include <SPI.h>
#include <ENC28J60.h>
#include <ethernet.h>

uint8_t
ENC28J60Class::spi_command(uint8_t cmd, uint8_t value, bool third_byte) const {
    uint8_t buffer[4];
    size_t  len;

    buffer[0] = cmd;
    buffer[1] = value;

    len = 2;
    if (third_byte) len = 3;

    digitalWrite(ss_pin_, 0);
    spi_transfer(buffer, len);
    digitalWrite(ss_pin_, 1);

    return (third_byte)? buffer[2]: buffer[1];
}
