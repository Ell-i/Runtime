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

/**
 * C test wrappers for calling our APIs from Robot Framework Python code
 *
 * For compile time efficiency, most of the Ell-i Runtime APIs are defined
 * as inline functions.  Here we create simple non-inline C wrappers
 * for them, making it easier to call them from the Python code when
 * we run the test cases against the emulator.
 */

extern "C" {
    /*
     * This is a dummy main, called by startup code, doing nothing.
     */
    int main() {
        return 0;
    }

    /*
     * The actual C test wrappers.  For the individual functions,
     * see the actual API call.
     */
    void t_pinMode(pin_t pin, const enum pin_mode mode) {
        pinMode(pin, mode);
    }
    int t_digitalRead(pin_t pin) {
        return digitalRead(pin);
    }
    void t_digitalWrite(pin_t pin, uint32_t val) {
        digitalWrite(pin, val);
    }
    void t_analogWrite(pin_t pin, uint32_t val) {
        analogWrite(pin, val);
    }
};
