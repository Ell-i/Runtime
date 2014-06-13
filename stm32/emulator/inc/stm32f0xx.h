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

#ifndef _EMULATOR_STM32F0XX_
#define _EMULATOR_STM32F0XX_

#include <stdint.h>

#include "../../system/stm32/inc/stm32f0xx.h"  // XXX FIX PATH

/*
 * Undefine the main address defines in the real stm32f0xx.h, causing
 * a compile error on all constructs that use them.
 */
#undef FLASH_BASE
#undef SRAM_BASE
#undef PERIPH_BASE

#undef RCC
#undef FLASH
#undef GPIOA
#undef GPIOB
#undef GPIOC
#undef GPIOD
#undef GPIOE
#undef GPIOF
#undef GPIOG
#undef GPIOH

#undef TIM1
#undef TIM2
#undef TIM3
#undef TIM14
#undef TIM15
#undef TIM16
#undef TIM17

#undef USART1
#undef USART2

#undef SPI1
#undef SPI2

#ifndef __cplusplus
/*
 * Definitions when compiling in C mode for the emulator
 * Please avoid this, use only to circumvent g++ (or clang++) bugs.
 */

typedef uint32_t preg32_t;
typedef uint16_t preg16_t;

#else
/*
 * The real definitions when compiling for the emulator, in C++ mode.
 */

# include <Register.h>

typedef Register preg32_t;
typedef Register preg16_t;

# include <RCC.h>
# include <FLASH.h>
# include <GPIO.h>
# include <TIM.h>
# include <USART.h>
# include <SPIemu.h>

#endif

#endif //_EMULATOR_STM32F0XX_
