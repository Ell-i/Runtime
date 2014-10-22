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
 * Minimal standalone ICMP
 *
 * @author: Pekka Nikander <pekka.nikander@ell-i.org>  2014
 */

#include <netinet/net_debug.h>
#include <netinet/ip.h>
#include <netinet/icmp.h>

/**
 * XXX
 */
void icmp_input(struct icmp *const icmp, size_t icmp_len) {
    net_error("ICMP type %d.\n", icmp->icmp_type);
    switch (icmp->icmp_type) {
    case ICMP_TYPE_ECHO:
        icmp->icmp_type = ICMP_TYPE_ECHO_REPLY;
        ip_checksum_update(&icmp->icmp_sum, ICMP_TYPE_ECHO, ICMP_TYPE_ECHO_REPLY);
        break;
    default:
        net_error("Unknown ICMP type %d.\n", icmp->icmp_type);
        // Drop silently
        return;
    }
    ip_output(icmp, icmp_len);
}

