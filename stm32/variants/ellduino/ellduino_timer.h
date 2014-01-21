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

#ifndef _ELLDUINO_TIMER_H_
# define _ELLDUINO_TIMER_H_

# include <arduelli_timer.h>

/**
 * Declarations for externally visible timer init records.
 *
 * STM32F051 has timers 1, 2, 3, 14, 15, 16 and 17.
 */

TIMER_INIT_DEFAULT(1);
TIMER_INIT_DEFAULT(2);
TIMER_INIT_DEFAULT(3);
TIMER_INIT_DEFAULT(14);
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

static const struct PWM PWMPIN[] = {
    DEFINE_PWM_PIN( 1, 3),   /*  0 PA10 D0 RX0 */
    DEFINE_PWM_PIN( 1, 2),   /*  1 PA9  D1 TX0 */
    DEFINE_PWM_PIN( 1, 1),   /*  2 PA8  D2 */
    DEFINE_PWM_PIN( 3, 4),   /*  3 PC9  D3 */
    DEFINE_PWM_PIN( 3, 3),   /*  4 PC8  D4 */
    DEFINE_PWM_PIN(14, 1),   /*  5 PA7  D5 */
    DEFINE_PWM_PIN(15, 2),   /*  6 PA3  D6 */
    DEFINE_PWM_PIN(15, 1),   /*  7 PA2  D7 */
    DEFINE_PWM_PIN( 2, 3),   /*  8 PB10 D8 */
    DEFINE_PWM_PIN( 2, 4),   /*  9 PB11 D9 */
    DEFINE_PWM_PIN( 2, 1),   /* 10 PA15 D10 */
    DEFINE_PWM_PIN( 3, 2),   /* 11 PB5  D11 */
    DEFINE_PWM_PIN( 3, 1),   /* 12 PB4  D12 */
    DEFINE_PWM_PIN( 2, 2),   /* 13 PB3  Led B3 Amber "L" */
    DEFINE_PWM_PIN( 3, 1),   /* 14 PC6  (TX3) */
    DEFINE_PWM_PIN( 3, 1),   /* 15 PC7  (RX3) */
    DEFINE_PWM_PIN_NONE,     /* 16 A14  (TX2) SWCLK */
    DEFINE_PWM_PIN_NONE,     /* 17 PD2  (RX2) */
    DEFINE_PWM_PIN(16, 1),   /* 18 PB6  TX1 */
    DEFINE_PWM_PIN(17, 1),   /* 19 PB7  RX1 */
    DEFINE_PWM_PIN(17, 1),   /* 20 PB9  SDA */
    DEFINE_PWM_PIN(16, 1),   /* 21 PB8  SCL */
    DEFINE_PWM_PIN_NONE,     /* 54 PC0  A0  */
    DEFINE_PWM_PIN_NONE,     /* 55 PC1  A1  */
    DEFINE_PWM_PIN_NONE,     /* 56 PC2  A2  */
    DEFINE_PWM_PIN_NONE,     /* 57 PC3  A3  */
    DEFINE_PWM_PIN( 2, 1),   /* 58 PA5  A4  */
    DEFINE_PWM_PIN( 3, 1),   /* 59 PA6  A5  */
    DEFINE_PWM_PIN( 2, 1),   /* 60 PA0  A6 WKUP1 */
    DEFINE_PWM_PIN( 2, 2),   /* 61 PA1  A7  */
    DEFINE_PWM_PIN_NONE,     /* 62 PC4  A8  */
    DEFINE_PWM_PIN_NONE,     /* 63 PC5  A9  */
    DEFINE_PWM_PIN( 3, 3),   /* 64 PB0  A10 */
    DEFINE_PWM_PIN( 3, 4),   /* 65 PB1  A11 */
    DEFINE_PWM_PIN(14, 1),   /* 66 PA4  DAC0 */
    DEFINE_PWM_PIN_NONE,     /* 67 PA11 (DAC1) */
    DEFINE_PWM_PIN_NONE,     /* 68 PA12 (CANRX) */
    DEFINE_PWM_PIN_NONE,     /* 69 PA13 (CANTX) SWDAT */
    DEFINE_PWM_PIN_NONE,     /* 70 PF7  SDA1 */
    DEFINE_PWM_PIN_NONE,     /* 71 PF6  SCL1 */
};

#endif//_ELLDUINO_TIMER_H_
