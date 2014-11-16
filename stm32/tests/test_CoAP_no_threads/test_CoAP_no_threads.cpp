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

#include <assert.h>
#include <stddef.h>
#include <string.h>
#include <encX24j600/ENCX24J600.h>
#include <ethernet.h>
#include <ip.h>
#include <udp.h>
#include <coap_internal.h>

#define DEBUG_LED 4

uint8_t address[ETHER_ADDR_LEN];
uint8_t buffer[2048 + 8/*XXX*/] __attribute__((aligned(8)));
struct ether_header *const ether_header = (struct ether_header *)(buffer+8);

extern "C" void debug_write(int c) {
    Serial.write(c);
}

void setup() {
    pinMode(DEBUG_LED, OUTPUT);
    Serial.begin(57600);
    Serial.write('B');
    ETHERNET.begin();
    ETHERNET.readEthernetAddr(address);
    eth_set_address(address);
    Serial.write('s');
}

void loop() {
    Serial.write('w');
    while (!(ETHERNET.availablePackets()))
        ;

    Serial.write('r');
    digitalWrite(DEBUG_LED, 1);
    ETHERNET.receivePacket(&buffer[8], sizeof(buffer) - 8);
    Serial.write('.');
    eth_input(ether_header);
    digitalWrite(DEBUG_LED, 0);


#ifdef EMULATOR
    _exit(0);
#endif
}

#include <CoAP.h>

#define HELLO_WORLD "Hello, World!"

int test_get_callback(
    const struct coap_options *input_options,
    const uint8_t *input_buffer, size_t input_length,
    uint8_t *output_buffer, size_t *output_buffer_length) {
    *output_buffer++ = COAP_OPTION_PAYLOAD;
    memcpy(output_buffer, HELLO_WORLD, sizeof(HELLO_WORLD));
    *output_buffer_length = sizeof(HELLO_WORLD); // Excludes NUL
    return 0; // XXX semantics not fixed yet
}


DEFINE_COAP_URL(test, "test", test_get_callback, NULL);
