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
 * @author Pekka Nikander <pekka.nikander@ell-i.org>  2014
 *
 * @brief  Macros and data types for PWM timers
 */

#ifndef _ARDUELLI_TIMER_H_
# define _ARDUELLI_TIMER_H_

# include <system_init.h>

/***************************
 *
 * Static, compile-time-only records for boot-time initialisation
 * of PWM timers.
 *
 * For each of the ports, we set the corresponding Enable bit in the
 * RCC AHBENR register.  Other than that, the factory defaults are
 * good enough for us.
 *
 * Note that the actual record is placed at the SYSTEM_INIT_SECTION
 * linker section, causing the boot-time initialisation code called from main() to
 * initialise the timer.  If the timer is not used, the record won't be
 * placed at the .init.default section, and the timer won't be enabled.
 */

/**
 * Declares an timer init record so that they are externally
 * visible.
 */
#  define TIMER_INIT_DEFAULT(timer) \
    extern const SystemInitRecordArray TIM ## timer ## _INIT1, TIM ## timer ## _INIT2, TIM ## timer ## _RCC_INIT

/**
 * Defines an TIMER init record and makes it visible through the
 * @see SYSTEM_INIT_SECTION.
 * @param port The timer as a single numbr
 *
 * See the corresponding definitions in <variant>_timer.c
 *
 * XXX (later): At the moment these are NOT declared as static, to
 * make sure that the compiler does *not* optimise these away.  It
 * would be good for someone to see if the definitions work also if
 * they are static, as they don't need to pollute the name space.
 */

#define DEFINE_TIMER(apbus, timer, init_records1, init_records2)        \
    const SystemInitRecordAddrAndOnes                                   \
      TIM ## timer ## _RCC_INIT_DefaultRecords[] = {                    \
        {                                                               \
            IF(init_r_address) &RCC->APB ## apbus ## ENR,               \
            IF(init_r_ones)    RCC_APB ## apbus ## ENR_TIM ## timer ## EN, \
        },                                                              \
    };                                                                  \
    const SystemInitRecordArray                                         \
      TIM ## timer ## _INIT2                                            \
       __attribute__((section(SYSTEM_INIT_SECTION(2, TIM ## timer))))   \
        = {                                                             \
        IF(init_record_type)   DATA16_ONLY,                             \
        IF(init_record_number) COUNT_OF(init_records2),                 \
        IF(init_record_reserved) 0,                                     \
        { IF(init_record_address16) &TIM ## timer->CR1 },               \
        { IF(init_records_data16_only) init_records2, },                \
    };                                                                  \
    const SystemInitRecordArray                                         \
      TIM ## timer ## _INIT1                                            \
       __attribute__((section(SYSTEM_INIT_SECTION(1, TIM ## timer))))   \
        = {                                                             \
        IF(init_record_type)   DATA16_ONLY,                             \
        IF(init_record_number) COUNT_OF(init_records1),                 \
        IF(init_record_reserved) 0,                                     \
        { IF(init_record_address16) &TIM ## timer->CR1 },               \
        { IF(init_records_data16_only) init_records1, },                \
    };                                                                  \
    const SystemInitRecordArray                                         \
      TIM ## timer ## _RCC_INIT                                         \
       __attribute__((section(SYSTEM_INIT_SECTION(RCC, TIM ## timer)))) \
        = {                                                             \
        IF(init_record_type)   ADDR_AND_ONES,                           \
        IF(init_record_number) COUNT_OF(TIM ## timer ##_RCC_INIT_DefaultRecords), \
        IF(init_record_reserved) 0,                                     \
        { IF(init_record_offset) 0 },                                   \
        { IF(init_records_addr_and_ones) TIM ## timer ## _RCC_INIT_DefaultRecords, }, \
    }

/**
 * A const data structure describing each Arduino-compatible PWM pin
 * in the target boards.  Each variant defines an array of these data
 * structures.  The Arduino PIN numbers act as indices to the array.
 *
 * In the typical case, the PWM pins are described as a static const
 * array, arranged in such a way that the compiler is able to optimise
 * the array completely away, generating code that accesses the PWM
 * registers directly.
 *
 * XXX define fields
 *
 * @see DEFINE_PWM_PIN
 */

struct PWM {
#ifdef EMULATOR
    Timer *const                  pwm_timer; /* Representation of the emulator timer */
#else
    TIM_TypeDef *const            pwm_timer; /* Pointer to the timer registers */
#endif
    volatile preg32_t *const      pwm_ccr;
};

/**
 * Defines a pin in a compact way.  This macro simply expands into a
 * struct initialisation.
 *
 * Used in the <variant>/<variant>_timer.h, to define a static const array of
 * pins.  The array is then optimised away by the compiler.
 *
 * @see struct PWM
 */
#define DEFINE_PWM_PIN(timer, channel) {           \
    IF(pwm_timer)   TIM ## timer,                  \
    IF(pwm_ccr) &((TIM ## timer)->CCR ## channel), \
}


#define DEFINE_PWM_PIN_NONE { 0, 0 }

#endif//_ARDUELLI_PWM_H_
