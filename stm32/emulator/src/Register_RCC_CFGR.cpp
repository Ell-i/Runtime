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

#include <Register_RCC_CFGR.h>

uint32_t Register_RCC_CFGR::operator = (uint32_t arg) {
    printout("=", arg);
    /* XXX Keep PLL enabled to prevent loop in the startup code */
    /* NB.  This is really an ugly hack.  We need to think hard how to model this better. */
    value_ = arg | 0x00000008;
    return value_;
}
