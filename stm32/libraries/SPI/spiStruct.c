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
 * @brief SPI interface for STM32F
 */

#include <spiStruct.h>

void spi_master_begin(const struct SPI *const spi) {
    PinFunctionActivate(&spi->spi_miso_function_);
    PinFunctionActivate(&spi->spi_mosi_function_);
    PinFunctionActivate(&spi->spi_clk_function_);
}

void spi_master_end(const struct SPI *const spi) {
    PinFunctionDeactivate(&spi->spi_miso_function_);
    PinFunctionDeactivate(&spi->spi_mosi_function_);
    PinFunctionDeactivate(&spi->spi_clk_function_);
}
