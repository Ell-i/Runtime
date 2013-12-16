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
 */

#ifndef _SYSTEM_INIT_H_
#define _SYSTEM_INIT_H_

#include <stdint.h>

/*
 * From http://stackoverflow.com/questions/1598773/\
 * is-there-a-standard-function-in-c-that-would-return-the-length-of-an-array:
 *
 * In this version if a pointer is mistakenly passed as the argument,
 * the compiler will complain in some cases - specifically if the
 * pointer's size isn't evenly divisible by the size of the object the
 * pointer points to. In that situation a divide-by-zero will cause
 * the compiler to error out. Actually at least one compiler
 * gives a warning instead of an error.
 *
 * That macro doesn't close the door on using it erroneously, but it
 * comes close in straight C.
 */

#define COUNT_OF(x) ((sizeof(x)/sizeof(0[x])) / ((uint32_t)(!(sizeof(x) % sizeof(0[x])))))

typedef struct {
    volatile uint32_t *const init_r_address; /* Address of resister to initialize. */
    const uint32_t           init_r_mask;    /* Bitmask of the bits to set (to ones). */
} SystemInitRecordMaskOnly;

typedef struct {
    volatile uint32_t *const init_r_address; /* Address of resister to initialize. */
    const uint32_t           init_r_mask;    /* Bitmask of the bits to set. */
    const uint32_t           init_r_value;   /* Value to be set at the masked bits.*/
} SystemInitRecordMaskAndValue;

enum system_init_r_type {
    MASK_ONLY = 0,
    MASK_AND_VALUE = 1,
};

#define SYSTEM_INIT_TYPES (MASK_AND_VALUE + 1)

typedef struct {
    const enum system_init_r_type   init_record_type;
    const uint8_t                   init_record_number;
    const union {
        const SystemInitRecordMaskOnly *     init_records_mask_only;
        const SystemInitRecordMaskAndValue * init_records_mask_and_value;
    };
} SystemInitRecord;

#ifdef __cplusplus
extern "C" {
#endif

extern void SystemInitMaskOnly(    const SystemInitRecord *records);
extern void SystemInitMaskAndValue(const SystemInitRecord *records);
extern void SystemInitPeripherals(void);

#ifdef __cplusplus
}
#endif

#endif//_SYSTEM_INIT_H_
