/*
 * Copyright (c) 2014 ELL-i co-op.
 *
 * This is part of ELL-i software.
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

#if !defined(EMULATOR)
# error "Cannot execute mockups on real hardware"
#endif

#include <unistd.h>

#include <coap_int.h>
#include <udp.h>
#include <ip.h>
#include <ethernet.h>

#include <string.h>
#include <pcap/pcap.h>
#include <stdio.h>
#include <err.h>
#include <sysexits.h>
#include <errno.h>

/// XXX Attempt to fix linking
DECLARE_UDP_SOCKET(UDP_PORT_COAP);

const void * __UDP_SOCKET_COAP = &__udp_socket5683;

struct coap_payload {
    struct coap coap; 
    uint32_t    token;
#define URI_PATH_LEN 6
    uint8_t     uri_path_dl;
    char        uri_path[URI_PATH_LEN];
} __attribute__((packed));

void dump_packet(const u_char *p) {
    fprintf(stderr,
            "eth: dst=%02x:%02x:%02x:%02x:%02x:%02x "
            "src=%02x:%02x:%02x:%02x:%02x:%02x len=%02x:%02x\n",
            p[ 0], p[ 1], p[ 2], p[ 3], p[ 4], p[ 5], 
            p[ 6], p[ 7], p[ 8], p[ 9], p[10], p[11], 
            p[12], p[13]);
    fprintf(stderr,
            "ip:  vhl=%02x tos=%02x "
            "len=%02x%02x id=%02x%02x "
            "off=%02x%02x ttl=%02x p=%02x sum=%02x%02x "
            "src=%d.%d.%d.%d dst=%d.%d.%d.%d\n",
            p[14], p[15], 
            p[16], p[17], p[18], p[19],
            p[20], p[21], p[22], p[23], p[24], p[25],
            p[26], p[27], p[28], p[29],
            p[30], p[31], p[32], p[33]);
}

extern "C" { int emulated_main(void); };

int emulated_main(void) {
    return 0;
}

#undef main

char errbuf[PCAP_ERRBUF_SIZE];
pcap_t *pcap;
char *input_file;
char *progname;
char buffer[2048 /*XXX*/];
pcap_dumper_t *dumper;

int main(int ac, char **av) {
    progname = av[0];
    input_file = av[1];
    const u_char *pkt_data;
    struct ether_header *const ether_header = (struct ether_header *)buffer;
    struct pcap_pkthdr *pkt_header;

    if (ac < 2) {
        fprintf(stderr, "%s: Exiting.  Usage: %s pcap-file | tcpdump -r -\n", 
                progname, progname);
        return EX_USAGE;
    }

    pcap = pcap_open_offline(input_file, errbuf);
    if (NULL == pcap) {
        err(EX_NOINPUT, "Exiting.  Failed to open file '%s'", input_file);
    }

    dumper = pcap_dump_fopen(pcap, stdout);
    if (NULL == dumper) {
        err(EX_OSERR,   "Exiting.  Failed to open output for packet dumping.");
    }

    while (pcap_next_ex(pcap, &pkt_header, &pkt_data) >= 0) {
        fprintf(stderr, "%s: Sending a packet of %d bytes.\n", progname, pkt_header->len);
        /* Copy data to a modifyable buffer */
        dump_packet(pkt_data);
        memcpy(buffer, pkt_data, pkt_header->len);
        eth_input(ether_header);
    }

    pcap_close(pcap);

    return 0;
}

/* Intercept resulting outgoing packet */
void eth_output(struct ether_header *mockup_output) {
    fprintf(stderr, "Received output packet\n");
    dump_packet((const u_char *)mockup_output);

    const struct ip *ip = (struct ip *)((char *)mockup_output + sizeof(ether_header));
    struct pcap_pkthdr pkthdr;
    gettimeofday(&pkthdr.ts, NULL);
    pkthdr.caplen = pkthdr.len = sizeof(struct ether_header) + ip->ip_len;
    pcap_dump((u_char *)dumper, &pkthdr, (const u_char *)mockup_output);
}

