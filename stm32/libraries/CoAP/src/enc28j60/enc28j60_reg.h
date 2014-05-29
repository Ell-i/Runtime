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

#ifndef  _ENC28J60_REG_H_
# define _ENC28J60_REG_H_


# define SPI_XFER_RX(op, reg, xtra)  spi_command((op) | ((reg) & ENC_REG_MASK), 0, (xtra))
# define SPI_XFER_TX(op, reg, value) spi_command((op) | ((reg) & ENC_REG_MASK), (value), 0)

inline int
ENC28J60Class::reg_get(enc_reg_t reg) const {
    int xfer_3rd_byte = 0;
    int value = 0;

    spi_master_activate(ss_pin_);

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
        if (reg & ENC_TYPE_LONG) {
            value |= SPI_XFER_RX(ENC_SPI_READ_REG, reg+1, xfer_3rd_byte) << 8;
        }
        break;
    case ENC_BANK_PHY:
        value = phy_get(static_cast<enc_reg_t>(reg & ENC_REG_MASK));
        break;
    default:
        abort();
    }

    spi_master_deactivate(ss_pin_);
    
    return value;
}

inline void 
ENC28J60Class::reg_set_inner(enc_reg_t reg, int value) const {
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
        break;
    case ENC_BANK_PHY:
        phy_set(static_cast<enc_reg_t>(reg & ENC_REG_MASK), value, 0);
        break;
    default:
        abort();
    }
}

inline void
ENC28J60Class::reg_set(enc_reg_t reg, int value) const {
    spi_master_activate(ss_pin_);
    reg_set_inner(reg, value);
    spi_master_deactivate(ss_pin_);
}

inline void
ENC28J60Class::reg_bitop(enc_spi_op_t bitop, enc_reg_t reg, int mask) const {
    //assert(bitop == ENC_SPI_SET_BF || bitop == ENC_SPI_CLR_BF);

    spi_master_activate(ss_pin_);

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
        break;
    case ENC_BANK2_MREG:
    case ENC_BANK3_MREG:
    case ENC_BANK_PHY:
    default:
        abort();
    }

    spi_master_deactivate(ss_pin_);
}

/**
 * Switches to the right register bank
 * if not there already
 */
inline void
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

inline int
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

inline void
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

#endif //_ENC28J60_REG_H_
