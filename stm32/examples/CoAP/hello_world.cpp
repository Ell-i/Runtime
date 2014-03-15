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
#include <CoAP.h>

#define HELLO_WORLD "Hello, World!"

/**
 * A CoAP GET callback
 *
 * This callback gets called called, in a CoAP-associated context,
 * whenever the underlying CoAP stack receives a CoAP GET request
 * targeting the associated URL path.  The input buffer contains the
 * CoAP payload (if any).  The output buffer may be used to encode the
 * reply, including additional CoAP options (if any) and the payload
 * (if any).  The default is to answer with an empty payload.
 *
 * @param input_options
 * @param input_buffer
 * @param input_buffer_length
 * @param output_buffer
 * @param output_buffer_length
 *
 * @return One of the pre-defined COAP_RETURN_CODE values.
 */
int coap_hello_get_callback(
    const struct coap_options *const input_options,
    const uint8_t *input_buffer, 
    size_t input_buffer_length,
    uint8_t *output_buffer, 
    size_t *output_buffer_length) {

    *output_buffer++ = COAP_OPTION_PAYLOAD;
    memcpy(output_buffer, HELLO_WORLD, sizeof(HELLO_WORLD));
    (*output_buffer_length) = sizeof(HELLO_WORLD); // Includes OPTION_PAYLOAD, excludes the NUL

    return COAP_CODE_CONTENT;
}

/**
 * Copy & modify the Doxygen comment from get_callback here, too, once stabilised.
 */

int coap_hello_put_callback(
    const struct coap_options *const input_options,
    const uint8_t *input_buffer, 
    size_t input_buffer_length,
    uint8_t *output_buffer, 
    size_t *output_buffer_length) {
    
    return COAP_CODE_CHANGED;
}

/**
 * Define a CoAP URL, with associated callbacks.
 *
 * Creates a link-time constant data structure that defines a CoAP
 * URL, together with the associated callback functions.
 *
 * @param name          Compile-time name for the generated CoAP URL.
 * @param path          Relative URL path.  Currently no slashes are allowed.
 * @param get_callback  Callback function called whenever a CoAP GET
 *                      is received at this URL.
 * @param put_callback  Callback function called whenever a CoAP PUT
 *                      is received at this URL.
 */

DEFINE_COAP_URL(hello_world, "hello", coap_hello_get_callback, coap_hello_put_callback);

uint8_t packet_buffer[2048 + 8 /* To get it properly aligned */] __attribute__((aligned(8)));

/*
 * Note that CoAP.loop will eventually go away, once we get CoAP
 * running in its own thread.  But that will take some time.  
 * It is mandatory to call CoAP.begin() from setup(), to start DHCP.
 */

void setup() {
    CoAP.begin(); 
}

void loop() {
    CoAP.loop(); // Must be called at least 10 times per second, preferably more often.
}
