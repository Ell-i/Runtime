/*
 * Copyright (c) 2013-2014 ELL-i co-operative
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
 * @author  Pekka Nikander <pekka.nikander@ell-i.org>  2013-2014
 *
 * @brief   STM32F334X8 devices startup code, written mostly in C.
 *          Based on startup_stm32f334x8.s, for STM32F334x8,
 *          distributed by STMicroelectronics.
 */

#include <stdint.h>
#include <stdlib.h>
#include <main.h>

#include <system_stm32f3xx.h>

/*
 * The main motivation of writing this is C is go give those beginners
 * that don't want to study assembler syntax in detail a chance to
 * understand what is going on during the start time.
 *
 * If you modify this, be sure to compile this into assembler and
 * check carefully that you get out what you want.
 */

/**
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

#ifdef __cplusplus
extern "C" {
#endif

/*
 * The Reset_Handler and Default_handler must be defined in the C
 * naming space, even in the Emulator, or the linkage will fail.
 */

// Must be in the C context, as this is called in that way from SystemInit
void Reset_Handler(void)        __attribute__((/*reset*/, naked));

# ifndef EMULATOR

// Must be in the C context, for alias attribute to compile
void Default_Handler(void)      __attribute__((interrupt, naked));

void NMI_Handler(void)          __attribute__((weak, alias ("Default_Handler")));
void HardFault_Handler(void)    __attribute__((weak, alias ("Default_Handler")));
void MemManage_Handler(void)    __attribute__((weak, alias ("Default_Handler")));
void BusFault_Handler(void)     __attribute__((weak, alias ("Default_Handler")));
void UsageFault_Handler(void)   __attribute__((weak, alias ("Default_Handler")));
void SVC_Handler(void)          __attribute__((weak, alias ("Default_Handler")));
void DebugMon_Handler(void)     __attribute__((weak, alias ("Default_Handler")));
void PendSV_Handler(void)       __attribute__((weak, alias ("Default_Handler")));
void SysTick_Handler(void)      __attribute__((weak, alias ("Default_Handler")));
void WWDG_IRQHandler(void)      __attribute__((weak, alias ("Default_Handler")));
void PVD_IRQHandler(void)       __attribute__((weak, alias ("Default_Handler")));
void TAMP_STAMP_IRQHandler(void)
                                __attribute__((weak, alias ("Default_Handler")));
void RTC_WKUP_IRQHandler(void)
                                __attribute__((weak, alias ("Default_Handler")));
void FLASH_IRQHandler(void)     __attribute__((weak, alias ("Default_Handler")));
void RCC_IRQHandler(void)       __attribute__((weak, alias ("Default_Handler")));
void EXTI0_IRQHandler(void)     __attribute__((weak, alias ("Default_Handler")));
void EXTI1_IRQHandler(void)     __attribute__((weak, alias ("Default_Handler")));
void EXTI2_TSC_IRQHandler(void)
                                __attribute__((weak, alias ("Default_Handler")));
void EXTI3_IRQHandler(void)     __attribute__((weak, alias ("Default_Handler")));
void EXTI4_IRQHandler(void)     __attribute__((weak, alias ("Default_Handler")));
void DMA1_Channel1_IRQHandler(void)
                                __attribute__((weak, alias ("Default_Handler")));
void DMA1_Channel2_IRQHandler(void)
                                __attribute__((weak, alias ("Default_Handler")));
void DMA1_Channel3_IRQHandler(void)
                                __attribute__((weak, alias ("Default_Handler")));
void DMA1_Channel4_IRQHandler(void)
                                __attribute__((weak, alias ("Default_Handler")));
void DMA1_Channel5_IRQHandler(void)
                                __attribute__((weak, alias ("Default_Handler")));
void DMA1_Channel6_IRQHandler(void)
                                __attribute__((weak, alias ("Default_Handler")));
void DMA1_Channel7_IRQHandler(void)
                                __attribute__((weak, alias ("Default_Handler")));
void ADC1_2_IRQHandler(void)    __attribute__((weak, alias ("Default_Handler")));
void CAN_TX_IRQHandler(void)    __attribute__((weak, alias ("Default_Handler")));
void CAN_RX0_IRQHandler(void)   __attribute__((weak, alias ("Default_Handler")));
void CAN_RX1_IRQHandler(void)   __attribute__((weak, alias ("Default_Handler")));
void CAN_SCE_IRQHandler(void)   __attribute__((weak, alias ("Default_Handler")));
void EXTI9_5_IRQHandler(void)   __attribute__((weak, alias ("Default_Handler")));
void TIM1_BRK_TIM15_IRQHandler(void)
                                __attribute__((weak, alias ("Default_Handler")));
void TIM1_UP_TIM16_IRQHandler(void)
                                __attribute__((weak, alias ("Default_Handler")));
void TIM1_TRG_COM_TIM17_IRQHandler(void)
                                __attribute__((weak, alias ("Default_Handler")));
void TIM1_CC_IRQHandler(void)   __attribute__((weak, alias ("Default_Handler")));
void TIM2_IRQHandler(void)      __attribute__((weak, alias ("Default_Handler")));
void TIM3_IRQHandler(void)      __attribute__((weak, alias ("Default_Handler")));
void I2C1_EV_IRQHandler(void)   __attribute__((weak, alias ("Default_Handler")));
void I2C1_ER_IRQHandler(void)   __attribute__((weak, alias ("Default_Handler")));
void SPI1_IRQHandler(void)      __attribute__((weak, alias ("Default_Handler")));
void USART1_IRQHandler(void)    __attribute__((weak, alias ("Default_Handler")));
void USART2_IRQHandler(void)    __attribute__((weak, alias ("Default_Handler")));
void USART3_IRQHandler(void)    __attribute__((weak, alias ("Default_Handler")));
void EXTI15_10_IRQHandler(void)
                                __attribute__((weak, alias ("Default_Handler")));
void RTC_Alarm_IRQHandler(void)
                                __attribute__((weak, alias ("Default_Handler")));
void TIM6_DAC1_IRQHandler(void)
                                __attribute__((weak, alias ("Default_Handler")));
void TIM7_DAC2_IRQHandler(void)
                                __attribute__((weak, alias ("Default_Handler")));
void COMP2_IRQHandler(void)     __attribute__((weak, alias ("Default_Handler")));
void COMP4_6_IRQHandler(void)   __attribute__((weak, alias ("Default_Handler")));
void HRTIM1_Master_IRQHandler(void)
                                __attribute__((weak, alias ("Default_Handler")));
void HRTIM1_TIMA_IRQHandler(void)
                                __attribute__((weak, alias ("Default_Handler")));
void HRTIM1_TIMB_IRQHandler(void)
                                __attribute__((weak, alias ("Default_Handler")));
void HRTIM1_TIMC_IRQHandler(void)
                                __attribute__((weak, alias ("Default_Handler")));
void HRTIM1_TIMD_IRQHandler(void)
                                __attribute__((weak, alias ("Default_Handler")));
void HRTIM1_TIME_IRQHandler(void)
                                __attribute__((weak, alias ("Default_Handler")));
void HRTIM1_FLT_IRQHandler(void)
                                __attribute__((weak, alias ("Default_Handler")));
void FPU_IRQHandler(void)       __attribute__((weak, alias ("Default_Handler")));

/**
 * Interrupt vector table for STM32F4 Cortex-M4.
 *
 * Must be placed at the address 0x00000000, typically in the flash.
 */

void *const g_pfnVectors[] __attribute__((section(".isr_vector"))) = {
    (void*)&_estack,
    (void*)Reset_Handler,
    (void*)NMI_Handler,
    (void*)HardFault_Handler,
    (void*)MemManage_Handler,
    (void*)BusFault_Handler,
    (void*)UsageFault_Handler,
    (void*)0,
    (void*)0,
    (void*)0,
    (void*)0,
    (void*)SVC_Handler,
    (void*)DebugMon_Handler,
    (void*)0,
    (void*)PendSV_Handler,
    (void*)SysTick_Handler,
    (void*)WWDG_IRQHandler,
    (void*)PVD_IRQHandler,
    (void*)TAMP_STAMP_IRQHandler,
    (void*)RTC_WKUP_IRQHandler,
    (void*)FLASH_IRQHandler,
    (void*)RCC_IRQHandler,
    (void*)EXTI0_IRQHandler,
    (void*)EXTI1_IRQHandler,
    (void*)EXTI2_TSC_IRQHandler,
    (void*)EXTI3_IRQHandler,
    (void*)EXTI4_IRQHandler,
    (void*)DMA1_Channel1_IRQHandler,
    (void*)DMA1_Channel2_IRQHandler,
    (void*)DMA1_Channel3_IRQHandler,
    (void*)DMA1_Channel4_IRQHandler,
    (void*)DMA1_Channel5_IRQHandler,
    (void*)DMA1_Channel6_IRQHandler,
    (void*)DMA1_Channel7_IRQHandler,
    (void*)ADC1_2_IRQHandler,
    (void*)CAN_TX_IRQHandler,
    (void*)CAN_RX0_IRQHandler,
    (void*)CAN_RX1_IRQHandler,
    (void*)CAN_SCE_IRQHandler,
    (void*)EXTI9_5_IRQHandler,
    (void*)TIM1_BRK_TIM15_IRQHandler,
    (void*)TIM1_UP_TIM16_IRQHandler,
    (void*)TIM1_TRG_COM_TIM17_IRQHandler,
    (void*)TIM1_CC_IRQHandler,
    (void*)TIM2_IRQHandler,
    (void*)TIM3_IRQHandler,
    (void*)0,
    (void*)I2C1_EV_IRQHandler,
    (void*)I2C1_ER_IRQHandler,
    (void*)0,
    (void*)0,
    (void*)SPI1_IRQHandler,
    (void*)0,
    (void*)USART1_IRQHandler,
    (void*)USART2_IRQHandler,
    (void*)USART3_IRQHandler,
    (void*)EXTI15_10_IRQHandler,
    (void*)RTC_Alarm_IRQHandler,
    (void*)0,
    (void*)0,
    (void*)0,
    (void*)0,
    (void*)0,
    (void*)0,
    (void*)0,
    (void*)0,
    (void*)0,
    (void*)0,
    (void*)0,
    (void*)0,
    (void*)TIM6_DAC1_IRQHandler,
    (void*)TIM7_DAC2_IRQHandler,
    (void*)0,
    (void*)0,
    (void*)0,
    (void*)0,
    (void*)0,
    (void*)0,
    (void*)0,
    (void*)0,
    (void*)COMP2_IRQHandler,
    (void*)COMP4_6_IRQHandler,
    (void*)0,
    (void*)HRTIM1_Master_IRQHandler,
    (void*)HRTIM1_TIMA_IRQHandler,
    (void*)HRTIM1_TIMB_IRQHandler,
    (void*)HRTIM1_TIMC_IRQHandler,
    (void*)HRTIM1_TIMD_IRQHandler,
    (void*)HRTIM1_TIME_IRQHandler,
    (void*)HRTIM1_FLT_IRQHandler,
    (void*)0,
    (void*)0,
    (void*)0,
    (void*)0,
    (void*)0,
    (void*)0,
    (void*)0,
    (void*)FPU_IRQHandler,
};
# endif

/*
 * Declare the segment addresses; provided by by the linker.
 * Unused in the emulator.
 */
extern uint32_t _sidata, _sdata, _edata, _sbss, _ebss;

#ifdef __cplusplus
}
#endif

/**
 * Reset handler
 */
void Reset_Handler(void) {
#ifndef EMULATOR
    /* XXX: I'm not sure if this stack initialisation is *really*
     *      needed.  According to ARM documentation the CPU should
     *      do it itself.
     */
    register void *const stack = &_estack;
    __asm__ volatile ("mov    sp, %0" : : "r" (stack));
#endif

    /* Copy initialised non-const data from flash to RAM */
    register uint32_t *flash = &_sidata;
    register uint32_t *ram   = &_sdata;
    register uint32_t *edata = &_edata;

    while (ram < edata)
        *ram++ = *flash++;

    /* XXX Possibly add support for initialising CCM RAM */

    /* Clear zero-initialised RAM */
    register uint32_t *bss   = &_sbss;
    register uint32_t *ebss  = &_ebss;

    while (bss < ebss)
        *bss++ = 0;

    /* Configure PLL, AHB/APBx prescalers and Flash settings. */
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

/**
 * The default handler, called by default from interrupts.
 */
void Default_Handler(void) {
    for (;;)
        ;
}

