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

#if defined(__STM32F051__)
# include <stm32f0xx.h>
# include <stm32f0xx_extra.h>
#elif defined(__STM32F407__)
# include <stm32f4xx.h>
# include <stm32f4xx_extra.h>
#elif defined(__STM32F334__)
# include <stm32f3xx.h>
# include <stm32f3xx_extra.h>
#endif

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

/**
 * Alignment of initialisation records
 */
#ifndef SYSTEM_INIT_ALIGNMENT
#define SYSTEM_INIT_ALIGNMENT 16
#endif

# include <stdint.h>
# include <string.h>

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
 * The SystemInitRecordAddrAndOnes describes a set of one-bits that need
 * to be set to a peripheral register.  As most peripheral registers
 * on STM Cortex-M MCUs are initialised to all-zeros, in practise this
 * can also be used to just write an initialisation value to most
 * registers.  Hence, this data structure has, for practial purposes,
 * a dual function.
 */
typedef struct {
    volatile preg32_t *const init_r_address; /* Address of register to initialize. */
    const uint32_t           init_r_ones;    /* Bitmask of the bits to set to ones. */
} SystemInitRecordAddrAndOnes;

/**
 * The SystemInitRecordAddrOnesAndZeroes gives both bits to zero and
 * bits to set one.  It is useful in the case where some of the
 * bits need to be initialised as zero while their reset-time value is
 * either unspecified, unknown, or one.
 */
typedef struct {
    volatile preg32_t *const init_r_address; /* Address of resister to initialize. */
    const uint32_t           init_r_zeroes;  /* Bits to set to zero. */
    const uint32_t           init_r_ones;    /* Bits to set to ones. */
} SystemInitRecordAddrOnesAndZeroes;

/**
 * The SystemInitRecordData16Only XXX document
 */
typedef struct {
    const uint16_t           init_data16;
} SystemInitRecordData16Only;

/**
 * The SystemInitRecordData32Only XXX document
 */
typedef struct {
    const uint32_t           init_data32;
} SystemInitRecordData32Only;

/**
 * The SystemInitRecordRegisterOffset XXX document
 */
typedef struct {
    const uint8_t            init_offset;
} SystemInitRecordRegisterOffset;

/**
 * The SystemInitRecordMaskAndWait XXX TBD later
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
    ADDR_AND_ONES = 0,
    ADDR_ONES_AND_ZEROES = 1,
    DATA16_ONLY = 2,
    DATA16_WITH_OFFSETS = 3,
    DATA32_ONLY = 4,
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
 * Must be aligned at a 16 bytes boundary; if you change this, you have
 * to change quite a lot of places (linker scripts, emulator, ...)
 */
typedef struct {
    // Align: 0
    const enum system_init_r_type   init_record_type;    // Type of SystemInitRecords in the union
    const uint8_t                   init_record_number;  // Number of SystemInitRecords
    const uint16_t                  init_record_reserved;// Reserved for future use
    // Align: 4
    const union {
        const int32_t               init_record_offset;  // Offset to be added to the addresses
                                                         // in the SystemInitRecords
        volatile preg16_t *const    init_record_address16; // Base register address for 16_only
                                                           // or 16_with_offset
        volatile preg32_t *const    init_record_address32; // Base register address for 32_no_address
    };
    // Align: 8
    const union {
        const SystemInitRecordAddrAndOnes *        init_records_addr_and_ones;
        const SystemInitRecordAddrOnesAndZeroes *  init_records_addr_ones_and_zeroes;
        const SystemInitRecordData16Only *         init_records_data16_only;
        const SystemInitRecordData32Only *         init_records_data32_only;
    };
    // Align: 12
    const union {
        const SystemInitRecordRegisterOffset *     init_records_register_offsets;
    };
    // Align: 16
} __attribute__((aligned(SYSTEM_INIT_ALIGNMENT))) SystemInitRecordArray;

/**
 * A linker section (aka segment) for SystemInitRecordArrays.
 */
# ifdef __MACH__
#  define SYSTEM_INIT_SECTION(sect, port) ".text,.peripheral"
# else
#  define SYSTEM_INIT_SECTION(sect, port) ".peripheral." # sect # port
# endif


# ifdef __cplusplus
extern "C" {
# endif

extern void SystemInitAddrAndOnes(      const SystemInitRecordArray *records);
extern void SystemInitAddrOnesAndZeroes(const SystemInitRecordArray *records);
extern void SystemInitData16Only(       const SystemInitRecordArray *records);
extern void SystemInitData16WithOffset( const SystemInitRecordArray *records);
extern void SystemInitData32Only(       const SystemInitRecordArray *records);

extern void SystemInitPeripherals(void);

#  ifndef memcpy
extern void *memcpy(void *dst, const void *src, size_t size);
#  endif
#  ifndef memset
extern void *memset(void *dst, int c, size_t size);
#  endif

# ifdef __cplusplus
}
# endif

/********************************
 * XXX TBD REMOVE THE USE OF THIS UGLY MACRO!
 */

# define IF(x) .x=

#endif//_SYSTEM_INIT_H_
