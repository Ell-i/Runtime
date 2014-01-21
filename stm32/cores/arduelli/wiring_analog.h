/*
 * Copyright (c) 2014 ELL-i co-operative
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
 * @author Pekka Nikander <pekka.nikander@ell-i.org>  2014
 */

#include "ellduino_gpio.h"  // XXX replace with variant.h
#include "ellduino_timer.h" // XXX replace with variant.h
#include "wiring_digital.h" // XXX Make sure the GPIO registers are initialised

/*
 * With the current Arduino API, it is not possible to reliably
 * determine at compile time which PWM ports are used and which are
 * not.  Hence, the only viable option at the moment is to explicitly
 * refer to the TIMER system init records, by creating explicit
 * references to them.  With the -fdata-sections gcc options, the
 * __TIMERx names below will be deleted during link time, leaving only
 * the referenced and explicitly kept TIMERx_INIT records into the
 * linked code (due to the corresponding linker KEEP directive.)
 *
 * Another option would be to create an explicit references from the
 * code, but that is even worse since it would generate runtime code.
 */

const void * __TIM1 = &TIM1_INIT;
const void * __TIM2 = &TIM2_INIT;
const void * __TIM3 = &TIM3_INIT;
const void * __TIM14 = &TIM14_INIT;
const void * __TIM15 = &TIM15_INIT;
const void * __TIM16 = &TIM16_INIT;
const void * __TIM17 = &TIM17_INIT;


/**************************************
 * Arduino APIs
 */

#include "wiring_analog_analogWrite.h"
