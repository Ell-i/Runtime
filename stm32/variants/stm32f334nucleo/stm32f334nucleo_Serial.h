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
 * Authors:  Otso Jousimaa <otso@ojousima.net> 2014
 */

#ifndef _STM32F334NUCLEO_SERIAL_H_
#define _STM32F334NUCLEO_SERIAL_H_

#include "Arduino_Serial.h"

// (usart_number, tx_letter, tx_pin, tx_af, rx_letter, rx_pin, rx_af)
static const class Serial Serial1  DEFINE_SERIAL(1, A, 9, 7, A, 10, 7);  // USART
static const class Serial Serial2  DEFINE_SERIAL(2, A, 2, 7, A, 3, 7);   // USART
static const class Serial Serial3  DEFINE_SERIAL(3, B, 8, 7, B, 9, 7);   // USART

static const class Serial &Serial = Serial2;

#endif //_STM32F334NUCLEO_SERIAL_H_
