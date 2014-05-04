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

#include <netinet/net_debug.h>
#include <netinet/ip.h>
#include <netinet/udp.h>

/**
 * XXX
 */

void udp_input(struct udp *const udp_packet, size_t len) {
#if 0
    /*
     * Verify UDP checksum
     */
    XXX;
#endif

    /* Swap ports */
    register uint16_t dport = udp_packet->udp_dport;
    udp_packet->udp_dport = udp_packet->udp_sport;
    udp_packet->udp_sport = dport;

    /* Find upper layer handler, if any */
    for (const struct udp_socket *socket = __udp_sockets; 
         socket < __udp_sockets_end;
         socket++ /* XXX */) {
        if (socket->udp_port == dport) {
            /* XXX Update statistics */
            const uint16_t payload_len = ntohs(udp_packet->udp_len) - sizeof(struct udp);
            socket->udp_socket_handler(udp_packet->udp_data, payload_len);
            return;
        }
    }
    net_error("Packet to unbound UDP socket %d\n", dport);
}

/**
 * Compute the UDP checksum, taking the addresses for the pseudo
 * header from the IP header.
 *
 * @param ip   IP header for the IP addresses in the UDP pseudo header
 * @param udp  UDP header, followed with the payload
 * @param len  UDP length, passed in register to save memory access
 */
static inline uint16_t
udp_checksum(
    const struct ip *const ip, const struct udp *const udp, const size_t len) {

    /*
     * Phase 1: Compute the pseudo-header checksum, using
     *          parallel 16-bit words in a 32-bit register.
     */

    // Initialize pseudo-header from the end, the UDP length
    register uint32_t checksum = len;

    // Assign a register with the pseudo-header constant value, for
    // using as a register in the ADC instruction below
#   if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#    define UDP_ZEROES_PROTOCOL_SHORT ((IPPROTO_UDP << 8) | 0)
#   else
#    define UDP_ZEROES_PROTOCOL_SHORT ((0 << 8) | IPPROTO_UDP)
#   endif
    register const uint32_t zeroes_protocol = UDP_ZEROES_PROTOCOL_SHORT;

#if defined(__thumb__) && 0//XXX remove zero here once works
# if defined(__ARM_ARCH_6M__)
    // Add IP addresses, as 32-bit entities, using ADC
    register const uint32_t *srcp = &ip->ip_src.s_addr;
    __asm__ (
        XXX DOES NOT WORK, CRASHES.  INVESTIGATE.
        "ldm	%[srcp]!, {r2, r3}\n\t"
        "add	%[checksum], r2\n\t"
        "adc	%[checksum], r3\n\t"
        "adc	%[checksum], %[zeroes_protocol]"
        : [checksum] "+r" (checksum), [srcp] "+r" (srcp)
        : [zeroes_protocol] "r" (zeroes_protocol)
        : "r2", "r3"
        );
# else
#  error "Not implemented for ARMv7 yet.  Please do."
# endif
#else
    checksum += (ip->ip_src.s_addr >> 16) & 0xFFFF;
    checksum += (ip->ip_src.s_addr      ) & 0xFFFF;
    checksum += (ip->ip_dst.s_addr >> 16) & 0xFFFF;
    checksum += (ip->ip_dst.s_addr      ) & 0xFFFF;
    checksum += zeroes_protocol;
#endif
    
    /*
     * Part 2: Compute the checksum over the UDP header and data.
     *         ip_checksum() accepts two parallel 16-bit words in its
     *         first argument.
     */
    checksum = ip_checksum(checksum, udp, len);
    if (checksum == 0)
        checksum = ~0;
    return checksum;
}

/**
 * XXX
 */

void udp_output(const void *payload, size_t payload_len) {
    struct udp *const udp = (struct udp *)((const char *)payload - sizeof(struct udp));
    const uint16_t udp_len = payload_len + sizeof(struct udp);

    udp->udp_len = htons(udp_len);
    udp->udp_sum = 0;
    
    /*
     * Clear the checksum, for now
     */
    udp->udp_sum = 0; // udp_checksum(ip, udp, udp_len);
    /*
     * Pass to lower layer.
     */
    ip_output(udp, udp_len);
}

void udp_echo(uint8_t udp_payload[], uint16_t udp_payload_len) {
    udp_output(udp_payload, udp_payload_len);
}

DEFINE_UDP_SOCKET(UDP_PORT_ECHO, udp_echo);
