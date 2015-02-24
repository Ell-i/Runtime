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

#include <Register_SPI_SR.h>

# if defined(__STM32F051__)
#  include <stm32f0xx.h>
# elif defined(__STM32F407__)
#  include <stm32f4xx.h>
# elif defined(__STM32F334__)
#  include <stm32f3xx.h>
# else
#  error "Unknown MCU."
# endif

uint32_t Register_SPI_SR::operator = (uint32_t arg) {
    printout("=", arg);
    return value_;
}

uint16_t Register_SPI_SR::operator &  (uint16_t arg) {
    dr_.printout("=", dr_.value_);
    printout("&(16b)", value_ & arg);
    // XXX SPI_SR_FRLVL should probably be part of value_,
    // but defining it in the constructor causes a circular
    // makefile dependency.  Hence we "cheat" and add it here.  YMMV.
    uint32_t v = value_;
#ifdef SPI_SR_FRLVL
    v |= SPI_SR_FRLVL;
#endif
    return v & arg;
}

uint16_t Register_SPI_SR::operator &  (uint32_t arg) {
    dr_.printout("=", dr_.value_);
    printout("&", value_ & arg);
    // XXX SPI_SR_FRLVL should probably be part of value_,
    // but defining it in the constructor causes a circular
    // makefile dependency.  Hence we "cheat" and add it here.  YMMV.
    uint32_t v = value_;
#ifdef SPI_SR_FRLVL
    v |= SPI_SR_FRLVL;
#endif
    return v & arg;
}
