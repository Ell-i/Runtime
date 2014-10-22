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

#include <SPI/spiStruct.h>
#if defined(ELLI_STM32F051_ELLDUINO)
# include <variants/ellduino_encX24j600.h>    // XXX To be placed into the variant.h!
#elif defined(ELLI_STM32F407_DISCOVERY)
# include <variants/stm32f4discovery_encX24j600.h>
#elif defined(ELLI_STM32F334_NUCLEO)
# include <variants/stm32f334nucleo_encX24j600.h>
#else
# error "Board not supported by the ENCX24J600 library."
#endif
