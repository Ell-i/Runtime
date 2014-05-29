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
 * @brief ENC28J60 ethernet interface
 */

#ifndef  _ENC28J60_PACKET_H_
# define _ENC28J60_PACKET_H_

# include <enc28j60/ENC28J60.h>
# include <netinet/ethernet.h>

inline int
ENC28J60Class::availablePackets(void) const {
    return reg_get(E_PKT_CNT);
}

inline int
ENC28J60Class::receivePacket(uint8_t *buffer, size_t maxlen) const {

    rx_header.rx_cmd = ENC_SPI_READ_MEM;
    spi_transfer((unsigned char *)&rx_header, sizeof(enc_rx_packet_header_t));

    register unsigned int plen = rx_header.rx_length;
    register unsigned int next = rx_header.rx_next;

    if (plen > maxlen)
        plen = maxlen;

    /* Assumed buffer has extra space at the
     * beginning for the command
     */
    *(buffer - 1) = ENC_SPI_READ_MEM;
    spi_transfer(buffer-1, plen+1);

    /*
     * Go to the beginning of the next packet.
     *
     * NB.  It might be possible to avoid this call if len ==
     *      rx_header.rx_length, but that would need to be tested, as
     *      it is not clear from the data sheet.
     */
    reg_set(E_RD_PTR, next);

    /*
     * Free the ENC28J60 buffer memory for the next packets.
     * See Errata #14.
     */
    reg_set(E_RX_RD_PTR, next == RX_BUFFER_START? RX_BUFFER_END: next-1);

    /* Decrement the packet count */
    reg_bitop(ENC_SPI_SET_BF, E_CON2, E_CON2_PKT_DEC);

    return plen;

}

inline void
ENC28J60Class::getHeader(enc_rx_packet_header_t *rx_header) const {
    rx_header->rx_cmd = ENC_SPI_READ_MEM;

    spi_transfer((unsigned char *)rx_header, sizeof(enc_rx_packet_header_t));

    register unsigned int next = rx_header->rx_next;

    /*
     * Go to the beginning of the next packet.
     */
    reg_set(E_RD_PTR, next);

    /*
     * Free the ENC28J60 buffer memory for the next packets.
     * See Errata #14.
     */
    reg_set(E_RX_RD_PTR, next == RX_BUFFER_START? RX_BUFFER_END: next-1);

    /* Decrement the packet count */
    reg_bitop(ENC_SPI_SET_BF, E_CON2, E_CON2_PKT_DEC);
}


inline void
ENC28J60Class::sendPacket(uint8_t *buffer, size_t len) const {
    /*
     * Wait until the previous packet has been sent.
     */
    // DEBUG_SET_LED0(1);
    while ((reg_get(E_CON1) & E_CON1_TX_REQUEST)) {
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
# if 0
        if ((reg_get(E_INT_REQ) & E_INT_REQ_TX_ERR)) {
# endif
            // DEBUG_SET_LED2(1);
            /* Reset the transmit logic */
            reg_bitop(ENC_SPI_SET_BF, E_CON1, E_CON1_TX_RESET);
            reg_bitop(ENC_SPI_CLR_BF, E_CON1, E_CON1_TX_RESET);
# if 0
            /* XXX: The example code doesn't do the following
               while the data sheet tells to do so. */
            reg_bitop(ENC_SPI_CLR_BF, E_INT_REQ, E_INT_REQ_TX_ERR);
# endif
            // DEBUG_SET_LED2(0);
# if 0
        } else {
            ; // XXX: Allow other threads to run
        }
# endif
        // DEBUG_SET_LED1(0);
    }

    /*
     * Write the packet to the ENC28J60 packet buffer.
     *
     * NB.  The per-packet control byte is there already
     *      at TX_BUFFER_START. It was written there at
     *      enc_init().
     */
    reg_set(E_WR_PTR, TX_BUFFER_START + 1);
    
    *(buffer - 1) = ENC_SPI_WRITE_MEM;
    spi_transfer_send(buffer-1, len+1);

    /*
     * Set the packet start and end.
     */
    reg_set(E_TX_STA, TX_BUFFER_START);
    reg_set(E_TX_END, TX_BUFFER_START + 1 + len);

    /*
     * Request transmission.
     */
    reg_bitop(ENC_SPI_SET_BF, E_CON1, E_CON1_TX_REQUEST);
    // DEBUG_SET_LED0(0);
}

#endif //_ENC28J60_PACKET_H_
