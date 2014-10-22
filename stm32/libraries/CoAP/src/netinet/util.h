/*
 * Copyright (c) 2014 ELL-i co-operative.
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
 * ARM CMSIS optimised hton{s,l} and ntoh{s,l}
 *
 * @author: Pekka Nikander <pekka.nikander@ell-i.org>  2014
 */

#ifndef  _UTIL_STM32_H_
# define _UTIL_STM32_H_

# include <stdint.h>

# if defined(STM32F0XX)
#  include <stm32f0xx.h>  // Declare __REV16() and __REV()
# elif defined(STM32F40_41xxx)
#  include <stm32f4xx.h>
# elif defined(STM32F334x8)
#  include <stm32f3xx.h>
# else
#  error "Unsupported MCU."
# endif

/* Compile time */
# define CONSTEXPR_HTONS(s) ((((s) >> 8) & 0xff) | (((s) << 8) & 0xff00))
# define CONSTEXPR_NTOHS(s) ((((s) >> 8) & 0xff) | (((s) << 8) & 0xff00))

# ifndef EMULATOR

/* Runtime */
static inline int htons(uint16_t s) { return __REV16(s); };
static inline int ntohs(uint16_t s) { return __REV16(s); };
static inline int htonl(uint32_t l) { return __REV(l);   };
static inline int ntohl(uint32_t l) { return __REV(l);   };

# else //EMULATOR

/* Defined already in the emulator header files, don't redefine here. */

# endif //EMULATOR

#endif //_UTIL_STM32_H_
