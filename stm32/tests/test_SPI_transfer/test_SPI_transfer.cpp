/*
 * Copyright (c) 2014 ELL-i co-op.
 *
 * This is part of ELL-i software.
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

#include <SPI.h>
#ifdef EMULATOR
#include <unistd.h>
#endif

void setup() {
    SPI.begin();
    SPI_2.begin();
}

uint8_t data[] = { 0x55, 0xAA, 0xCA, 0xFE, 0xBA, 0xBE };

void loop() {
    SPI.transfer(BOARD_SPI_DEFAULT_SS, data, sizeof(data), SPI_LAST);
#ifdef EMULATOR
    _exit(0);
#endif
}
