/*
 * Copyright (c) 2014 ELL-i co-operative.
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
 * along with ELL-i software.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

/*
 * Authors: Otso Jousimaa <otso@ojousima.net> 2014
 */

#ifndef _STM32F334NUCLEO_TIMER_H_
# define _STM32F334NUCLEO_TIMER_H_

# include <arduelli_timer.h>

/**
 * Declarations for externally visible timer init records.
 *
 * STM32F334 has timers from 1 to 14.
 */

TIMER_INIT_DEFAULT(1);
TIMER_INIT_DEFAULT(2);
TIMER_INIT_DEFAULT(3);
TIMER_INIT_DEFAULT(6);
TIMER_INIT_DEFAULT(7);
TIMER_INIT_DEFAULT(15);
TIMER_INIT_DEFAULT(16);
TIMER_INIT_DEFAULT(17);

/**
 * An array of Arduino-compatible TIMER pins, index by the Arduino Pin
 * index.
 *
 * The definitions are made as a static const array, thereby allowing
 * the compiler to optimise it completely away.  The resulting code
 * accesses directly the I/O registers.
 */

// TODO
static const struct PWM PWMPIN[] = {};

#endif //_STM32F334NUCLEO_TIMER_H_
