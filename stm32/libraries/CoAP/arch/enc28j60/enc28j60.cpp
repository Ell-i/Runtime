/*
 * Copyright 2012 Pekka Nikander.  See NOTICE for licensing information.
 */

#include <assert.h>

#include <ENC28J60Class.h>

#define SPI_XFER_RX(op, reg, xtra)  spiCmd((op) | ((reg) & ENC_REG_MASK), 0, (xtra))
#define SPI_XFER_TX(op, reg, value) spiCmd((op) | ((reg) & ENC_REG_MASK), (value), 0)

/**
 * Switches to the right register bank
 * if not there already
 */
void
ENC28J60Class::set_bank(int bank) const {
    static uint8_t curr = ENC_BANK0; /* Current bank */

    bank &= ENC_BANK_MASK;

    if (curr == bank || bank == ENC_BANK_GEN)
        return;

    register int bank_index = (bank & ENC_BANK_MASK) >> ENC_BANK_SHIFT;
    register int curr_index = (curr & ENC_BANK_MASK) >> ENC_BANK_SHIFT;

    register const int bits_to_clr = (curr_index  & ~bank_index);
    if (bits_to_clr != 0)
        SPI_XFER_TX(ENC_SPI_CLR_BF, E_CON1, bits_to_clr);

    register const int bits_to_set = (~curr_index &  bank_index);
    if (bits_to_set != 0)
        SPI_XFER_TX(ENC_SPI_SET_BF, E_CON1, bits_to_set);

    curr = bank;
}

int
ENC28J60Class::phy_get(enc_reg_t reg) const {
    set_bank(MII_REG_ADR);
    /* Write address and start read */
    SPI_XFER_TX(ENC_SPI_WRITE_REG, MII_REG_ADR, reg & ENC_REG_MASK);
    SPI_XFER_TX(ENC_SPI_WRITE_REG, MII_CMD, MII_CMD_READ);
    set_bank(MII_STAT);
    /* Wait until ready */
    while (SPI_XFER_RX(ENC_SPI_READ_REG, MII_STAT, 1) & MII_STAT_BUSY)
        ;
    set_bank(MII_CMD);
    /* Clear the read command; XXX is this needed? */
    SPI_XFER_TX(ENC_SPI_WRITE_REG, MII_CMD, 0);
    /* Read the value */
    return (SPI_XFER_RX(ENC_SPI_READ_REG, MII_RD_H, 1) << 8) |
            SPI_XFER_RX(ENC_SPI_READ_REG, MII_RD_L, 1);
}

void
ENC28J60Class::phy_set(enc_reg_t reg, int value, bool nowait) const {
    set_bank(MII_REG_ADR);
    SPI_XFER_TX(ENC_SPI_WRITE_REG, MII_REG_ADR, reg & ENC_REG_MASK);
    SPI_XFER_TX(ENC_SPI_WRITE_REG, MII_WR_L, value);
    SPI_XFER_TX(ENC_SPI_WRITE_REG, MII_WR_H, value >> 8);
    if (nowait)
        return;
    set_bank(MII_STAT);
    while (SPI_XFER_RX(ENC_SPI_READ_REG, MII_STAT, 1) & MII_STAT_BUSY)
        ;
}

int
ENC28J60Class::enc_reg_get(enc_reg_t reg) const {
    int xfer_3rd_byte = 0;
    int value;

    switch (reg & ENC_TYPE_MASK) {
    case ENC_BANK2_MREG:
    case ENC_BANK3_MREG:
        xfer_3rd_byte = 1;
        /* FALLTHROUGH */
    case ENC_BANK0:
    case ENC_BANK1:
    case ENC_BANK2:
    case ENC_BANK3:
        set_bank(reg & ENC_BANK_MASK);
        /* FALLTHROUGH */
    case ENC_BANK_GEN:
        value = SPI_XFER_RX(ENC_SPI_READ_REG, reg, xfer_3rd_byte);
        if (reg & ENC_TYPE_LONG)
            value |= SPI_XFER_RX(ENC_SPI_READ_REG, reg+1, xfer_3rd_byte) << 8;
        return value;
    case ENC_BANK_PHY:
        return phy_get(static_cast<enc_reg_t>(reg & ENC_REG_MASK));
        break;
    default:
        abort();
    }
}

void
ENC28J60Class::enc_reg_set(enc_reg_t reg, int value) const {
    switch (reg & ENC_TYPE_MASK) {
    case ENC_BANK2_MREG:
    case ENC_BANK3_MREG:
    case ENC_BANK0:
    case ENC_BANK1:
    case ENC_BANK2:
    case ENC_BANK3:
        set_bank(reg & ENC_BANK_MASK);
        /* FALLTHROUGH */
    case ENC_BANK_GEN:
        SPI_XFER_TX(ENC_SPI_WRITE_REG, reg, value);
        if (reg & ENC_TYPE_LONG)
            SPI_XFER_TX(ENC_SPI_WRITE_REG, reg+1, value >> 8);
        return;
    case ENC_BANK_PHY:
        phy_set(static_cast<enc_reg_t>(reg & ENC_REG_MASK), value, 0);
        return;
    default:
        abort();
    }
}

void
ENC28J60Class::enc_reg_bitop(enc_spi_op_t bitop, enc_reg_t reg, int mask) const {
    assert(bitop == ENC_SPI_SET_BF || bitop == ENC_SPI_CLR_BF);

    switch (reg & ENC_TYPE_MASK) {
    case ENC_BANK0:
    case ENC_BANK1:
    case ENC_BANK2:
    case ENC_BANK3:
        set_bank(reg & ENC_BANK_MASK);
        /* FALLTHROUGH */
    case ENC_BANK_GEN:
        SPI_XFER_TX(bitop, reg, mask);
        if (reg & ENC_TYPE_LONG)
            SPI_XFER_TX(bitop, reg, mask >> 8);
        return;
    case ENC_BANK2_MREG:
    case ENC_BANK3_MREG:
    case ENC_BANK_PHY:
    default:
        abort();
    }
}

