/*
 * Copyright (c) 2014 ELL-i co-operative
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
 *
 * @brief The Arduino library SPI class
 */

#ifndef _SPI_CLASS_H_
#define _SPI_CLASS_H_

#include <SPI/spiStruct.h>
#include <SPI/spiAPI.h>
#if defined(ELLI_STM32F051_ELLDUINO)
# include <ellduino_gpio.h>   // XXX To be placed into the variant.h!
#elif defined(ELLI_STM32F407_DISCOVERY)
# include <stm32f4discovery_gpio.h>
#else
# error "The SPI library is not yet supported with this board."
#endif
#include <wiring_digital.h>
#include <TinyMap.h>

#ifndef BOARD_SPI_DEFAULT_SS
#define BOARD_SPI_DEFAULT_SS 10 /* XXX */
#endif

enum SPITransferMode {
    SPI_CONTINUE,
    SPI_LAST
};

enum SPIBitOrder {
    MSBFIRST = !SPI_CR1_LSBFIRST,
    LSBFIRST =  SPI_CR1_LSBFIRST,
};

enum SPIClockDivider {
    SPI_CLOCK_DIV2   = !SPI_CR1_BR_2 | !SPI_CR1_BR_1 | !SPI_CR1_BR_0,
    SPI_CLOCK_DIV4   = !SPI_CR1_BR_2 | !SPI_CR1_BR_1 |  SPI_CR1_BR_0,
    SPI_CLOCK_DIV8   = !SPI_CR1_BR_2 |  SPI_CR1_BR_1 | !SPI_CR1_BR_0,
    SPI_CLOCK_DIV16  = !SPI_CR1_BR_2 |  SPI_CR1_BR_1 |  SPI_CR1_BR_0,
    SPI_CLOCK_DIV32  =  SPI_CR1_BR_2 | !SPI_CR1_BR_1 | !SPI_CR1_BR_0,
    SPI_CLOCK_DIV64  =  SPI_CR1_BR_2 | !SPI_CR1_BR_1 |  SPI_CR1_BR_0,
    SPI_CLOCK_DIV128 =  SPI_CR1_BR_2 |  SPI_CR1_BR_1 | !SPI_CR1_BR_0,
    SPI_CLOCK_DIV256 =  SPI_CR1_BR_2 |  SPI_CR1_BR_1 |  SPI_CR1_BR_0,
};

enum SPIDataMode {
    SPI_MODE0 = !SPI_CR1_CPHA | !SPI_CR1_CPOL,
    SPI_MODE1 =  SPI_CR1_CPHA | !SPI_CR1_CPOL,
    SPI_MODE2 = !SPI_CR1_CPHA |  SPI_CR1_CPOL,
    SPI_MODE3 =  SPI_CR1_CPHA |  SPI_CR1_CPOL,
};


/**
 * Type for mapping Arduino PIN numbers to SPI CR1 register values.
 */
typedef TinyMap<uint8_t,uint32_t,7> Pin2Int7;

//XXX TODO: Figure out a better implementation for setClock

class SPIClass {
public:
    const struct SPI &spi_;
    constexpr SPIClass(const SPI &spi, Pin2Int7 &ssPinCR1) : spi_(spi), ssPinCR1_(ssPinCR1) {};
    void begin(const uint8_t ss_pin = BOARD_SPI_DEFAULT_SS) const {
        spi_master_begin(&spi_, ss_pin);
        // Sigh.  While this fixes the initialisation, it generates huge tables?
        ssPinCR1_[ss_pin] = 0
                            | ! SPI_CR1_CPHA       /* Data at first edge */
                            | ! SPI_CR1_CPOL       /* Clock low when idle */
                            |   SPI_CR1_MSTR       /* Master mode */
                            |   SPI_CR1_BR_1       /* Clock divider 8 */
                            |   SPI_CR1_SPE        /* SPI enabled */
                            | ! SPI_CR1_LSBFIRST   /* MSB first */

                            |   SPI_CR1_SSI        /* Internal NSS high, needed for master mode */
                            |   SPI_CR1_SSM        /* Software Slave management enabled */
                            | ! SPI_CR1_RXONLY     /* 0: Full duplex */
                            | ! SPI_CR1_CRCL       /* 0: N/A (8-bit CRC length) */
                            | ! SPI_CR1_CRCNEXT    /* 0: Transmit TX buffer, not CERC */
                            | ! SPI_CR1_CRCEN      /* 0: CRC disabled */
                            |   SPI_CR1_BIDIOE     /* 1: Output enabled */
                            | ! SPI_CR1_BIDIMODE   /* 0: 2-Line (uni)directional data */
                            ;

    };

    void end(const uint8_t ss_pin = BOARD_SPI_DEFAULT_SS) const {
        spi_master_end(&spi_, ss_pin);
    };

    void setBitOrder(const SPIBitOrder bitOrder) const {
        setBitOrder(BOARD_SPI_DEFAULT_SS, bitOrder);
    }
    void setBitOrder(const uint8_t ss_pin, const SPIBitOrder bitOrder) const {
        ssPinCR1_[ss_pin] &= ~SPI_CR1_LSBFIRST;
        ssPinCR1_[ss_pin] |=  bitOrder;
    }

    uint32_t setClockDivider(const SPIClockDivider clockDivider) const {
        return setClockDivider(BOARD_SPI_DEFAULT_SS, clockDivider);
    }
    uint32_t setClockDivider(const uint8_t ss_pin, const SPIClockDivider clockDivider) const {
        uint32_t oldValue = ssPinCR1_[ss_pin] & SPI_CR1_BR;
        ssPinCR1_[ss_pin] &= ~SPI_CR1_BR;
        ssPinCR1_[ss_pin] |= clockDivider;
        return oldValue;
    }

    uint32_t setClock(const uint32_t hertz) const {
        return setClock(BOARD_SPI_DEFAULT_SS, hertz);
    }
    uint32_t setClock(const uint8_t ss_pin, const uint32_t hertz) const {
        // XXX Begin rewrite below
        uint32_t outputHertz = SystemCoreClock>>1;
        uint8_t wantedDivider = 0;
        SPIClockDivider wantedDividerEnum;

        if (hertz<outputHertz)
        {
            for (wantedDivider=1; wantedDivider < 7; wantedDivider++){
                outputHertz>>=1;
                if (hertz >= outputHertz) break;
            }
        }

        //XXX There should be a better way than typecasting.
        wantedDividerEnum =  static_cast<SPIClockDivider>(wantedDivider<<3);
        setClockDivider(ss_pin, wantedDividerEnum);
        // XXX End rewrite above
        return outputHertz;
    }

    void setDataMode(SPIDataMode dataMode) const {
        setDataMode(BOARD_SPI_DEFAULT_SS, dataMode);
    }
    void setDataMode(uint8_t ss_pin, SPIDataMode dataMode) const {
        ssPinCR1_[ss_pin] &= ~(SPI_CR1_CPHA | SPI_CR1_CPOL);
        ssPinCR1_[ss_pin] |=  dataMode;
    }

    uint8_t transfer(uint8_t data, SPITransferMode mode = SPI_LAST) const {
        return transfer(BOARD_SPI_DEFAULT_SS, data, mode);
    }

    uint8_t transfer(uint8_t ss_pin, uint8_t data, SPITransferMode mode = SPI_LAST) const {
        return transfer(ss_pin, &data, 1, mode);
    }

    uint8_t transfer(uint8_t ss_pin, uint8_t data[], uint8_t len,
                     SPITransferMode mode = SPI_LAST) const {
        // Lower slave select
        digitalWrite(ss_pin, 0);

        const uint32_t cr1 = ssPinCR1_[ss_pin];

        len = spi_transfer_raw(&spi_, cr1, data, len, 1);

        if (mode == SPI_LAST) {
            // Rise slave select
            digitalWrite(ss_pin, 1);
        }

        return len;
    };
private:
    Pin2Int7 &ssPinCR1_;
};

#endif//_SPI_CLASS_H_
