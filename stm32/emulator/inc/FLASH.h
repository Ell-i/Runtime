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

class Flash {
public:
    DEFINE_REGISTER(32, FLASH, ACR,     0x0000000);
    DEFINE_REGISTER(32, FLASH, KEYR,    0x0000000);
    DEFINE_REGISTER(32, FLASH, OPTKEYR, 0x0000000);
    DEFINE_REGISTER(32, FLASH, SR,      0x0000000);
    DEFINE_REGISTER(32, FLASH, CR,      0x0000080);
protected:
    Flash()
        : ACR()
        , CR()
        {}
public:
    static Flash FLASH;
};

Flash *const FLASH = &Flash::FLASH;
