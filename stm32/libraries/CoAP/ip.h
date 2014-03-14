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

#ifndef  _ETHERNET_IP_H
# define _ETHERNET_IP_H

# include <udp.h>
# include <icmp.h>

# define IPPROTO_ICMP  1
# define IPPROTO_UDP  17

typedef uint32_t in_addr_t;

static const in_addr_t IP_ADDRESS_UNSPECIFIED = 0;

struct in_addr {
    union {
        in_addr_t s_addr;
        uint8_t   s_bytes[sizeof(in_addr_t)];
    };
} __attribute__((packed));

extern struct in_addr ip_local_address;

struct ip {
    uint8_t        ip_vhl;
    uint8_t        ip_tos;
    uint16_t       ip_len;
    uint16_t       ip_id;
    union {
        uint16_t       ip_off;
        uint8_t        ip_foff[2];
    };
    uint8_t        ip_ttl;
    uint8_t        ip_p;
    uint16_t       ip_sum;
    struct in_addr ip_src;
    struct in_addr ip_dst;
} __attribute__((packed,aligned(2)));

union iph {
    struct ip iph;
    uint8_t   iph_bytes[0];
    uint16_t  iph_shorts[0];
    // Cannot have longs as must be aligned with 2.
} __attribute__((packed,aligned(2)));

struct ip_packet {
    union iph ip_iph;
    union {
        struct udp   ip_udp;
        struct icmp  ip_icmp;
    };
};

#define IP_VHL_DEFAULT 0x45 /* IPv4, 4*4 = 20 bytes */

#define IP_MSS       576    /* Default segment size */


# ifdef __cplusplus
extern "C" {
# endif
extern void ip_input( struct ip *const ip);
extern void ip_output(const void *payload, uint16_t payload_len /* 0: don't change */);
# ifdef __cplusplus
}
# endif

#endif//_ETHERNET_IP_H
