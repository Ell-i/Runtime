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
 * Authors:  Lari Lehtomäki <lari@lehtomaki.fi>  2014
 */

#ifndef _STM32F4DISCOVERY_SERIAL_H_
#define _STM32F4DISCOVERY_SERIAL_H_

#include "Arduino_Serial.h"

// (usart_number, tx_letter, tx_pin, tx_af, rx_letter, rx_pin, rx_af)
static const class Serial Serial1  DEFINE_SERIAL(1, A, 9, 1, A, 10, 1);  // USART
static const class Serial Serial2  DEFINE_SERIAL(2, A, 2, 1, A, 3, 1);   // USART
static const class Serial Serial3  DEFINE_SERIAL(3, D, 8, 1, D, 9, 1);   // USART
// static const class Serial Serial4  DEFINE_SERIAL(4, C, 10, 1, C, 11, 1); // UART
// static const class Serial Serial5  DEFINE_SERIAL(5, C, 12, 1, D, 2, 1);  // UART
static const class Serial Serial6  DEFINE_SERIAL(6, C, 6, 1, C, 7, 1);   // USART

#endif //_STM32F4DISCOVERY_SERIAL_H_
