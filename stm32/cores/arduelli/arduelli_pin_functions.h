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
 * @brief  Macros and data types for defining pin alternate functions
 */

#ifndef _ARDUELLI_PIN_FUNCTIONS_H_
# define _ARDUELLI_PIN_FUNCTIONS_H_

# include <system_init.h>

/**
 * A const data structure to define a pin alternate function.
 */

struct PinFunction {
    volatile preg32_t *const      gpio_afr_;       // GPIO AFR for setting the pin alternate function
    const uint32_t                gpio_afr_mask_;  // Bits to clear in the GPIO AFR
    const uint32_t                gpio_afr_ones_;  // Bits to set in the GPIO AFR
    volatile preg32_t *const      gpio_moder_ ;
    const uint32_t                gpio_moder_mask_;
    const uint32_t                gpio_moder_ones_;
};

/**
 * Constant initialiser for a pin alternate function.
 */
#define DEFINE_PIN_FUNCTION(gpio_letter, pin, af)                 \
    {                                                             \
        IF(gpio_afr_)        &GPIO ## gpio_letter->AFR[pin / 8],  \
        IF(gpio_afr_mask_)   ~((GPIO_AFRL_AFRL0) << ((pin % 8) * 4)), \
        IF(gpio_afr_ones_)     (af             ) << ((pin % 8) * 4),\
        IF(gpio_moder_)      &GPIO ## gpio_letter->MODER,         \
        IF(gpio_moder_mask_) ~((GPIO_MODER_MODER0  ) << (pin * 2)), \
        IF(gpio_moder_ones_)   (GPIO_MODER_MODER0_1) << (pin * 2),  \
    }

/**
 * XXX Document
 *
 * XXX Check that inlining really produces smaller code than explicit function!?
 */
static inline
void PinFunctionActivate(const struct PinFunction *const pin) {
    // NB.  Use a pointer so that it is clean C, with plain C++ would use a reference.
    register uint32_t afr = *(pin->gpio_afr_);
    afr &= pin->gpio_afr_mask_;
    afr |= pin->gpio_afr_ones_;
    *(pin->gpio_afr_) = afr;

    /* Place the GPIO pins into the right input/output mode */
    register uint32_t moder = *(pin->gpio_moder_);
    moder &= pin->gpio_moder_mask_;
    moder |= pin->gpio_moder_ones_;
    *(pin->gpio_moder_) = moder;
}

static inline
void PinFunctionDeactivate(const struct PinFunction *const pin) {
    /* Place the GPIO pins into the default (input) mode */
    register uint32_t moder = *(pin->gpio_moder_);
    moder &= pin->gpio_moder_mask_;
    *(pin->gpio_moder_) = moder;
}


#endif//_ARDUELLI_PIN_FUNCTION_H_
