/*
 * Copyright (c) 2013-2014 ELL-i co-operative.
 *
 * This is part of ELL-i software.
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

#ifndef  _REGISTER_SPI_SR_H_
# define _REGISTER_SPI_SR_H_

# include <Register.h>
# include <Register_SPI_DR.h>

class Register_SPI_SR : public Register {
    Register_SPI_DR & dr_;
public:
    Register_SPI_SR(Register_SPI_DR &dr)
        : Register("SPI", "SR", 16, 0)
        , dr_(dr)
        {}
    uint32_t operator = (uint32_t arg);
    uint16_t operator & (uint16_t) const;
    uint16_t operator & (uint32_t) const;
};

#endif //_REGISTER_SPI_SR_H_
