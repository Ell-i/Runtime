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

#include <stddef.h>
#include <CoAP.h>
#include <coap/coap_internal.h>
#include <netinet/udp.h>
#include <netinet/net_debug.h>

CoAPClass CoAP;

/**
 * XXX
 */
    
void coap_input(uint8_t coap_data[], uint16_t coap_data_len) {
    struct coap *const coap = (struct coap *)coap_data;
    register struct coap_hdr *coap_hdr = &coap->coap_hdr;
    register uint8_t *const packet_end = &coap_hdr->coap_vttkl + coap_data_len;
    uint32_t tkl = (coap_hdr->coap_vttkl & COAP_TKL_MASK);
    uint8_t *content_start = coap->coap_token + tkl;
    uint8_t is_confirmable = 0;
    uint8_t coap_error_code;

    switch (coap_hdr->coap_vttkl & COAP_VT_MASK) {
    case COAP_VT_CONFIRMABLE:
        is_confirmable = 1;
        /* Fall through */
    case COAP_VT_NON_CONFIRMABLE:
        break; // Handle the message
    case COAP_VT_ACKNOWLEDGEMENT:
        net_error("CoAP: Ignoring an acknowledgement.\n");
    case COAP_VT_RESET:
        return; // Ignore the message
    }

    if (tkl > COAP_TKL_MAX)
        goto send_reset;

    {
        struct coap_options options = COAP_OPTIONS_INITIALISATION;
        uint32_t option_number = 0;
        uint8_t *option_bytes = content_start;

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

            net_debug("CoAP: Found option %d (len=%d).\n", option_number, option_length);
            
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
#ifndef XXX_LENGTH
#define XXX_LENGTH 256 /* XXX */
#endif
        
        /* Handle GET and PUT requests */
        size_t reply_content_length = XXX_LENGTH; // Total buffer length
        int reply = coap_handle_request(coap_hdr->coap_code, &options, 
                                        option_bytes /*payload*/, packet_end - option_bytes,
                                        content_start, &reply_content_length);
        coap_hdr->coap_code = reply;
        if (reply != COAP_CODE_EMPTY) {
            udp_output(coap, sizeof(struct coap_hdr) + tkl + reply_content_length);
        }
        return;
    }

send_error:
    net_debug("CoAP: Sending a reset on error.\n");
    //XXX;

send_reset:
    net_debug("CoAP: Sending a reset.\n");
    coap_hdr->coap_code = COAP_CODE_EMPTY;
    udp_output(coap, sizeof(struct coap_hdr) + tkl);
}

DEFINE_UDP_SOCKET(UDP_PORT_COAP, coap_input);

