/*
 * Copyright (c) 2013-2014 ELL-i co-operative.
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
 * Assert-related macros, by default relying on Arduino APIs
 *
 * @author: Pekka Nikander <pekka.nikander@ell-i.org>  2014
 */

#ifndef  _ASSERT_H_
# define _ASSERT_H_

# ifdef _ASSERT_DEBUG_PIN_
#  include "wiring_digital.h"
#endif

# ifdef __cplusplus
extern "C" {
# endif

static inline void abort(void) __attribute__((noreturn));

# ifdef __cplusplus
} // extern "C"
# endif

static inline void assert(int a) {
    if (!a) abort();
}

static inline void abort(void) {

# ifdef _ASSERT_DEBUG_PIN_

    volatile int i;
    pinMode(_ASSERT_DEBUG_PIN_, OUTPUT);

    while (1) {
	    
        digitalWrite(_ASSERT_DEBUG_PIN_, 1);
		
        for (i=0; i<1000; i++)
            ;

        digitalWrite(_ASSERT_DEBUG_PIN_, 0);
        
        for (i=0; i<1000; i++)
            ;

    }
# endif //_ASSERT_DEBUG_PIN_
    for (;;)
        ;
}

#endif //_ASSERT_H_
