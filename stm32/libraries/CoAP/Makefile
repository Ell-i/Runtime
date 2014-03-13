#
# Copyright (c) 2014 ELL-i co-operative
#
# Compile and assemble the Arduino CoAP library
#

TOP ?= ../../

MAKEDIR ?= $(TOP)make/

#
# Define the variant to build for
#
PLATFORM ?= arduino
VARIANT  ?= ellduino

#
# Define the library name
#

LIB ?= CoAP

#
# Define source directories
#

vpath %.cpp . ./arch/enc28j60 ./arch/stm32
vpath %.c   . ./arch/enc28j60 ./arch/stm32

#
# Define app library objects.  Add new objects here.
#

LIB_OBJS := eth_input.o arp_input.o
LIB_OBJS += ip_input.o ip_output.o icmp_input.o
LIB_OBJS += udp.o coap_input.o coap_handle.o
LIB_OBJS += ellduino_enc28j60.o enc28j60.o enc28j60_packet.o enc28j60_spi.o

#
# Set up the compilation environment, identical to the Arduino IDE,
# for Arduino lib building.
#
include $(MAKEDIR)lib.mk
