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
 * (Hopefully temporary) W5100 compatibility layer.
 *
 * The Arduino Ethernet library currently depends on a number of
 * W5100-specific types and functions.  However, these seem to be
 * relatively easily abstractable.  At the moment, the abstraction
 * layer is defined in socket.h, as the Socket class.  This file
 * defines W5100 equivalents for the Socket class, so that this
 * version can be directly plugged to the current Ethernet library.
 *
 * @author: Pekka Nikander <pekka.nikander@ell-i.org>  2014
 */

#ifndef _ETHERNET_ARCH_STM32_W5100_H_
#define _ETHERNET_ARCH_STM32_W5100_H

#include <SPI.h>

XXX

class W5100 {
public:
    void init(void) const { Ethernet.init(); };
    // read_data not supported, not used 
    void send_data_processing(SOCKET s, const uint8_t *data, uint16_t len) const {
        s.send(data, len);
    };
    // XXX remains to be seen if send_data_processing_offset is needed
    void receive_data_processing(SOCKET s, uint8_t *data, uint16_t len, uint8_t peek = 0) const {
        s.receive(data, len, peek);
    };

    void setGatewayIp (uint8_t *addr) const { /* XXX not implemented yet */ };
    void getGatewayIp (uint8_t *addr) const { /* XXX not implemented yet */ };
    void setSubnetMask(uint8_t *addr) const { /* XXX not implemented yet */ };
    void getSubnetMask(uint8_t *addr) const { /* XXX not implemented yet */ };

    void setMacAddress(const EthernetAddress *addr) const;
    void getMacAddress(      EthernetAddress *addr) const;

    void setIPAddress( const IPAddress *addr)       const;
    void getIPAddress(       IPAddress *addr)       const;

    void setRetransmissionTime(uint16_t timeout) const { /* XXX not implemented yet */ };
    void setRetransmissionCount(uint8_t timeout) const { /* XXX not implemented yet */ };

    uint16_t getTXFreeSize(SOCKET s);
    uint16_t getRXReceivedSize(SOCKET s);
}

extern class W5100 W5100;

#endif /* _ETHERNET_ARCH_STM32_W5100_H */
