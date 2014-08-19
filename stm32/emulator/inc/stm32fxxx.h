/*
 * Copyright (c) 2013-2014 ELL-i co-operative.
 *
 * This is part of ELL-i software.
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

#ifndef _EMULATOR_STM32FXXX_
#define _EMULATOR_STM32FXXX_

#include <Register.h>

typedef Register preg32_t;
typedef Register preg16_t;

/*
 * Undefine the main address defines in the real stm32f0xx.h, causing
 * a compile error on all constructs that use them.
 */
/* XXX There is a problem with undefining FLASH_BASE, because it
 * is used by the stm32f4 initialization of the SCB->VTOR
 */
//#undef FLASH_BASE
#undef SRAM_BASE
#undef PERIPH_BASE

#undef RCC
#undef PWR
#undef SCB
#undef FLASH
#undef GPIOA
#undef GPIOB
#undef GPIOC
#undef GPIOD
#undef GPIOE
#undef GPIOF
#undef GPIOG
#undef GPIOH
#undef GPIOI

#undef TIM1
#undef TIM2
#undef TIM3
#undef TIM4
#undef TIM5
#undef TIM6
#undef TIM7
#undef TIM8
#undef TIM9
#undef TIM10
#undef TIM11
#undef TIM12
#undef TIM13
#undef TIM14
#undef TIM15
#undef TIM16
#undef TIM17

#undef USART1
#undef USART2
#undef USART3
#undef USART4
#undef USART5

#undef SPI1
#undef SPI2

#include <RCC.h>
#include <PWR.h>
#include <SCB.h>
#include <FLASH.h>
#include <GPIO.h>
#include <TIM.h>
#include <USART.h>
#include <SPIemu.h>

#endif //_EMULATOR_STM32FXXX_
