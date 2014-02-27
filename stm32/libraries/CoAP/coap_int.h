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

#ifndef _ETHERNET_COAP_H
#define _ETHERNET_COAP_H

# include <stdint.h>

# define UDP_PORT_COAP 5683

struct coap_hdr {
    uint8_t  coap_vttkl;
    uint8_t  coap_code;
    uint16_t coap_id;
};

struct coap {
    union {
        struct coap_hdr coap_hdr;
        uint32_t        coap_hdr_long;
    };
    uint8_t coap_token[0];
};

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

# define DEFINE_COAP_VT(v, t)     (((v) & 0x3) << 6 | ((t) & 0x3) << 4)

# define COAP_VT_CONFIRMABLE      DEFINE_COAP_VT(1, 0)
# define COAP_VT_NON_CONFIRMABLE  DEFINE_COAP_VT(1, 1)
# define COAP_VT_ACKNOWLEDGEMENT  DEFINE_COAP_VT(1, 2)
# define COAP_VT_RESET            DEFINE_COAP_VT(1, 3)
# define COAP_VT_MASK             DEFINE_COAP_VT(~0,~0)

# define COAP_TKL_MIN             0x00
# define COAP_TKL_MAX             0x08
# define COAP_TKL_MASK            0x0f

# define DEFINE_COAP_CODE(h, l)   (((h) & 0x7) << 5 | ((l) & 0x1f))

# define COAP_CODE_CLASS_REQUEST  DEFINE_COAP_CODE(0, 0)
# define COAP_CODE_CLASS_SUCCESS  DEFINE_COAP_CODE(2, 0)
# define COAP_CODE_CLASS_C_ERROR  DEFINE_COAP_CODE(4, 0)
# define COAP_CODE_CLASS_S_ERROR  DEFINE_COAP_CODE(5, 0)
# define COAP_CODE_CLASS_MASK     DEFINE_COAP_CODE(~0,0)

# define COAP_CODE_EMPTY          DEFINE_COAP_CODE(0, 00)
# define COAP_CODE_GET            DEFINE_COAP_CODE(0, 01)
# define COAP_CODE_POST           DEFINE_COAP_CODE(0, 02)
# define COAP_CODE_PUT            DEFINE_COAP_CODE(0, 03)
# define COAP_CODE_DELETE         DEFINE_COAP_CODE(0, 04)

# define COAP_CODE_CREATED        DEFINE_COAP_CODE(2, 01)
# define COAP_CODE_DELETED        DEFINE_COAP_CODE(2, 02)
# define COAP_CODE_VALID          DEFINE_COAP_CODE(2, 03)
# define COAP_CODE_CHANGED        DEFINE_COAP_CODE(2, 04)
# define COAP_CODE_CONTENT        DEFINE_COAP_CODE(2, 05)

# define COAP_CODE_BAD_REQUEST    DEFINE_COAP_CODE(4, 00)
# define COAP_CODE_UNAUTHORIZED   DEFINE_COAP_CODE(4, 01)
# define COAP_CODE_BAD_OPTION     DEFINE_COAP_CODE(4, 02)
# define COAP_CODE_FORBIDDEN      DEFINE_COAP_CODE(4, 03)
# define COAP_CODE_NOT_FOUND      DEFINE_COAP_CODE(4, 04)
# define COAP_CODE_NOT_ALLOWED    DEFINE_COAP_CODE(4, 05)
# define COAP_CODE_NOT_ACCEPTABLE DEFINE_COAP_CODE(4, 06)
# define COAP_CODE_PRECOND_FAILED DEFINE_COAP_CODE(4, 12)
# define COAP_CODE_TOO_LARGE      DEFINE_COAP_CODE(4, 13)
# define COAP_CODE_UNSUPP_FORMAT  DEFINE_COAP_CODE(4, 15)

# define COAP_CODE_SERVER_ERROR    DEFINE_COAP_CODE(5, 00)
# define COAP_CODE_NOT_IMPLEMENTED DEFINE_COAP_CODE(5, 01)
# define COAP_CODE_BAD_GATEWAY     DEFINE_COAP_CODE(5, 02)
# define COAP_CODE_SERV_UNAVAIL    DEFINE_COAP_CODE(5, 03)
# define COAP_CODE_GATEWAY_TIMEOUT DEFINE_COAP_CODE(5, 04)
# define COAP_CODE_PROXY_NOT_SUPP  DEFINE_COAP_CODE(5, 05)

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

# ifdef __cplusplus
extern "C" {
# endif
extern void coap_input(void *enclosing_packet, uint8_t data[], uint16_t coap_packet_len);
extern int  coap_handle_request(uint8_t coap_code, struct coap_options *options, uint8_t *payload);
# ifdef __cplusplus
}
# endif

#endif//_ETHERNET_COAP_H
