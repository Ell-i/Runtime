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
 * @brief   STM32F40XX devices startup code, written mostly in C.
 *          Based on startup_stm32f40xx.s, for STM32F40xx,
 *          distributed by STMicroelectronics but enhanced also
 *          for STM32F03x.
 */

#include <stdint.h>
#include <stdlib.h>
#include <main.h>

#include <system_stm32f4xx.h>

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
void RTC_WKUP_IRQHandler(void)  __attribute__((weak, alias ("Default_Handler")));
void FLASH_IRQHandler(void)     __attribute__((weak, alias ("Default_Handler")));
void RCC_IRQHandler(void)       __attribute__((weak, alias ("Default_Handler")));
void EXTI0_IRQHandler(void)     __attribute__((weak, alias ("Default_Handler")));
void EXTI1_IRQHandler(void)     __attribute__((weak, alias ("Default_Handler")));
void EXTI2_IRQHandler(void)     __attribute__((weak, alias ("Default_Handler")));
void EXTI3_IRQHandler(void)     __attribute__((weak, alias ("Default_Handler")));
void EXTI4_IRQHandler(void)     __attribute__((weak, alias ("Default_Handler")));
void DMA1_Stream0_IRQHandler(void)
                                __attribute__((weak, alias ("Default_Handler")));
void DMA1_Stream1_IRQHandler(void)
                                __attribute__((weak, alias ("Default_Handler")));
void DMA1_Stream2_IRQHandler(void)
                                __attribute__((weak, alias ("Default_Handler")));
void DMA1_Stream3_IRQHandler(void)
                                __attribute__((weak, alias ("Default_Handler")));
void DMA1_Stream4_IRQHandler(void)
                                __attribute__((weak, alias ("Default_Handler")));
void DMA1_Stream5_IRQHandler(void)
                                __attribute__((weak, alias ("Default_Handler")));
void DMA1_Stream6_IRQHandler(void)
                                __attribute__((weak, alias ("Default_Handler")));
void ADC_IRQHandler(void)       __attribute__((weak, alias ("Default_Handler")));
void CAN1_TX_IRQHandler(void)   __attribute__((weak, alias ("Default_Handler")));
void CAN1_RX0_IRQHandler(void)  __attribute__((weak, alias ("Default_Handler")));
void CAN1_RX1_IRQHandler(void)  __attribute__((weak, alias ("Default_Handler")));
void CAN1_SCE_IRQHandler(void)  __attribute__((weak, alias ("Default_Handler")));
void EXTI9_5_IRQHandler(void)   __attribute__((weak, alias ("Default_Handler")));
void TIM1_BRK_TIM9_IRQHandler(void)
                                __attribute__((weak, alias ("Default_Handler")));
void TIM1_UP_TIM10_IRQHandler(void)
                                __attribute__((weak, alias ("Default_Handler")));
void TIM1_TRG_COM_TIM11_IRQHandler(void)
                                __attribute__((weak, alias ("Default_Handler")));
void TIM1_CC_IRQHandler(void)   __attribute__((weak, alias ("Default_Handler")));
void TIM2_IRQHandler(void)      __attribute__((weak, alias ("Default_Handler")));
void TIM3_IRQHandler(void)      __attribute__((weak, alias ("Default_Handler")));
void TIM4_IRQHandler(void)      __attribute__((weak, alias ("Default_Handler")));
void I2C1_EV_IRQHandler(void)   __attribute__((weak, alias ("Default_Handler")));
void I2C1_ER_IRQHandler(void)   __attribute__((weak, alias ("Default_Handler")));
void I2C2_EV_IRQHandler(void)   __attribute__((weak, alias ("Default_Handler")));
void I2C2_ER_IRQHandler(void)   __attribute__((weak, alias ("Default_Handler")));
void SPI1_IRQHandler(void)      __attribute__((weak, alias ("Default_Handler")));
void SPI2_IRQHandler(void)      __attribute__((weak, alias ("Default_Handler")));
void USART1_IRQHandler(void)    __attribute__((weak, alias ("Default_Handler")));
void USART2_IRQHandler(void)    __attribute__((weak, alias ("Default_Handler")));
void USART3_IRQHandler(void)    __attribute__((weak, alias ("Default_Handler")));
void EXTI15_10_IRQHandler(void) __attribute__((weak, alias ("Default_Handler")));
void RTC_Alarm_IRQHandler(void) __attribute__((weak, alias ("Default_Handler")));
void OTG_FS_WKUP_IRQHandler(void)
                                __attribute__((weak, alias ("Default_Handler")));
void TIM8_BRK_TIM12_IRQHandler(void)
                                __attribute__((weak, alias ("Default_Handler")));
void TIM8_UP_TIM13_IRQHandler(void)
                                __attribute__((weak, alias ("Default_Handler")));
void TIM8_TRG_COM_TIM14_IRQHandler(void)    __attribute__((weak, alias ("Default_Handler")));
void TIM8_CC_IRQHandler(void)   __attribute__((weak, alias ("Default_Handler")));
void DMA1_Stream7_IRQHandler(void)
                                __attribute__((weak, alias ("Default_Handler")));
void FSMC_IRQHandler(void)      __attribute__((weak, alias ("Default_Handler")));
void SDIO_IRQHandler(void)      __attribute__((weak, alias ("Default_Handler")));
void TIM5_IRQHandler(void)      __attribute__((weak, alias ("Default_Handler")));
void SPI3_IRQHandler(void)      __attribute__((weak, alias ("Default_Handler")));
void UART4_IRQHandler(void)     __attribute__((weak, alias ("Default_Handler")));
void UART5_IRQHandler(void)     __attribute__((weak, alias ("Default_Handler")));
void TIM6_DAC_IRQHandler(void)  __attribute__((weak, alias ("Default_Handler")));
void TIM7_IRQHandler(void)      __attribute__((weak, alias ("Default_Handler")));
void DMA2_Stream0_IRQHandler(void)
                                __attribute__((weak, alias ("Default_Handler")));
void DMA2_Stream1_IRQHandler(void)
                                __attribute__((weak, alias ("Default_Handler")));
void DMA2_Stream2_IRQHandler(void)
                                __attribute__((weak, alias ("Default_Handler")));
void DMA2_Stream3_IRQHandler(void)
                                __attribute__((weak, alias ("Default_Handler")));
void DMA2_Stream4_IRQHandler(void)
                                __attribute__((weak, alias ("Default_Handler")));
void ETH_IRQHandler(void)       __attribute__((weak, alias ("Default_Handler")));
void ETH_WKUP_IRQHandler(void)  __attribute__((weak, alias ("Default_Handler")));
void CAN2_TX_IRQHandler(void)   __attribute__((weak, alias ("Default_Handler")));
void CAN2_RX0_IRQHandler(void)  __attribute__((weak, alias ("Default_Handler")));
void CAN2_RX1_IRQHandler(void)  __attribute__((weak, alias ("Default_Handler")));
void CAN2_SCE_IRQHandler(void)  __attribute__((weak, alias ("Default_Handler")));
void OTG_FS_IRQHandler(void)    __attribute__((weak, alias ("Default_Handler")));
void DMA2_Stream5_IRQHandler(void)
                                __attribute__((weak, alias ("Default_Handler")));
void DMA2_Stream6_IRQHandler(void)
                                __attribute__((weak, alias ("Default_Handler")));
void DMA2_Stream7_IRQHandler(void)
                                __attribute__((weak, alias ("Default_Handler")));
void USART6_IRQHandler(void)    __attribute__((weak, alias ("Default_Handler")));
void I2C3_EV_IRQHandler(void)   __attribute__((weak, alias ("Default_Handler")));
void I2C3_ER_IRQHandler(void)   __attribute__((weak, alias ("Default_Handler")));
void OTG_HS_EP1_OUT_IRQHandler(void)
                                __attribute__((weak, alias ("Default_Handler")));
void OTG_HS_EP1_IN_IRQHandler(void)
                                __attribute__((weak, alias ("Default_Handler")));
void OTG_HS_WKUP_IRQHandler(void)
                                __attribute__((weak, alias ("Default_Handler")));
void OTG_HS_IRQHandler(void)    __attribute__((weak, alias ("Default_Handler")));
void DCMI_IRQHandler(void)      __attribute__((weak, alias ("Default_Handler")));
void CRYP_IRQHandler(void)      __attribute__((weak, alias ("Default_Handler")));
void HASH_RNG_IRQHandler(void)  __attribute__((weak, alias ("Default_Handler")));
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
    /* External Interrupts */
    (void*)WWDG_IRQHandler,                 /* Window WatchDog              */
    (void*)PVD_IRQHandler,                  /* PVD through EXTI Line detection */
    (void*)TAMP_STAMP_IRQHandler,           /* Tamper and TimeStamps through the EXTI line */
    (void*)RTC_WKUP_IRQHandler,             /* RTC Wakeup through the EXTI line */
    (void*)FLASH_IRQHandler,                /* FLASH                        */
    (void*)RCC_IRQHandler,                  /* RCC                          */
    (void*)EXTI0_IRQHandler,                /* EXTI Line0                   */
    (void*)EXTI1_IRQHandler,                /* EXTI Line1                   */
    (void*)EXTI2_IRQHandler,                /* EXTI Line2                   */
    (void*)EXTI3_IRQHandler,                /* EXTI Line3                   */
    (void*)EXTI4_IRQHandler,                /* EXTI Line4                   */
    (void*)DMA1_Stream0_IRQHandler,         /* DMA1 Stream 0                */
    (void*)DMA1_Stream1_IRQHandler,         /* DMA1 Stream 1                */
    (void*)DMA1_Stream2_IRQHandler,         /* DMA1 Stream 2                */
    (void*)DMA1_Stream3_IRQHandler,         /* DMA1 Stream 3                */
    (void*)DMA1_Stream4_IRQHandler,         /* DMA1 Stream 4                */
    (void*)DMA1_Stream5_IRQHandler,         /* DMA1 Stream 5                */
    (void*)DMA1_Stream6_IRQHandler,         /* DMA1 Stream 6                */
    (void*)ADC_IRQHandler,                  /* ADC1, ADC2 and ADC3s         */
    (void*)CAN1_TX_IRQHandler,              /* CAN1 TX                      */
    (void*)CAN1_RX0_IRQHandler,             /* CAN1 RX0                     */
    (void*)CAN1_RX1_IRQHandler,             /* CAN1 RX1                     */
    (void*)CAN1_SCE_IRQHandler,             /* CAN1 SCE                     */
    (void*)EXTI9_5_IRQHandler,              /* External Line[9:5]s          */
    (void*)TIM1_BRK_TIM9_IRQHandler,        /* TIM1 Break and TIM9          */
    (void*)TIM1_UP_TIM10_IRQHandler,        /* TIM1 Update and TIM10        */
    (void*)TIM1_TRG_COM_TIM11_IRQHandler,   /* TIM1 Trigger and Commutation and TIM11 */
    (void*)TIM1_CC_IRQHandler,              /* TIM1 Capture Compare         */
    (void*)TIM2_IRQHandler,                 /* TIM2                         */
    (void*)TIM3_IRQHandler,                 /* TIM3                         */
    (void*)TIM4_IRQHandler,                 /* TIM4                         */
    (void*)I2C1_EV_IRQHandler,              /* I2C1 Event                   */
    (void*)I2C1_ER_IRQHandler,              /* I2C1 Error                   */
    (void*)I2C2_EV_IRQHandler,              /* I2C2 Event                   */
    (void*)I2C2_ER_IRQHandler,              /* I2C2 Error                   */
    (void*)SPI1_IRQHandler,                 /* SPI1                         */
    (void*)SPI2_IRQHandler,                 /* SPI2                         */
    (void*)USART1_IRQHandler,               /* USART1                       */
    (void*)USART2_IRQHandler,               /* USART2                       */
    (void*)USART3_IRQHandler,               /* USART3                       */
    (void*)EXTI15_10_IRQHandler,            /* External Line[15:10]s        */
    (void*)RTC_Alarm_IRQHandler,            /* RTC Alarm (A and B) through EXTI Line */
    (void*)OTG_FS_WKUP_IRQHandler,          /* USB OTG FS Wakeup through EXTI line */
    (void*)TIM8_BRK_TIM12_IRQHandler,       /* TIM8 Break and TIM12         */
    (void*)TIM8_UP_TIM13_IRQHandler,        /* TIM8 Update and TIM13        */
    (void*)TIM8_TRG_COM_TIM14_IRQHandler,   /* TIM8 Trigger and Commutation and TIM14 */
    (void*)TIM8_CC_IRQHandler,              /* TIM8 Capture Compare         */
    (void*)DMA1_Stream7_IRQHandler,         /* DMA1 Stream7                 */
    (void*)FSMC_IRQHandler,                 /* FSMC                         */
    (void*)SDIO_IRQHandler,                 /* SDIO                         */
    (void*)TIM5_IRQHandler,                 /* TIM5                         */
    (void*)SPI3_IRQHandler,                 /* SPI3                         */
    (void*)UART4_IRQHandler,                /* UART4                        */
    (void*)UART5_IRQHandler,                /* UART5                        */
    (void*)TIM6_DAC_IRQHandler,             /* TIM6 and DAC1&2 underrun errors */
    (void*)TIM7_IRQHandler,                 /* TIM7                         */
    (void*)DMA2_Stream0_IRQHandler,         /* DMA2 Stream 0                */
    (void*)DMA2_Stream1_IRQHandler,         /* DMA2 Stream 1                */
    (void*)DMA2_Stream2_IRQHandler,         /* DMA2 Stream 2                */
    (void*)DMA2_Stream3_IRQHandler,         /* DMA2 Stream 3                */
    (void*)DMA2_Stream4_IRQHandler,         /* DMA2 Stream 4                */
    (void*)ETH_IRQHandler,                  /* Ethernet                     */
    (void*)ETH_WKUP_IRQHandler,             /* Ethernet Wakeup through EXTI line */
    (void*)CAN2_TX_IRQHandler,              /* CAN2 TX                      */
    (void*)CAN2_RX0_IRQHandler,             /* CAN2 RX0                     */
    (void*)CAN2_RX1_IRQHandler,             /* CAN2 RX1                     */
    (void*)CAN2_SCE_IRQHandler,             /* CAN2 SCE                     */
    (void*)OTG_FS_IRQHandler,               /* USB OTG FS                   */
    (void*)DMA2_Stream5_IRQHandler,         /* DMA2 Stream 5                */
    (void*)DMA2_Stream6_IRQHandler,         /* DMA2 Stream 6                */
    (void*)DMA2_Stream7_IRQHandler,         /* DMA2 Stream 7                */
    (void*)USART6_IRQHandler,               /* USART6                       */
    (void*)I2C3_EV_IRQHandler,              /* I2C3 event                   */
    (void*)I2C3_ER_IRQHandler,              /* I2C3 error                   */
    (void*)OTG_HS_EP1_OUT_IRQHandler,       /* USB OTG HS End Point 1 Out   */
    (void*)OTG_HS_EP1_IN_IRQHandler,        /* USB OTG HS End Point 1 In    */
    (void*)OTG_HS_WKUP_IRQHandler,          /* USB OTG HS Wakeup through EXTI */
    (void*)OTG_HS_IRQHandler,               /* USB OTG HS                   */
    (void*)DCMI_IRQHandler,                 /* DCMI                         */
    (void*)CRYP_IRQHandler,                 /* CRYP crypto                  */
    (void*)HASH_RNG_IRQHandler,             /* Hash and Rng                 */
    (void*)FPU_IRQHandler,                  /* FPU                          */
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

