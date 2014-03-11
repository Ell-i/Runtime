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


#include <ENC28J60.h>
#include <ethernet.h>

#define DEBUG_LED 5

uint8_t buffer[2048 + 8/*XXX*/] __attribute__((aligned(8)));
bool    toggle = false;
struct ether_header *const ether_header = (struct ether_header *)(buffer+8);

void setup() {

    ENC28J60.begin(ether_local_address);

    pinMode(DEBUG_LED, OUTPUT);

}

void loop() {
#ifdef EMULATOR
    _exit(0);
#endif
    while (!(ENC28J60.availablePackets()))
        ;

    ENC28J60.receivePacket(&buffer[8]);

    eth_input(ether_header);

    if (toggle) {
        digitalWrite(DEBUG_LED, 0);
        toggle = false;   
    }else{
        digitalWrite(DEBUG_LED, 1);
        toggle = true;   
    }

}
