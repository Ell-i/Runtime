#
# Copyright (c) 2013-2014 ELL-i co-operative
#
# Compile and link an application
#
# XXX Do we really need this makefile?  The default app.mk should work.
# 

TOP ?= $(shell pwd)/../../
MAKEDIR ?= $(TOP)make/

#
# Define the variant to build for
#
PLATFORM := arduino
VARIANT  ?= ellduino

APP := test_CoAP_net_packet

APP_OBJS ?= main.o $(APP).o $(VARIANT).o

include $(TOP)make/app.mk

VPATH  += ../../libraries/CoAP/src/coap
CXXFLAGS += \
	-I../../libraries/CoAP/src/netinet \
	-I../../libraries/CoAP/src/coap \
	-I../../libraries/CoAP/src/enc28j60 \

ifeq ($(PLATFORM),emulator)
$(APP):	$(APP_OBJS) $(SYSTEM_LIBS) $(PRE_OBJS) $(POST_OBJS) $(LIBS)
	$(LD) $(LDFLAGS) -o $@ $(PRE_OBJS) $(APP_OBJS) $(LIBS) $(POST_OBJS) $(EMULATOR_LIBS) -lpcap
endif

ifeq ($(PLATFORM),emulator)
test_CoAP_net_packet.o: CFLAGS := $(subst -std=c++11,-std=c99,$(CFLAGS))
ifeq ($(shell uname -s),Darwin)
test_CoAP_net_packet.o: CC := clang++ -x c
else
test_CoAP_net_packet.o: CC := gcc
endif
endif

tests:  $(APP)
	./$(APP) | tcpdump -r -
