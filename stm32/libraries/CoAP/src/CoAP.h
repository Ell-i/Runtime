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
 * Compile-time-allocation based API for CoAP
 *
 * @author: Pekka Nikander <pekka.nikander@ell-i.org>  2014
 */
#ifndef  _ETHERNET_COAP_API_H
# define _ETHERNET_COAP_API_H

# include <stdint.h>
# include <stddef.h>   // Define size_t
# include <assert.h>

# include <system_init.h>

# include <netinet/ip.h>       // XXX Define in_addr_t, IP_MSS, to be removed
# include <netinet/ethernet.h> // XXX Define ether_header, to be removed

# include <coap/coap_options.h> 
# include <coap/coap_codes.h>


# ifdef __cplusplus
#  include <enc28j60/ENC28J60.h>
# endif

// Define the semantics for the return value
typedef int (*coap_callback)(
    const struct coap_options * input_options,
    const uint8_t *input_buffer, size_t input_length,
    uint8_t *output_buffer, size_t *output_buffer_length);

/*
 * Note that we *must* align the IP header (and subsequent headers) at
 * 4 byte boundary.  However, the Ethernet header is 6+6+2=14 bytes
 * long.  Consequently, we have to align the Ethernet header at
 * two-byte boundary.  Bowing slightly to potential future 64-bit
 * version and IPv6 compatibility, we align the IP header at a 8-byte
 * boundary, leaving two bytes at the beginning of the buffer
 */
#define ALIGNMENT_OFFSET 2

typedef struct CoAPClass {
    // XXX Move to some other header, buffer.h?
    // XXX And define properly
    uint8_t packet_buffer_[
        ALIGNMENT_OFFSET 
        + sizeof(struct ether_header) 
        + IP_MSS]
    __attribute__((aligned(8)));
#define PACKET_BUFFER_SIZE    (sizeof(packet_buffer_) - ALIGNMENT_OFFSET)
#define PACKET_BUFFER_START          (packet_buffer_  + ALIGNMENT_OFFSET)
#define PACKET_BUFFER_ETHER   ((struct ether_header *)PACKET_BUFFER_START)
    
# ifdef __cplusplus
public:
    void begin(in_addr_t ip_address = IP_ADDRESS_UNSPECIFIED) {
        assert(((uint32_t)PACKET_BUFFER_ETHER) % 4 == 2);
        // XXX ENC28J60.begin(ether_local_address);
        ENC28J60.begin();
    }
    void loop(void) {
        if (ENC28J60.availablePackets()) {
            ENC28J60.receivePacket(PACKET_BUFFER_START, PACKET_BUFFER_SIZE);
            eth_input(PACKET_BUFFER_ETHER);
        }
    }
# endif
} CoAPClass;

extern CoAPClass CoAP;

typedef struct {
    const coap_callback              coap_url_get_callback;
    const coap_callback              coap_url_put_callback;
    const char *                     coap_url_path;
    const uint8_t                    coap_url_path_length;
} __attribute__((aligned(SYSTEM_INIT_ALIGNMENT))) CoAPURL;

# ifdef __MACH__
#  define COAP_URL_SECTION(name) ".text,.coapurl"
# else
#  define COAP_URL_SECTION(name) ".coap.url." # name
# endif


# define DEFINE_COAP_URL(name, path, get_callback, put_callback) \
    extern const CoAPURL __coap_url ## name                      \
    __attribute__((section(COAP_URL_SECTION(name))));            \
    const CoAPURL __coap_url ## name                             \
    = {                                                          \
        IF(coap_url_get_callback) get_callback,                  \
        IF(coap_url_put_callback) put_callback,                  \
        IF(coap_url_path) path,                                  \
        IF(coap_url_path_length) sizeof(path) - 1,               \
    }                                                            \

extern const CoAPURL __coap_urls[];
extern const CoAPURL __coap_urls_end[];

#endif //_ETHERNET_COAP_API_H
