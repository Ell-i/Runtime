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

#ifndef  _COAP_OPTIONS_H
# define _COAP_OPTIONS_H

struct coap_option {
    uint8_t  option_len;
    uint8_t *option_value;
};

struct coap_options {
    struct coap_option uri_path;
    struct coap_option uri_query;
    struct coap_option content_format;
    struct coap_option accept;
};

# define COAP_OPTIONS_INITIALISATION { { 0, NULL }, { 0, NULL }, { 0, NULL }, { 0, NULL } }

# define COAP_OPTION_DELTA(b)     (((b) >> 4) & 0x0f)
# define COAP_OPTION_LENGTH(b)    (((b) >> 0) & 0x0f)
# define COAP_OPTION_DL_EXT1      13
# define COAP_OPTION_DL_EXT2      14
# define COAP_OPTION_DL_PAYLOAD   15

# define COAP_OPTION_PAYLOAD      0xff

# define COAP_OPTION_IF_MATCH        1
# define COAP_OPTION_URI_HOST        3
# define COAP_OPTION_ETAG            4
# define COAP_OPTION_IF_NONE         5
# define COAP_OPTION_URI_PORT        7
# define COAP_OPTION_LOCATION_PATH   8
# define COAP_OPTION_URI_PATH       11
# define COAP_OPTION_CONTENT_FORMAT 12
# define COAP_OPTION_MAX_AGE        14
# define COAP_OPTION_URI_QUERY      15
# define COAP_OPTION_ACCEPT         17
# define COAP_OPTION_LOCATION_QUERY 20
# define COAP_OPTION_PROXY_URI      35
# define COAP_OPTION_PROXY_SCHEME   39
# define COAP_OPTION_SIZE1          60

# define COAP_OPTION_CRITICAL     0x01

# define COAP_FORMAT_TEXT_PLAIN          0
# define COAP_FORMAT_APPLICATION_LINK   40
# define COAP_FORMAT_APPLICATION_XML    41
# define COAP_FORMAT_APPLICATION_STREAM 42
# define COAP_FORMAT_APPLICATION_EXI    47
# define COAP_FORMAT_APPLICATION_JSON   50

/**
 * XXX
 * @param  v  option delta or length, must be 0-15
 * @param  p  pointer to a pointer to the next byte, may get incremented
 * @return -1 if a payload marker is detected
 */
static inline int32_t coap_option_dl_value(const uint8_t v, uint8_t ** p) {
    const uint16_t *const ext2 = (const uint16_t *)(*p);
    switch (v) {
    case COAP_OPTION_DL_EXT1:    (*p)++;    return **p   - 13;
    case COAP_OPTION_DL_EXT2:    (*p) += 2; return *ext2 - 269;
    case COAP_OPTION_DL_PAYLOAD:            return -1;
    default:                                return v;
    }
}

#endif //_COAP_OPTIONS_H

