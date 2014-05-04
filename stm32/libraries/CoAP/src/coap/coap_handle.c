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

#include <CoAP.h>
#include <coap/coap_internal.h>
#include <string.h>

/**
 * XXX
 */
int coap_handle_request(
    uint8_t coap_code, 
    const struct coap_options *const options, 
    const uint8_t *const payload,
    size_t payload_length,
    uint8_t *reply_content_buffer, 
    size_t *reply_content_buffer_length) {

    // XXX Replace the linear search with a binary one; see CoAP.h
    for (const CoAPURL *coap_url = __coap_urls; 
         coap_url < __coap_urls_end;
         coap_url++) {

        if (options->uri_path.option_len == coap_url->coap_url_path_length &&
            0 == memcmp(options->uri_path.option_value, coap_url->coap_url_path, 
                        options->uri_path.option_len)) {

            switch (coap_code) {
            case COAP_CODE_GET:
                if (NULL == coap_url->coap_url_get_callback)
                    return COAP_CODE_NOT_ALLOWED;
                return coap_url->coap_url_get_callback(options,
                                                       payload,
                                                       payload_length,
                                                       reply_content_buffer,
                                                       reply_content_buffer_length);
            case COAP_CODE_PUT:
                if (NULL == coap_url->coap_url_put_callback)
                    return COAP_CODE_NOT_ALLOWED;
                return coap_url->coap_url_put_callback(options,
                                                       payload,
                                                       payload_length,
                                                       reply_content_buffer,
                                                       reply_content_buffer_length);
            }
            *reply_content_buffer_length = 0;
            return COAP_CODE_NOT_IMPLEMENTED;
        }
    }
    *reply_content_buffer_length = 0;
    return COAP_CODE_NOT_FOUND; // Send reply
}
