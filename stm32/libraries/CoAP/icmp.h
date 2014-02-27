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

#ifndef  _ETHERNET_ICMP_H
# define _ETHERNET_ICMP_H

# include <system_init.h>

struct icmp {
    uint16_t icmp_sport;
    uint16_t icmp_dport;
    uint16_t icmp_len;
    uint16_t icmp_sum;
    uint8_t  icmp_data[0];
};

/**
 * XXX
 */

extern const struct icmp_socket {
    void (*icmp_socket_handler)(void *enclosing, uint8_t data[], uint16_t len);
    const uint16_t icmp_port;
    /* XXX Add statistics */
} icmp_sockets[], icmp_sockets_end[];

# ifdef __MACH__
#  define ICMP_SOCKET_SECTION(port)  ".text,.socket"
# else
#  define ICMP_SOCKET_SECTION(port)  ".socket.icmp." # port
# endif

# define DEFINE_ICMP_SOCKET(port, handler)               \
    const struct icmp_socket __icmp_port ## port          \
    __attribute__((section(ICMP_SOCKET_SECTION(port))))  \
        = {                                             \
        IF(icmp_socket_handler) handler,                 \
        IF(icmp_port) port,                              \
    }

/**
 * XXX
 *
 * The pointed packet MUST be a pointer to inside an Ethernet packet,
 * containing valid IP and Ethernet frames.
 */
extern void icmp_output(struct icmp *const icmp_packet);

/**
 * XXX
 */
extern void icmp_input(struct icmp *const icmp_packet);

#endif //_ETHERNET_ICMP_H
