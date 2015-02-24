/*
 * Copyright (c) 2014 ELL-i co-op.
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

#include <Arduino.h>
#include <SPI.h>
//#include <SCB.h>
//#include <PWR.h>
//#include <FLASH.h>

/**
 * C test wrappers for calling our APIs from Robot Framework Python code
 *
 * For compile time efficiency, most of the Ell-i Runtime APIs are defined
 * as inline functions.  Here we create simple non-inline C wrappers
 * for them, making it easier to call them from the Python code when
 * we run the test cases against the emulator.
 */

extern "C" {
    /*
     * The actual C test wrappers.  For the individual functions,
     * see the actual API call.
     */

    /*
     * This is a dummy main, called by startup code, doing nothing.
     */
    int main() {
        return 0;
    }

//######################################################################################################//
//                         Arduino Fuctions Interface
//--------------------------------------------------------------------------------------------------------
    /*
     * C interface for the Arduino Digital API calls
     */
    void t_pinMode(pin_t pin, const enum pin_mode mode) {
        pinMode(pin, mode);
    }
    int t_digitalRead(pin_t pin) {
        return digitalRead(pin);
    }
    void t_digitalWrite(pin_t pin, uint32_t val) {
        digitalWrite(pin, val);
    }
//--------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------
    /*
     * C interface for the Arduino Analog API calls
     */
    void t_analogWrite(pin_t pin, uint32_t val) {
        analogWrite(pin, val);
    }
    void t_noAnalogWrite(pin_t pin) {
        noAnalogWrite(pin);
    }
//--------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------
    /*
     * C interface for the Arduino Serial API calls
     */
#if defined(__STM32F407__)
    ARDUINO_GLOBAL_IMMUTABLE class SerialClass STM32F4DiscoverySerialArray[] = { Serial1, Serial2 };
#elif defined(__STM32F334__)
    ARDUINO_GLOBAL_IMMUTABLE class SerialClass STM32F334NucleoSerialArray[]  = { Serial1, Serial2, Serial3 };
#elif defined(__STM32F051__)
    ARDUINO_GLOBAL_IMMUTABLE class SerialClass EllduinoSerialArray[]         = { Serial1, Serial };
#else
# error "Unknown MCU die.  Please define."
#endif

    void t_SerialBegin(uint32_t baudrate, int usartNum) {
#if defined(__STM32F407__)
        STM32F4DiscoverySerialArray[usartNum-1].begin(baudrate);
#elif defined(__STM32F334__)
        STM32F334NucleoSerialArray[usartNum-1].begin(baudrate);
#elif defined(__STM32F051__)
        EllduinoSerialArray[usartNum-1].begin(baudrate);
#else
# error "Unknown MCU die.  Please define."
#endif
    }
    void t_SerialWrite(uint8_t c, int usartNum) {
#if defined(__STM32F407__)
        STM32F4DiscoverySerialArray[usartNum-1].write(c);
#elif defined(__STM32F334__)
        STM32F334NucleoSerialArray[usartNum-1].write(c);
#elif defined(__STM32F051__)
        EllduinoSerialArray[usartNum-1].write(c);
#else
# error "Unknown MCU die.  Please define."
#endif
    }
//--------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------
    /*
     * C interface for the Arduino SPI library API calls
     */
    void t_SPI_begin(const uint8_t ss_pin) {
        SPI.begin(ss_pin);
    }
    void t_SPI_end(const uint8_t ss_pin) {
        SPI.end(ss_pin);
    }
    void t_SPI_setBitOrder(const SPIBitOrder bitOrder) {
        SPI.setBitOrder(bitOrder);
    }
    uint32_t t_SPI_setClockDivider(const uint8_t ss_pin, const SPIClockDivider clockDivider) {
        return SPI.setClockDivider(ss_pin, clockDivider);
    }
    uint32_t t_SPI_setClock(const uint8_t ss_pin, const uint32_t hertz) {
        return SPI.setClock(ss_pin, hertz);
    }
    void t_SPI_setDataMode(uint8_t ss_pin, SPIDataMode dataMode) {
        SPI.setDataMode(ss_pin, dataMode);
    }
    uint8_t t_SPI_transfer(uint8_t ss_pin, uint8_t data) {
        return SPI.transfer(ss_pin, data);
    }
//--------------------------------------------------------------------------------------------------------

//######################################################################################################//

//######################################################################################################//
//                          Callback Fuctions Interface
//--------------------------------------------------------------------------------------------------------
    /*
     * C interface for General Purpose Input Output (GPIO) python callback functions
     */
    void t_GPIO_MODER( const char *port, CALLBACK(GPIO_MODER_CALLBACK) ) {
        GPIOPORT[IDX(port)]->GPIO_MODER_VALUES( GPIOPORT[IDX(port)], GPIO_MODER_CALLBACK );
    }
    void t_GPIO_PUPDR( const char *port, CALLBACK(GPIO_PUPDR_CALLBACK) ) {
        GPIOPORT[IDX(port)]->GPIO_PUPDR_VALUES( GPIOPORT[IDX(port)], GPIO_PUPDR_CALLBACK );
    }
    void t_GPIO_ODR( const char *port, CALLBACK(GPIO_ODR_CALLBACK) ) {
        GPIOPORT[IDX(port)]->GPIO_ODR_VALUES( GPIOPORT[IDX(port)], GPIO_ODR_CALLBACK );
    }
    void t_GPIO_IDR( const char *port, CALLBACK(GPIO_IDR_CALLBACK) ) {
        GPIOPORT[IDX(port)]->GPIO_IDR_VALUES( GPIOPORT[IDX(port)], GPIO_IDR_CALLBACK );

    }
#if defined(__STM32F407__) || defined(__STM32F334__)
    void t_GPIO_BSRRL( const char *port, CALLBACK(GPIO_BSRRL_CALLBACK) ) {
        GPIOPORT[IDX(port)]->GPIO_BSRRL_VALUES( GPIOPORT[IDX(port)], GPIO_BSRRL_CALLBACK );
    }
    void t_GPIO_AFR( const char *port, CALLBACK(GPIO_AFR_CALLBACK) ) {
        GPIOPORT[IDX(port)]->GPIO_AFR_VALUES( GPIOPORT[IDX(port)], GPIO_AFR_CALLBACK );
    }
    void t_GPIO_BSRRH( const char *port, CALLBACK(GPIO_BSRRH_CALLBACK) ) {
        GPIOPORT[IDX(port)]->GPIO_BSRRH_VALUES( GPIOPORT[IDX(port)], GPIO_BSRRH_CALLBACK );
    }
#elif defined(__STM32F051__)
    void t_GPIO_BSRR( const char *port, CALLBACK(GPIO_BSRR_CALLBACK) ) {
        GPIOPORT[IDX(port)]->GPIO_BSRR_VALUES( GPIOPORT[IDX(port)], GPIO_BSRR_CALLBACK );
    }
    void t_GPIO_AFR( const char *port, CALLBACK(GPIO_AFR_CALLBACK) ) {
        GPIOPORT[IDX(port)]->GPIO_AFR_VALUES( GPIOPORT[IDX(port)], GPIO_AFR_CALLBACK );
    }
    void t_GPIO_BRR( const char *port, CALLBACK(GPIO_BRR_CALLBACK) ) {
        GPIOPORT[IDX(port)]->GPIO_BRR_VALUES( GPIOPORT[IDX(port)], GPIO_BRR_CALLBACK );
    }
#else
# error "Unknown MCU die.  Please define."
#endif

//--------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------
    /*
     * C interface for Universal Synchronous Asynchronous Reciever Transmitter (USART) python
     * callback functions
     */
#if defined(__STM32F407__)
    void t_USART_SR( int usartNum, CALLBACK(USART_SR_CALLBACK) ) {
        STM32F4DiscoveryUsartArray[usartNum-1]->USART_SR_VALUES
            (   STM32F4DiscoveryUsartArray[usartNum-1]
                , USART_SR_CALLBACK
            );
    }
    void t_USART_DR( int usartNum, CALLBACK(USART_DR_CALLBACK) ) {
        STM32F4DiscoveryUsartArray[usartNum-1]->USART_DR_VALUES
            (   STM32F4DiscoveryUsartArray[usartNum-1]
                , USART_DR_CALLBACK
            );
    }
    void t_USART_BRR( int usartNum, CALLBACK(USART_BRR_CALLBACK) ) {
        STM32F4DiscoveryUsartArray[usartNum-1]->USART_BRR_VALUES
            (   STM32F4DiscoveryUsartArray[usartNum-1]
                , USART_BRR_CALLBACK
            );
    }
    void t_USART_CR1( int usartNum, CALLBACK(USART_CR1_CALLBACK) ) {
        STM32F4DiscoveryUsartArray[usartNum-1]->USART_CR1_VALUES
            (   STM32F4DiscoveryUsartArray[usartNum-1]
                , USART_CR1_CALLBACK
            );
    }
    void t_USART_CR2( int usartNum, CALLBACK(USART_CR2_CALLBACK) ) {
        STM32F4DiscoveryUsartArray[usartNum-1]->USART_CR2_VALUES
            (   STM32F4DiscoveryUsartArray[usartNum-1]
                , USART_CR2_CALLBACK
            );
    }
    void t_USART_CR3( int usartNum, CALLBACK(USART_CR3_CALLBACK) ) {
        STM32F4DiscoveryUsartArray[usartNum-1]->USART_CR3_VALUES
            (   STM32F4DiscoveryUsartArray[usartNum-1]
                , USART_CR3_CALLBACK
            );
    }
    void t_USART_GTPR( int usartNum, CALLBACK(USART_GTPR_CALLBACK) ) {
        STM32F4DiscoveryUsartArray[usartNum-1]->USART_GTPR_VALUES
            (   STM32F4DiscoveryUsartArray[usartNum-1]
                , USART_GTPR_CALLBACK
            );
    }
#elif defined(__STM32F051__) || defined(__STM32F334__)
    void t_USART_BRR( int usartNum, CALLBACK(USART_BRR_CALLBACK) ) {
#if defined(__STM32F051__)
        EllduinoSerialArray[usartNum-1].usart_.usart_->USART_BRR_VALUES
            (   EllduinoSerialArray[usartNum-1].usart_.usart_
                , USART_BRR_CALLBACK
            );
#elif defined(__STM32F334__)
        STM32F334NucleoSerialArray[usartNum-1].usart_.usart_->USART_BRR_VALUES
            (   STM32F334NucleoSerialArray[usartNum-1].usart_.usart_
                , USART_BRR_CALLBACK
            );
#endif
    }
    void t_USART_CR1( int usartNum, CALLBACK(USART_CR1_CALLBACK) ) {
#if defined(__STM32F051__)
        EllduinoSerialArray[usartNum-1].usart_.usart_->USART_CR1_VALUES
            (   EllduinoSerialArray[usartNum-1].usart_.usart_
                , USART_CR1_CALLBACK
            );
#elif defined(__STM32F334__)
        STM32F334NucleoSerialArray[usartNum-1].usart_.usart_->USART_CR1_VALUES
            (   STM32F334NucleoSerialArray[usartNum-1].usart_.usart_
                , USART_CR1_CALLBACK
            );
#endif
    }
    void t_USART_CR2( int usartNum, CALLBACK(USART_CR2_CALLBACK) ) {
#if defined(__STM32F051__)
        EllduinoSerialArray[usartNum-1].usart_.usart_->USART_CR2_VALUES
            (   EllduinoSerialArray[usartNum-1].usart_.usart_
                , USART_CR2_CALLBACK
            );
#elif defined(__STM32F334__)
        STM32F334NucleoSerialArray[usartNum-1].usart_.usart_->USART_CR2_VALUES
            (   STM32F334NucleoSerialArray[usartNum-1].usart_.usart_
                , USART_CR2_CALLBACK
            );
#endif
    }
    void t_USART_CR3( int usartNum, CALLBACK(USART_CR3_CALLBACK) ) {
#if defined(__STM32F051__)
        EllduinoSerialArray[usartNum-1].usart_.usart_->USART_CR3_VALUES
            (   EllduinoSerialArray[usartNum-1].usart_.usart_
                , USART_CR3_CALLBACK
            );
#elif defined(__STM32F334__)
        STM32F334NucleoSerialArray[usartNum-1].usart_.usart_->USART_CR3_VALUES
            (   STM32F334NucleoSerialArray[usartNum-1].usart_.usart_
                , USART_CR3_CALLBACK
            );
#endif
    }
    void t_USART_GTPR( int usartNum, CALLBACK(USART_GTPR_CALLBACK) ) {
#if defined(__STM32F051__)
        EllduinoSerialArray[usartNum-1].usart_.usart_->USART_GTPR_VALUES
            (   EllduinoSerialArray[usartNum-1].usart_.usart_
                , USART_GTPR_CALLBACK
            );
#elif defined(__STM32F334__)
        STM32F334NucleoSerialArray[usartNum-1].usart_.usart_->USART_GTPR_VALUES
            (   STM32F334NucleoSerialArray[usartNum-1].usart_.usart_
                , USART_GTPR_CALLBACK
            );
#endif
    }
    void t_USART_RTOR( int usartNum, CALLBACK(USART_RTOR_CALLBACK) ) {
#if defined(__STM32F051__)
        EllduinoSerialArray[usartNum-1].usart_.usart_->USART_RTOR_VALUES
            (   EllduinoSerialArray[usartNum-1].usart_.usart_
                , USART_RTOR_CALLBACK
            );
#elif defined(__STM32F334__)
        STM32F334NucleoSerialArray[usartNum-1].usart_.usart_->USART_RTOR_VALUES
            (   STM32F334NucleoSerialArray[usartNum-1].usart_.usart_
                , USART_RTOR_CALLBACK
            );
#endif
    }
    void t_USART_RQR( int usartNum, CALLBACK(USART_RQR_CALLBACK) ) {
#if defined(__STM32F051__)
        EllduinoSerialArray[usartNum-1].usart_.usart_->USART_RQR_VALUES
            (   EllduinoSerialArray[usartNum-1].usart_.usart_
                , USART_RQR_CALLBACK
            );
#elif defined(__STM32F334__)
        STM32F334NucleoSerialArray[usartNum-1].usart_.usart_->USART_RQR_VALUES
            (   STM32F334NucleoSerialArray[usartNum-1].usart_.usart_
                , USART_RQR_CALLBACK
            );
#endif
    }
    void t_USART_ISR( int usartNum, CALLBACK(USART_ISR_CALLBACK) ) {
#if defined(__STM32F051__)
        EllduinoSerialArray[usartNum-1].usart_.usart_->USART_ISR_VALUES
            (   EllduinoSerialArray[usartNum-1].usart_.usart_
                , USART_ISR_CALLBACK
            );
#elif defined(__STM32F334__)
        STM32F334NucleoSerialArray[usartNum-1].usart_.usart_->USART_ISR_VALUES
            (   STM32F334NucleoSerialArray[usartNum-1].usart_.usart_
                , USART_ISR_CALLBACK
            );
#endif
    }
    void t_USART_ICR( int usartNum, CALLBACK(USART_ICR_CALLBACK) ) {
#if defined(__STM32F051__)
        EllduinoSerialArray[usartNum-1].usart_.usart_->USART_ICR_VALUES
            (   EllduinoSerialArray[usartNum-1].usart_.usart_
                , USART_ICR_CALLBACK
            );
#elif defined(__STM32F334__)
        STM32F334NucleoSerialArray[usartNum-1].usart_.usart_->USART_ICR_VALUES
            (   STM32F334NucleoSerialArray[usartNum-1].usart_.usart_
                , USART_ICR_CALLBACK
            );
#endif
    }
    void t_USART_RDR( int usartNum, CALLBACK(USART_RDR_CALLBACK) ) {
#if defined(__STM32F051__)
        EllduinoSerialArray[usartNum-1].usart_.usart_->USART_RDR_VALUES
            (   EllduinoSerialArray[usartNum-1].usart_.usart_
                , USART_RDR_CALLBACK
            );
#elif defined(__STM32F334__)
        STM32F334NucleoSerialArray[usartNum-1].usart_.usart_->USART_RDR_VALUES
            (   STM32F334NucleoSerialArray[usartNum-1].usart_.usart_
                , USART_RDR_CALLBACK
            );
#endif
    }
    void t_USART_TDR( int usartNum, CALLBACK(USART_TDR_CALLBACK) ) {
#if defined(__STM32F051__)
        EllduinoSerialArray[usartNum-1].usart_.usart_->USART_TDR_VALUES
            (   EllduinoSerialArray[usartNum-1].usart_.usart_
                , USART_TDR_CALLBACK
            );
#elif defined(__STM32F334__)
        STM32F334NucleoSerialArray[usartNum-1].usart_.usart_->USART_TDR_VALUES
            (   STM32F334NucleoSerialArray[usartNum-1].usart_.usart_
                , USART_TDR_CALLBACK
            );
#endif
    }
#else
# error "Unknown MCU die.  Please define."
#endif
//--------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------
    /*
     * C interface for System Control Block (SCB) python callback functions
     */
#if defined(__STM32F407__) || defined(__STM32F334__)
    void t_SCB_CPUID( CALLBACK(SCB_CPUID_CALLBACK) ) {
        SCB->SCB_CPUID_VALUES(SCB, SCB_CPUID_CALLBACK);
    }
    void t_SCB_ICSR( CALLBACK(SCB_ICSR_CALLBACK) ) {
        SCB->SCB_ICSR_VALUES(SCB, SCB_ICSR_CALLBACK);
    }
    void t_SCB_VTOR( CALLBACK(SCB_VTOR_CALLBACK) ) {
        SCB->SCB_VTOR_VALUES(SCB, SCB_VTOR_CALLBACK);
    }
#endif
//--------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------
    /*
     * C interface for Power Control (PWR) python callback functions
     */
#if defined(__STM32F407__)
    void t_PWR_CR( CALLBACK(PWR_CR_CALLBACK) ) {
        PWR->PWR_CR_VALUES(PWR, PWR_CR_CALLBACK);
    }
#endif
//--------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------
    /*
     * C interface for Power Control (PWR) python callback functions
     */
    void t_FLASH_ACR( CALLBACK(FLASH_ACR_CALLBACK) ) {
        FLASH->FLASH_ACR_VALUES(FLASH, FLASH_ACR_CALLBACK);
    }
    void t_FLASH_KEYR( CALLBACK(FLASH_KEYR_CALLBACK) ) {
        FLASH->FLASH_KEYR_VALUES(FLASH, FLASH_KEYR_CALLBACK);
    }
    void t_FLASH_OPTKEYR( CALLBACK(FLASH_OPTKEYR_CALLBACK) ) {
        FLASH->FLASH_OPTKEYR_VALUES(FLASH, FLASH_OPTKEYR_CALLBACK);
    }
    void t_FLASH_SR( CALLBACK(FLASH_SR_CALLBACK) ) {
        FLASH->FLASH_SR_VALUES(FLASH, FLASH_SR_CALLBACK);
    }
    void t_FLASH_CR( CALLBACK(FLASH_CR_CALLBACK) ) {
        FLASH->FLASH_CR_VALUES(FLASH, FLASH_CR_CALLBACK);
    }
//--------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------
    /*
     * C interface for Reset Clock Control (RCC) python callback functions
     */
    void t_RCC_CR( CALLBACK(RCC_CR_CALLBACK) ) {
        RCC->RCC_CR_VALUES(RCC, RCC_CR_CALLBACK);
    }
#if defined(__STM32F407__)
    void t_RCC_PLLCFGR( CALLBACK(RCC_PLLCFGR_CALLBACK) ) {
        RCC->RCC_PLLCFGR_VALUES(RCC, RCC_PLLCFGR_CALLBACK);
    }
#endif
    void t_RCC_CFGR( CALLBACK(RCC_CFGR_CALLBACK) ) {
        RCC->RCC_CFGR_VALUES(RCC, RCC_CFGR_CALLBACK);
    }
    void t_RCC_CIR( CALLBACK(RCC_CIR_CALLBACK) ) {
        RCC->RCC_CIR_VALUES(RCC, RCC_CIR_CALLBACK);
    }
    void t_RCC_APB1RSTR( CALLBACK(RCC_APB1RSTR_CALLBACK) ) {
        RCC->RCC_APB1RSTR_VALUES(RCC, RCC_APB1RSTR_CALLBACK);
    }
#if defined(__STM32F407__)
    void t_RCC_AHB1ENR( CALLBACK(RCC_AHB1ENR_CALLBACK) ) {
        RCC->RCC_AHB1ENR_VALUES(RCC, RCC_AHB1ENR_CALLBACK);
    }
#elif defined(__STM32F051__) || defined(__STM32F334__)
    void t_RCC_AHBENR( CALLBACK(RCC_AHBENR_CALLBACK) ) {
        RCC->RCC_AHBENR_VALUES(RCC, RCC_AHBENR_CALLBACK);
    }
#else
# error "Unknown MCU die.  Please define."
#endif
    void t_RCC_APB2ENR( CALLBACK(RCC_APB2ENR_CALLBACK) ) {
        RCC->RCC_APB2ENR_VALUES(RCC, RCC_APB2ENR_CALLBACK);
    }
    void t_RCC_APB1ENR( CALLBACK(RCC_APB1ENR_CALLBACK) ) {
        RCC->RCC_APB1ENR_VALUES(RCC, RCC_APB1ENR_CALLBACK);
    }
    void t_RCC_APB2RSTR( CALLBACK(RCC_APB2RSTR_CALLBACK) ) {
        RCC->RCC_APB2RSTR_VALUES(RCC, RCC_APB2RSTR_CALLBACK);
    }
    void t_RCC_BDCR( CALLBACK(RCC_BDCR_CALLBACK) ) {
        RCC->RCC_BDCR_VALUES(RCC, RCC_BDCR_CALLBACK);
    }
    void t_RCC_CSR( CALLBACK(RCC_CSR_CALLBACK) ) {
        RCC->RCC_CSR_VALUES(RCC, RCC_CSR_CALLBACK);
    }
    void t_RCC_AHBRSTR( CALLBACK(RCC_AHBRSTR_CALLBACK) ) {
        RCC->RCC_AHBRSTR_VALUES(RCC, RCC_AHBRSTR_CALLBACK);
    }
    void t_RCC_CFGR2( CALLBACK(RCC_CFGR2_CALLBACK) ) {
        RCC->RCC_CFGR2_VALUES(RCC, RCC_CFGR2_CALLBACK);
    }
    void t_RCC_CFGR3( CALLBACK(RCC_CFGR3_CALLBACK) ) {
        RCC->RCC_CFGR3_VALUES(RCC, RCC_CFGR3_CALLBACK);
    }
    void t_RCC_CR2( CALLBACK(RCC_CR2_CALLBACK) ) {
        RCC->RCC_CR2_VALUES(RCC, RCC_CR2_CALLBACK);
    }
//--------------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------------
    /*
     * C interface for Timers (TIM<num>) python callback functions
     */
    void t_TIM_CR1( int timNum, CALLBACK(TIM_CR1_CALLBACK) ) {
        TIM[timNum-1]->TIM_CR1_VALUES(TIM[timNum-1], TIM_CR1_CALLBACK);
    }
    void t_TIM_CR2( int timNum, CALLBACK(TIM_CR2_CALLBACK) ) {
        TIM[timNum-1]->TIM_CR2_VALUES(TIM[timNum-1], TIM_CR2_CALLBACK);
    }
    void t_TIM_SMCR( int timNum, CALLBACK(TIM_SMCR_CALLBACK) ) {
        TIM[timNum-1]->TIM_SMCR_VALUES(TIM[timNum-1], TIM_SMCR_CALLBACK);
    }
    void t_TIM_DIER( int timNum, CALLBACK(TIM_DIER_CALLBACK) ) {
        TIM[timNum-1]->TIM_DIER_VALUES(TIM[timNum-1], TIM_DIER_CALLBACK);
    }
    void t_TIM_CCMR1( int timNum, CALLBACK(TIM_CCMR1_CALLBACK) ) {
        TIM[timNum-1]->TIM_CCMR1_VALUES(TIM[timNum-1], TIM_CCMR1_CALLBACK);
    }
    void t_TIM_CCMR2( int timNum, CALLBACK(TIM_CCMR2_CALLBACK) ) {
        TIM[timNum-1]->TIM_CCMR2_VALUES(TIM[timNum-1], TIM_CCMR2_CALLBACK);
    }
    void t_TIM_CCER( int timNum, CALLBACK(TIM_CCER_CALLBACK) ) {
        TIM[timNum-1]->TIM_CCER_VALUES(TIM[timNum-1], TIM_CCER_CALLBACK);
    }
    void t_TIM_BDTR( int timNum, CALLBACK(TIM_BDTR_CALLBACK) ) {
        TIM[timNum-1]->TIM_BDTR_VALUES(TIM[timNum-1], TIM_BDTR_CALLBACK);
    }
    void t_TIM_PSC( int timNum, CALLBACK(TIM_PSC_CALLBACK) ) {
        TIM[timNum-1]->TIM_PSC_VALUES(TIM[timNum-1], TIM_PSC_CALLBACK);
    }
    void t_TIM_ARR( int timNum, CALLBACK(TIM_ARR_CALLBACK) ) {
        TIM[timNum-1]->TIM_ARR_VALUES(TIM[timNum-1], TIM_ARR_CALLBACK);
    }
    void t_TIM_CCR1( int timNum, CALLBACK(TIM_CCR1_CALLBACK) ) {
        TIM[timNum-1]->TIM_CCR1_VALUES(TIM[timNum-1], TIM_CCR1_CALLBACK);
    }
    void t_TIM_CCR2( int timNum, CALLBACK(TIM_CCR2_CALLBACK) ) {
        TIM[timNum-1]->TIM_CCR2_VALUES(TIM[timNum-1], TIM_CCR2_CALLBACK);
    }
    void t_TIM_CCR3( int timNum, CALLBACK(TIM_CCR3_CALLBACK) ) {
        TIM[timNum-1]->TIM_CCR3_VALUES(TIM[timNum-1], TIM_CCR3_CALLBACK);
    }
    void t_TIM_CCR4( int timNum, CALLBACK(TIM_CCR4_CALLBACK) ) {
        TIM[timNum-1]->TIM_CCR4_VALUES(TIM[timNum-1], TIM_CCR4_CALLBACK);
    }
//--------------------------------------------------------------------------------------------------------

//######################################################################################################//

};
