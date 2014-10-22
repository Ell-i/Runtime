#
# Copyright (c) 2014 ELL-i co-operative
#
# Compile and link an application
#

TOP ?= $(shell pwd)/../../
MAKEDIR ?= $(TOP)make/

APP := test_ENCX24J600_send

APP_OBJS ?= main.o $(APP).o $(VARIANT).o encX24j600_init.o

include $(TOP)make/app.mk

VPATH  += \
	$(TOP)libraries/CoAP/src/coap \
	$(TOP)libraries/CoAP/src/encX24j600 \
	$(PWD)

CXXFLAGS += \
	-I$(TOP)libraries/CoAP/src/netinet \
	-I$(TOP)libraries/CoAP/src/encX24J600 \
	-I$(TOP)libraries/CoAP/src \
	-I$(TOP)libraries/SPI/src \

