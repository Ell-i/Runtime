#include <ellduino_enc28j60.h> 
#include <ethernet.h>

void eth_output(const void *payload, uint16_t payload_len) {
   /*
     * XXX
     *
     * This implementation assumes there is free space before the
     * Ethernet Header start to store the command.
     */
    ENC28J60.sendPacket((uint8_t *) payload - ETHER_HEADER_LEN, payload_len + ETHER_HEADER_LEN);
}
