/*
 * Copyright (c) 2013 Ell-i.org.  All rights reserved.
 */

#include "wiring_digital.h"

#ifdef __cplusplus
extern "C" {
#endif

void abort(void) __attribute__((noreturn));

#ifdef __cplusplus
} // extern "C"
#endif

static inline void assert(int a) {
    if (!a) abort();
}

void abort(void) {
/*	volatile int i;
    pinMode(5, OUTPUT);

	while (1) {
	    
	    digitalWrite(5, 1);
		
		for(i=0;i<1000;i++)
			;

	    digitalWrite(5, 0);

		for(i=0;i<1000;i++)
			;

	}
*/	
	for(;;)
		;

}
