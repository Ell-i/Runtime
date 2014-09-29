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
 * @author Pekka Nikander <pekka.nikander@ell-i.org>  2014
 */

#include "variants/stm32f334nucleo_spi.h"

#include "SPIInitSTM32F0.cppinc"

/*
 * Boot-time definitions for the STM32F334 series MCU SPIs.
 *
 * These macros here generate SystemInitRecord structures to the
 * SYSTEM_INIT_SECTION linker section.  The boot time initialisation
 * code iterates the records from that section, initialising the MCU
 * peripheral ports accordingly.
 */

DEFINE_SPI_DEVICE(/*SPI*/1, /*APB*/2,
                  SPI_INIT_STM32F_DefaultRecordsData,
                  SPI_INIT_STM32F_DefaultRecordsOffsets,
                  SPI_INIT_STM32F_DefaultRecordsCount);


struct SPIdynamicFields _SPI1dynamicFields;


/**
 * XXX.  Linking hack, to be removed once linking gets fixed.
 */

const void * __SPI1 = &SPI1_INIT;
