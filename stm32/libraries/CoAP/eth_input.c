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
 * Minimal Ethernet 
 *
 * @author: Pekka Nikander <pekka.nikander@ell-i.org>  2014
 */

#ifdef EMULATOR
#include <stdio.h>
#define error(...) fprintf(stderr, __VA_ARGS__)
#else
#define error(...)
#endif

#include <ethernet.h>
#include <arp.h>
#include <ip.h>
#include <util.h>

/**
 * XXX
 */

void eth_input(struct ether_header *const ether) {

#if 0
    /*
     * Verify destination address.
     */
    XXX;
#endif

    /*
     * Swap source and destination address for return packet.
     *
     * If the upper layers need the src/dst information, they 
     * must be written with this swapping in mind.
     */
    // XXX Check that the following produces optimal code.  Revise if not.
    //     Write in assembler if needed.
    register uint32_t word0 = ether->ether_longs[0];
    register uint32_t word1 = ether->ether_longs[1];
    register uint32_t word2 = ether->ether_longs[2];
    ether->ether_longs[0] = (word1 << 16) | ((word2 >> 16) & 0xFFFF);
    ether->ether_longs[1] = (word2 << 16) | ((word0 >> 16) & 0xFFFF);
    ether->ether_longs[2] = (word0 << 16) | ((word1 >> 16) & 0xFFFF);

    /*
     * Pass to the upper layer
     */
    switch (ether->ether_type) {
    case CONSTEXPR_NTOHS(ETHERTYPE_IP):
        ip_input ((struct ip *) ((char *)ether + ETHER_HEADER_LEN));
        return;
    case CONSTEXPR_NTOHS(IPPROTO_ICMP):
        arp_input((struct arp *)((char *)ether + ETHER_HEADER_LEN));
        return;
    default:
        error("Unknown protocol %d.\n", ether->ether_type);
        return; // Unknown protocol -- dropped silently
    }
}

