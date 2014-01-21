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
 * Authors:  Pekka Nikander <pekka.nikander@ell-i.org>  2014
 */

#ifndef _ELLDUINO_USART_H_
# define _ELLDUINO_USART_H_

# include <arduelli_usart.h>

/**
 * Declarations for externally visible USART init records.
 *
 * STM32F0 has USART ports 1 and 2.
 */
USART_INIT_DEFAULT(1);
USART_INIT_DEFAULT(2);

/**
 * The USART objects themselves, initially as base class objects.
 *
 * XXX TBD Replace with the real Serial class, once defined.
 */
static const SerialBase Serials[] = {
    DEFINE_SERIAL(1),
    DEFINE_SERIAL(2)
};

static const SerialBase& Serial  = Serials[0];
static const SerialBase& Serial1 = Serials[1];

#endif//_ELLDUINO_USART_H_
