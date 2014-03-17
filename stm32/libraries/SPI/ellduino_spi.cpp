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

#include "ellduino_spi.h"

/*
 * Boot-time definitions for the STM32F0 series MCU SPI registers.
 */

# ifndef offsetof
#  define offsetof(st, m) ((uint32_t)(&((st *)0)->m))
# endif

# define D16(p, r, v) \
static const uint16_t p ## _ ## r ## _value = v; \
static const uint8_t  p ## _ ## r ## _offset =  offsetof(p, r)/sizeof(uint32_t);

    D16(SPI_TypeDef, CR2,
        0
        | ! SPI_CR2_RXDMAEN    /* Disable RX DMA */
        | ! SPI_CR2_TXDMAEN    /* Disable TX DMA */
        |   SPI_CR2_SSOE       /* NSS output automatically managed by hardware */
        | ! SPI_CR2_NSSP       /* Default: NO NSS pulse */
        | ! SPI_CR2_FRF        /* SPI Motorola mode */
        | ! SPI_CR2_ERRIE      /* Error interrupt disabled */
        | ! SPI_CR2_RXNEIE     /* RX buffer not empty interrupt disabled */
        | ! SPI_CR2_TXEIE      /* TX buffer empty interrupt disabled */
        /* 0111: 8 bits data size */
        |   SPI_CR2_DS_2 | SPI_CR2_DS_1 | SPI_CR2_DS_0
        | ! SPI_CR2_FRXTH      /* 0: RXNE goes high with two bytes */
        | ! SPI_CR2_LDMARX     /* N/A: RX DMA even */
        | ! SPI_CR2_LDMATX     /* N/A: TX DMA even */
        );
    D16(SPI_TypeDef, CR1,
        0
        | ! SPI_CR1_CPHA       /* Data at first edge */
        | ! SPI_CR1_CPOL       /* Clock low when idle */
        |   SPI_CR1_MSTR       /* Master mode */
        |   SPI_CR1_BR_1       /* Clock divider 8 */
        | ! SPI_CR1_SPE        /* SPI disabled until used */
        | ! SPI_CR1_LSBFIRST   /* MSB first */

        |   SPI_CR1_SSI        /* Internal NSS high, needed for master mode */
        |   SPI_CR1_SSM        /* Software Slave management enabled */
        | ! SPI_CR1_RXONLY     /* 0: Full duplex */
        | ! SPI_CR1_CRCL       /* 0: N/A (8-bit CRC length) */
        | ! SPI_CR1_CRCNEXT    /* 0: Transmit TX buffer, not CERC */
        | ! SPI_CR1_CRCEN      /* 0: CRC disabled */
        |   SPI_CR1_BIDIOE     /* 1: Output enabled */
        | ! SPI_CR1_BIDIMODE   /* 0: 2-Line (uni)directional data */
        );

const SystemInitRecordData16Only SPI_INIT_DefaultRecordsData[] = {
    { SPI_TypeDef_CR2_value },
    { SPI_TypeDef_CR1_value },
};

const SystemInitRecordRegisterOffset SPI_INIT_DefaultRecordsOffsets[] = {
    { SPI_TypeDef_CR2_offset },
    { SPI_TypeDef_CR1_offset },
};

/*
 * Boot-time definitions for the STM32F0 series MCU SPIs.
 *
 * These macros here generate SystemInitRecord structures to the
 * SYSTEM_INIT_SECTION linker section.  The boot time initialisation
 * code iterates the records from that section, initialising the MCU
 * peripheral ports accordingly.
 */

DEFINE_SPI_DEVICE(/*SPI*/1, /*APB*/2, SPI_INIT_DefaultRecordsData, SPI_INIT_DefaultRecordsOffsets);
DEFINE_SPI_DEVICE(/*SPI*/2, /*APB*/1, SPI_INIT_DefaultRecordsData, SPI_INIT_DefaultRecordsOffsets);

struct SPIdynamicFields _SPI1dynamicFields;
struct SPIdynamicFields _SPI2dynamicFields;

/**
 * XXX
 */

const void * __SPI1 = &SPI1_INIT;
const void * __SPI2 = &SPI2_INIT;
