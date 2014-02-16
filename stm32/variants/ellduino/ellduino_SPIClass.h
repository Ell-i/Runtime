/*
 * Copyright (c) 2014 ELL-i co-operative.
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
 * along with ELL-i software.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

/*
 * Authors:  Pekka Nikander <pekka.nikander@ell-i.org>  2014
 */

#ifndef _ELLDUINO_SPICLASS_H_
#define _ELLDUINO_SPICLASS_H_

#include "Arduino_SPI.h"

static const class SPIClass SPI   DEFINE_SPI(1, A, 15, 0, B,  4, 0, B,  5, 0, B,  3, 0);
static const class SPIClass SPI_2 DEFINE_SPI(2, B, 12, 0, B, 14, 0, B, 15, 0, B, 12, 0);

#endif //_ELLDUINO_SPICLASS_H_
