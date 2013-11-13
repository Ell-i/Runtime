/*
 * Copyright (c) 2013 ELL-i co-operative
 *
 * The Arduino IDE compatible main function.
 *
 * @see startup_stm32f0xx/4xx.c for the startup code that is executed before main.
 */

#include <main.h>
#include <system_init.h>

int main(void) {
    SystemInitPeripherals();

    setup();
    for (;;)
        loop();
}



