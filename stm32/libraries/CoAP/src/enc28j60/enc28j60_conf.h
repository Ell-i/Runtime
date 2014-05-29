/*
 * Copyright 2014 Pekka Nikander.  See NOTICE for licensing information.
 */

#ifndef  _ENC28J60_CONF_H
# define _ENC28J60_CONF_H

# include <stdlib.h>
# include <stdint.h>

/*
 * ENC28J60 RX/TX buffer assignment
 *
 * The RX buffer should start at zero. See Rev. B4 Silicon Errata.
 *
 * Leave one Ethernet packet worth for the TX buffer, 0x600 = 1536 bytes
 */
# define MAX_PACKET_SIZE 0x0600

# define RX_BUFFER_START (ENC_BUFFER_START)
# define RX_BUFFER_END   (TX_BUFFER_START - 1)
# define TX_BUFFER_START (ENC_BUFFER_START + ENC_BUFFER_SIZE - MAX_PACKET_SIZE)
# define TX_BUFFER_END   (ENC_BUFFER_START + ENC_BUFFER_SIZE)

# define ETH_ADDRESS_LEN 6

# define ENC_BUFFER_START 0x0000
# define ENC_BUFFER_SIZE  0x2000

enum enc_bank_t {
# define ENC_BANK_SHIFT 5
    ENC_BANK0      = 0x00,
    ENC_BANK1      = 0x20,
    ENC_BANK2      = 0x40,
    ENC_BANK3      = 0x60,
    ENC_BANK_FLAG0 = 0x80,
    ENC_BANK_GEN   = ENC_BANK_FLAG0 | ENC_BANK0,
    ENC_BANK2_MREG = ENC_BANK_FLAG0 | ENC_BANK2,
    ENC_BANK3_MREG = ENC_BANK_FLAG0 | ENC_BANK3,
    ENC_BANK_MASK  = ENC_BANK0 | ENC_BANK1 | ENC_BANK2 | ENC_BANK3,
    /* 16-bit constants for 16-bit registers */
    ENC_BANK_PHY   = 0x100,
    ENC_TYPE_LONG  = 0x200, /* NB. Not in TYPE_MASK! */
    ENC_TYPE_MASK  = ENC_BANK_PHY | ENC_BANK_FLAG0 | ENC_BANK_MASK,
};

# define ENC_REG_MASK 0x1F

# define ENC_GEN_REG(number)    (ENC_BANK_GEN   | (number))
# define ENC_BANK0__REG(number) (ENC_BANK0      | (number))
# define ENC_BANK0_LREG(number) (ENC_BANK0      | (number) | ENC_TYPE_LONG)
# define ENC_BANK1__REG(number) (ENC_BANK1      | (number))
# define ENC_BANK1_LREG(number) (ENC_BANK1      | (number) | ENC_TYPE_LONG)
# define ENC_BANK2__REG(number) (ENC_BANK2      | (number))
# define ENC_BANK2_MREG(number) (ENC_BANK2_MREG | (number))
# define ENC_BANK2LMREG(number) (ENC_BANK2_MREG | (number) | ENC_TYPE_LONG)
# define ENC_BANK3__REG(number) (ENC_BANK3      | (number))
# define ENC_BANK3_MREG(number) (ENC_BANK3_MREG | (number))
# define ENC_BANK3LMREG(number) (ENC_BANK3_MREG | (number) | ENC_TYPE_LONG)
# define ENC_PHY_REG(number)    (ENC_BANK_PHY   | (number))

enum enc_reg_t {
    E_INT_ENA     = ENC_GEN_REG(0x1B),
# define E_INT_ENA_INT        0x80
# define E_INT_ENA_PKT        0x40
# define E_INT_ENA_DMA        0x20
# define E_INT_ENA_LINK       0x10
# define E_INT_ENA_TX         0x08
# define E_INT_ENA_WOL        0x04
# define E_INT_ENA_TX_ERR     0x02
# define E_INT_ENA_RX_ERR     0x01

    E_INT_REQ     = ENC_GEN_REG(0x1C),
# define E_INT_REQ_PKT        0x40
# define E_INT_REQ_DMA        0x20
# define E_INT_REQ_LINK       0x10
# define E_INT_REQ_TX         0x08
# define E_INT_REQ_WOL        0x04
# define E_INT_REQ_TX_ERR     0x02
# define E_INT_REQ_RX_ERR     0x01

    E_STAT        = ENC_GEN_REG(0x1D),
# define E_STAT_INT           0x80
# define E_STAT_LATE_COL      0x10
# define E_STAT_RX_BUSY       0x04
# define E_STAT_TX_ABORT      0x02
# define E_STAT_CLOCK_READY   0x01

    E_CON2        = ENC_GEN_REG(0x1E),
# define E_CON2_AUTO_INC      0x80
# define E_CON2_PKT_DEC       0x40
# define E_CON2_POWER_SAVE    0x20
# define E_CON2_VR_POWER_SAVE  0x08
    E_CON1        = ENC_GEN_REG(0x1F),
# define E_CON1_TX_RESET      0x80
# define E_CON1_RX_RESET      0x40
# define E_CON1_DMA_START     0x20
# define E_CON1_CSUM_ENABLE   0x10
# define E_CON1_TX_REQUEST    0x08
# define E_CON1_RX_ENABLE     0x04
# define E_CON1_B_SEL1        0x02
# define E_CON1_B_SEL0        0x01

    E_RD_PTR      = ENC_BANK0_LREG(0x00),
    E_RD_PTR_L    = ENC_BANK0__REG(0x00),
    E_RD_PTR_H    = ENC_BANK0__REG(0x01),
    E_WR_PTR      = ENC_BANK0_LREG(0x02),
    E_WR_PTR_L    = ENC_BANK0__REG(0x02),
    E_WR_PTR_H    = ENC_BANK0__REG(0x03),
    E_TX_STA      = ENC_BANK0_LREG(0x04),
    E_TX_STA_L    = ENC_BANK0__REG(0x04),
    E_TX_STA_H    = ENC_BANK0__REG(0x05),
    E_TX_END      = ENC_BANK0_LREG(0x06),
    E_TX_END_L    = ENC_BANK0__REG(0x06),
    E_TX_END_H    = ENC_BANK0__REG(0x07),
    E_RX_STA      = ENC_BANK0_LREG(0x08),
    E_RX_STA_L    = ENC_BANK0__REG(0x08),
    E_RX_STA_H    = ENC_BANK0__REG(0x09),
    E_RX_END      = ENC_BANK0_LREG(0x0A),
    E_RX_END_L    = ENC_BANK0__REG(0x0A),
    E_RX_END_H    = ENC_BANK0__REG(0x0B),
    E_RX_RD_PTR   = ENC_BANK0_LREG(0x0C),
    E_RX_RD_PTR_L = ENC_BANK0__REG(0x0C),
    E_RX_RD_PTR_H = ENC_BANK0__REG(0x0D),
    E_RX_WR_PTR   = ENC_BANK0_LREG(0x0E),
    E_RX_WR_PTR_L = ENC_BANK0__REG(0x0E),
    E_RX_WR_PTR_H = ENC_BANK0__REG(0x0F),
    E_DMA_STA     = ENC_BANK0_LREG(0x10),
    E_DMA_STA_L   = ENC_BANK0__REG(0x10),
    E_DMA_STA_H   = ENC_BANK0__REG(0x11),
    E_DMA_END     = ENC_BANK0_LREG(0x12),
    E_DMA_END_L   = ENC_BANK0__REG(0x12),
    E_DMA_END_H   = ENC_BANK0__REG(0x13),
    E_DMA_DST     = ENC_BANK0_LREG(0x14),
    E_DMA_DST_L   = ENC_BANK0__REG(0x14),
    E_DMA_DST_H   = ENC_BANK0__REG(0x15),
    E_DMA_CS      = ENC_BANK0_LREG(0x16),
    E_DMA_CS_L    = ENC_BANK0__REG(0x16),
    E_DMA_CS_H    = ENC_BANK0__REG(0x17),

    E_HT0         = ENC_BANK1__REG(0x00),
    E_HT1         = ENC_BANK1__REG(0x01),
    E_HT2         = ENC_BANK1__REG(0x02),
    E_HT3         = ENC_BANK1__REG(0x03),
    E_HT4         = ENC_BANK1__REG(0x04),
    E_HT5         = ENC_BANK1__REG(0x05),
    E_HT6         = ENC_BANK1__REG(0x06),
    E_HT7         = ENC_BANK1__REG(0x07),
    E_PM_M0       = ENC_BANK1__REG(0x08),
    E_PM_M1       = ENC_BANK1__REG(0x09),
    E_PM_M2       = ENC_BANK1__REG(0x0A),
    E_PM_M3       = ENC_BANK1__REG(0x0B),
    E_PM_M4       = ENC_BANK1__REG(0x0C),
    E_PM_M5       = ENC_BANK1__REG(0x0D),
    E_PM_M6       = ENC_BANK1__REG(0x0E),
    E_PM_M7       = ENC_BANK1__REG(0x0F),
    E_PM_CHSUM    = ENC_BANK1_LREG(0x10),
    E_PM_CHSUM_L  = ENC_BANK1__REG(0x10),
    E_PM_CHSUM_H  = ENC_BANK1__REG(0x11),
    E_PM_OFF      = ENC_BANK1_LREG(0x14),
    E_PM_OFF_L    = ENC_BANK1__REG(0x14),
    E_PM_OFF_H    = ENC_BANK1__REG(0x15),
    E_WOL_IE      = ENC_BANK1__REG(0x16),
    E_WOL_IR      = ENC_BANK1__REG(0x17),
    E_RX_FCOND    = ENC_BANK1__REG(0x18),
# define E_RX_FCOND_UC_EN     0x80
# define E_RX_FCOND_AND_OR    0x40
# define E_RX_FCOND_CRC_EN    0x20
# define E_RX_FCOND_PM_EN     0x10
# define E_RX_FCOND_MP_EN     0x08
# define E_RX_FCOND_HT_EN     0x04
# define E_RX_FCOND_MC_EN     0x02
# define E_RX_FCOND_BC_EN     0x01
    E_PKT_CNT     = ENC_BANK1__REG(0x19),

    MAC_CON1      = ENC_BANK2_MREG(0x00),
# define MAC_CON1_LOOP_BACK   0x10
# define MAC_CON1_TX_PAUSE    0x08
# define MAC_CON1_RX_PAUSE    0x04
# define MAC_CON1_PASS_ALL    0x02
# define MAC_CON1_RX_EN       0x01
    MAC_CON2      = ENC_BANK2_MREG(0x01),
# define MAC_CON2_MAC_RST     0x80
# define MAC_CON2_RND_RST     0x40
# define MAC_CON2_RX_RST      0x08
# define MAC_CON2_RX_FUN_RST  0x04
# define MAC_CON2_TX_RST      0x02
# define MAC_CON2_TX_FUN_RST  0x01
    MAC_CON3      = ENC_BANK2_MREG(0x02),
# define MAC_CON3_PAD_CRC_2   0x80
# define MAC_CON3_PAD_CRC_1   0x40
# define MAC_CON3_PAD_CRC_0   0x20
# define MAC_CON3_TX_CRC_EN   0x10
# define MAC_CON3_PHDR_LEN    0x08
# define MAC_CON3_HUGE_FRAMES 0x04
# define MAC_CON3_FR_LEN_CHK  0x02
# define MAC_CON3_FULL_DPX    0x01
    MAC_CON4      = ENC_BANK2_MREG(0x03),
# define MAC_CON4_DEFER       0x40
# define MAC_CON4_BP_EN       0x20
# define MAC_CON4_NO_BKOFF    0x10
# define MAC_CON4_LONG_PRE    0x02
# define MAC_CON4_PURE_PRE    0x01
    MAC_BBIP_GAP  = ENC_BANK2_MREG(0x04),
    MAC_IP_GAP    = ENC_BANK2LMREG(0x06),
    MAC_IP_GAP_L  = ENC_BANK2_MREG(0x06),
    MAC_IP_GAP_H  = ENC_BANK2_MREG(0x07),
    MAC_COL_CON1  = ENC_BANK2_MREG(0x08),
    MAC_COL_CON2  = ENC_BANK2_MREG(0x09),
    MAC_MAX_FRAME   = ENC_BANK2LMREG(0x0A),
    MAC_MAX_FRAME_L = ENC_BANK2_MREG(0x0A),
    MAC_MAX_FRAME_H = ENC_BANK2_MREG(0x0B),
    MAC_PHY_SUP   = ENC_BANK2_MREG(0x0D),
# define MAC_PHY_SUP_RSTINTFC 0x80
# define MAC_PHY_SUP_RSTRMII  0x40

    MII_CON       = ENC_BANK2_MREG(0x11),
    MII_CMD       = ENC_BANK2_MREG(0x12),
# define MII_CMD_SCAN       0x02
# define MII_CMD_READ       0x01
    MII_REG_ADR   = ENC_BANK2_MREG(0x14),
    MII_WR        = ENC_BANK2LMREG(0x16),
    MII_WR_L      = ENC_BANK2_MREG(0x16),
    MII_WR_H      = ENC_BANK2_MREG(0x17),
    MII_RD        = ENC_BANK2LMREG(0x18),
    MII_RD_L      = ENC_BANK2_MREG(0x18),
    MII_RD_H      = ENC_BANK2_MREG(0x19),

    /* NB.  Note the peciular order. */
    MAC_ADR1        = ENC_BANK3_MREG(0x00),
    MAC_ADR0        = ENC_BANK3_MREG(0x01),
    MAC_ADR3        = ENC_BANK3_MREG(0x02),
    MAC_ADR2        = ENC_BANK3_MREG(0x03),
    MAC_ADR5        = ENC_BANK3_MREG(0x04),
    MAC_ADR4        = ENC_BANK3_MREG(0x05),

    E_BSTSD       = ENC_BANK3__REG(0x06),
    E_BSTCON      = ENC_BANK3__REG(0x07),
    E_BSTCSL      = ENC_BANK3__REG(0x08),
    E_BSTCSH      = ENC_BANK3__REG(0x09),

    MII_STAT      = ENC_BANK3_MREG(0x0A),
# define MII_STAT_NVALID    0x04
# define MII_STAT_SCAN      0x02
# define MII_STAT_BUSY      0x01

    E_REVID       = ENC_BANK3__REG(0x12),
    E_COCON       = ENC_BANK3__REG(0x15),
    E_FLOCON      = ENC_BANK3__REG(0x17),
    E_PAUSL       = ENC_BANK3__REG(0x18),
    E_PAUSH       = ENC_BANK3__REG(0x19),

    PHY_CON1      = ENC_PHY_REG(0x00),
# define PHY_CON1_PRST      0x8000
# define PHY_CON1_PLOOPBK   0x4000
# define PHY_CON1_PPWRSV    0x0800
# define PHY_CON1_PDPXMD    0x0100

    PHY_STAT1     = ENC_PHY_REG(0x01),
# define PHY_STAT1_PFDPX    0x1000
# define PHY_STAT1_PHDPX    0x0800
# define PHY_STAT1_LLSTAT   0x0004
# define PHY_STAT1_JBSTAT   0x0002

    PHY_HID1      = ENC_PHY_REG(0x02),
    PHY_HID2      = ENC_PHY_REG(0x03),
    PHY_CON2      = ENC_PHY_REG(0x10),
# define PHY_CON2_FRCLINK   0x4000
# define PHY_CON2_TXDIS     0x2000
# define PHY_CON2_JABBER    0x0400
# define PHY_CON2_HDLDIS    0x0100
    PHY_STAT2     = ENC_PHY_REG(0x11),
    PHY_IE        = ENC_PHY_REG(0x12),
    PHY_IR        = ENC_PHY_REG(0x13),
    PHY_LCON      = ENC_PHY_REG(0x14),
};

enum enc_spi_op_t {
    ENC_SPI_READ_REG  = 0x00,
    ENC_SPI_READ_MEM  = 0x3A,
    ENC_SPI_WRITE_REG = 0x40,
    ENC_SPI_WRITE_MEM = 0x7A,
    ENC_SPI_SET_BF    = 0x80,
    ENC_SPI_CLR_BF    = 0xA0,
    ENC_SPI_RESET     = 0xFF,
};

typedef uint8_t  enc_reg_value_t, enc_buf_value_t;
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
 * ENC28J60 internal RX packet header.
 *
 * Transferred over SPI, see Data Sheet page 33-34
 */

typedef struct enc28j60_register_init_static_8bit {
    enc_reg_t       reg;
    enc_reg_value_t value;
} device_register_init_static_8bit_t;

//XXX This is no longer used, needs to be removed, for reference meanwhile
# ifdef __cplusplus
extern "C" {
# endif

//XXX packed to prevent any padding
typedef struct __attribute__((__packed__)) enc_rx_packet_header {
    uint8_t    rx_cmd;
    uint16_t   rx_next;
    uint16_t   rx_length;      /* Length of the received frame */
    uint16_t   rx_status;
} enc_rx_packet_header_t;


# ifdef __cplusplus
} // extern "C"
# endif

#endif //_ENC28J60_CONF_H
