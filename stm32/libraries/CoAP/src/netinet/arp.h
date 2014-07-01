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
 * Minimal standalone ARP
 *
 * @author: Pekka Nikander <pekka.nikander@ell-i.org>  2014
 */

#ifndef  _ARP_H
# define _ARP_H

# include <netinet/ip.h>

struct arp {
    uint16_t  arp_hardware_address_space;
    uint16_t  arp_protocol_address_space;
    uint8_t   arp_hardware_address_length;
    uint8_t   arp_protocol_address_length;
    uint16_t  arp_opcode;
    uint8_t   arp_src_eth_addr[ETHER_ADDR_LEN];
    in_addr_t arp_src_ip_addr;
    uint8_t   arp_dst_eth_addr[ETHER_ADDR_LEN];
    in_addr_t arp_dst_ip_addr;
} __attribute__((packed,aligned(2)));

# define ARP_HARDWARE_ETHERNET 1

# define ARP_OPCODE_REQUEST 1
# define ARP_OPCODE_REPLY   2

/**
 * XXX
 */
extern void arp_input(struct arp *const arp);

#endif //_ARP_H
