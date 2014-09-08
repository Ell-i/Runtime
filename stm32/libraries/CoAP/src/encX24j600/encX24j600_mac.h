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
 * ENCx24J600 driver
 *
 * @author: Pekka Nikander <pekka.nikander@ell-i.org>  2014
 */

#ifndef  _ENCX24J600_MAC_H
# define _ENCX24J600_MAC_H

enum MAC_CON1 {
    LOOPBK       = 0x10,
    LOOP_BACK    = 0x10,
    RXPAU        = 0x04,
    RX_PAUSE     = 0x04,
    PASSALL      = 0x02,
    PASS_ALL     = 0x02,
};

enum MAC_CON2 {
    DEFER        = 0x4000,
    BPEN         = 0x2000,
    BP_EN        = 0x2000,
    NOBKOFF      = 0x1000,
    NO_BKOFF     = 0x1000,
//  LONG_PRE       0x0200 reserved
//  PURE_PRE       0x0100 reserved

    PAD_64       = 0x00E0,
    PAD_VLAN     = 0x00A0,
    //             0x0060 is redunant
    PAD_60       = 0x0020,
    PAD_NONE     = 0x0000,
    PADCFG_EN    = 0x0020,

    TXCRCEN      = 0x0010,
    TX_CRC_EN    = 0x0010,
    PHDREN       = 0x0008,
    P_HDR_EN     = 0x0008,
    HFRMEN       = 0x0004,
    HUGE_FRM_EN  = 0x0004,
//  FR_LEN_CHK     0x0002 reserved
    FULDPX       = 0x0001,
    FULL_DUPLEX  = 0x0001,
};

// XXX TBD
# define MII_CMD_SCAN       0x02
# define MII_CMD_READ       0x01

#endif //_ENCX24J600_MAC_H
