/*
 * Copyright (c) 2014 ELL-i co-operative
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
 * @brief The Arduino Serial class
 */

#include <stm32f0xx.h>
#include <ellduino_gpio.h>   // XXX To be placed into the variant.h!
#include <ellduino_usart.h>  // XXX To be placed into the variant.h!
#include <Arduino_Stream.h>

class Serial : public Stream {
public:
    const USART usart_;
    constexpr Serial(const USART &);
    void begin(unsigned long) const;
};

#define DEFINE_SERIAL(usart_number, gpio_letter, tx_pin, af) \
    ({ DEFINE_USART_STRUCT(usart_number, gpio_letter, tx_pin, af) })


constexpr Serial::Serial(const USART &usart)
    : usart_(usart) {}

inline void Serial::begin(unsigned long baudrate) const {
    /* Place the GPIO pins into the right alternative function */
    register uint32_t afr = *usart_.gpio_afr_;
    afr &= usart_.gpio_afr_mask_;
    afr |= usart_.gpio_afr_ones_;
    *usart_.gpio_afr_ = afr;

    /* Place the GPIO pins into the right input/output mode */
    register uint32_t moder = *usart_.gpio_moder_;
    moder &= usart_.gpio_moder_mask_;
    moder |= usart_.gpio_moder_ones_;
    *usart_.gpio_moder_ = moder;

    /* Set the baud rate -- use 16 bit oversampling */
    usart_.usart_->BRR = SystemCoreClock / baudrate;

    /* Enable the transmitter and the USART */
    usart_.usart_->CR1 |= USART_CR1_TE | USART_CR1_UE;
}
