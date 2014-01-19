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
    DEFINE_REGISTER(GPIO, MODER, 0);
    //DEFINE_REGISTER(GPIO, OTYPER, 0);
    //DEFINE_REGISTER(GPIO, OSPEEDR, 0);
    DEFINE_REGISTER(GPIO, PUPDR, 0);
    DEFINE_REGISTER(GPIO, IDR, 0);
    //DEFINE_REGISTER(GPIO, ODR, 0);
    DEFINE_REGISTER(GPIO, BSRR, 0);
    //DEFINE_REGISTER(GPIO, LCKR, 0);
    //DEFINE_REGISTER(GPIO, AFR[2], 0);
    DEFINE_REGISTER(GPIO, BRR, 0);
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
};

GeneralPurposeInputOutput *const GPIOA = &GeneralPurposeInputOutput::GPIOA;
GeneralPurposeInputOutput *const GPIOB = &GeneralPurposeInputOutput::GPIOB;
GeneralPurposeInputOutput *const GPIOC = &GeneralPurposeInputOutput::GPIOC;
GeneralPurposeInputOutput *const GPIOD = &GeneralPurposeInputOutput::GPIOD;
GeneralPurposeInputOutput *const GPIOE = &GeneralPurposeInputOutput::GPIOE;
GeneralPurposeInputOutput *const GPIOF = &GeneralPurposeInputOutput::GPIOF;
GeneralPurposeInputOutput *const GPIOG = &GeneralPurposeInputOutput::GPIOG;
GeneralPurposeInputOutput *const GPIOH = &GeneralPurposeInputOutput::GPIOH;
