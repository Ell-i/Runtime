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

#include <Arduino.h>
#include <SPI.h>
//#include <GPIO.h>

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

    /*
     * C interface for python callback functions
     */
    void t_GPIO_MODER( const char *port, CALLBACK(GPIO_MODER_CALLBACK) ) {
#if defined(__STM32F407__) || defined(__STM32F334__)
        if ( strcmp(port, "A") == 0 ) {
            GPIOA->GPIO_MODER_VALUES(GPIOA, GPIO_MODER_CALLBACK);
        }
        else if ( strcmp(port, "B") == 0 ) {
            GPIOB->GPIO_MODER_VALUES(GPIOB, GPIO_MODER_CALLBACK);
        }
        else if ( strcmp(port, "C") == 0 ) {
            GPIOC->GPIO_MODER_VALUES(GPIOC, GPIO_MODER_CALLBACK);
        }
        else {
            std::cout << "The port is wrong. Please check valid port for the board" << std::endl;
        }
#elif defined(__STM32F051__)
        if ( strcmp(port, "A") == 0 ) {
            GPIOA->GPIO_MODER_VALUES(GPIOA, GPIO_MODER_CALLBACK);
        }
        else if ( strcmp(port, "B") == 0 ) {
            GPIOB->GPIO_MODER_VALUES(GPIOB, GPIO_MODER_CALLBACK);
        }
        else if ( strcmp(port, "C") == 0 ) {
            GPIOC->GPIO_MODER_VALUES(GPIOC, GPIO_MODER_CALLBACK);
        }
        else if ( strcmp(port, "D") == 0 ) {
            GPIOD->GPIO_MODER_VALUES(GPIOD, GPIO_MODER_CALLBACK);
        }
        else if ( strcmp(port, "F") == 0 ) {
            GPIOF->GPIO_MODER_VALUES(GPIOF, GPIO_MODER_CALLBACK);
        }
        else {
            std::cout << "The port is wrong. Please check valid port for the board" << std::endl;
        }
#else
# error "Unknown MCU die.  Please define."
#endif
    }

    void t_GPIO_PUPDR( const char *port, CALLBACK(GPIO_MODER_CALLBACK) ) {
#if defined(__STM32F407__) || defined(__STM32F334__)
        if ( strcmp(port, "A") == 0 ) {
            GPIOA->GPIO_PUPDR_VALUES(GPIOA, GPIO_MODER_CALLBACK);
        }
        else if ( strcmp(port, "B") == 0 ) {
            GPIOB->GPIO_PUPDR_VALUES(GPIOB, GPIO_MODER_CALLBACK);
        }
        else if ( strcmp(port, "C") == 0 ) {
            GPIOC->GPIO_PUPDR_VALUES(GPIOC, GPIO_MODER_CALLBACK);
        }
        else {
            std::cout << "The port is wrong. Please check valid port for the board" << std::endl;
        }
#elif defined(__STM32F051__)
        if ( strcmp(port, "A") == 0 ) {
            GPIOA->GPIO_PUPDR_VALUES(GPIOA, GPIO_MODER_CALLBACK);
        }
        else if ( strcmp(port, "B") == 0 ) {
            GPIOB->GPIO_PUPDR_VALUES(GPIOB, GPIO_MODER_CALLBACK);
        }
        else if ( strcmp(port, "C") == 0 ) {
            GPIOC->GPIO_PUPDR_VALUES(GPIOC, GPIO_MODER_CALLBACK);
        }
        else if ( strcmp(port, "D") == 0 ) {
            GPIOD->GPIO_PUPDR_VALUES(GPIOD, GPIO_MODER_CALLBACK);
        }
        else if ( strcmp(port, "F") == 0 ) {
            GPIOF->GPIO_PUPDR_VALUES(GPIOF, GPIO_MODER_CALLBACK);
        }
        else {
            std::cout << "The port is wrong. Please check valid port for the board" << std::endl;
        }
#else
# error "Unknown MCU die.  Please define."
#endif
    }

    void t_GPIO_ODR( const char *port, CALLBACK(GPIO_MODER_CALLBACK) ) {
#if defined(__STM32F407__) || defined(__STM32F334__)
        if ( strcmp(port, "A") == 0 ) {
            GPIOA->GPIO_ODR_VALUES(GPIOA, GPIO_MODER_CALLBACK);
        }
        else if ( strcmp(port, "B") == 0 ) {
            GPIOB->GPIO_ODR_VALUES(GPIOB, GPIO_MODER_CALLBACK);
        }
        else if ( strcmp(port, "C") == 0 ) {
            GPIOC->GPIO_ODR_VALUES(GPIOC, GPIO_MODER_CALLBACK);
        }
        else {
            std::cout << "The port is wrong. Please check valid port for the board" << std::endl;
        }
#elif defined(__STM32F051__)
        if ( strcmp(port, "A") == 0 ) {
            GPIOA->GPIO_ODR_VALUES(GPIOA, GPIO_MODER_CALLBACK);
        }
        else if ( strcmp(port, "B") == 0 ) {
            GPIOB->GPIO_ODR_VALUES(GPIOB, GPIO_MODER_CALLBACK);
        }
        else if ( strcmp(port, "C") == 0 ) {
            GPIOC->GPIO_ODR_VALUES(GPIOC, GPIO_MODER_CALLBACK);
        }
        else if ( strcmp(port, "D") == 0 ) {
            GPIOD->GPIO_ODR_VALUES(GPIOD, GPIO_MODER_CALLBACK);
        }
        else if ( strcmp(port, "F") == 0 ) {
            GPIOF->GPIO_ODR_VALUES(GPIOF, GPIO_MODER_CALLBACK);
        }
        else {
            std::cout << "The port is wrong. Please check valid port for the board" << std::endl;
        }
#else
# error "Unknown MCU die.  Please define."
#endif
    }

    void t_GPIO_IDR( const char *port, CALLBACK(GPIO_MODER_CALLBACK) ) {
#if defined(__STM32F407__) || defined(__STM32F334__)
        if ( strcmp(port, "A") == 0 ) {
            GPIOA->GPIO_IDR_VALUES(GPIOA, GPIO_MODER_CALLBACK);
        }
        else if ( strcmp(port, "B") == 0 ) {
            GPIOB->GPIO_IDR_VALUES(GPIOB, GPIO_MODER_CALLBACK);
        }
        else if ( strcmp(port, "C") == 0 ) {
            GPIOC->GPIO_IDR_VALUES(GPIOC, GPIO_MODER_CALLBACK);
        }
        else {
            std::cout << "The port is wrong. Please check valid port for the board" << std::endl;
        }
#elif defined(__STM32F051__)
        if ( strcmp(port, "A") == 0 ) {
            GPIOA->GPIO_IDR_VALUES(GPIOA, GPIO_MODER_CALLBACK);
        }
        else if ( strcmp(port, "B") == 0 ) {
            GPIOB->GPIO_IDR_VALUES(GPIOB, GPIO_MODER_CALLBACK);
        }
        else if ( strcmp(port, "C") == 0 ) {
            GPIOC->GPIO_IDR_VALUES(GPIOC, GPIO_MODER_CALLBACK);
        }
        else if ( strcmp(port, "D") == 0 ) {
            GPIOD->GPIO_IDR_VALUES(GPIOD, GPIO_MODER_CALLBACK);
        }
        else if ( strcmp(port, "F") == 0 ) {
            GPIOF->GPIO_IDR_VALUES(GPIOF, GPIO_MODER_CALLBACK);
        }
        else {
            std::cout << "The port is wrong. Please check valid port for the board" << std::endl;
        }
#else
# error "Unknown MCU die.  Please define."
#endif
    }
#if defined(__STM32F407__) || defined(__STM32F334__)
    void t_GPIO_BSRRL( const char *port, CALLBACK(GPIO_MODER_CALLBACK) ) {
        if ( strcmp(port, "A") == 0 ) {
            GPIOA->GPIO_BSRRL_VALUES(GPIOA, GPIO_MODER_CALLBACK);
        }
        else if ( strcmp(port, "B") == 0 ) {
            GPIOB->GPIO_BSRRL_VALUES(GPIOB, GPIO_MODER_CALLBACK);
        }
        else if ( strcmp(port, "C") == 0 ) {
            GPIOC->GPIO_BSRRL_VALUES(GPIOC, GPIO_MODER_CALLBACK);
        }
        else {
            std::cout << "The port is wrong. Please check valid port for the board" << std::endl;
        }
    }

    void t_GPIO_AFR( const char *port, CALLBACK(GPIO_MODER_CALLBACK) ) {
        if ( strcmp(port, "A") == 0 ) {
            GPIOA->GPIO_AFR_VALUES(GPIOA, GPIO_MODER_CALLBACK);
        }
        else if ( strcmp(port, "B") == 0 ) {
            GPIOB->GPIO_AFR_VALUES(GPIOB, GPIO_MODER_CALLBACK);
        }
        else if ( strcmp(port, "C") == 0 ) {
            GPIOC->GPIO_AFR_VALUES(GPIOC, GPIO_MODER_CALLBACK);
        }
        else {
            std::cout << "The port is wrong. Please check valid port for the board" << std::endl;
        }
    }

    void t_GPIO_BSRRH( const char *port, CALLBACK(GPIO_MODER_CALLBACK) ) {
        if ( strcmp(port, "A") == 0 ) {
            GPIOA->GPIO_BSRRH_VALUES(GPIOA, GPIO_MODER_CALLBACK);
        }
        else if ( strcmp(port, "B") == 0 ) {
            GPIOB->GPIO_BSRRH_VALUES(GPIOB, GPIO_MODER_CALLBACK);
        }
        else if ( strcmp(port, "C") == 0 ) {
            GPIOC->GPIO_BSRRH_VALUES(GPIOC, GPIO_MODER_CALLBACK);
        }
        else {
            std::cout << "The port is wrong. Please check valid port for the board" << std::endl;
        }
    }
#elif defined(__STM32F051__)
    void t_GPIO_BSRR( const char *port, CALLBACK(GPIO_MODER_CALLBACK) ) {
        if ( strcmp(port, "A") == 0 ) {
            GPIOA->GPIO_BSRR_VALUES(GPIOA, GPIO_MODER_CALLBACK);
        }
        else if ( strcmp(port, "B") == 0 ) {
            GPIOB->GPIO_BSRR_VALUES(GPIOB, GPIO_MODER_CALLBACK);
        }
        else if ( strcmp(port, "C") == 0 ) {
            GPIOC->GPIO_BSRR_VALUES(GPIOC, GPIO_MODER_CALLBACK);
        }
        else if ( strcmp(port, "D") == 0 ) {
            GPIOD->GPIO_BSRR_VALUES(GPIOD, GPIO_MODER_CALLBACK);
        }
        else if ( strcmp(port, "F") == 0 ) {
            GPIOF->GPIO_BSRR_VALUES(GPIOF, GPIO_MODER_CALLBACK);
        }
        else {
            std::cout << "The port is wrong. Please check valid port for the board" << std::endl;
        }
    }

    void t_GPIO_AFR( const char *port, CALLBACK(GPIO_MODER_CALLBACK) ) {
        if ( strcmp(port, "A") == 0 ) {
            GPIOA->GPIO_AFR_VALUES(GPIOA, GPIO_MODER_CALLBACK);
        }
        else if ( strcmp(port, "B") == 0 ) {
            GPIOB->GPIO_AFR_VALUES(GPIOB, GPIO_MODER_CALLBACK);
        }
        else if ( strcmp(port, "C") == 0 ) {
            GPIOC->GPIO_AFR_VALUES(GPIOC, GPIO_MODER_CALLBACK);
        }
        else if ( strcmp(port, "D") == 0 ) {
            GPIOD->GPIO_AFR_VALUES(GPIOD, GPIO_MODER_CALLBACK);
        }
        else if ( strcmp(port, "F") == 0 ) {
            GPIOF->GPIO_AFR_VALUES(GPIOF, GPIO_MODER_CALLBACK);
        }
        else {
            std::cout << "The port is wrong. Please check valid port for the board" << std::endl;
        }
    }

    void t_GPIO_BRR( const char *port, CALLBACK(GPIO_MODER_CALLBACK) ) {
        if ( strcmp(port, "A") == 0 ) {
            GPIOA->GPIO_BRR_VALUES(GPIOA, GPIO_MODER_CALLBACK);
        }
        else if ( strcmp(port, "B") == 0 ) {
            GPIOB->GPIO_BRR_VALUES(GPIOB, GPIO_MODER_CALLBACK);
        }
        else if ( strcmp(port, "C") == 0 ) {
            GPIOC->GPIO_BRR_VALUES(GPIOC, GPIO_MODER_CALLBACK);
        }
        else if ( strcmp(port, "D") == 0 ) {
            GPIOD->GPIO_BRR_VALUES(GPIOD, GPIO_MODER_CALLBACK);
        }
        else if ( strcmp(port, "F") == 0 ) {
            GPIOF->GPIO_BRR_VALUES(GPIOF, GPIO_MODER_CALLBACK);
        }
        else {
            std::cout << "The port is wrong. Please check valid port for the board" << std::endl;
        }
    }
#else
# error "Unknown MCU die.  Please define."
#endif

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

    /*
     * C interface for the Arduino Analog API calls
     */
    void t_analogWrite(pin_t pin, uint32_t val) {
        analogWrite(pin, val);
    }
    void t_noAnalogWrite(pin_t pin) {
        noAnalogWrite(pin);
    }

    /*
     * C interface for the Arduino Serial object
     */
    void t_SerialBegin(uint32_t baudrate) {
        Serial.begin(baudrate);
    }
    void t_SerialWrite(uint8_t c) {
        Serial.write(c);
    }

    /*
     * C interface for the Arduino SPI library
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
};
