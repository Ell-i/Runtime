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
 * Authors: Lari Lehtomäki <lari@lehtomaki.fi>  2014
 */

#include "stm32f4discovery_gpio.h"
#include "stm32f4discovery_timer.h"
// #include "stm32f4discovery_usart.h" // TODO

/*
 * With the current Arduino API, it is not possible to reliably
 * determine at compile time which peripherals are used and which are
 * not.  Hence, the only viable option at the moment is to explicitly
 * refer to the peripherap system init records, by creating explicit
 * references to them.  With the -fdata-sections gcc options, the
 * __GPIOx names below will be deleted during link time, leaving only
 * the referenced and explicitly kept GPIOx_INIT records into the
 * linked code (due to the corresponding linker KEEP directive.)
 *
 * Another option would be to create an explicit references from the
 * code, but that is even worse since it would generate runtime code.
 */

const void * __GPIOA = &GPIOA_INIT1;
const void * __GPIOB = &GPIOB_INIT1;
const void * __GPIOC = &GPIOC_INIT1;
const void * __GPIOD = &GPIOD_INIT1;
const void * __GPIOE = &GPIOE_INIT1;
const void * __GPIOF = &GPIOF_INIT1;
const void * __GPIOG = &GPIOG_INIT1;
const void * __GPIOH = &GPIOH_INIT1;
// const void * __GPIOI = &GPIOI_INIT1; // TODO 


const void * __TIM1 = &TIM1_INIT1;
const void * __TIM2 = &TIM2_INIT1;
const void * __TIM3 = &TIM3_INIT1;
const void * __TIM4 = &TIM4_INIT1;
const void * __TIM5 = &TIM5_INIT1;
const void * __TIM6 = &TIM6_INIT1;
const void * __TIM7 = &TIM7_INIT1;
const void * __TIM8 = &TIM8_INIT1;
const void * __TIM9 = &TIM9_INIT1;
const void * __TIM10 = &TIM10_INIT1;
const void * __TIM11 = &TIM11_INIT1;
const void * __TIM12 = &TIM12_INIT1;
const void * __TIM13 = &TIM13_INIT1;
const void * __TIM14 = &TIM14_INIT1;


#if 0
const void * __USART1 = &USART1_INIT;
const void * __USART2 = &USART2_INIT;
const void * __USART3 = &USART3_INIT;
// const void * __USART4 = &USART4_INIT; // TODO UART
// const void * __USART5 = &USART5_INIT; // TODO UART
const void * __USART6 = &USART6_INIT;
#endif
