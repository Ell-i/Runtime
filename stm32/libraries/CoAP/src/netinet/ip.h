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

#ifndef  _IP_H_
# define _IP_H_

# include <stdint.h>
# include <stddef.h>

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
} __attribute__((packed,aligned(4)));

union iph {
    struct ip iph;
    uint8_t   iph_bytes[0];
    uint16_t  iph_shorts[0];
    uint32_t  iph_longs[0];
} __attribute__((packed,aligned(4)));

# define IP_VHL_DEFAULT 0x45 /* IPv4, 4*4 = 20 bytes */
# define IP_TOS_DEFAULT 0x0  /* XXX define */
# define IP_OFF_DEFAULT CONSTEXPR_HTONS(0x4000)
# define IP_TTL_DEFAULT 64    /* Default TTL, from RFC1340 */

# define IP_MSS         576    /* Default segment size */

# ifdef __cplusplus
extern "C" {
# endif

extern void ip_input( struct ip *const ip);
extern void ip_output(const void *payload, uint16_t payload_len);
extern uint16_t ip_checksum(uint32_t seed, const void *data, size_t data_len);

/**
 * XXX
 */
static inline void ip_checksum_update(
    uint16_t *const chksump, uint16_t oldvalue, uint16_t newvalue) {
    register uint16_t sum_; // 1's complement of the sum
    sum_     = ~(*chksump); // Fetch old sum and complement.
    sum_    += -oldvalue + newvalue;
    *chksump = ~sum_;       // Complement and store new sum.
    
}

# ifdef __cplusplus
}
# endif

#endif //_IP_H_
