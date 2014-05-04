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

#ifndef  _COAP_CODES_H
# define _COAP_CODES_H

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

#endif //_COAP_CODES_H
