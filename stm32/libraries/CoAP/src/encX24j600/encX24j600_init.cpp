/*
 * Copyright (c) 2014 ELL-i co-operative
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
 * @author Pekka Nikander <pekka.nikander@ell-i.org>  2014
 * @author Ivan Raul <ivan.raul@ell-i.org> 2014
 *
 * @brief ENC28J60 ethernet interface
 */

#if 0
/* We do want the lower level C API functions inline
   here, even when compiling for the emulator. */
# define ARDUINO_INLINE_API static inline
#endif

#include <encX24j600/ENCX24J600.h>
#include <encX24j600/encX24j600_mac.h>

#define D16(r, v) { .reg = (r), .value = (v) }

const struct encX24j600_register_init_static_16bit ENCX24J600Class::encX24j600_init[] = {

    /**********************************
     * Sestions 8.4 and 8.5: RX and TX buffers
     **********************************/

    /* TX buffer -- not really needed, but we us for backwards compatibility */
    D16(E_TX_START,  TX_BUFFER_START),
    D16(E_TX_LEN,    TX_BUFFER_LEN),
    /* RX buffer */
    D16(E_RX_START,  RX_BUFFER_START),
    D16(E_RX_TAIL,   RX_BUFFER_END & ~0x01), // Clear low-order bit for an even address
    D16(E_RX_HEAD,   RX_BUFFER_START),

    /**********************************
     * Section 8.5: Packet filtering
     **********************************/

    /*
     * Hash-table not used
     */

    /*
     * Filtering configuration.
     */
    D16(E_RX_FCOND,
        0
        | ! HT_EN       /* 0: Hash-table filter disabled */
        | ! MP_EN       /* 0: Magic packet filter disabled */
        | ! NOT_PM      /* 0: Patterh match checksum match required for a match */
        |   PM_DISABLE  /* 0: Pattern matching filter disabled */
        | ! CRC_E_EN    /* 0: Filter disabled */
        |   CRC_EN      /* 1: Packets with an invalid CRC will be discarded  */
        | ! RUNT_E_EN   /* 0: Filter disabled */
        | ! RUNT_EN     /* 0: Discard packets that are 64 bytes or smaller */
        |   UC_EN       /* 1: Unicast with my MAC received */
        | ! NOT_ME_EN   /* 0: Unicast without my MAC discarded */
        | ! MC_EN       /* 0: Multicast disabled */
        |   BC_EN       /* 1: Broadcast enabled */
      ),

    /**********************************
     * Section 8.6 MAC
     **********************************/
    D16(MAC_CON1,
        0
        | ! LOOP_BACK   /* 0: No loopback */
        |   TX_PAUSE    /* 1: Allow sending pause control frames */
        |   RX_PAUSE    /* 1: Adhere received pause control frames */
        | ! PASS_ALL    /* 0: Don't pass control frames to host */
        |   RX_EN       /* 1: Enable the MAC */
        ),
    D16(MAC_CON2,
        0
        | ! DEFER       /* 0: Abort after excessive wait */
        | ! BP_EN       /* 0: Use binary backoff algorithm */
        | ! NO_BKOFF    /* 0: Use binary backoff algorithm */
// res  | ! LONG_PRE    /* 0: Long preambles allowed */
// res  | ! PURE_PRE    /* 0: Don't check preable contents */
        |   PAD_VLAN    /* 101: Pad according to VLAN settings and add CRC */
        |   TX_CRC_EN   /* 1: Enable CRC for Transmit */
        | ! P_HDR_EN    /* 0: No proprietary header */
        | ! HUGE_FRM_EN /* 0: No huge frames */
        |   FR_LEN_CHK  /* 1: Check frame lengths */
        | ! FULL_DUPLEX /* 0: No full duplex (yet) XXX */
      ),
#if 0
    D16(MAC_MAX_FL, 0x05ee), // reset value
#endif


#ifdef old
    XXX
    D8(MAC_BBIP_GAP, 0x12),  /* Recommended back-to-back gap for half duplex XXX */
    D16(MAC_IP_GAP, 0x0C12), /* As recommended in the data sheet */
    // Collision control default values as per data sheet
    // MAC-PHY Support not changed as per data sheet

    // MII Control register not changed as per data sheet
    // MII Command, status, MII reg address and data registers
    // used for MII communication, not initialised.
#endif

    /**********************************
     * MAC address and misc
     **********************************/

#if 0
    MISTAT
    EREVID
    ECOCON
    EFLOCON
    EPAUS
#endif

#ifdef notyet
    /* XXX */
    D16(E_TX_STAT,   XXX),
    D16(E_TX_WIRE,   XXX),
    /* XXX */
    D16(E_UDA_START, 0x0000), // Reset value
    D16(E_UDA_END,   XXX),
    /* XXX */
    D16(E_STAT,      XXX),
    D16(E_IR,        XXX),
    D16(E_CON1,      XXX),
#endif

    /**********************************
     * Control registers
     **********************************/
    D16(E_CON2,
        0
        |   ETHEN             /* 1: Enable Ethernet */
        |   STRCH             /* 1: Stretch events on LEDs to 50 ms */
        | ! TXMAC             /* 0: Do not insert source MAC address to outgoing packets */
        | ! SHA1MD5           /* 1: Use SHA1 in the hashing engine */
        |   COCON_4000        /* 1011: 4 MHz */
        /*
         * NOTE!  Automatic flow control will not work, at least not with
         *        some more configuration somewhere else.
         *
         *        Pekka tried to enable AUTOFC bit back in September 2014,
         *        and ended up hunting for the resulting bug for several
         *        days.  The symptom is that the activity LED flashes quickly
         *        and the packet count in E_STAT does not get updated.
         */
        | ! AUTOFC            /* 0: Enable automatic flow control */
        | ! TX_RESET          /* 0: Normal operation */
        | ! RX_RESET          /* 0: Normal operation */
        | ! ETH_RESET         /* 0: Normal operation */
        |   MODLEN_512        /* 00: 512-bit exponential modulus and operands */
        |   AESLEN_128        /* 10: 128-bit AES */
        ),


    D16(E_INT_ENA,
        0
        |   INT_ENABLE       /* 1: Enable INT pin */
        |   PKT_IE           /* 1: Interrupt on pending packets */
        | ! DMA_IE           /* 0: Disable DMA interrupt */
        |   LINK_IE          /* 1: Interrupt on link status change */
        |   TX_IE            /* 1: Interrupt on transmit ready */
// XXX  |   E_INT_ENA_WOL      /* 1: Enable WOL pin */
        | ! TX_ABT_IE        /* 0: Disable transmit error interrupts */
        | ! RX_ABT_IE        /* 0: Disable receive error interrupts */
        ),

    D16(E_CON1,
        0
        | ! DMA_START    /* 0: Don't use DMA now */
        | ! TX_REQUEST   /* 0: Don't transmit yet */
        |   RX_ENABLE    /* 1: Enable Receiving */
        ),
};

const size_t ENCX24J600Class::encX24j600_init_size = COUNT_OF(ENCX24J600Class::encX24j600_init);

// enc_rx_packet_header_t ENCX24J600Class::rx_header;
