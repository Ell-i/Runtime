#
# Copyright (c) 2014 ELL-i co-operative
#
# This is part of ELL-i software
#
# ELL-i software is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# ELL-i software is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with ELL-i software.  If not, see <http://www.gnu.org/licenses/>.
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
# Define the library name, if not coming from the calling make
#

LIB ?= libCoAP.a

#
# Define source directories
#

D := $(TOP)libraries/CoAP/src/

vpath %.cpp $(D) $(D)coap $(D)enc28j60 $(D)encX24j600 $(D)netinet
vpath %.c   $(D) $(D)coap $(D)enc28j60 $(D)encX24j600 $(D)netinet

EXTRA_CFLAGS  += -I$(TOP)libraries/SPI/src

#
# Define app library objects.  Add new objects here.
#

LIB_OBJS := eth_input.o arp_input.o
LIB_OBJS += ip_input.o ip_output.o icmp_input.o ip_checksum.o
LIB_OBJS += udp.o coap_input.o coap_handle.o
LIB_OBJS += enc28j60_init.o ethernet_output.o

#
# Set up the compilation environment, identical to the Arduino IDE,
# for Arduino lib building.
#
LOCAL_RULES := TRUE

include $(MAKEDIR)lib.mk
