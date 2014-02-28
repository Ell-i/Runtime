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
 * Minimal CoAP
 *
 * @author: Pekka Nikander <pekka.nikander@ell-i.org>  2014
 */

#include <coap_int.h>
#include <udp.h>
#include <stddef.h>

/**
 * XXX
 */
    
void coap_input(void *enclosing_packet, uint8_t coap_packet_data[], uint16_t coap_packet_len) {
    struct udp *const udp_packet = (struct udp *)enclosing_packet;
    struct coap *const coap_packet = (struct coap *)coap_packet_data;
    register struct coap_hdr *coap_hdr = &coap_packet->coap_hdr;
    register uint8_t *const packet_end = &coap_hdr->coap_vttkl + coap_packet_len;
    uint8_t is_confirmable = 0;
    uint8_t coap_error_code;

    switch (coap_hdr->coap_vttkl & COAP_VT_MASK) {
    case COAP_VT_CONFIRMABLE:
        is_confirmable = 1;
        /* Fall through */
    case COAP_VT_NON_CONFIRMABLE:
        break; // Handle the message
    case COAP_VT_ACKNOWLEDGEMENT:
    case COAP_VT_RESET:
        return; // Ignore the message
    }

    register uint32_t tkl = (coap_hdr->coap_vttkl & COAP_TKL_MASK);
    if (tkl > COAP_TKL_MAX)
        goto send_reset;

    {
        struct coap_options options = COAP_OPTIONS_INITIALISATION;
        uint32_t option_number = 0;
        uint8_t *option_bytes = coap_packet->coap_token + tkl;

        while (option_bytes < packet_end && option_bytes[0] != COAP_OPTION_PAYLOAD) {
            uint8_t option_byte   = option_bytes[0];
            int32_t option_delta  = coap_option_dl_value(option_byte >> 4,  &option_bytes);
            int32_t option_length = coap_option_dl_value(option_byte & 0xF, &option_bytes);
            
            if (option_delta < 0 || option_length < 0) {
                goto send_reset; // Message format error
            }

            uint8_t *option_value  = ++option_bytes;
            option_bytes  += option_length;
            option_number += option_delta;
            
            switch (option_number) {
            case COAP_OPTION_URI_PATH:
                options.uri_path.option_len   = option_length;
                options.uri_path.option_value = option_value;
                break;
            case COAP_OPTION_CONTENT_FORMAT:
                options.content_format.option_len   = option_length;
                options.content_format.option_value = option_value;
                break;
            case COAP_OPTION_URI_QUERY:
                options.uri_query.option_len   = option_length;
                options.uri_query.option_value = option_value;
                break;
            case COAP_OPTION_ACCEPT:
                options.accept.option_len   = option_length;
                options.accept.option_value = option_value;
                break;
                
            case COAP_OPTION_IF_MATCH:
            case COAP_OPTION_URI_HOST:
            case COAP_OPTION_ETAG:
            case COAP_OPTION_IF_NONE:
            case COAP_OPTION_URI_PORT:
            case COAP_OPTION_LOCATION_PATH:
            case COAP_OPTION_MAX_AGE:
            case COAP_OPTION_LOCATION_QUERY:
            case COAP_OPTION_PROXY_URI:
            case COAP_OPTION_PROXY_SCHEME:
            case COAP_OPTION_SIZE1:
            default:
                if (!(option_number & COAP_OPTION_CRITICAL))
                    break; // Silently ignored
                if (is_confirmable) {
                    // XXX diagnostic payload as per section 5.5.2
                    coap_error_code = COAP_CODE_BAD_OPTION;
                    goto send_error;
                }
                goto send_reset;
            }
        }

        switch (coap_hdr->coap_code) {
        case COAP_CODE_EMPTY:
        case COAP_CODE_POST:
        case COAP_CODE_DELETE:
            goto send_reset;
        case COAP_CODE_GET:
        case COAP_CODE_PUT:
            break; // Handle the message
        }
        
        /* Handle GET and PUT requests */
        int reply = coap_handle_request(coap_hdr->coap_code, &options, option_bytes /*payload*/);
        if (reply)
            udp_output(udp_packet);
        return;
    }

send_error:
    //XXX;

send_reset:
    //XXX;
    udp_output(udp_packet);
}

DEFINE_UDP_SOCKET(UDP_PORT_COAP, coap_input);

