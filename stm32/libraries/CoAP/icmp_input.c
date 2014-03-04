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

#include <net_debug.h>
#include <ip.h>
#include <icmp.h>

// XXX Move elsewhere?  ip.h
static inline void chksum_update(uint16_t *const chksump, uint16_t oldvalue, uint16_t newvalue) {
    register uint16_t sum_; // 1's complement of the sum
    sum_     = ~(*chksump); // Fetch old sum and complement.
    sum_    += ~oldvalue + newvalue;
    *chksump = ~sum_;       // Complement and store new sum.
    
}

/**
 * XXX
 */
void icmp_input(struct icmp *const icmp) {
    net_error("ICMP type %d.\n", icmp->icmp_type);
    switch (icmp->icmp_type) {
    case ICMP_TYPE_ECHO:
        icmp->icmp_type = ICMP_TYPE_ECHO_REPLY;
        // Fix checksum 
        chksum_update(&icmp->icmp_sum, ICMP_TYPE_ECHO, ICMP_TYPE_ECHO_REPLY);
        break;
    default:
        net_error("Unknown ICMP type %d.\n", icmp->icmp_type);
        // Drop silently
        return;
    }
    ip_output(icmp, 0 /* Don't update ip->ip_len */);
}

