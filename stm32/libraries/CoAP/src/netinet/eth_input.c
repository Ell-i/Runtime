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

#include <netinet/net_debug.h>
#include <netinet/ethernet.h>
#include <netinet/ip.h>
#include <netinet/arp.h>
#include <netinet/util.h>

uint8_t ether_local_address[ETHER_ADDR_LEN] = { 0, 0, 0, 0, 0, 0 }; // XXX better default?

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
    register uint16_t d0 = ether->ether_addrs[0];
    register uint16_t d1 = ether->ether_addrs[1];
    register uint16_t d2 = ether->ether_addrs[2];
    ether->ether_addrs[0] = ether->ether_addrs[3];
    ether->ether_addrs[1] = ether->ether_addrs[4];
    ether->ether_addrs[2] = ether->ether_addrs[5];
    ether->ether_addrs[3] = d0;
    ether->ether_addrs[4] = d1;
    ether->ether_addrs[5] = d2;

    /*
     * Pass to the upper layer
     */
    switch (ether->ether_type) {
    case CONSTEXPR_HTONS(ETHERTYPE_IP):
        ip_input ((struct ip *) ((char *)ether + ETHER_HEADER_LEN));
        return;
    case CONSTEXPR_HTONS(ETHERTYPE_ARP):
        arp_input((struct arp *)((char *)ether + ETHER_HEADER_LEN));
        return;
    default:
        net_error("Unknown ethernet protocol %d.\n", ether->ether_type);
        return; // Unknown protocol -- dropped silently
    }
}

