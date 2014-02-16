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
 * @brief The Arduino Serial class
 */

#include <stm32f0xx.h>
#include <ellduino_gpio.h>   // XXX To be placed into the variant.h!
#include <ellduino_spi.h>  // XXX To be placed into the variant.h!
#include <arduelli_thread.h> // XXX TBD -- is this the right file name?

class SPIClass {
public:
    const SPI spi_;
    constexpr SPIClass(const SPI &);
    void begin(uint32_t ss_pin = SPI1_SS_PIN) const;
};

#define DEFINE_SPI(spi_number, ss_port, ss_pin, ss_af, miso_port, miso_pin, miso_af, mosi_port, mosi_pin, mosi_af, clk_port, clk_pin, clk_af) \
    ({ DEFINE_SPI_STRUCT(spi_number, ss_port, ss_pin, ss_af, miso_port, miso_pin, miso_af, mosi_port, mosi_pin, mosi_af, clk_port, clk_pin, clk_af) })


constexpr SPIClass::SPIClass(const SPI &spi)
    : spi_(spi) {}

void SPIClass::begin(uint32_t ss_pin) const {
    // XXX TBD
}
