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

#include <SPI.h>
#include <ENC28J60.h>
#include <ethernet.h>

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

