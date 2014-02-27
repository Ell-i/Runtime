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

typedef struct {
    const uint8_t coap_content_format;
    const uint8_t coap_content_template[]; /* NUL terminated */
} CoAPContentTemplate;

typedef struct {
    const uint8_t *coap_url_path;
    //XXX;
} CoAPGetURL;

# define DEFINE_COAP_FORMAT_TEMPLATE(format, template) \
    {                                                  \
        IF(coap_content_format) format,                \
        IF(coap_content_template) template,            \
    }                                                  \

# define DEFINE_COAP_GET_URL(path, callback, content_format_template_pairs) \
    XXX

#endif //_ETHERNET_COAP_API_H
