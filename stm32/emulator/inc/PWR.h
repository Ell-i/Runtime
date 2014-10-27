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
 * @author Pekka Nikander <pekka.nikander@ell-i.org>  2014
 */

#ifndef _PWR_H_
#define _PWR_H_

#include <Register.h>
#if defined(__STM32F407__)
# include <Register_PWR_CR.h>
#endif

class PowerController {
public:
#if defined(__STM32F407__)
    //DEFINE_REGISTER(32, PWR, CR,       0x00004000); // XXX Check, set to reset value
    Register_PWR_CR CR;
#endif
protected:
    PowerController()
#if defined(__STM32F407__)
    	: CR(0x00004000)
#endif
    	{}
public:
    static PowerController PWR;
#if defined(__STM32F407__)
    void PWR_CR_VALUES( PowerController *const pwr, CALLBACK(PWR_CR_CALLBACK) );
#endif
};

PowerController *const PWR = &PowerController::PWR;

#endif //_PWR_H_
