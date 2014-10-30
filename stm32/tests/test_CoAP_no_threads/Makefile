#
# Copyright (c) 2013-2014 ELL-i co-operative
#
# Compile and link an application
#

TOP ?= $(shell pwd)/../../
MAKEDIR ?= $(TOP)make/

APP := test_CoAP_no_threads

APP_OBJS ?= main.o coap_input.o $(APP).o $(VARIANT).o encX24j600_init.o

EXTRA_CFLAGS += -DETHERNET=ENCX24J600 -DDEBUG_WRITE=debug_write

include $(TOP)make/app.mk

VPATH  += ../../libraries/CoAP/src/coap \
	$(TOP)libraries/CoAP/src/encX24j600 \
	$(PWD)

CXXFLAGS += \
	-I$(TOP)libraries/CoAP/src/coap \
	-I$(TOP)libraries/CoAP/src/netinet \
	-I$(TOP)libraries/CoAP/src/encX24J600 \
	-I$(TOP)libraries/CoAP/src \
	-I$(TOP)libraries/SPI/src \

