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
 * ENC28J60 interface through the Arduino SPI library
 *
 * @author: Pekka Nikander <pekka.nikander@ell-i.org>  2014
 */

#ifndef  _ENCX24J600_INIT_H_
# define _ENCX24J600_INIT_H_

#if 1
#include <Arduino.h>
#endif

inline void
ENCX24J600Class::begin() const {

    spi_master_begin(&ENCX24J600_SPI, ss_pin_);

    /* Reset routine, see Section 8.1 of the Data shsset (39935c.pdf) */

#if 1
# define DEBUG_PIN 3
    pinMode(DEBUG_PIN, OUTPUT);
    digitalWrite(DEBUG_PIN, 1);
#endif
    /*
     * Steps 1-2: Write 1234h to EUDAST.  Read EUDAST to see if it now
     * equals 1234h. If it does not, the SPI/PSP interface may not be
     * ready yet, so return to step 1 and try again.
     */
    do {
        reg_set(E_UDA_START, 0x1234);
#if 1
        static int c = 0;

        if (c++ > 10000) {
            if (digitalRead(DEBUG_PIN)) {
                digitalWrite(DEBUG_PIN, 0);
            } else {
                digitalWrite(DEBUG_PIN, 1);
            }
            c = 0;
        }
#endif
    } while (reg_get(E_UDA_START) != 0x1234);

    digitalWrite(DEBUG_PIN, 0);

    /* Step 3. Poll CLKRDY (ESTAT<12>) and wait for it to become set. */
    while ((reg_get(E_STAT) & CLOCK_READY) == 0)
        ;

    /* Step 4. Issue a System Reset command by setting ETHRST (ECON2<4>). */
    spi_send_single_byte(ENC_SPI_RESET);

    /*
     * Step 5. In software, wait at least 25us for the Reset to take
     * place and the SPI/PSP interface to begin operating again.
     */
    // XXX Replace with something better
    for (volatile int i = 0; i < 25 * 48; i++)
        ;

    /*
     * Step 6. Read EUDAST to confirm that the System Reset took
     * place. EUDAST should have reverted back to its Reset default of
     * 0000h.
     */
    if (reg_get(E_UDA_START) != 0x0000)
        /* XXX fail? */;


    /*
     * Initialize all non-phy registers to their desired values
     */

    for (   const device_register_init_static_8bit_t *p = encX24j600_init;
            p < encX24j600_init + encX24j600_init_size;
            p++) {
        reg_set(p->reg, p->value);
    }

    /*
     * Wait until the PHY is no longer in reset.  We do this instead of
     * Step 7. Wait at least 256us for the PHY registers and PHY
     * status bits to become available.
     */

    while (reg_get(PHY_CON1) & PHY_CON1_PRST)
        ;

    /*
     * Initialise the PHY
     */
    // XXX no-op at the moment
    digitalWrite(DEBUG_PIN, 1);
}


#endif // _ENCX24J600_INIT_H_
