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

#include <netinet/net_debug.h>
#include <netinet/ethernet.h>
#include <netinet/ip.h>
#include <netinet/util.h>

/**
 * XXX
 *
 * The pointed packet MUST be a pointer to inside an Ethernet packet,
 * containing valid Ethernet fields.
 *
 * The payload MUST be aligned at a 4 byte boundary, meaning that
 * the IP header will also be properly aligned at 4 bytes.
 */
void ip_output(const void *payload, uint16_t payload_len) {
    static uint16_t ip_id;

    struct ip *const iph = (struct ip *)((char *)payload - sizeof(struct ip));

    const uint16_t len = payload_len += sizeof(struct ip);

    // XXX Check that the compiler optimises properly
    // XXX Check if passing proto in argument would produce better code
    iph->ip_vhl = IP_VHL_DEFAULT;
#if 0  // Reply with whatever TOS there was
    iph->ip_tos = IP_TOS_DEFAULT; 
#endif
    iph->ip_len = htons(len);
    iph->ip_id  = ip_id++;
    iph->ip_off = IP_OFF_DEFAULT;    // We don't support fragments
    iph->ip_ttl = IP_TTL_DEFAULT;    // Always reply with default TTL
    // Proto MUST be set when calling
    iph->ip_sum = 0; 
    iph->ip_src.s_addr = ip_local_address.s_addr;
    // Dst MUST be set when calling

    iph->ip_sum = ip_checksum(0, iph, sizeof(struct ip));

    /*
     * Pass to lower layer.  NB. Tail call.
     */
    eth_output(iph, len);
}
