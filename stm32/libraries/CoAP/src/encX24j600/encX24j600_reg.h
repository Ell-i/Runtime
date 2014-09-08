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
 * @brief ENCX24J600 ethernet interface
 */

#ifndef  _ENCX24J600_REG_H_
# define _ENCX24J600_REG_H_


inline int
ENCX24J600Class::reg_get(enc_reg_t reg) const {
    register int value;

    spi_master_activate(ss_pin_);

    if (!ENC_IS_PHY_REG(reg)) {
        value = spi_transfer_4bytes(ENC_SPI_READ_REG_UB, reg, 0/*dummy*/);
    } else {
        value = phy_get(static_cast<enc_reg_t>(reg - ENC_PHY_OFFSET));
    }

    spi_master_deactivate(ss_pin_);

    return value;
}

inline void
ENCX24J600Class::reg_set(enc_reg_t reg, int value) const {
    spi_master_activate(ss_pin_);

    if (!ENC_IS_PHY_REG(reg)) {
        spi_transfer_4bytes(ENC_SPI_WRITE_REG_UB, reg, value);
    } else {
        phy_set(static_cast<enc_reg_t>(reg - ENC_PHY_OFFSET), value, 0);
    }

    spi_master_deactivate(ss_pin_);
}

inline void
ENCX24J600Class::reg_clr_bits(enc_reg_t reg, int mask) const {
    spi_master_activate(ss_pin_);
    spi_transfer_4bytes(ENC_SPI_CLR_BF_UB, reg, mask);
    spi_master_deactivate(ss_pin_);
}

inline void
ENCX24J600Class::reg_set_bits(enc_reg_t reg, int mask) const {
    spi_master_activate(ss_pin_);
    spi_transfer_4bytes(ENC_SPI_SET_BF_UB, reg, mask);
    spi_master_deactivate(ss_pin_);
}

inline int
ENCX24J600Class::phy_get(uint8_t reg) const {
    // XXX TODO
    return 0;
}

inline void
ENCX24J600Class::phy_set(uint8_t reg, int value, bool nowait) const {
    // XXX TODO
#if 0
    OLD CODE
    SPI_XFER_TX(ENC_SPI_WRITE_REG, MII_REG_ADR, reg);
    SPI_XFER_TX(ENC_SPI_WRITE_REG, MII_WR_L, value);
    SPI_XFER_TX(ENC_SPI_WRITE_REG, MII_WR_H, value >> 8);
    if (nowait)
        return;
    set_bank(MII_STAT);
    while (SPI_XFER_RX(ENC_SPI_READ_REG, MII_STAT, 1) & MII_STAT_BUSY)
        ;
#endif
}

#endif //_ENCX24J600_REG_H_
