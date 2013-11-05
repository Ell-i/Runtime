/*
 * Copyright (c) 2013 ELL-i co-operative
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

