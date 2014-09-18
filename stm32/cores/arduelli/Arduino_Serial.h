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

#ifndef _ARDUINO_SERIAL_H_
#define _ARDUINO_SERIAL_H_

#if defined(ELLI_STM32F051_ELLDUINO)
# include <stm32f0xx.h>       // XXX To be placed into the variant.h!
# include <ellduino_gpio.h>   // XXX To be placed into the variant.h!
# include <ellduino_usart.h>  // XXX To be placed into the variant.h!
#elif defined(ELLI_STM32F407_DISCOVERY)
# include <stm32f4xx.h>              // XXX To be placed into the variant.h!
# include <stm32f4discovery_gpio.h>  // XXX To be placed into the variant.h!
# include <stm32f4discovery_usart.h> // XXX To be placed into the variant.h!
#elif defined(ELLI_STM32F334_NUCLEO)
# include <stm32f3xx.h>           // XXX To be placed into the variant.h!
# include <stm32f334nucleo_gpio.h>  // XXX To be placed into the variant.h!
# include <stm32f334nucleo_usart.h> // XXX To be placed into the variant.h!
#else
# error "Unknown board.  Please define."
#endif

#include <arduelli_thread.h> // XXX TBD -- is this the right file name?
#include <Arduino_Stream.h>

class SerialClass : public Stream {
public:
    const USART usart_;
    constexpr SerialClass(const USART &);
    void begin(uint32_t) const;
    void write(uint8_t) const;
};

#define DEFINE_SERIAL(usart_number, tx_letter, tx_pin, tx_af, rx_letter, rx_pin, rx_af) \
    ({ DEFINE_USART_STRUCT(usart_number, tx_letter, tx_pin, tx_af, rx_letter, rx_pin, rx_af) })

constexpr SerialClass::SerialClass(const USART &usart)
    : usart_(usart) {}

ARDUINO_INLINE_MEMBER_FUNCTION
void SerialClass::begin(uint32_t baudrate) const {
    /* Place the GPIO pins into the right alternative function */
    PinFunctionActivate(&usart_.usart_tx_function_);
    PinFunctionActivate(&usart_.usart_rx_function_);

    /* Set the baud rate -- use 16 bit oversampling */
    usart_.usart_->BRR = (SystemCoreClock / baudrate);

    /* Enable the transmitter and the USART */
    usart_.usart_->CR1 |= (USART_CR1_TE | USART_CR1_UE);
}

ARDUINO_INLINE_MEMBER_FUNCTION
void SerialClass::write(uint8_t c) const {

# if defined(STM32F0XX)

    usart_.usart_->TDR = c;
    while ((usart_.usart_->ISR & USART_ISR_TXE) == 0) {
        yield();
    }

# elif defined(STM32F40_41xxx)

    usart_.usart_->DR = c;
    while ((usart_.usart_->SR & USART_SR_TXE) == 0) {
        yield();
    }

# else
#  error "Unsupported MCU."
# endif

}

#endif//_ARDUINO_SERIAL_H_
