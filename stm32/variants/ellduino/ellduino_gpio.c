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

#include <arduelli_gpio.h>

/*
 * Boot-time definitions for the STM32F0 series MCU ports.
 *
 * These macros here generate SystemInitRecord structures to the
 * SYSTEM_INIT_SECTION linker section.  The boot time initialisation
 * code iterates the records from that section, initialising the MCU
 * peripheral ports accordingly.
 */

DEFINE_GPIO_PORT(A);
DEFINE_GPIO_PORT(B);
DEFINE_GPIO_PORT(C);
DEFINE_GPIO_PORT(D);
DEFINE_GPIO_PORT(F);

