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
 * @author: Pekka Nikander <pekka.nikander@ell-i.org>  2014
 * @author Ivan Raul <ivan.raul@ell-i.org> 2014
 *
 * @brief ENC28J60 ethernet interface
 */

#include <enc28j60/ENC28J60.h>
#include <netinet/ethernet.h>

void eth_output(const void *payload, uint16_t payload_len) {
   /*
     * XXX
     *
     * This implementation assumes there is free space before the
     * Ethernet Header start to store the command.
     */
    ENC28J60.sendPacket((uint8_t *) payload - ETHER_HEADER_LEN, payload_len + ETHER_HEADER_LEN);
}
