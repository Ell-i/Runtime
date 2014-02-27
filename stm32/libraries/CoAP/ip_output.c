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

#include <ip.h>
#include <ethernet.h>

/**
 * XXX
 *
 * The pointed packet MUST be a pointer to inside an Ethernet packet,
 * containing valid Ethernet fields.
 */
void ip_output(struct ip_packet *const ip_packet) {
    struct ip *const iph = &(ip_packet->ip_iph.iph);

#if 0
    /*
     * Fix TTL and generate a new packet ID, updating the checksum
     */
    XXX;
#endif

#if 1
    /*
     * Verify source address.
     */
    if (iph->ip_src != 0/*XXX*/) {
        // XXX Reply with ICMP destination unreachable?
        return; // Wrong destiation address -- dropped silently
    }
#endif
    /*
     * Pass to lower layer.
     */
    struct eth *const eth = (struct eth *)(((char *)iph) - sizeof(struct ether_header));
    eth_output(eth);
}
