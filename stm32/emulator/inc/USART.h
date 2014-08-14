/*
 * Copyright (c) 2014 ELL-i co-operative.
 *
 * This is part of ELL-i software.
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
 */

#ifndef _USART_H_
#define _USART_H_

#include <Register.h>

#ifdef __STM32F051__
# include <stm32f0xx.h>
#endif
#ifdef __STM32F407__
# include <stm32f4xx.h>
#endif

class UniversalSynchronousAsynchronousReceiverTransmitter {
public:
    DEFINE_REGISTER(32, USART, CR1,      0);
    DEFINE_REGISTER(32, USART, CR2,      0);
    DEFINE_REGISTER(32, USART, CR3,      0);
    DEFINE_REGISTER(16, USART, BRR,      0);
    DEFINE_REGISTER(16, USART, GTPR,     0);
    DEFINE_REGISTER(32, USART, RTOR,     0);
    DEFINE_REGISTER(16, USART, RQR,      0);
    DEFINE_REGISTER(32, USART, ISR,      USART_ISR_TXE);
    DEFINE_REGISTER(32, USART, ICR,      0);
    DEFINE_REGISTER(16, USART, RDR,      0);
    DEFINE_REGISTER(16, USART, TDR,      0);
protected:
    UniversalSynchronousAsynchronousReceiverTransmitter() {}
public:
    static UniversalSynchronousAsynchronousReceiverTransmitter USART1;
    static UniversalSynchronousAsynchronousReceiverTransmitter USART2;
};

UniversalSynchronousAsynchronousReceiverTransmitter *const USART1 =
    &UniversalSynchronousAsynchronousReceiverTransmitter::USART1;
UniversalSynchronousAsynchronousReceiverTransmitter *const USART2 =
    &UniversalSynchronousAsynchronousReceiverTransmitter::USART2;

#endif //_USART_H_
