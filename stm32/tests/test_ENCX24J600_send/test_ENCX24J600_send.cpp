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

#include <ENCX24J600.h>
#include <Arduino.h>

#ifdef EMULATOR
#include <unistd.h>
#endif

#include <udp.h>
#include <ip.h>
#include <ethernet.h>

struct {
    char   extra_space[2];
    struct ether_header eth;
    struct ip   ip;
    struct udp  udp;
} __attribute__((packed)) _mockup_packet = {
    .eth = {
        .ether_dhost = { 1,   2,  3,  4,  5,  6 }, // XXX TBD
        .ether_shost = { 10, 11, 12, 13, 14, 15 },
        .ether_type  = ETHERTYPE_IP,
    },
    .ip = {
        .ip_vhl    = IP_VHL_DEFAULT,
        .ip_tos    = 0,
        .ip_len    = sizeof(ip) + sizeof(udp),
        .ip_id     = 0x4321,
        .ip_off    = 0,
        .ip_ttl    = 1,
        .ip_p      = IPPROTO_UDP,
        .ip_sum    = 0,  // XXX TBD
        .ip_src    = { .s_bytes = { 10, 0, 0, 1 } },
        .ip_dst    = { .s_bytes = { 10, 0, 0, 2 } },
    },
    .udp = {
        .udp_sport = 's',
        .udp_dport = UDP_PORT_ECHO,
        .udp_len   = 0,
        .udp_sum   = 0,
    },
};

uint8_t *const mockup_packet = (unsigned char *)&(_mockup_packet.eth);
const uint16_t mockup_packet_size = sizeof(_mockup_packet) - sizeof(_mockup_packet.extra_space);

void setup() {
    Serial.begin(57600);
    ENCX24J600.begin();
}

void loop() {
    ENCX24J600.sendPacket(mockup_packet, mockup_packet_size);
#ifdef EMULATOR
    _exit(0);
#endif
}
