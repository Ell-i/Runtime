/*
 * Copyright (c) 2014 ELL-i co-operative.
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
 * Minimal standalone IPv4
 *
 * @author: Pekka Nikander <pekka.nikander@ell-i.org>  2014
 */

#include <stddef.h>
#include <stdint.h>
#include <limits.h>
#include <netinet/ip.h>

/**
 * Incrementally computes IP checksum over the data.
 *
 * Starting from a partial non-complemented checksum, adds the 16-bit
 * words in the 32-bit aligned data to the checksum, carrying data
 * over.  Returns one's complement of the generated checksum.
 *
 * The seed may contain two 16-bit values in parallel.
 *
 * The data buffer must be 32-bits aligned.
 *
 * For simply computing the checksum over a memory area, call this
 * function with the checksum argument as zero.  In a more typical
 * case, you first compute a pseudo-header checksum to the checksum
 * argument, and then call this function with the data buffer.
 *
 * @param checksum non-complemented checksum seed, two 16-bit words in parallel
 * @param data     a 32-bit aligned memory area to compute the checksum over
 * @param len      the length of the memory area, may be of any length
 *
 */
uint16_t ip_checksum(register uint32_t checksum, const void *data, size_t len) {
    register const uint8_t *dp  = (const uint8_t *)data;
    register const uint8_t *end = dp + len;

    /*
     * The default (if OPTIMIZE_SIZE hasn't been defined) is to first
     * compute the checksum in 64-bit chunks, using a 32-bit register
     * and ADC (add with carry) instructions; see the assembly code.
     * Once there is less than 64 bits left, the remainder is first
     * computed using 16-bit additions, and finally adding the lone
     * 8-bit byte (if any).
     *
     * The 'end' variable is not really the end of the buffer, but a
     * pseudo-end adjusted so that the comparisons in the while loops
     * are simple, generating more compact code.
     *
     * The default size of this function on Cortex-M0 is 72 bytes, and
     * the size-optimized size 46 bytes.  The default version runs
     * about 3-4 times as fast as the size-optimised one on large buffers.
     */
#define OPTIMIZE_SIZE 1
        
#ifndef OPTIMIZE_SIZE
    // Process the data in 64 bit chunks, using LDM and ADC instructions
    {
        register const uint32_t zero = 0;

        end -= 2 * sizeof(uint32_t) - 1;

        while (dp < end) {
#if defined(__thumb__)
# if defined(__ARM_ARCH_6M__)
            XXX DOES NOT WORK, CRASHES.  INVESTIGATE.  PROBABLY *WAS* ALIGNMENT, TEST.
            __asm__ (
                "ldm	%[dp]!, {r2,r3}\n\t"
                "add	%[checksum], r2\n\t"
                "adc	%[checksum], r3\n\t"
                "adc	%[checksum], %[zero]"
                : [checksum] "+r" (checksum), [dp] "+r" (dp)
                : [zero] "r" (zero)
                : "r2", "r3"
                );
# else
#  error "Not implemented for ARMv7 yet.  Please do."
# endif
#else
            register const uint16_t *hp = (const uint16_t *)dp;
            checksum += *hp++;
            checksum += *hp++;
            checksum += *hp++;
            checksum += *hp++;
            dp += 2 * sizeof(uint32_t);
#endif
        }

        end += 2 * sizeof(uint32_t) - 1;
    }
#endif

    // Add the half words together.  This cannot overflow.
    {
        register uint32_t checksum_high = (checksum >> 16) & 0xFFFF;
        checksum = checksum & 0xFFFF;
        checksum += checksum_high;
    }

    // If there are any remaining 16 bit words, add them. Cannot overflow.
    // In the worst case, we get 1fffe + ffff + ffff + ffff = 4fffb
    {
        end -= 1;

        while (dp < end) {
            register uint32_t d = *((uint16_t *)dp);
            checksum += d;
            dp += sizeof(uint16_t);
        }

        end += 1;
    }

    // If the is a remaining 8 bit byte, add it.  Cannot overflow.
    // Note that we can add it directly, as byte swapping will do the right thing.
    // In the worst case, we get 4fffx or 5fffx
    if (dp < end) {
        checksum += *dp;
    }

    // Add the half words together again, 
    // two times for the worst case, e.g.
    // 4ffff -> 10003 -> 4 or 5fffd -> 10002 -> 3
    {
        register uint32_t checksum_high;
        checksum_high = (checksum >> 16) & 0xFFFF;
        checksum = checksum & 0xFFFF;
        checksum += checksum_high;

        checksum_high = (checksum >> 16) & 0xFFFF;
        checksum = checksum & 0xFFFF;
        checksum += checksum_high;
    }

    // XXX Should we have this complementing here?  Or at the caller?
    // Return 1's complement
    return ~checksum;
}

#ifdef UNIT_TEST

#include <stdio.h>

static uint8_t test_vector[] = { 
    0xe3, 0x4f, 0x23, 0x96, 0x44, 0x27, 0x99, 0xf3,
};

static uint8_t test_vector2[] = { 
    0xe3, 0x4f, 0x23, 0x96, 0x44, 0x27, 0x99, 0xf3, 0x01, 0x01, 0x10,
};

int main(void) {
    uint16_t checksum = ip_checksum(0, test_vector, sizeof(test_vector));
    if (checksum != 0xff1a) {
        fprintf(stderr, "%x != 0xff1a\n", checksum);
        return 1;
    }
    checksum = ip_checksum(0, test_vector2, sizeof(test_vector2));
    if (checksum != 0xfe09) {
        fprintf(stderr, "%x != 0xfe09\n", checksum);
        return 1;
    }
    return 0;
}

#endif //UNIT_TEST
