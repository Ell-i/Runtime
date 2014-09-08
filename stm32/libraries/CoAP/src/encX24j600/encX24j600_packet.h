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
 * @author: Pekka Nikander <pekka.nikander@ell-i.org>  2014
 * @author Ivan Raul <ivan.raul@ell-i.org> 2014
 *
 * @brief ENCX24J600 ethernet interface
 */

#ifndef  _ENCX24J600_PACKET_H_
# define _ENCX24J600_PACKET_H_

# include <encX24J600/ENCX24J600.h>
# include <netinet/ethernet.h>

typedef struct {
    uint8_t  rx_padding0;
    uint8_t  rx_cmd;
    // Start of the actual RX header
    uint16_t rx_next;
    uint16_t rx_length;
    uint8_t  rx_flags0;
    uint8_t  rx_flags1;
    uint8_t  rx_flags2;
    uint8_t  rx_padding2;
} enc_rx_packet_header_t;

inline int
ENCX24J600Class::availablePackets(void) const {
    register int value;

    spi_master_activate(ss_pin_);
    // Read just the low order 8 bits of E_STAT, the packet count
    value = spi_transfer_3bytes(ENC_SPI_READ_REG_UB, E_STAT, 0);
    spi_master_deactivate(ss_pin_);

    return value;
}

inline int
ENCX24J600Class::receivePacket(uint8_t *buffer, size_t maxlen) const {
    enc_rx_packet_header_t rx_header;

    rx_header.rx_cmd = ENC_SPI_READ_RX;
    spi_transfer((unsigned char *)&rx_header, sizeof(enc_rx_packet_header_t));

    register unsigned int plen = rx_header.rx_length;
    register unsigned int next = rx_header.rx_next;

    if (plen > maxlen)
        plen = maxlen;

    /* Assumed buffer has extra space at the
     * beginning for the command
     */
    *(buffer - 1) = ENC_SPI_READ_RX;
    spi_transfer(buffer-1, plen+1);

    /*
     * Go to the beginning of the next packet.
     */
    reg_set(E_RX_TAIL, next);
    reg_set(E_RX_RD_PT, next);

    /* Decrement the packet count */
    spi_master_activate(ss_pin_);
    spi_send_single_byte(ENC_SPI_SET_PKT_DEC);
    spi_master_deactivate(ss_pin_);

    return plen;

}

inline void
ENCX24J600Class::sendPacket(uint8_t *buffer, size_t len) const {
    /*
     * Wait until the previous packet has been sent.
     */
    // DEBUG_SET_LED0(1);
    while ((reg_get(E_CON1) & TX_REQUEST)) {
# if 0
        // DEBUG_SET_LED1(1);
        /*
         * Reset the transmit logic if it has been stalled
         * as per Errata #12.
         *
         * The current implementation below (with #if 0s)
         * is copied from the example implementation, and
         * seems to work.  The errata seems to indicate
         * otherwise.  As far as I (Pekka) understand, this
         * implementation is bad and may lead to some packets
         * being partial or lost.  Return to here.
         *
         * XXX FIXME
         */
#  if 0
        if ((reg_get(E_INT_REQ) & E_INT_REQ_TX_ERR)) {
#  endif
            // DEBUG_SET_LED2(1);
            /* Reset the transmit logic */
            reg_bitop(ENC_SPI_SET_BF, E_CON1, E_CON1_TX_RESET);
            reg_bitop(ENC_SPI_CLR_BF, E_CON1, E_CON1_TX_RESET);
#  if 0
            /* XXX: The example code doesn't do the following
               while the data sheet tells to do so. */
            reg_bitop(ENC_SPI_CLR_BF, E_INT_REQ, E_INT_REQ_TX_ERR);
#  endif
            // DEBUG_SET_LED2(0);
#  if 0
        } else {
            ; // XXX: Allow other threads to run
        }
#  endif
        // DEBUG_SET_LED1(0);
# endif
    }

    /*
     * Write the packet to the ENCX24J600 packet buffer.
     */
    reg_set(E_GP_RD_PT, TX_BUFFER_START);

    *(buffer - 1) = ENC_SPI_WRITE_MEM;
    spi_transfer_send(buffer-1, len+1);

    /*
     * Set the packet start and end.
     */
    reg_set(E_TX_START, TX_BUFFER_START);
    reg_set(E_TX_LEN,   TX_BUFFER_START + len);

    /*
     * Request transmission.
     */
    spi_send_single_byte(ENC_SPI_TX_REQUEST);
    // DEBUG_SET_LED0(0);
}

#endif //_ENCX24J600_PACKET_H_
