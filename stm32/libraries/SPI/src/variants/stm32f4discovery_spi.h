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

# include <system_init.h>
# include <SPI/spiStruct.h>

# error NOT PORTED YET.

/**
 * Declarations for externally visible SPI init records.
 *
 * STM32F0 has SPI ports 1 and 2.
 */
SPI_INIT_DEFAULT(1);
SPI_INIT_DEFAULT(2);

#define BOARD_SPI_DEFAULT_SS 10 /* XXX: Should be D10 but that is not defined yet */

# ifdef __cplusplus
extern "C" {
# endif

/* Defined in ellduino_spi.cpp */
extern struct SPIdynamicFields _SPI1dynamicFields;
extern struct SPIdynamicFields _SPI2dynamicFields;

# ifdef __cplusplus
}
# endif

DEFINE_SPI_STRUCT(1, A, 15, 0, B,  4, 0, B,  5, 0, B,  3, 0, &_SPI1dynamicFields) ;
DEFINE_SPI_STRUCT(2, B, 12, 0, B, 14, 0, B, 15, 0, B, 13, 0, &_SPI2dynamicFields);

# ifdef __cplusplus

#  include <SPI/SPIClass.h>

extern Pin2Int7 spimap1, spimap2;

static const class SPIClass SPI  (SPI1struct, spimap1);
static const class SPIClass SPI_2(SPI2struct, spimap2);

# endif //__cplusplus

#endif//_ELLDUINO_SPI_H_
