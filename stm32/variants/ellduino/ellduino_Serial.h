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

#ifndef _ELLDUINO_SERIAL_H_
#define _ELLDUINO_SERIAL_H_

#include "Arduino_Serial.h"

static const class SerialClass Serial  DEFINE_SERIAL(2, A, 14, 1, A, 15, 1);
static const class SerialClass Serial1 DEFINE_SERIAL(1, A,  9, 1, A, 10, 1);

#endif //_ELLDUINO_SERIAL_H_
