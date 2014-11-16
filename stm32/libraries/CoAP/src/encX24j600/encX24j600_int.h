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

#ifndef  _ENCX24J600_INT_H_
# define _ENCX24J600_INT_H_

# include <encX24j600/ENCX24J600.h>

inline void
ENCX24J600Class::enableInterrupt(const enum E_INT_ENA mask) const {
    reg_set_bits(E_INT_ENA, mask);
}

inline void
ENCX24J600Class::disableInterrupt(const enum E_INT_ENA mask) const {
    reg_clr_bits(E_INT_ENA, mask);
}

inline void
ENCX24J600Class::clearInterrupt(const enum E_INT_ENA mask) const {
    reg_clr_bits(E_IR, mask);
}

inline void
ENCX24J600Class::enableGlobalInterrupts(void) const {
    spi_send_single_byte(ENC_SPI_SET_EIE);
}

inline void
ENCX24J600Class::disableGlobalInterrupts(void) const {
    spi_send_single_byte(ENC_SPI_CLR_EIE);
}

#endif //_ENCX24J600_INT_H_
