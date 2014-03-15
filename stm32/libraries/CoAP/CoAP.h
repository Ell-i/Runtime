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
 * Compile-time-allocation based API for CoAP
 *
 * @author: Pekka Nikander <pekka.nikander@ell-i.org>  2014
 */
#ifndef  _ETHERNET_COAP_API_H
# define _ETHERNET_COAP_API_H

# include <stdint.h>
# include <stddef.h>   // Define size_t
# include <ip.h>       // XXX Define in_addr_t, IP_MSS, to be removed
# include <ethernet.h> // XXX Define ether_header, to be removed

# include "coap_options.h" // XXX fix path if not in -I directories?  This is a public API.
# include "coap_codes.h"


# ifdef __cplusplus
#  include <ENC28J60.h>
#  include <Arduino.h> // XXX REMOVE
# endif

// Define the semantics for the return value
typedef int (*coap_callback)(
    const struct coap_options * input_options,
    const uint8_t *input_buffer, size_t input_length,
    uint8_t *output_buffer, size_t *output_buffer_length);

typedef struct CoAPClass {
    uint8_t packet_buffer[IP_MSS + sizeof(struct ether_header) + 8 /* To get it properly aligned */] __attribute__((aligned(8)));
# ifdef __cplusplus
public:
    void begin(in_addr_t ip_address = IP_ADDRESS_UNSPECIFIED) {
        Serial.begin(57600);
        Serial.write('S');
        ENC28J60.begin(ether_local_address);
    }
    void loop(void) {
        if (ENC28J60.availablePackets()) {
            Serial.write('R');
            ENC28J60.receivePacket(           packet_buffer + 8, sizeof(packet_buffer) - 8);
            Serial.write('E');
            eth_input((struct ether_header *)(packet_buffer + 8));
            Serial.write('C');
            Serial.write('\n');
        }
    }
# endif
} CoAPClass;

extern CoAPClass CoAP;

typedef struct {
    const coap_callback              coap_url_get_callback;
    const coap_callback              coap_url_put_callback;
    const char *                     coap_url_path;
    const uint8_t                    coap_url_path_length;
} __attribute__((aligned(SYSTEM_INIT_ALIGNMENT))) CoAPURL;

# ifdef __MACH__
#  define COAP_URL_SECTION(name) ".text,.coapurl"
# else
#  define COAP_URL_SECTION(name) ".coap.url." # name
# endif


# define DEFINE_COAP_URL(name, path, get_callback, put_callback) \
    extern const CoAPURL __coap_url ## name                      \
    __attribute__((section(COAP_URL_SECTION(name))));            \
    const CoAPURL __coap_url ## name                             \
    = {                                                          \
        IF(coap_url_get_callback) get_callback,                  \
        IF(coap_url_put_callback) put_callback,                  \
        IF(coap_url_path) path,                                  \
        IF(coap_url_path_length) sizeof(path) - 1,               \
    }                                                            \

extern const CoAPURL __coap_urls[];
extern const CoAPURL __coap_urls_end[];

#endif //_ETHERNET_COAP_API_H
