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
 * Minimal standalone IPv4
 *
 * @author: Pekka Nikander <pekka.nikander@ell-i.org>  2014
 */

#ifdef EMULATOR
#include <stdio.h>
#define error(...) fprintf(stderr, __VA_ARGS__)
#else
#define error(...)
#endif

#include <ip.h>
#include <ethernet.h>

/**
 * XXX
 *
 * The pointed packet MUST be a pointer to inside an Ethernet packet,
 * containing valid Ethernet fields.
 */
void ip_output(const void *payload, uint16_t payload_len) {
    struct ip *const iph = (struct ip *)((char *)payload - sizeof(struct ip));

    /*
     * Verify source address.
     */
    if (iph->ip_src.s_addr != ip_local_address.s_addr) {
        error("IP dropping wrong source address %d.%d.%d.%d\n",
              iph->ip_src.s_bytes[0], 
              iph->ip_src.s_bytes[1], 
              iph->ip_src.s_bytes[2], 
              iph->ip_src.s_bytes[3]);
        return; // Wrong destiation address -- dropped silently
    }

    /*
     * Cache one's complement of the current checksum
     * in preparing for field updates.
     */

    register uint16_t ip_sum_ = ~(iph->ip_sum);
    /*
     * Set packet length, TTL, and ID, updating the checksum.  
     * See RFC1624.
     *
     * XXX Check the assembly.  Using uint16_t may cause inefficiencies;
     */
    if (0 != payload_len) {
        uint16_t len = payload_len + sizeof(struct ip);
        len = htons(len);

        ip_sum_ += ~(iph->ip_len) + len;
        iph->ip_len = len;
    }

#if 0
    /*
     * Fix TTL and generate a new packet ID, updating the checksum
     */
    XXX;
#endif
    /*
     * Store the updated checksum.
     */
    iph->ip_sum = ~ip_sum_;

    /*
     * Pass to lower layer.
     */
    eth_output(iph, ntohs(iph->ip_len));
}
