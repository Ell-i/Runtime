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
 * The complete packet structure handled by the Ell-i stack.
 *
 * XXX Add here more documentation how the Ell-i stack handles
 * packets.
 *
 * @author: Pekka Nikander <pekka.nikander@ell-i.org>  2014
 */

#ifndef  _NET_PACKET_H
# define _NET_PACKET_H

#include <netinet/ethernet.h>
#include <netinet/ip.h>
#include <netinet/arp.h>
#include <netinet/udp.h>
#include <netinet/icmp.h>
// #include <netinet/tcp.h>

struct net_packet {
    uint16_t                np_padding;  // For aligning the ip header correctly
    struct ether_header     np_ether;
    union {
        struct arp          np_arp;
        struct {
            struct ip       np_ip;       // Must be 4 bytes aligned
            union {
                struct udp  np_udp;
                struct icmp np_icmp;
            };
        };
    };
} __attribute__((packed));

#endif //_NET_PACKET_H

