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
#include <netinet/net_packet.h>


const struct net_packet test_arp_packet = {
};

const struct net_packet test_ip_udp_packet = {
};

const struct net_packet test_ip_icmp_packet = {
    .np_ether = {
        .ether_dhost = { 0, 0, 0, 0, 0, 0, }, // Ethernet broadcast
        .ether_shost = { 0, 0, 0, 0, 0, 0, }, // Filled in at runtime
        .ether_type  = ETHERTYPE_IP,
    },
    .np_ip    = {
        .ip_vhl = IP_VHL_DEFAULT,
        .ip_tos = IP_TOS_DEFAULT,
        .ip_len = 0,                          // Filled in at runtime by ip_output
        .ip_id  = 0,                          // Filled in at runtime
        .ip_off = IP_OFF_DEFAULT,
        .ip_ttl = IP_TTL_DEFAULT,
        .ip_p   = IPPROTO_ICMP,
        .ip_sum = 0,                          // Filled in at runtime by ip_output
        .ip_src = { .s_bytes = {   0,   0,   0,   0 } },
        .ip_dst = { .s_bytes = { 255, 255, 255, 255 } },
    },
    .np_icmp  = {
        .icmp_type  = ICMP_TYPE_ECHO,
        .icmp_code  = 0,
        .icmp_sum   = 0,                      // Filled in at runtime
        .icmp_id    = 0,
        .icmp_seqno = 0,
    }
};

struct net_packet test_packet_buffer; // No space for actual payload

// Mockup for testing
uint8_t ether_laddr[ETHER_ADDR_LEN] = { 1, 2, 3, 4, 5, 6 };

void eth_output(const void *payload, uint16_t payload_len) {
    // XXX
}

void setup() {
    memcpy(&test_packet_buffer, &test_ip_icmp_packet, sizeof(test_packet_buffer));
    memcpy(test_packet_buffer.np_ether.ether_shost,
           ether_laddr,a
           sizeof(test_packet_buffer.np_ether.ether_shost));
    test_packet_buffer.np_ip.ip_id = 12345; // XXX randomize or something
    test_packet_buffer.np_icmp.icmp_sum
        = ip_checksum(0, &test_packet_buffer.np_icmp, sizeof(test_packet_buffer.np_icmp));

    ip_output(&test_packet_buffer.np_icmp, sizeof(test_packet_buffer.np_icmp));
}



void loop() {
}

