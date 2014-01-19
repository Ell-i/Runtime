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
 * @author  Pekka Nikander <pekka.nikander@ell-i.org>  2013-2014
 *
 * @brief The Arduino IDE compatible main function.
 *
 * @see startup_stm32f0xx/stm32f4xx.c for the startup code that is
 *      executed before calling main.
 *
 */

#include <main.h>
#include <system_init.h>

int main(void) {
    SystemInitPeripherals();

    setup();
    for (;;)
        loop();
    return 0;
}



