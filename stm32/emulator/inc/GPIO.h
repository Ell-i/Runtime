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

class GeneralPurposeInputOutput {
public:
    DEFINE_REGISTER(32, GPIO, MODER, 0);
    //DEFINE_REGISTER(32, GPIO, OTYPER, 0);
    //DEFINE_REGISTER(32, GPIO, OSPEEDR, 0);
    DEFINE_REGISTER(32, GPIO, PUPDR, 0);
    DEFINE_REGISTER(32, GPIO, IDR, 0);
    //DEFINE_REGISTER(32, GPIO, ODR, 0);
#if defined(__STM32F407__)
    DEFINE_REGISTER(16, GPIO, BSRRL, 0);
    DEFINE_REGISTER(32, GPIO, AFR, 0)[2];
    DEFINE_REGISTER(16, GPIO, BSRRH, 0);
#elif defined(__STM32F051__)
    DEFINE_REGISTER(32, GPIO, BSRR, 0);
    //DEFINE_REGISTER(32, GPIO, LCKR, 0);
    DEFINE_REGISTER(32, GPIO, AFR, 0)[2];
    DEFINE_REGISTER(32, GPIO, BRR, 0);
#else
# error "Unknown MCU die.  Please define."
#endif
protected:
    GeneralPurposeInputOutput() {}
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
