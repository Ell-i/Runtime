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

#ifdef EMULATOR
#include <Register.h>
#endif

void SystemInitOnesOnly(const SystemInitRecordArray *ra) {
    const SystemInitRecordOnesOnly *r
        = (const SystemInitRecordOnesOnly *)ra->init_records_ones_only;

    for (int i = 0; i < ra->init_record_number; i++) {
        register volatile uint32_t *const a = r->init_r_address + ra->init_record_offset;
        register uint32_t d = *a;
        d |= r->init_r_ones;
        *a = d;
    }
}

void SystemInitOnesAndZeroes(const SystemInitRecordArray *ra) {
    const SystemInitRecordOnesAndZeroes *r
        = (const SystemInitRecordOnesAndZeroes *)ra->init_records_ones_only;

    for (int i = 0; i < ra->init_record_number; i++) {
        register volatile uint32_t *const a = r->init_r_address + ra->init_record_offset;
        register uint32_t d = *a;
        d &= ~r->init_r_zeroes; // Clear the bits to set zero
        d |=  r->init_r_ones;   // Set the one bits be set to one
        *a = d;
    }

}

void SystemInitData16NoAddress(const SystemInitRecordArray *ra) {
    const SystemInitRecordData16NoAddress *r
        = (const SystemInitRecordData16NoAddress *)ra->init_records_data16_no_address;

    register volatile uint32_t *a = ra->init_record_address16;
    for (int i = 0; i < ra->init_record_number; i++) {
        *a = (r++)->init_data16;   // Write 16 bits, advance src pointer
        a++;                       // Advance dst by 32 bits
    }
}

void SystemInitData32NoAddress(const SystemInitRecordArray *ra) {
    const SystemInitRecordData32NoAddress *r
        = (const SystemInitRecordData32NoAddress *)ra->init_records_data32_no_address;

    register volatile uint32_t *a = ra->init_record_address32;
    for (int i = 0; i < ra->init_record_number; i++) {
        *a = r->init_data32;   // Write 32 bits
        a++;                   // Advance by 32 bits
    }
}

/*
 * Function pointer table, indexed by the system_init_r_type enum.
 */
typedef void (*SystemInitFunctionType)(const SystemInitRecordArray *ra);

const SystemInitFunctionType SystemInitFunctions[SYSTEM_INIT_TYPE_NUMBER] = {
    SystemInitOnesOnly,
    SystemInitOnesAndZeroes,
    SystemInitData16NoAddress,
    SystemInitData32NoAddress,
};

/*
 * Start and end addresses of the peripheral initialisation records.
 */
extern unsigned int __peripheral_start, __peripheral_end;

void SystemInitPeripherals(void) {
#ifdef EMULATOR
    // XXX FIXME.  Now we simply jump over the void *__peripheral_start, defined
    // in emulator_pre.c.  Instead of this, in Linux we should use a linker script
    // similar to the Cortex-M0 one, and in Mac OS X use the -alias LD option
    // However, for the latter we know what is the first peripheral, and that
    // we won't know for sure before we implement the segment order file for Mac OS X.
    const SystemInitRecordArray *const peri_start
        = (const SystemInitRecordArray *const)((char *)&__peripheral_start + sizeof(void *const));
#else
    const SystemInitRecordArray *const peri_start
        = (const SystemInitRecordArray *const)&__peripheral_start;
#endif
    const SystemInitRecordArray *const peri_end
        = (const SystemInitRecordArray *const)&__peripheral_end;

    for (register const SystemInitRecordArray *ir = peri_start; ir < peri_end; ir++) {
#ifdef EMULATOR
        std::cout << "InitRecord: " << (uint32_t)ir << " type: " << ir->init_record_type
                  << " count: " << (uint32_t)ir->init_record_number << '\n';
#endif
        SystemInitFunctions[ir->init_record_type](ir);
    }
}
