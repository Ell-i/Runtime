/*
 * Copyright (c) 2013 ELL-i co-operative
 *
 * The Arduino IDE compatible main function.
 *
 * @see startup_stm32f0xx/4xx.c for the underlying startup code
 */

#ifdef __cplusplus
extern "C" { int main(void); }
#else
extern int  main(void);
#endif

extern void setup(void);
extern void loop(void);
