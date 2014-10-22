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

#ifndef  _UDP_H
# define _UDP_H

# include <system_init.h>
# include <netinet/util.h>

typedef uint16_t udp_port_t;

# define UDP_PORT_ECHO 7

struct udp {
    udp_port_t udp_sport;
    udp_port_t udp_dport;
    uint16_t   udp_len;
    uint16_t   udp_sum;
    uint8_t    udp_data[0];
};


/**
 * A compile-time allocated const data structure describing an UDP socket.
 *
 * @see DEFINE_UDP_SOCKET
 */

struct udp_socket {
    void (*udp_socket_handler)(uint8_t data[], uint16_t data_len);
    const uint16_t udp_port;
    /* XXX Add pointer to statistics, in RAM */
} __attribute__((aligned(SYSTEM_INIT_ALIGNMENT)));

# ifdef __MACH__
#  define UDP_SOCKET_SECTION(port)  ".text,.socket"
# else
#  define UDP_SOCKET_SECTION(port)  ".socket.udp." # port
# endif

# define __EXPAND_SOCKET_NAME(port) __udp_socket ## port

# define DECLARE_UDP_SOCKET(port)                              \
    extern const struct udp_socket  __EXPAND_SOCKET_NAME(port) \
    __attribute__((section(UDP_SOCKET_SECTION(port)))) 

/**
 * Defines an UDP socket.
 *
 * To define a UDP socket at compile time, use the DEFINE_UDP_SOCKET
 * macro to XXX.
 */

# define DEFINE_UDP_SOCKET(port, handler)                  \
    DECLARE_UDP_SOCKET(port);                              \
    const struct udp_socket __EXPAND_SOCKET_NAME(port)     \
        __attribute__((section(UDP_SOCKET_SECTION(port)))) \
        = {                                                \
        IF(udp_socket_handler) handler,                    \
        IF(udp_port) CONSTEXPR_HTONS(port),                \
    }

extern const struct udp_socket __attribute__((section(UDP_SOCKET_SECTION()))) __udp_sockets[];
extern const struct udp_socket __attribute__((section(UDP_SOCKET_SECTION()))) __udp_sockets_end[];

# ifdef __cplusplus
extern "C" {
# endif
extern void udp_input(struct udp *const udp_packet, size_t len);
extern void udp_output(const void * payload, size_t payload_len);
# ifdef __cplusplus
}
# endif

#endif //_UDP_H
