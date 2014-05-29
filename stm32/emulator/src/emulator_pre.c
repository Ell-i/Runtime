/*
 * Copyright (c) 2013 ELL-i co-operative.
 *
 * This is part of ELL-i software.
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

extern void *const __peripheral_start __attribute__((section(".text,.peripheral")));
void *const __peripheral_start = 0;

#include <assert.h>
#include <netinet/udp.h>

const struct udp_socket __udp_sockets[0] = {};

#include <CoAP.h>

const CoAPURL __coap_urls[0] __attribute__((section(COAP_URL_SECTION("")))) = {};


