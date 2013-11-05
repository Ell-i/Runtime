/*
 * Copyright (c) 2013 ELL-i co-operative
 *
 * License TBD
 *
 * @author:  Pekka Nikander <pekka.nikander@ell-i.org>
 *
 * @brief:  STM32F0XX devices startup code, written mostly in C
 *          Based on startup_stm32f0xx.s, for STM32F05x,
 *          distribute by STMicroelectronics but enhanced also
 *          for STM32F03x.
 */

#include <stdint.h>
#include <stdlib.h>
#include <main.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * The main motivation of writing this is C is go give those beginners
 * that don't want to study assembler syntax in detail a chance to
 * understand what is going on during the start time.
 *
 * If you modify this, be sure to compile this into assembler and
 * check carefully that you get out what you want.
 */

#define BootRAM ((void *)0xF108F85F) /* For booting from RAM, see XXX. */

/*
 * The end of stack segment, provided by the linker.
 */
extern uint32_t _estack;

/*
 * NB.  Note that the reset and interrupt attributes below are
 * not needed by GCC (as they are not needed for ARM-V7), but we still
 * use them for documentational purposes.
 */

/* GCC generates the corrext .text.<function> sections automatically,
 * as we use with -ffunction-sections.  Hence, we don't need any
 * attribute for them. */

void Reset_Handler(void)        __attribute__((/*reset*/, naked));

void Default_Handler(void)      __attribute__((interrupt, naked));

void NMI_Handler(void)          __attribute__((weak, alias ("Default_Handler")));
void HardFault_Handler(void)    __attribute__((weak, alias ("Default_Handler")));
void SVC_Handler(void)          __attribute__((weak, alias ("Default_Handler")));
void PendSV_Handler(void)       __attribute__((weak, alias ("Default_Handler")));
void SysTick_Handler(void)      __attribute__((weak, alias ("Default_Handler")));
void WWDG_IRQHandler(void)      __attribute__((weak, alias ("Default_Handler")));
void PVD_IRQHandler(void)       __attribute__((weak, alias ("Default_Handler")));
void RTC_IRQHandler(void)       __attribute__((weak, alias ("Default_Handler")));
void FLASH_IRQHandler(void)     __attribute__((weak, alias ("Default_Handler")));
void RCC_IRQHandler(void)       __attribute__((weak, alias ("Default_Handler")));
void EXTI0_1_IRQHandler(void)   __attribute__((weak, alias ("Default_Handler")));
void EXTI2_3_IRQHandler(void)   __attribute__((weak, alias ("Default_Handler")));
void EXTI4_15_IRQHandler(void)  __attribute__((weak, alias ("Default_Handler")));
void TS_IRQHandler(void)        __attribute__((weak, alias ("Default_Handler")));
void DMA1_Channel1_IRQHandler(void)
                                __attribute__((weak, alias ("Default_Handler")));
void DMA1_Channel2_3_IRQHandler(void)
                                __attribute__((weak, alias ("Default_Handler")));
void DMA1_Channel4_5_IRQHandler(void)
                                __attribute__((weak, alias ("Default_Handler")));
void ADC1_COMP_IRQHandler(void) __attribute__((weak, alias ("Default_Handler")));
void TIM1_BRK_UP_TRG_COM_IRQHandler(void)
                                __attribute__((weak, alias ("Default_Handler")));
void TIM1_CC_IRQHandler(void)   __attribute__((weak, alias ("Default_Handler")));
void TIM2_IRQHandler(void)      __attribute__((weak, alias ("Default_Handler")));
void TIM3_IRQHandler(void)      __attribute__((weak, alias ("Default_Handler")));
void TIM6_DAC_IRQHandler(void)  __attribute__((weak, alias ("Default_Handler")));
void TIM14_IRQHandler(void)     __attribute__((weak, alias ("Default_Handler")));
void TIM15_IRQHandler(void)     __attribute__((weak, alias ("Default_Handler")));
void TIM16_IRQHandler(void)     __attribute__((weak, alias ("Default_Handler")));
void TIM17_IRQHandler(void)     __attribute__((weak, alias ("Default_Handler")));
void I2C1_IRQHandler(void)      __attribute__((weak, alias ("Default_Handler")));
void I2C2_IRQHandler(void)      __attribute__((weak, alias ("Default_Handler")));
void SPI1_IRQHandler(void)      __attribute__((weak, alias ("Default_Handler")));
void SPI2_IRQHandler(void)      __attribute__((weak, alias ("Default_Handler")));
void USART1_IRQHandler(void)    __attribute__((weak, alias ("Default_Handler")));
void USART2_IRQHandler(void)    __attribute__((weak, alias ("Default_Handler")));
void CEC_IRQHandler(void)       __attribute__((weak, alias ("Default_Handler")));

/**
 * Interrupt vector table for STM32F0 Cortex-M0.
 *
 * Must be placed at the address 0x00000000, typically in flash.
 */

void *const g_pfnVectors[] __attribute__((section(".isr_vector"))) = {
    (void*)&_estack,
    (void*)Reset_Handler,
    (void*)NMI_Handler,
    (void*)HardFault_Handler,
    (void*)0,
    (void*)0,
    (void*)0,
    (void*)0,
    (void*)0,
    (void*)0,
    (void*)0,
    (void*)SVC_Handler,
    (void*)0,
    (void*)0,
    (void*)PendSV_Handler,
    (void*)SysTick_Handler,
    (void*)WWDG_IRQHandler,
    (void*)PVD_IRQHandler,
    (void*)RTC_IRQHandler,
    (void*)FLASH_IRQHandler,
    (void*)RCC_IRQHandler,
    (void*)EXTI0_1_IRQHandler,
    (void*)EXTI2_3_IRQHandler,
    (void*)EXTI4_15_IRQHandler,
    (void*)TS_IRQHandler,
    (void*)DMA1_Channel1_IRQHandler,
    (void*)DMA1_Channel2_3_IRQHandler,
    (void*)DMA1_Channel4_5_IRQHandler,
    (void*)ADC1_COMP_IRQHandler,
    (void*)TIM1_BRK_UP_TRG_COM_IRQHandler,
    (void*)TIM1_CC_IRQHandler,
    (void*)TIM2_IRQHandler,
    (void*)TIM3_IRQHandler,
    (void*)TIM6_DAC_IRQHandler,
    (void*)0,
    (void*)TIM14_IRQHandler,
    (void*)TIM15_IRQHandler,
    (void*)TIM16_IRQHandler,
    (void*)TIM17_IRQHandler,
    (void*)I2C1_IRQHandler,
    (void*)I2C2_IRQHandler,
    (void*)SPI1_IRQHandler,
    (void*)SPI2_IRQHandler,
    (void*)USART1_IRQHandler,
    (void*)USART2_IRQHandler,
    (void*)0,
    (void*)CEC_IRQHandler,
    (void*)0,
    (void*)BootRAM,         /* @0x108. Fro boot in RAM mode for STM32F0xx */
};

/*
 * Declare the segment addresses; provided by by the linker.
 */
extern uint32_t _sidata, _sdata, _edata, _sbss, _ebss;

/**
 * Reset handler
 */

/* XXX: Move to the proper system header */
extern void SystemInit(void);
extern void __libc_init_array(void);

void Reset_Handler(void) {
    /* XXX: I'm not sure if this stack initialisation is *really*
     *      needed.  According to ARM documentation the CPU should
     *      do it itself.
     */
#ifndef EMULATOR
    register void *const stack = &_estack;
    __asm__ volatile ("mov    sp, %0" : : "r" (stack));
#endif

    /* Copy initialised non-const data from flash to RAM */
    register uint32_t *flash = &_sidata;
    register uint32_t *ram   = &_sdata;
    register uint32_t *edata = &_edata;

    while (ram < edata)
        *ram++ = *flash++;

    /* Clear zero-initialised RAM */
    register uint32_t *bss   = &_sbss;
    register uint32_t *ebss  = &_ebss;

    while (bss < ebss)
        *bss++ = 0;

    /* Call the system clock initialisation function. */
    SystemInit();

    /* Do NOT call C++ static constructors */
    // C++ static constructors would normally be initialised from here
    // but we do not support them!

    /* Call the main program */
    main();
    /* Loop forever */
    for (;;)
        ;
}

/*
 * The default handler, called by default by interrupts
 */
void Default_Handler(void) {
    for (;;)
        ;
}

#ifdef __cplusplus
}
#endif
