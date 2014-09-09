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

#include <Register.h>
#include <Register_GPIO_MODER.h>
//#include <Register_GPIO_OTYPER.h>
//#include <Register_GPIO_OSPEEDR.h>
#include <Register_GPIO_PUPDR.h>
#include <Register_GPIO_IDR.h>
#include <Register_GPIO_ODR.h>
#include <Register_GPIO_BSRR.h>
//#include <Register_GPIO_LCKR.h>
#include <Register_GPIO_AFR.h>
#include <Register_GPIO_BRR.h>


class GeneralPurposeInputOutput {
public:
    Register_GPIO_MODER MODER;
    //Register_GPIO_OTYPER OTYPER;
    //Register_GPIO_OSPEEDR OSPEEDR;
    Register_GPIO_PUPDR PUPDR;
    Register_GPIO_ODR ODR;
    Register_GPIO_IDR IDR;
#if defined(__STM32F407__) || defined(__STM32F334__)
    // XXX REWRITE
    DEFINE_REGISTER(32, GPIO, MODER, 0);
    //DEFINE_REGISTER(32, GPIO, OTYPER, 0);
    //DEFINE_REGISTER(32, GPIO, OSPEEDR, 0);
    DEFINE_REGISTER(32, GPIO, PUPDR, 0);
    DEFINE_REGISTER(32, GPIO, IDR, 0);
    //DEFINE_REGISTER(32, GPIO, ODR, 0);
#if defined(__STM32F407__) || defined(__STM32F334__)
    //Add partial emulator support for STM32F334
    DEFINE_REGISTER(16, GPIO, BSRRL, 0);
    DEFINE_REGISTER(16, GPIO, BSRRH, 0);
    DEFINE_REGISTER(32, GPIO, AFR, 0)[2];
#elif defined(__STM32F051__)
    Register_GPIO_BSRR BSRR;
    Register_GPIO_AFR AFR[2];
    //Register_GPIO_LCKR LCKR;
    Register_GPIO_BRR BRR;
#else
# error "Unknown MCU die.  Please define."
#endif
protected:
    GeneralPurposeInputOutput()
        : ODR(IDR)
#if defined(__STM32F051__)
        , BSRR(ODR)
        , BRR(ODR)
#endif
        {}
public:
    static GeneralPurposeInputOutput GPIOA;
    static GeneralPurposeInputOutput GPIOB;
    static GeneralPurposeInputOutput GPIOC;
    static GeneralPurposeInputOutput GPIOD;
    static GeneralPurposeInputOutput GPIOE;
    static GeneralPurposeInputOutput GPIOF;
    static GeneralPurposeInputOutput GPIOG;
    static GeneralPurposeInputOutput GPIOH;
    static GeneralPurposeInputOutput GPIOI;
};

GeneralPurposeInputOutput *const GPIOA = &GeneralPurposeInputOutput::GPIOA;
GeneralPurposeInputOutput *const GPIOB = &GeneralPurposeInputOutput::GPIOB;
GeneralPurposeInputOutput *const GPIOC = &GeneralPurposeInputOutput::GPIOC;
GeneralPurposeInputOutput *const GPIOD = &GeneralPurposeInputOutput::GPIOD;
GeneralPurposeInputOutput *const GPIOE = &GeneralPurposeInputOutput::GPIOE;
GeneralPurposeInputOutput *const GPIOF = &GeneralPurposeInputOutput::GPIOF;
GeneralPurposeInputOutput *const GPIOG = &GeneralPurposeInputOutput::GPIOG;
GeneralPurposeInputOutput *const GPIOH = &GeneralPurposeInputOutput::GPIOH;
GeneralPurposeInputOutput *const GPIOI = &GeneralPurposeInputOutput::GPIOI;
