/*
 * Copyright (c) 2013 ELL-i co-op.
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

#include <arduelli_api_definitions.h>

#if defined(ELLI_STM32F051_ELLDUINO)
#include "ellduino_Serial.h"
#elif defined(ELLI_STM32F407_DISCOVERY)
#include "stm32f4discovery_Serial.h"
#else
#error "Unknown board."
#endif
#ifdef EMULATOR
#include <unistd.h>
#endif

void setup() {
    Serial.begin(57600);
    Serial.write('H');
    Serial.write('e');
    Serial.write('l');
    Serial.write('l');
    Serial.write('o');
    Serial.write('\n');
}

void loop() {
#ifdef EMULATOR
    _exit(0);
#endif
}
