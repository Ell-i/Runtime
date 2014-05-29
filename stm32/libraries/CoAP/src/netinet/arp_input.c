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
 * Minimal standalone ICMP
 *
 * @author: Pekka Nikander <pekka.nikander@ell-i.org>  2014
 */

#include <netinet/net_debug.h>
#include <netinet/ethernet.h>
#include <netinet/ip.h>
#include <netinet/arp.h>
#include <netinet/util.h>

/**
 * XXX
 */

void arp_input(struct arp *const arp) {
#if 0
    /**
     * Verify packet format  XXX revise
     */
    if (arp->arp_hardware_address_space != ARP_HARDWARE_ETHERNET ||
        arp->arp_protocol_address_space != ETHERTYPE_IP)
        return;
#endif

    /*
     * Switch on opcode
     */
    switch (arp->arp_opcode) {
    default:
        // Ignore replies and all other packets.
        net_error("Unknown ARP opcode %d.\n", ntohs(arp->arp_opcode));
        return;
    case CONSTEXPR_HTONS(ARP_OPCODE_REQUEST):
        if (arp->arp_dst_ip_addr != ip_local_address.s_addr) {
            // Not us
            return;
        }
        // The ethernet src and dst have already been swapped
        arp->arp_opcode = CONSTEXPR_HTONS(ARP_OPCODE_REPLY);
        memcpy(arp->arp_dst_eth_addr, arp->arp_src_eth_addr, sizeof(arp->arp_dst_eth_addr));
        memcpy(arp->arp_src_eth_addr, ether_local_address,   sizeof(arp->arp_src_eth_addr));
        arp->arp_dst_ip_addr = arp->arp_src_ip_addr;
        arp->arp_src_ip_addr = ip_local_address.s_addr;
        eth_output(arp, sizeof(struct arp));
        return;
    }
}

