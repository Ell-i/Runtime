/*
 * Copyright (c) 2013-2014 ELL-i co-operative.
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
 * @author Asif Sardar <engr.asif.sardar@gmail.com>  2014
 */

#include <USART.h>

UniversalSynchronousAsynchronousReceiverTransmitter
UniversalSynchronousAsynchronousReceiverTransmitter::USART1;
UniversalSynchronousAsynchronousReceiverTransmitter
UniversalSynchronousAsynchronousReceiverTransmitter::USART2;
UniversalSynchronousAsynchronousReceiverTransmitter
UniversalSynchronousAsynchronousReceiverTransmitter::USART3;

#if defined(__STM32F407__)
void UniversalSynchronousAsynchronousReceiverTransmitter::USART_SR_VALUES(
	UniversalSynchronousAsynchronousReceiverTransmitter *const usartPort, CALLBACK(USART_SR_CALLBACK) ) {
	USART_SR_CALLBACK( usartPort->SR.registerPeriph().c_str()
		, usartPort->SR.registerName().c_str()
		, usartPort->SR.registerValue()
		, usartPort->SR.registerOpStr().c_str()
		);
}

void UniversalSynchronousAsynchronousReceiverTransmitter::USART_DR_VALUES(
	UniversalSynchronousAsynchronousReceiverTransmitter *const usartPort, CALLBACK(USART_DR_CALLBACK) ) {
	USART_DR_CALLBACK( usartPort->DR.registerPeriph().c_str()
		, usartPort->DR.registerName().c_str()
		, usartPort->DR.registerValue()
		, usartPort->DR.registerOpStr().c_str()
		);
}

void UniversalSynchronousAsynchronousReceiverTransmitter::USART_BRR_VALUES(
	UniversalSynchronousAsynchronousReceiverTransmitter *const usartPort, CALLBACK(USART_BRR_CALLBACK) ) {
	USART_BRR_CALLBACK( usartPort->BRR.registerPeriph().c_str()
		, usartPort->BRR.registerName().c_str()
		, usartPort->BRR.registerValue()
		, usartPort->BRR.registerOpStr().c_str()
		);
}

void UniversalSynchronousAsynchronousReceiverTransmitter::USART_CR1_VALUES(
	UniversalSynchronousAsynchronousReceiverTransmitter *const usartPort, CALLBACK(USART_CR1_CALLBACK) ) {
	USART_CR1_CALLBACK( usartPort->CR1.registerPeriph().c_str()
		, usartPort->CR1.registerName().c_str()
		, usartPort->CR1.registerValue()
		, usartPort->CR1.registerOpStr().c_str()
		);
}

void UniversalSynchronousAsynchronousReceiverTransmitter::USART_CR2_VALUES(
	UniversalSynchronousAsynchronousReceiverTransmitter *const usartPort, CALLBACK(USART_CR2_CALLBACK) ) {
	USART_CR2_CALLBACK( usartPort->CR2.registerPeriph().c_str()
		, usartPort->CR2.registerName().c_str()
		, usartPort->CR2.registerValue()
		, usartPort->CR2.registerOpStr().c_str()
		);
}

void UniversalSynchronousAsynchronousReceiverTransmitter::USART_CR3_VALUES(
	UniversalSynchronousAsynchronousReceiverTransmitter *const usartPort, CALLBACK(USART_CR3_CALLBACK) ) {
	USART_CR3_CALLBACK( usartPort->CR3.registerPeriph().c_str()
		, usartPort->CR3.registerName().c_str()
		, usartPort->CR3.registerValue()
		, usartPort->CR3.registerOpStr().c_str()
		);
}

void UniversalSynchronousAsynchronousReceiverTransmitter::USART_GTPR_VALUES(
	UniversalSynchronousAsynchronousReceiverTransmitter *const usartPort, CALLBACK(USART_GTPR_CALLBACK) ) {
	USART_GTPR_CALLBACK( usartPort->GTPR.registerPeriph().c_str()
		, usartPort->GTPR.registerName().c_str()
		, usartPort->GTPR.registerValue()
		, usartPort->GTPR.registerOpStr().c_str()
		);
}
#elif defined(__STM32F051__) || defined(__STM32F334__)
void UniversalSynchronousAsynchronousReceiverTransmitter::USART_BRR_VALUES(
	UniversalSynchronousAsynchronousReceiverTransmitter *const usartPort, CALLBACK(USART_BRR_CALLBACK) ) {
	USART_BRR_CALLBACK( usartPort->BRR.registerPeriph().c_str()
		, usartPort->BRR.registerName().c_str()
		, usartPort->BRR.registerValue()
		, usartPort->BRR.registerOpStr().c_str()
		);
}

void UniversalSynchronousAsynchronousReceiverTransmitter::USART_CR1_VALUES(
	UniversalSynchronousAsynchronousReceiverTransmitter *const usartPort, CALLBACK(USART_CR1_CALLBACK) ) {
	USART_CR1_CALLBACK( usartPort->CR1.registerPeriph().c_str()
		, usartPort->CR1.registerName().c_str()
		, usartPort->CR1.registerValue()
		, usartPort->CR1.registerOpStr().c_str()
		);
}

void UniversalSynchronousAsynchronousReceiverTransmitter::USART_CR2_VALUES(
	UniversalSynchronousAsynchronousReceiverTransmitter *const usartPort, CALLBACK(USART_CR2_CALLBACK) ) {
	USART_CR2_CALLBACK( usartPort->CR2.registerPeriph().c_str()
		, usartPort->CR2.registerName().c_str()
		, usartPort->CR2.registerValue()
		, usartPort->CR2.registerOpStr().c_str()
		);
}

void UniversalSynchronousAsynchronousReceiverTransmitter::USART_CR3_VALUES(
	UniversalSynchronousAsynchronousReceiverTransmitter *const usartPort, CALLBACK(USART_CR3_CALLBACK) ) {
	USART_CR3_CALLBACK( usartPort->CR3.registerPeriph().c_str()
		, usartPort->CR3.registerName().c_str()
		, usartPort->CR3.registerValue()
		, usartPort->CR3.registerOpStr().c_str()
		);
}

void UniversalSynchronousAsynchronousReceiverTransmitter::USART_GTPR_VALUES(
	UniversalSynchronousAsynchronousReceiverTransmitter *const usartPort, CALLBACK(USART_GTPR_CALLBACK) ) {
	USART_GTPR_CALLBACK( usartPort->GTPR.registerPeriph().c_str()
		, usartPort->GTPR.registerName().c_str()
		, usartPort->GTPR.registerValue()
		, usartPort->GTPR.registerOpStr().c_str()
		);
}

void UniversalSynchronousAsynchronousReceiverTransmitter::USART_RTOR_VALUES(
	UniversalSynchronousAsynchronousReceiverTransmitter *const usartPort, CALLBACK(USART_RTOR_CALLBACK) ) {
	USART_RTOR_CALLBACK( usartPort->RTOR.registerPeriph().c_str()
		, usartPort->RTOR.registerName().c_str()
		, usartPort->RTOR.registerValue()
		, usartPort->RTOR.registerOpStr().c_str()
		);
}

void UniversalSynchronousAsynchronousReceiverTransmitter::USART_RQR_VALUES(
	UniversalSynchronousAsynchronousReceiverTransmitter *const usartPort, CALLBACK(USART_RQR_CALLBACK) ) {
	USART_RQR_CALLBACK( usartPort->RQR.registerPeriph().c_str()
		, usartPort->RQR.registerName().c_str()
		, usartPort->RQR.registerValue()
		, usartPort->RQR.registerOpStr().c_str()
		);
}

void UniversalSynchronousAsynchronousReceiverTransmitter::USART_ISR_VALUES(
	UniversalSynchronousAsynchronousReceiverTransmitter *const usartPort, CALLBACK(USART_ISR_CALLBACK) ) {
	USART_ISR_CALLBACK( usartPort->ISR.registerPeriph().c_str()
		, usartPort->ISR.registerName().c_str()
		, usartPort->ISR.registerValue()
		, usartPort->ISR.registerOpStr().c_str()
		);
}

void UniversalSynchronousAsynchronousReceiverTransmitter::USART_ICR_VALUES(
	UniversalSynchronousAsynchronousReceiverTransmitter *const usartPort, CALLBACK(USART_ICR_CALLBACK) ) {
	USART_ICR_CALLBACK( usartPort->ICR.registerPeriph().c_str()
		, usartPort->ICR.registerName().c_str()
		, usartPort->ICR.registerValue()
		, usartPort->ICR.registerOpStr().c_str()
		);
}

void UniversalSynchronousAsynchronousReceiverTransmitter::USART_RDR_VALUES(
	UniversalSynchronousAsynchronousReceiverTransmitter *const usartPort, CALLBACK(USART_RDR_CALLBACK) ) {
	USART_RDR_CALLBACK( usartPort->RDR.registerPeriph().c_str()
		, usartPort->RDR.registerName().c_str()
		, usartPort->RDR.registerValue()
		, usartPort->RDR.registerOpStr().c_str()
		);
}

void UniversalSynchronousAsynchronousReceiverTransmitter::USART_TDR_VALUES(
	UniversalSynchronousAsynchronousReceiverTransmitter *const usartPort, CALLBACK(USART_TDR_CALLBACK) ) {
	USART_TDR_CALLBACK( usartPort->TDR.registerPeriph().c_str()
		, usartPort->TDR.registerName().c_str()
		, usartPort->TDR.registerValue()
		, usartPort->TDR.registerOpStr().c_str()
		);
}
#else
# error "Unknown MCU die.  Please define."
#endif
