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

#ifndef  _ENCX24J600_CONF_H
# define _ENCX24J600_CONF_H

# include <stdlib.h>
# include <stdint.h>

/*
 * ENCX24J600 RX/TX buffer assignment
 *
 * ENCx24J600 can use a TX buffer from anywhere; the RX buffer is
 * at the end of memory, by default at 0x5340, see Section 3.5.2.
 *
 * Use larger than standard Ethernet packet worths for the RX/TX buffer, 0x600 = 1536 bytes
 */

# define MAX_PACKET_SIZE 1536

# define ENC_BUFFER_START 0x0000
# define ENC_BUFFER_SIZE  0x2000
# define ENC_BUFFER_END   0x5FFF

# define RX_BUFFER_START (0x5340) /* Default value */
# define RX_BUFFER_END   (ENC_BUFFER_END)
# define TX_BUFFER_LEN   (0x2000)
# define TX_BUFFER_END   (RX_BUFFER_START)
# define TX_BUFFER_START (TX_BUFFER_END - TX_BUFFER_LEN)

/* Offset added to physical register addresses to fold them into the same address space */
# define ENC_PHY_OFFSET 0xA0 /* See Table 3-1 on page 20.  0x9F is the last SPI SFR */

# define ENC_SFR_REG(number)    ((number))
# define ENC_PHY_REG(number)    ((number) +  ENC_PHY_OFFSET)
# define ENC_IS_PHY_REG(number) ((number) >= ENC_PHY_OFFSET)

/* ESTAT: Ethernet status register.  Page 93. */
enum {
    E_STAT_CLOCK_READY = 0x1000,
};
enum enc_reg_t {
    E_TX_START  = ENC_SFR_REG(0x00),
    E_TX_LEN    = ENC_SFR_REG(0x02),
    E_RX_START  = ENC_SFR_REG(0x04),
    E_RX_TAIL   = ENC_SFR_REG(0x06),
    E_RX_HEAD   = ENC_SFR_REG(0x08),
    E_DMA_START = ENC_SFR_REG(0x0A),
    E_DMA_LEN   = ENC_SFR_REG(0x0C),
    E_DMA_DST   = ENC_SFR_REG(0x0E),
    E_DMA_CS    = ENC_SFR_REG(0x10),
    E_TX_STAT   = ENC_SFR_REG(0x12),
    E_TX_WIRE   = ENC_SFR_REG(0x14),
    E_UDA_START = ENC_SFR_REG(0x16),
    E_UDA_END   = ENC_SFR_REG(0x18),
    E_STAT      = ENC_SFR_REG(0x1A),
    E_IR        = ENC_SFR_REG(0x1C),
    E_CON1      = ENC_SFR_REG(0x1E),

    E_HT1       = ENC_SFR_REG(0x20),
    E_HT2       = ENC_SFR_REG(0x22),
    E_HT3       = ENC_SFR_REG(0x24),
    E_HT4       = ENC_SFR_REG(0x26),
    E_PM_M1     = ENC_SFR_REG(0x28),
    E_PM_M2     = ENC_SFR_REG(0x2A),
    E_PM_M3     = ENC_SFR_REG(0x2C),
    E_PM_M4     = ENC_SFR_REG(0x2E),
    E_PM_CKSUM  = ENC_SFR_REG(0x30),
    E_PM_OFF    = ENC_SFR_REG(0x32),
    E_RX_FCOND  = ENC_SFR_REG(0x34),

    MAC_CON1    = ENC_SFR_REG(0x40),
    MAC_CON2    = ENC_SFR_REG(0x42),
    MAC_BBIPG   = ENC_SFR_REG(0x44),
    MAC_IPG     = ENC_SFR_REG(0x46),
    MAC_CL_CON  = ENC_SFR_REG(0x48),
    MAC_MAX_FL  = ENC_SFR_REG(0x4A),

    MII_CMD     = ENC_SFR_REG(0x52),
    MII_REG_ADR = ENC_SFR_REG(0x54),

    MAC_ADDR3   = ENC_SFR_REG(0x60),
    MAC_ADDR2   = ENC_SFR_REG(0x62),
    MAC_ADDR1   = ENC_SFR_REG(0x64),
    MII_WR      = ENC_SFR_REG(0x66),
    MII_RD      = ENC_SFR_REG(0x68),
    MII_STAT    = ENC_SFR_REG(0x6A),
# define MII_STAT_NVALID    0x04
# define MII_STAT_SCAN      0x02
# define MII_STAT_BUSY      0x01
    E_PAUSE     = ENC_SFR_REG(0x6C),
    E_CON2      = ENC_SFR_REG(0x6E),
    E_RX_WM     = ENC_SFR_REG(0x70),
    E_INT_ENA   = ENC_SFR_REG(0x72),
    E_IDLE_D    = ENC_SFR_REG(0x74),

    E_GP_DATA   = ENC_SFR_REG(0x80), /* 8-bit register, ok to access as 16 bits */
    E_RX_DATA   = ENC_SFR_REG(0x82), /* 8-bit register, ok to access as 16 bits */
    E_UDA_DATA  = ENC_SFR_REG(0x84), /* 8-bit register, ok to access as 16 bits */
    E_GP_RD_PT  = ENC_SFR_REG(0x86),
    E_GP_WR_PT  = ENC_SFR_REG(0x88),
    E_RX_RD_PT  = ENC_SFR_REG(0x8A),
    E_RX_WR_PT  = ENC_SFR_REG(0x8C),
    E_UDA_RD_PT = ENC_SFR_REG(0x8E),
    E_UDA_WR_PT = ENC_SFR_REG(0x90),

    PHY_CON1    = ENC_PHY_REG(0x00),
# define PHY_CON1_PRST      0x8000
# define PHY_CON1_PLOOPBK   0x4000
# define PHY_CON1_PPWRSV    0x0800
# define PHY_CON1_PDPXMD    0x0100
    PHY_STAT1   = ENC_PHY_REG(0x01),
# define PHY_STAT1_PFDPX    0x1000
# define PHY_STAT1_PHDPX    0x0800
# define PHY_STAT1_LLSTAT   0x0004
# define PHY_STAT1_JBSTAT   0x0002
    PHY_AN_A    = ENC_PHY_REG(0x04),
    PHY_AN_LPA  = ENC_PHY_REG(0x05),
    PHY_AN_E    = ENC_PHY_REG(0x06),
    PHY_CON2    = ENC_PHY_REG(0x11),
# define PHY_CON2_FRCLINK   0x4000
# define PHY_CON2_TXDIS     0x2000
# define PHY_CON2_JABBER    0x0400
# define PHY_CON2_HDLDIS    0x0100
    PHY_STAT2   = ENC_PHY_REG(0x1B),
    PHY_STAT3   = ENC_PHY_REG(0x1F),
};

enum enc_spi_op_t {
    ENC_SPI_READ_REG      = 0x00, /* 0x00 - 0x1F */
    ENC_SPI_READ_REG_UB   = 0x20,
    ENC_SPI_WRITE_REG_UB  = 0x22,
    ENC_SPI_SET_BF_UB     = 0x24,
    ENC_SPI_CLR_BF_UB     = 0x26,
    ENC_SPI_READ_MEM      = 0x28, /* Through GP */
    ENC_SPI_WRITE_MEM     = 0x2A, /* Through GP */
    ENC_SPI_READ_RX       = 0x2C,
    ENC_SPI_WRITE_RX      = 0x2E,
    ENC_SPI_READ_UDA      = 0x30,
    ENC_SPI_WRITE_UDA     = 0x32,
    ENC_SPI_WRITE_REG     = 0x40, /* 0x40 - 0x5F */
    ENC_SPI_WRITE_GP_RDP  = 0x60,
    ENC_SPI_READ_GP_RDP   = 0x62,
    ENC_SPI_WRITE_RX_RDP  = 0x64,
    ENC_SPI_READ_RX_RDP   = 0x66,
    ENC_SPI_WRITE_UDA_RPT = 0x68,
    ENC_SPI_READ_UDA_RPT  = 0x6A,
    ENC_SPI_WRITE_GP_WRP  = 0x6C,
    ENC_SPI_READ_GP_WRP   = 0x6E,
    ENC_SPI_WRITE_RX_WRP  = 0x70,
    ENC_SPI_READ_RX_WRP   = 0x72,
    ENC_SPI_WRITE_UDA_WRP = 0x74,
    ENC_SPI_READ_UPDA_WRP = 0x76,
    ENC_SPI_SET_BF        = 0x80, /* 0x80-0x9F */
    ENC_SPI_CLR_BF        = 0xA0, /* 0xA0-0xBF */
    ENC_SPI_BANK0_SELECT  = 0xC0,
    ENC_SPI_BANK1_SELECT  = 0xC2,
    ENC_SPI_BANK2_SELECT  = 0xC4,
    ENC_SPI_BANK3_SELECT  = 0xC6,
    ENC_SPI_BANK_READ     = 0xC8,
    ENC_SPI_RESET         = 0xCA,
    ENC_SPI_SET_PKT_DEC   = 0xCC,

    ENC_SPI_DMA_STOP      = 0xD2,
    ENC_SPI_DMA_CKSUM     = 0xD4,
    ENC_SPI_SET_TX_RTS    = 0xD8,
    ENC_SPI_DMA_CKSUM_S   = 0xDA,
    ENC_SPI_DMA_COPY      = 0xDC,
    ENC_SPI_DMA_COPY_S    = 0xDE,
    ENC_SPI_FC_DISABLE    = 0xE0,
    ENC_SPI_FC_SINGLE     = 0xE2,
    ENC_SPI_FC_MULTIPLE   = 0xE4,
    ENC_SPI_FC_CLEAR      = 0xE6,
    ENC_SPI_ENABLE_RX     = 0xE8,
    ENC_SPI_DISABLE_RX    = 0xEA,
    ENC_SPI_SET_EIE       = 0xEC,
    ENC_SPI_CLR_EIE       = 0xEE,

//    XXX CHECK ABOVE
};

enum E_CON1 {
    MODEXST      = 0x8000,
    HASHEN       = 0x4000,
    HASHOP       = 0x2000,
    HASHLST      = 0x1000,
    AESST        = 0x0800,
    AES_DECRYPT  = 0x0400,
    AES_ENCRYPT  = 0x0200,
    AES_INIT     = 0x0000,
    PKT_DEC      = 0x0100,
    FC_END       = 0x00C0,
    FC_ENABLE    = 0x0080,
    FC_PAUSE     = 0x0040,
    FC_IDLE      = 0x0000,
    DMA_START    = 0x0020,
    DMAST        = 0x0020,
    DMACPY       = 0x0010,
    DMACSSD      = 0x0008,
    DMANOCS      = 0x0004,
    TX_REQUEST   = 0x0002,
    RX_ENABLE    = 0x0001,
    RXEN         = 0x0001,
};

enum E_CON2 {
    ETHEN        = 0x8000,
    STRCH        = 0x4000,
    TXMAC        = 0x2000,
    SHA1MD5      = 0x1000,
    COCON_50     = 0x0F00,
    COCON_100    = 0x0E00,
    COCON_NONE1  = 0x0D00,
    COCON_3125   = 0x0C00,
    COCON_4000   = 0x0B00,
    COCON_5000   = 0x0A00,
    COCON_6250   = 0x0900,
    COCON_8000   = 0x0800,
    COCON_8333   = 0x0700,
    COCON_10000  = 0x0600,
    COCON_12500  = 0x0500,
    COCON_16666  = 0x0400,
    COCON_20000  = 0x0300,
    COCON_25000  = 0x0200,
    COCON_33333  = 0x0100,
    COCON_NONE0  = 0x0000,
    AUTOFC       = 0x0080,
    TX_RESET     = 0x0040,
    RX_RESET     = 0x0020,
    ETH_RESET    = 0x0010,
    MODLEN_1024  = 0x0008,
    MODLEN_768   = 0x0004,
    MODLEN_512   = 0x0000,
    AESLEN_256   = 0x0002,
    AESLEN_192   = 0x0001,
    AESLEN_128   = 0x0000,
};

enum E_RX_FILTER_CON {
    HT_EN        = 0x8000,
    MP_EN        = 0x4000,
    NOT_PM       = 0x1000,
    PM_MAGIC     = 0x0900,
    PM_HASHTABLE = 0x0800,
    PM_NOT_BCAST = 0x0700,
    PM_IS_BCAST  = 0x0600,
    PM_NOT_MCAST = 0x0500,
    PM_IS_MCAST  = 0x0400,
    PM_NOT_UCAST = 0x0300,
    PM_IS_UCAST  = 0x0200,
    PM_ALL       = 0x0100,
    PM_DISABLE   = 0x0000,
    CRC_E_EN     = 0x0080,
    CRC_EN       = 0x0040,
    RUNT_E_EN    = 0x0020,
    RUNT_EN      = 0x0010,
    UC_EN        = 0x0008,
    NOT_ME_EN    = 0x0004,
    MC_EN        = 0x0002,
    BC_EN        = 0x0001,
};

enum E_INT_ENA {
    INT          = 0x8000,
    MODEX        = 0x4000,
    HASH         = 0x2000,
    AES          = 0x1000,
    LINK         = 0x0800,
    PKT          = 0x0040,
    DMA          = 0x0020,
    TX           = 0x0008,
    TX_ABT       = 0x0004,
    RX_ABT       = 0x0002,
    PC_FULL      = 0x0001,
};

typedef uint16_t enc_reg_value_t;
typedef uint8_t  enc_buf_value_t;
typedef size_t   enc_buf_len_t;
typedef uint16_t enc_phy_value_t;

enum enc_rx_packet_status_t {
    ENC_RX_STATUS_LONG_DROP      = 0x0001,
    ENC_RX_STATUS_CARRIER_SEEN   = 0x0004,
    ENC_RX_STATUS_CEC_ERROR      = 0x0010,
    ENC_RX_STATUS_LENGTH_ERROR   = 0x0020,
    ENC_RX_STATUS_LONG_TYPE      = 0x0040,
    ENC_RX_STATUS_RECEIVE_OK     = 0x0080,
    ENC_RX_STATUS_MULTICAST      = 0x0100,
    ENC_RX_STATUS_BROADCAST      = 0x0200,
    ENC_RX_STATUS_DRIBBLE        = 0x0400,
    ENC_RX_STATUS_CONTROL_FRAME  = 0x0800,
    ENC_RX_STATUS_PAUSE_FRAME    = 0x1000,
    ENC_RX_STATUS_UNKNOWN_OPCODE = 0x2000,
    ENC_RX_STATUS_VLAN_FRAME     = 0x4000,
};

/**
 * ENCX24J600 internal RX packet header.
 *
 * Transferred over SPI, see Data Sheet page 33-34
 */

typedef struct encX24j600_register_init_static_16bit {
    enc_reg_t       reg;
    enc_reg_value_t value;
} device_register_init_static_8bit_t;

#endif //_ENCX24J600_CONF_H
