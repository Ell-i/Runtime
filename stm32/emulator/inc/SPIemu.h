/*
 * Copyright (c) 2014 ELL-i co-operative.
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

/**
 * @author Pekka Nikander <pekka.nikander@ell-i.org>  2014
 */

#ifndef _SPI_H_
#define _SPI_H_

#include <Register.h>

#ifdef __STM32F051__
# include <stm32f0xx.h>
#endif
#ifdef __STM32F407__
# include <stm32f4xx.h>
#endif


class SerialPeripheralInterface {
public:
    DEFINE_REGISTER(16, SPI, CR1,      0);
    DEFINE_REGISTER(16, SPI, CR2,      0);
    DEFINE_REGISTER(16, SPI, SR,       0);
    DEFINE_REGISTER(16, SPI, DR,       0);
protected:
    SerialPeripheralInterface() {}
public:
    static SerialPeripheralInterface SPI1;
    static SerialPeripheralInterface SPI2;
};

SerialPeripheralInterface *const SPI1 = &SerialPeripheralInterface::SPI1;
SerialPeripheralInterface *const SPI2 = &SerialPeripheralInterface::SPI2;

#endif //_SPI_H_
