/*
 * Copyright (c) 2013-2014 ELL-i co-operative.
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
 */

#include <ellduino_gpio.h>

/*
 * Boot-time definitions for the STM32F0 series MCU GPIO registers.
 */

DEFINE_GPIO_INIT_RECORD(A);
DEFINE_GPIO_INIT_RECORD(B);
DEFINE_GPIO_INIT_RECORD(C);
DEFINE_GPIO_INIT_RECORD(D);
DEFINE_GPIO_INIT_RECORD(F);

/*
 * Boot-time definitions for the STM32F0 series MCU ports.
 *
 * These macros here generate SystemInitRecord structures to the
 * SYSTEM_INIT_SECTION linker section.  The boot time initialisation
 * code iterates the records from that section, initialising the MCU
 * peripheral ports accordingly.
 */

DEFINE_GPIO_PORT(A, GPIOA_INIT_DefaultRecords, GPIOA_INIT_AltFunctRecords);
DEFINE_GPIO_PORT(B, GPIOB_INIT_DefaultRecords, GPIOB_INIT_AltFunctRecords);
DEFINE_GPIO_PORT(C, GPIOC_INIT_DefaultRecords, GPIOC_INIT_AltFunctRecords);
DEFINE_GPIO_PORT(D, GPIOD_INIT_DefaultRecords, GPIOD_INIT_AltFunctRecords);
DEFINE_GPIO_PORT(F, GPIOF_INIT_DefaultRecords, GPIOF_INIT_AltFunctRecords);

