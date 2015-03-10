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

#include <Register.h>
#include <Register_FLASH_ACR.h>
#include <Register_FLASH_KEYR.h>
#include <Register_FLASH_OPTKEYR.h>
#include <Register_FLASH_SR.h>
#include <Register_FLASH_CR.h>

class Flash {
public:
    //DEFINE_REGISTER(32, FLASH, ACR,     0x0000000);
    //DEFINE_REGISTER(32, FLASH, KEYR,    0x0000000);
    //DEFINE_REGISTER(32, FLASH, OPTKEYR, 0x0000000);
    //DEFINE_REGISTER(32, FLASH, SR,      0x0000000);
    //DEFINE_REGISTER(32, FLASH, CR,      0x0000080);
    Register_FLASH_ACR ACR;
    Register_FLASH_KEYR KEYR;
    Register_FLASH_OPTKEYR OPTKEYR;
    Register_FLASH_SR SR;
    Register_FLASH_CR CR;
protected:
    Flash()
        : CR(0x0000080)
        {}
public:
    static Flash FLASH;

    void FLASH_ACR_VALUES( Flash *const flash, CALLBACK(FLASH_ACR_CALLBACK) );
    void FLASH_KEYR_VALUES( Flash *const flash, CALLBACK(FLASH_KEYR_CALLBACK) );
    void FLASH_OPTKEYR_VALUES( Flash *const flash, CALLBACK(FLASH_OPTKEYR_CALLBACK) );
    void FLASH_SR_VALUES( Flash *const flash, CALLBACK(FLASH_SR_CALLBACK) );
    void FLASH_CR_VALUES( Flash *const flash, CALLBACK(FLASH_CR_CALLBACK) );
};

Flash *const FLASH = &Flash::FLASH;
