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

#ifndef  _COAP_INTERNAL_H
# define _COAP_INTERNAL_H

# include <stdint.h>
# include <coap/coap_options.h>
# include <coap/coap_codes.h>

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

# define DEFINE_COAP_VT(v, t)     (((v) & 0x3) << 6 | ((t) & 0x3) << 4)

# define COAP_VT_CONFIRMABLE      DEFINE_COAP_VT(1, 0)
# define COAP_VT_NON_CONFIRMABLE  DEFINE_COAP_VT(1, 1)
# define COAP_VT_ACKNOWLEDGEMENT  DEFINE_COAP_VT(1, 2)
# define COAP_VT_RESET            DEFINE_COAP_VT(1, 3)
# define COAP_VT_MASK             DEFINE_COAP_VT(~0,~0)

# define COAP_TKL_MIN             0x00
# define COAP_TKL_MAX             0x08
# define COAP_TKL_MASK            0x0f

# ifdef __cplusplus
extern "C" {
# endif
extern void coap_input(uint8_t data[], uint16_t coap_data_len);
extern int  coap_handle_request(uint8_t coap_code, const struct coap_options *options, 
                                const uint8_t *payload, size_t payload_length,
                                uint8_t *reply_content, size_t *reply_content_length);
# ifdef __cplusplus
}
# endif

#endif //_COAP_INTERNAL_H
