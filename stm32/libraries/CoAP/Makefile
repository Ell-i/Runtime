#
# Copyright (c) 2014 ELL-i co-operative
#
# Compile and assemble the Arduino Ethernet library
#

TOP ?=../../

MAKEDIR ?= $(TOP)make/

#
# Define the variant to build for
#
VARIANT ?= ellduino

#
# Define the library name
#

LIB ?= Ethernet

#
# Define app library objects.  Add new objects here.
#

LIB_OBJS := Dhcp.o Dns.o Ethernet.o EthernetUdp.o # EthernetClient.o EthernetServer.o 
LIB_OBJS := Socket.o 
LIB_OBJS := XXX Add enc28j60 objects here

#
# Set up the compilation environment, identical to the Arduino IDE,
# for Arduino lib building.
#
include $(MAKEDIR)arduino_lib.mk
