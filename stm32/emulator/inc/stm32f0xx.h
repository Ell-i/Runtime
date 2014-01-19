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

#include <RCC.h>
#include <FLASH.h>

