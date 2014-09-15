/*
 * Copyright (c) 2013-2014 ELL-i co-operative
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
 * @author Pekka Nikander <pekka.nikander@ell-i.org>  2013-2014
 *
 * @brief The Arduino IDE compatible header.
 */

#include <arduelli_api_definitions.h>

#include <main.h>
#if defined(ELLI_STM32F051_ELLDUINO)
# include <ellduino_gpio.h> // XXX To be placed into the variant.h!
# include <ellduino_timer.h>
# include <ellduino_usart.h>
# include <ellduino_Serial.h>
#elif defined(ELLI_STM32F407_DISCOVERY)
# include <stm32f4discovery_gpio.h> // XXX To be placed into the variant.h!
# include <stm32f4discovery_timer.h>
# include <stm32f4discovery_usart.h>
# include <stm32f4discovery_Serial.h>
#else
# error "Unknown board.  Please define."
#endif

#include <wiring_digital.h>
#include <wiring_analog.h>
