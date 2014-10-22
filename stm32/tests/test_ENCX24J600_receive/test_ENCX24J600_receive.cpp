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

#include <Arduino.h>
#include <encX24j600/ENCX24J600.h>

#ifdef EMULATOR
#include <unistd.h>
#endif

#include <udp.h>
#include <ip.h>
#include <ethernet.h>

uint8_t buffer[2048];

#define DEBUG 4

void setup() {
    pinMode(DEBUG, OUTPUT);
    digitalWrite(DEBUG, 1);
    Serial.begin(57600);
    ENCX24J600.begin();
    digitalWrite(DEBUG, 0);
}

void loop() {
    while (ENCX24J600.availablePackets() <= 0)
        ;
    digitalWrite(DEBUG, 1);
    ENCX24J600.receivePacket(buffer, sizeof(buffer));
    digitalWrite(DEBUG, 0);
#ifdef EMULATOR
    _exit(0);
#endif
}
