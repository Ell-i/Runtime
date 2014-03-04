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
 * Minimal standalone UDP
 *
 * @author: Pekka Nikander <pekka.nikander@ell-i.org>  2014
 */

#include <net_debug.h>
#include <ip.h>
#include <udp.h>

/**
 * XXX
 */

void udp_input(struct udp *const udp_packet) {
#if 0
    /*
     * Verify UDP checksum
     */
    XXX;
#endif

    /* Swap ports */
    register uint16_t dport = udp_packet->udp_dport;
    udp_packet->udp_dport = udp_packet->udp_sport;
    udp_packet->udp_sport = dport;

    /* Find upper layer handler, if any */
    for (const struct udp_socket *socket = __udp_sockets; 
         socket < __udp_sockets_end;
         socket++ /* XXX */) {
        if (socket->udp_port == dport) {
            /* XXX Update statistics */
            const uint16_t payload_len = ntohs(udp_packet->udp_len) - sizeof(struct udp);
            socket->udp_socket_handler(udp_packet->udp_data, payload_len);
            return;
        }
    }
    net_error("Packet to unbound UDP socket %d\n", dport);
}

/**
 * XXX
 */

void udp_output(const void *payload, uint16_t payload_len) {
    struct udp *const udp = (struct udp *)((const char *)payload - sizeof(struct udp));
    const int udp_len = payload_len + sizeof(struct udp);

    udp->udp_len = htons(udp_len);
    
    /*
     * Clear the checksum, for now
     */
    udp->udp_sum = 0;
    /*
     * Pass to lower layer.
     */
    ip_output(udp, udp_len);
}

