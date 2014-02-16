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

#ifndef _ELLDUINO_SPI_H_
# define _ELLDUINO_SPI_H_

# include <arduelli_spi.h>

/**
 * Declarations for externally visible SPI init records.
 *
 * STM32F0 has SPI ports 1 and 2.
 */
SPI_INIT_DEFAULT(1);
SPI_INIT_DEFAULT(2);

#define SPI1_SS_PIN 10 /* XXX: Should be D10 but that is not defined yet */

#endif//_ELLDUINO_SPI_H_
