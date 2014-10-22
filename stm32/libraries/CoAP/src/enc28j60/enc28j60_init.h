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
 * ENC28J60 interface through the Arduino SPI library
 *
 * @author: Pekka Nikander <pekka.nikander@ell-i.org>  2014
 */

#ifndef  _ENC28J60_INIT_H_
# define _ENC28J60_INIT_H_

inline void
ENC28J60Class::begin() const {
    const device_register_init_static_8bit_t *p;

    spi_master_begin(&ENC28J60_SPI, ss_pin_);

    // XXX reset the device

    while ((reg_get(E_STAT) & E_STAT_CLOCK_READY) == 0) {
        ;
    }

    // XXX CHECK ORDER!
    reg_set(MAC_ADR0, mac_address_[5]);
    reg_set(MAC_ADR1, mac_address_[4]);
    reg_set(MAC_ADR2, mac_address_[3]);
    reg_set(MAC_ADR3, mac_address_[2]);
    reg_set(MAC_ADR4, mac_address_[1]);
    reg_set(MAC_ADR5, mac_address_[0]);

    for (p = enc28j60_init; p < enc28j60_init + enc28j60_init_size; p++) {
        reg_set(p->reg, p->value);
    }

    while (reg_get(PHY_CON1) & PHY_CON1_PRST)
        ;

    reg_set(PHY_CON2, PHY_CON2_HDLDIS);

    enc_buf_value_t b[2] = { ENC_SPI_WRITE_MEM, 0 };

    spi_transfer(b, sizeof(b));

}

// XXX For debugging purposes
inline bool
ENC28J60Class::checkBegin(const uint8_t mac_address[ETH_ADDRESS_LEN]) const {
    const device_register_init_static_8bit_t *p;

    if(reg_get(MAC_ADR0) != mac_address[5]) return false;
    if(reg_get(MAC_ADR1) != mac_address[4]) return false;
    if(reg_get(MAC_ADR2) != mac_address[3]) return false;
    if(reg_get(MAC_ADR3) != mac_address[2]) return false;
    if(reg_get(MAC_ADR4) != mac_address[1]) return false;
    if(reg_get(MAC_ADR5) != mac_address[0]) return false;

    for (p = enc28j60_init + 14;                          //skip buffer pointers
         p < enc28j60_init + enc28j60_init_size - 1; //skip ECON1
         p++) {
        if (reg_get(p->reg) != p->value) return false;
    }

    return true;
}

#endif // _ENC28J60_INIT_H_
