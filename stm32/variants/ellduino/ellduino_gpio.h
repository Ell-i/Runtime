/*
 * Copyright (c) 2013 ELL-i co-operative.
 *
 * ELL-i software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * ELL-i software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with ELL-i software.  If not, see <http://www.gnu.org/licenses/>.
 *
 *
 */

#ifndef _ELLDUINO_GPIO_H_
#define _ELLDUINO_GPIO_H_

#include <arduelli_gpio.h>

static const struct GPIO GPIO[] = {
    DEFINE_GPIO(A, 10),   /*  0 PA10 D0 RX0 */
    DEFINE_GPIO(A,  9),   /*  1 PA9  D1 TX0 */
    DEFINE_GPIO(A,  8),   /*  2 PA8  D2 */
    DEFINE_GPIO(C,  9),   /*  3 PC9  D3 */
    DEFINE_GPIO(C,  8),   /*  4 PC8  D4 */
    DEFINE_GPIO(A,  7),   /*  5 PA7  D5 */
    DEFINE_GPIO(A,  3),   /*  6 PA3  D6 */
    DEFINE_GPIO(A,  2),   /*  7 PA2  D7 */
    DEFINE_GPIO(B, 10),   /*  8 PB10 D8 */
    DEFINE_GPIO(B, 11),   /*  9 PB11 D9 */
    DEFINE_GPIO(A, 15),   /* 10 PA15 D10 */
    DEFINE_GPIO(B,  5),   /* 11 PB5  D11 */
    DEFINE_GPIO(B,  4),   /* 12 PB4  D12 */
    DEFINE_GPIO(B,  3),   /* 13 PB3  Led B3 Amber "L" */
    DEFINE_GPIO(C,  6),   /* 14 PC6  (TX3) */
    DEFINE_GPIO(C,  7),   /* 15 PC7  (RX3) */
    DEFINE_GPIO(A, 14),   /* 16 A14  (TX2) SWCLK */
    DEFINE_GPIO(D,  2),   /* 17 PD2  (RX2) */
    DEFINE_GPIO(B,  6),   /* 18 PB6  TX1 */
    DEFINE_GPIO(B,  7),   /* 19 PB7  RX1 */
    DEFINE_GPIO(B,  9),   /* 20 PB9  SDA */
    DEFINE_GPIO(B,  8),   /* 21 PB8  SCL */
    DEFINE_GPIO(C,  0),   /* 54 PC0  A0  */
    DEFINE_GPIO(C,  1),   /* 55 PC1  A1  */
    DEFINE_GPIO(C,  2),   /* 56 PC2  A2  */
    DEFINE_GPIO(C,  3),   /* 57 PC3  A3  */
    DEFINE_GPIO(A,  5),   /* 58 PA5  A4  */
    DEFINE_GPIO(A,  6),   /* 59 PA6  A5  */
    DEFINE_GPIO(A,  0),   /* 60 PA0  A6 WKUP1 */
    DEFINE_GPIO(A,  1),   /* 61 PA1  A7  */
    DEFINE_GPIO(C,  4),   /* 62 PC4  A8  */
    DEFINE_GPIO(C,  5),   /* 63 PC5  A9  */
    DEFINE_GPIO(B,  0),   /* 64 PB0  A10 */
    DEFINE_GPIO(B,  1),   /* 65 PB1  A11 */
    DEFINE_GPIO(A,  4),   /* 66 PA4  DAC0 */
    DEFINE_GPIO(A, 11),   /* 67 PA11 (DAC1) */
    DEFINE_GPIO(A, 12),   /* 68 PA12 (CANRX) */
    DEFINE_GPIO(A, 13),   /* 69 PA13 (CANTX) SWDAT */
    DEFINE_GPIO(F,  7),   /* 70 PF7  SDA1 */
    DEFINE_GPIO(F,  6),   /* 71 PF6  SCL1 */
};

#endif//_ELLDUINO_GPIO_H_
