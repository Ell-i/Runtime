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

#if !defined(EMULATOR)
# error "Cannot execute mockups on real hardware"
#endif

#include <unistd.h>
#include <stdio.h>
#include <coap_int.h>
#include <udp.h>
#include <ip.h>
#include <ethernet.h>

/// XXX Attempt to fix linking
DECLARE_UDP_SOCKET(UDP_PORT_COAP);

const void * __UDP_SOCKET_COAP = &__udp_socket5683;

struct coap_payload {
    union {
        struct coap coap; 
        uint8_t first_byte;
    };
    uint32_t    token;
#define URI_PATH_LEN 6
    uint8_t     uri_path_dl;
    char        uri_path[URI_PATH_LEN];
};

struct {
    struct udp  udp;
    struct coap_payload payload;
} mockup_packet = {
    .udp = { 
        .udp_sport = 's',
        .udp_dport = UDP_PORT_COAP,
        .udp_len   = sizeof(struct coap_payload),
        .udp_sum   = 0,
    },
    .payload = {
        {
            .coap = {
                .coap_hdr = {
                    .coap_vttkl = COAP_VT_CONFIRMABLE | 4, // 4-byte token
                    .coap_code  = COAP_CODE_GET,
                    .coap_id    = 0,
                },
            },
        },
        1234,
        COAP_OPTION_URI_PATH << 4 | URI_PATH_LEN,
        "/test",
    },
};

/* Intercept resulting outgoing packet */
void eth_output(struct ether_header *mockup_enclosing) {
    printf("Received output packet\n");
}

void setup() {
    printf("Sending input packet\n");
    /* Mockup an incoming packet */
    udp_input(&mockup_packet.udp);
}

void loop() {
#ifdef EMULATOR
    _exit(0);
#endif
}
