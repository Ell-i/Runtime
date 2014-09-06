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
 * @author Otso Jousimaa <otso@ojousima.net> 2014
 */

#include <stm32f334nucleo_timer.h>

/*
 * Boot-time definitions for the STM32F334 series MCU timers.
 */

#ifdef __cplusplus
# define D16(p, r, v) { v }
#else
# ifndef offsetof
#  define offsetof(st, m) ((uint32_t)(&((st *)0)->m))
# endif
# define D16(p, r, v) [offsetof(p, r)/sizeof(uint32_t)] = { v }
#endif

// TODO \/
const SystemInitRecordData16Only TIM_INIT_DefaultRecords[] = {
    D16(TIM_TypeDef, CR1, 0),      /* Disable the counter */
    D16(TIM_TypeDef, CR2, 0),      /* Default value */
    D16(TIM_TypeDef, SMCR, 0),     /* Default value */
    D16(TIM_TypeDef, DIER, 0),     /* Default value */
    D16(TIM_TypeDef, CCMR1,
        0
        |   TIM_CCMR1_OC2M_PWM1 /* 110 = CH2 PWM Mode 1 */
        |   TIM_CCMR1_OC2PE     /* 1   = CH2 preload register in use */
        |   TIM_CCMR1_OC2FE     /* 1   = CH2 compare fast mode enabled */
        | ! TIM_CCMR1_CC2S      /* 00  = CH2 is output */
        |   TIM_CCMR1_OC1M_PWM1 /* 110 = CH1 PWM Mode 1 */
        |   TIM_CCMR1_OC1PE     /* 1   = CH1 preload register in use */
        |   TIM_CCMR1_OC1FE     /* 1   = CH1 compare fast mode enabled */
        | ! TIM_CCMR1_CC1S      /* 00  = CH1 is output */
        ),
    D16(TIM_TypeDef, CCMR2,
        0
        |   TIM_CCMR2_OC4M_PWM1 /* 110 = CH4 PWM Mode 1 */
        |   TIM_CCMR2_OC4PE     /* 1   = CH4 preload register in use */
        |   TIM_CCMR2_OC4FE     /* 1   = CH4 compare fast mode enabled */
        | ! TIM_CCMR2_CC4S      /* 00  = CH4 is output */
        |   TIM_CCMR2_OC3M_PWM1 /* 110 = CH3 PWM Mode 1 */
        |   TIM_CCMR2_OC3PE     /* 1   = CH3 preload register in use */
        |   TIM_CCMR2_OC3FE     /* 1   = CH3 compare fast mode enabled */
        | ! TIM_CCMR2_CC3S      /* 00  = CH3 is output */
        ),
    D16(TIM_TypeDef, CCER,
        0
        | ! TIM_CCER_CC4P       /* 0   = OC4  active high */
        |   TIM_CCER_CC4E       /* 1   = OC4  is actively output */
        | ! TIM_CCER_CC3NP      /* 0   = OC3N active high */
        | ! TIM_CCER_CC3NE      /* 0   = OC3N is not output */
        | ! TIM_CCER_CC3P       /* 0   = OC3  active high */
        |   TIM_CCER_CC3E       /* 1   = OC3  is actively output */
        | ! TIM_CCER_CC2NP      /* 0   = OC2N active high */
        | ! TIM_CCER_CC2NE      /* 0   = OC2N is not output */
        | ! TIM_CCER_CC2P       /* 0   = OC2  active high */
        |   TIM_CCER_CC2E       /* 1   = OC2  is actively output */
        | ! TIM_CCER_CC1NP      /* 0   = OC1N active high */
        | ! TIM_CCER_CC1NE      /* 0   = OC1N is not output */
        | ! TIM_CCER_CC1P       /* 0   = OC1  active high */
        |   TIM_CCER_CC1E       /* 1   = OC1  is actively output */
        ),
    D16(TIM_TypeDef, BDTR,
        0
        |   TIM_BDTR_MOE        /* 1   = Main output enable */
        |   TIM_BDTR_AOE        /* 1   = Automatic output enable */
        | ! TIM_BDTR_BKP        /* 0   = BRK is active low, default value */
        | ! TIM_BDTR_BKE        /* 0   = Break inputs disabled */
        |   TIM_BDTR_OSSR       /* 1   = OC/OCN outputs are enabled */
        |   TIM_BDTR_OSSI       /* 1   = OC/OCN outputs are forced to idle level when inactive */
        | ! TIM_BDTR_LOCK       /* 00  = No bits are write proteced */
        | ! TIM_BDTR_DTG        /* 0   = No dead time */
        ),

    D16(TIM_TypeDef, PSC,   383),      /* 48MHz / (383+1) = 125 kHz (125 000 Hz) */
    D16(TIM_TypeDef, ARR,   255),      /* 125 kHz / 256 = 488 Hz */
    D16(TIM_TypeDef, CCR1,  0),        /* Boot with 0% duty */
    D16(TIM_TypeDef, CCR2,  0),        /* Boot with 0% duty */
    D16(TIM_TypeDef, CCR3,  0),        /* Boot with 0% duty */
    D16(TIM_TypeDef, CCR4,  0),        /* Boot with 0% duty */
};


const SystemInitRecordData16Only TIM_INIT_EnableRecords[] = {
    D16(TIM_TypeDef, CR1,
        0
        | ! TIM_CR1_CKD         /* 00 = Clock divide by 1 */
        |   TIM_CR1_ARPE        /* 1  = Auto-reload preload enabled, ARR buffered */
        | ! TIM_CR1_CMS         /* 00 = Edge-aligned mode */
        | ! TIM_CR1_DIR         /* 0  = Upcounter */
        | ! TIM_CR1_OPM         /* 0  = Continuous */
        | ! TIM_CR1_URS         /* 0  = All UEV sources generate interrupt, if enabled */
        | ! TIM_CR1_UDIS        /* 0  = Update events are generated, shadow registers updated */
        |   TIM_CR1_CEN         /* 1  = Enable the counter */
        ),
};

// TODO ^ 

/*
 * These macros here generate SystemInitRecord structures to the
 * SYSTEM_INIT_SECTION linker section.  The boot time initialisation
 * code iterates the records from that section, initialising the MCU
 * peripheral timers accordingly.
 */
DEFINE_TIMER(2, 1,  TIM_INIT_DefaultRecords, TIM_INIT_EnableRecords);
DEFINE_TIMER(1, 2,  TIM_INIT_DefaultRecords, TIM_INIT_EnableRecords);
DEFINE_TIMER(1, 3,  TIM_INIT_DefaultRecords, TIM_INIT_EnableRecords);
DEFINE_TIMER(1, 6,  TIM_INIT_DefaultRecords, TIM_INIT_EnableRecords);
DEFINE_TIMER(1, 7,  TIM_INIT_DefaultRecords, TIM_INIT_EnableRecords);
DEFINE_TIMER(2, 15, TIM_INIT_DefaultRecords, TIM_INIT_EnableRecords);
DEFINE_TIMER(2, 16, TIM_INIT_DefaultRecords, TIM_INIT_EnableRecords);
DEFINE_TIMER(2, 17, TIM_INIT_DefaultRecords, TIM_INIT_EnableRecords);

