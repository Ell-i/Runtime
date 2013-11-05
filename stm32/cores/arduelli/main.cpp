/*
 * Copyright (c) 2013 ELL-i co-operative
 *
 * The Arduino IDE compatible main function.
 *
 * @see startup_stm32f0xx/4xx.c for the underlying startup code
 */

#include <main.h>

void main() {
    setup();
    for (;;)
        loop();
}



