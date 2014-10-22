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
 * Minimal standalone UDP
 *
 * @author: Pekka Nikander <pekka.nikander@ell-i.org>  2014
 */

#ifndef  _ETHERNET_H_
# define _ETHERNET_H_

# include <stdint.h>

# define ETHER_ADDR_LEN 6

/**
 * Local host Ethernet address.  
 *
 * While it would be more efficient to have a compiled-in ethernet
 * address, we cannot support that at the moment.  XXX WHY? Explain.
 */
extern uint8_t ether_local_address[ETHER_ADDR_LEN];

/// XXXXXXX CLEAN UP THE FOLLOWING

struct ether_header_real {
    uint8_t  ether_dhost[ETHER_ADDR_LEN];
    uint8_t  ether_shost[ETHER_ADDR_LEN];
    uint16_t ether_type;
} __attribute__((packed));

struct ether_header {
    union {
        struct {
            uint8_t  ether_dhost[ETHER_ADDR_LEN];
            uint8_t  ether_shost[ETHER_ADDR_LEN];
        };
        struct {
            uint16_t ether_addrs[2*ETHER_ADDR_LEN/sizeof(uint16_t)];
        };
    };
    uint16_t ether_type;
} __attribute__((packed));

# define ETHER_HEADER_LEN  (2 * ETHER_ADDR_LEN + sizeof(uint16_t))

# define ETHERTYPE_IP      0x0800
# define ETHERTYPE_ARP     0x0806
# define ETHERTYPE_IPV6    0x86dd

# ifdef __cplusplus
extern "C" {
# endif
extern void eth_input(struct ether_header *const eth_packet);
extern void eth_output(const void *payload, uint16_t payload_len);
# ifdef __cplusplus
}
# endif

#endif //_ETHERNET_H_
