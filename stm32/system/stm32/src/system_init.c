/*
 * Copyright (c) 2013-2014 ELL-i co-operative.
 *
 * This file is part of ELL-i software.
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
 * @author Pekka Nikander <pekka.nikander@ell-i.org>  2013-2014
 */

#include <system_init.h>

void SystemInitOnesOnly(const SystemInitRecordArray *ra) {
    const SystemInitRecordOnesOnly *r
        = (const SystemInitRecordOnesOnly *)ra->init_records_ones_only;

    for (int i = 0; i < ra->init_record_number; i++) {
        register volatile uint32_t *const a = r->init_r_address;
        register uint32_t d = *a;
        d |= r->init_r_ones;
        *a = d;
    }
}

void SystemInitOnesAndZeroes(const SystemInitRecordArray *ra) {
    const SystemInitRecordOnesAndZeroes *r
        = (const SystemInitRecordOnesAndZeroes *)ra->init_records_ones_only;

    for (int i = 0; i < ra->init_record_number; i++) {
        register volatile uint32_t *const a = r->init_r_address;
        register uint32_t d = *a;
        d &= ~r->init_r_zeroes; // Clear the bits to set zero
        d |=  r->init_r_ones;   // Set the one bits be set to one
        *a = d;
    }

}

/*
 * Function pointer table, indexed by the system_init_r_type enum.
 */
typedef void (*SystemInitFunctionType)(const SystemInitRecordArray *ra);

const SystemInitFunctionType SystemInitFunctions[SYSTEM_INIT_TYPE_NUMBER] = {
    SystemInitOnesOnly,
    SystemInitOnesAndZeroes,
};

/*
 * Start and end addresses of the peripheral initialisation records.
 */
extern int __peripheral_start, __peripheral_end;

void SystemInitPeripherals(void) {
    const SystemInitRecordArray *const peri_start
        = (const SystemInitRecordArray *)__peripheral_start;
    const SystemInitRecordArray *const peri_end
        = (const SystemInitRecordArray *)__peripheral_end;

    for (register const SystemInitRecordArray *ir = peri_start; ir < peri_end; ir++) {
        SystemInitFunctions[ir->init_record_type](ir);
    }
}


