/*
 * Copyright (c) 2013 ELL-i co-operative.
 *
 * ELL-i software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * ELL-i software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with ELL-i software.  If not, see <http://www.gnu.org/licenses/>.
 *
 *
 */

#include <system_init.h>

void SystemInitMaskOnly(const SystemInitRecord *records) {
}

void SystemInitMaskAndValue(const SystemInitRecord *records) {
}

/*
 * Function pointer table, indexed by the enum.
 */
typedef void (*SystemInitFunctionType)(const SystemInitRecord *records);

const SystemInitFunctionType SystemInitFunctions[SYSTEM_INIT_TYPES] = {
    SystemInitMaskOnly,
    SystemInitMaskAndValue,
};

/*
 * Start and end addresses of the peripheral initialisation records.
 */
extern int __peripheral_start, __peripheral_end;
const SystemInitRecord *const peri_start = (const SystemInitRecord *)&__peripheral_start;
const SystemInitRecord *const peri_end   = (const SystemInitRecord *)&__peripheral_end;

void SystemInitPeripherals(void) {
    for (register const SystemInitRecord *ir = peri_start; ir < peri_end; ir++) {
        SystemInitFunctions[ir->init_record_type](ir);
    }
}


