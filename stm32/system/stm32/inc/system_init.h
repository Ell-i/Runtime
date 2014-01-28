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
 * @author: Pekka Nikander <pekka.nikander@ell-i.org>  2013-2014
 */

#ifndef _SYSTEM_INIT_H_
# define _SYSTEM_INIT_H_

/**
 * System initialisation interface.
 *
 * In the ELL-i platform the MCU system is initialised in a
 * data-driven approach, where the peripheral registers and their
 * initialisation values are described with data structures rather
 * than sequential code.  There are two reasons for this.  Firstly,
 * the resulting code is about 30-40% smaller, mainly due to the way
 * constants are handled in Thumb code.  Secondly, this leans towards
 * later implementing a domain specific language (DSL) for describing
 * peripheral use.
 *
 * The actual implementation places the main initialisation data into
 * a separate read-only linker section, @see SYSTEM_INIT_SECTION.  The
 * linker records the beginning and end of this section, similar to
 * the practise used for C++ static initialisers in traditional C++
 * runtimes.  The initialisation code in @see SystemInitPeripherals
 * iterates through the section, initialising those peripherals that
 * are used in the application.  Those that are not used are not
 * linked in to the binary, and therefore not initialised.
 *
 * If any peripherals need to be initialised in a specific order, such
 * as initialising clocks before anything else, this may be arranged
 * with linker directives in the linker script.  For the Mac OS X
 * version of the emulator, a linker order file needs to be used.
 */

# include <stdint.h>

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

# define COUNT_OF(x) ((sizeof(x)/sizeof(0[x])) / ((uint32_t)(!(sizeof(x) % sizeof(0[x])))))

/********************
 * System Init Records describe the inititalisation value for a single
 * peripheral register.  There may be many different ways to describe
 * the value; initially we support two ways: mask only and mask &
 * value.
 */

/**
 * The SystemInitRecordOnesOnly describes a set of one-bits that need
 * to be set to a peripheral register.  As most peripheral registers
 * on STM Cortex-M MCUs are initialised to all-zeros, in practise this
 * can also be used to just write an initialisation value to most
 * registers.  Hence, this data structure has, for practial purposes,
 * a dual function.
 */
typedef struct {
    volatile uint32_t *const init_r_address; /* Address of register to initialize. */
    const uint32_t           init_r_ones;    /* Bitmask of the bits to set to ones. */
} SystemInitRecordOnesOnly;

/**
 * The SystemInitRecordOnesAndZeroes gives both bits to zero and
 * bits to set one.  It is useful in the case where some of the
 * bits need to be initialised as zero while their reset-time value is
 * either unspecified, unknown, or one.
 */
typedef struct {
    volatile uint32_t *const init_r_address; /* Address of resister to initialize. */
    const uint32_t           init_r_zeroes;  /* Bits to set to zero. */
    const uint32_t           init_r_ones;    /* Bits to set to ones. */
} SystemInitRecordOnesAndZeroes;

/**
 * The SystemInitRecordData16WithOffset XXX
 */
typedef struct {
    const uint16_t           init_data16;
} SystemInitRecordData16NoAddress;

/**
 * The SystemInitRecordData16WithOffset XXX
 */
typedef struct {
    const uint32_t           init_data32;
} SystemInitRecordData32NoAddress;

/**
 * The SystemInitRecordMaskAndWait XXX
 */

typedef struct {
    // XXX TBD
} SystemInitRecordMaskAndWait;

/**
 * The system_init_r_type enum gives indices for the different
 * SystemInitRecord types.  It is used to index a table of function
 * pointers for initialisation handlers.
 *
 * XXX (later): Try an alternative implementation of using a sparse
 * switch statement.  According to Lauri it should give a smaller
 * implementation.
 */

enum system_init_r_type {
    ONES_ONLY = 0,
    ONES_AND_ZEROES = 1,
    DATA16_NO_ADDRESS = 2,
    DATA32_NO_ADDRESS = 3,
    SYSTEM_INIT_TYPE_NUMBER
};

/**
 * An explicitly sized array of SystemInitRecords.
 *
 * For each MCU (or other memory mapped) peripheral that needs
 * reset-time initialisation, one or more SystemInitRecordArrays
 * describe the desired state of the peripheral registers at the end
 * of the initialisation.
 *
 * The SystemInitRecordArrays are by convention placed in the
 * @see SYSTEM_INIT_SECTION linker section, from where the
 * @see SystemInitPeripherals automatically finds them.  Alternatively,
 * when more programmatic control is needed, the records may be placed
 * in the default read-only data section, and the initialisation code
 * may explicitly call the SystemInit functions as appropriate.
 *
 * XXX FIXME Currently the record is explicitly padded to 8 bytes,
 * the linker (used for emulator) on Mac OS X places the records so.
 */
typedef struct {
    const enum system_init_r_type   init_record_type;    // Type of SystemInitRecords in the union
    const uint8_t                   init_record_number;  // Number of SystemInitRecords
    const union {
        const int32_t               init_record_offset;  // Offset to be added to the addresses
                                                         // in the SystemInitRecords
        volatile uint32_t *const    init_record_address16; // Base register address for 16_no_address
        volatile uint32_t *const    init_record_address32; // Base register address for 32_no_address
    };
    const union {
        const SystemInitRecordOnesOnly *        init_records_ones_only;
        const SystemInitRecordOnesAndZeroes *   init_records_ones_and_zeroes;
        const SystemInitRecordData16NoAddress * init_records_data16_no_address;
        const SystemInitRecordData32NoAddress * init_records_data32_no_address;
    };
} SystemInitRecordArray;

/**
 * A linker section (aka segment) for SystemInitRecordArrays.
 */
# ifdef __MACH__
#  define SYSTEM_INIT_SECTION(port) ".text,.peripheral"
# else
#  define SYSTEM_INIT_SECTION(port) ".peripheral.default." # port
# endif


# ifdef __cplusplus
extern "C" {
# endif

extern void SystemInitOnesOnly(       const SystemInitRecordArray *records);
extern void SystemInitOnesAndZeroes(  const SystemInitRecordArray *records);
extern void SystemInitData16NoAddress(const SystemInitRecordArray *records);
extern void SystemInitData32NoAddress(const SystemInitRecordArray *records);

extern void SystemInitPeripherals(void);

# ifdef __cplusplus
}
# endif

/********************************
 * XXX TBD
 */

# define IF(x) .x=

#endif//_SYSTEM_INIT_H_
