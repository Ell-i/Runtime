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
 */

#ifndef _WIRING_ANALOG_H_
# define _WIRING_ANALOG_H_

#if defined(ELLI_STM32F051_ELLDUINO)
# include "ellduino_gpio.h"  // XXX replace with variant_gpio.h
# include "ellduino_timer.h" // XXX replace with variant_timer.h
#elif defined(ELLI_STM32F407_DISCOVERY)
# include "stm32f4discovery_gpio.h" // XXX To be placed into the variant.h!
# include "stm32f4discovery_timer.h" // XXX replace with variant_timer.h
#elif defined(ELLI_STM32F334_NUCLEO)
# include "stm32f334nucleo_gpio.h" // XXX To be placed into the variant.h!
# include "stm32f334nucleo_timer.h" // XXX replace with variant_timer.h
#else
# error "Unknown board.  Please define."
#endif

#include "wiring_digital.h"

/**************************************
 * Arduino APIs
 */

#include "wiring_analog_analogWrite.h"

#endif//_WIRING_ANALOG_H_
