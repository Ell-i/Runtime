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
#if defined(__STM32F407__)
# include <Register_USART_SR.h>
# include <Register_USART_DR.h>
# include <Register_USART_BRR.h>
# include <Register_USART_CR1.h>
# include <Register_USART_CR2.h>
# include <Register_USART_CR3.h>
# include <Register_USART_GTPR.h>
#elif defined(__STM32F051__) || defined(__STM32F334__)
# include <Register_USART_BRR.h>
# include <Register_USART_CR1.h>
# include <Register_USART_CR2.h>
# include <Register_USART_CR3.h>
# include <Register_USART_GTPR.h>
# include <Register_USART_RTOR.h>
# include <Register_USART_RQR.h>
# include <Register_USART_ISR.h>
# include <Register_USART_ICR.h>
# include <Register_USART_RDR.h>
# include <Register_USART_TDR.h>
#else
# error "Unknown MCU die.  Please define."
#endif

#if defined(__STM32F051__)
# include <stm32f0xx.h>
#elif defined(__STM32F407__)
# include <stm32f4xx.h>
#elif defined(__STM32F334__)
# include <stm32f3xx.h>
#else
# error "Unknown MCU die.  Please define."
#endif

class UniversalSynchronousAsynchronousReceiverTransmitter {
public:
#if defined(__STM32F407__)
    Register_USART_SR SR;
    Register_USART_DR DR;
    Register_USART_BRR BRR;
    Register_USART_CR1 CR1;
    Register_USART_CR2 CR2;
    Register_USART_CR3 CR3;
    Register_USART_GTPR GTPR;
#elif defined(__STM32F051__) || defined(__STM32F334__)
    Register_USART_CR1 CR1;
    Register_USART_CR2 CR2;
    Register_USART_CR3 CR3;
    Register_USART_BRR BRR;
    Register_USART_GTPR GTPR;
    Register_USART_RTOR RTOR;
    Register_USART_RQR RQR;
    Register_USART_ISR ISR;
    Register_USART_ICR ICR;
    Register_USART_RDR RDR;
    Register_USART_TDR TDR;
#else
# error "Unknown MCU die.  Please define."
#endif
protected:
    UniversalSynchronousAsynchronousReceiverTransmitter()
#if defined(__STM32F407__)
        : SR(USART_SR_TXE)
        , BRR(16)
        , CR1(16)
        , CR2(16)
        , CR3(16)
        , GTPR(16)
#elif defined(__STM32F051__) || defined(__STM32F334__)
        : CR1(32)
        , CR2(32)
        , CR3(32)
        , BRR(32)
        , GTPR(32)
        , ISR(0x00000080)
#else
# error "Unknown MCU die.  Please define."
#endif
        {}
public:
    static UniversalSynchronousAsynchronousReceiverTransmitter USART1;
    static UniversalSynchronousAsynchronousReceiverTransmitter USART2;
    static UniversalSynchronousAsynchronousReceiverTransmitter USART3;

#if defined(__STM32F407__)
    void USART_SR_VALUES( UniversalSynchronousAsynchronousReceiverTransmitter *const usartPort, CALLBACK(USART_SR_CALLBACK) );
    void USART_DR_VALUES( UniversalSynchronousAsynchronousReceiverTransmitter *const usartPort, CALLBACK(USART_DR_CALLBACK) );
    void USART_BRR_VALUES( UniversalSynchronousAsynchronousReceiverTransmitter *const usartPort, CALLBACK(USART_BRR_CALLBACK) );
    void USART_CR1_VALUES( UniversalSynchronousAsynchronousReceiverTransmitter *const usartPort, CALLBACK(USART_CR1_CALLBACK) );
    void USART_CR2_VALUES( UniversalSynchronousAsynchronousReceiverTransmitter *const usartPort, CALLBACK(USART_CR2_CALLBACK) );
    void USART_CR3_VALUES( UniversalSynchronousAsynchronousReceiverTransmitter *const usartPort, CALLBACK(USART_CR3_CALLBACK) );
    void USART_GTPR_VALUES( UniversalSynchronousAsynchronousReceiverTransmitter *const usartPort, CALLBACK(USART_GTPR_CALLBACK) );
#elif defined(__STM32F051__) || defined(__STM32F334__)
    void USART_BRR_VALUES( UniversalSynchronousAsynchronousReceiverTransmitter *const usartPort, CALLBACK(USART_BRR_CALLBACK) );
    void USART_CR1_VALUES( UniversalSynchronousAsynchronousReceiverTransmitter *const usartPort, CALLBACK(USART_CR1_CALLBACK) );
    void USART_CR2_VALUES( UniversalSynchronousAsynchronousReceiverTransmitter *const usartPort, CALLBACK(USART_CR2_CALLBACK) );
    void USART_CR3_VALUES( UniversalSynchronousAsynchronousReceiverTransmitter *const usartPort, CALLBACK(USART_CR3_CALLBACK) );
    void USART_GTPR_VALUES( UniversalSynchronousAsynchronousReceiverTransmitter *const usartPort, CALLBACK(USART_GTPR_CALLBACK) );
    void USART_RTOR_VALUES( UniversalSynchronousAsynchronousReceiverTransmitter *const usartPort, CALLBACK(USART_RTOR_CALLBACK) );
    void USART_RQR_VALUES( UniversalSynchronousAsynchronousReceiverTransmitter *const usartPort, CALLBACK(USART_RQR_CALLBACK) );
    void USART_ISR_VALUES( UniversalSynchronousAsynchronousReceiverTransmitter *const usartPort, CALLBACK(USART_ISR_CALLBACK) );
    void USART_ICR_VALUES( UniversalSynchronousAsynchronousReceiverTransmitter *const usartPort, CALLBACK(USART_ICR_CALLBACK) );
    void USART_RDR_VALUES( UniversalSynchronousAsynchronousReceiverTransmitter *const usartPort, CALLBACK(USART_RDR_CALLBACK) );
    void USART_TDR_VALUES( UniversalSynchronousAsynchronousReceiverTransmitter *const usartPort, CALLBACK(USART_TDR_CALLBACK) );
#else
# error "Unknown MCU die.  Please define."
#endif
};

UniversalSynchronousAsynchronousReceiverTransmitter *const USART1 =
    &UniversalSynchronousAsynchronousReceiverTransmitter::USART1;
UniversalSynchronousAsynchronousReceiverTransmitter *const USART2 =
    &UniversalSynchronousAsynchronousReceiverTransmitter::USART2;
UniversalSynchronousAsynchronousReceiverTransmitter *const USART3 =
    &UniversalSynchronousAsynchronousReceiverTransmitter::USART2;
#if defined(__STM32F407__)
    UniversalSynchronousAsynchronousReceiverTransmitter *const STM32F4DiscoveryUsartArray[] = { USART1, USART2 };
#elif defined(__STM32F334__)
    UniversalSynchronousAsynchronousReceiverTransmitter *const STM32F334NucleoUsartArray[]  = { USART1, USART2, USART3 };
#elif defined(__STM32F051__)
    UniversalSynchronousAsynchronousReceiverTransmitter *const EllduinoUsartArray[]         = { USART2, USART1 };
#else
# error "Unknown MCU die.  Please define."
#endif

#endif //_USART_H_
