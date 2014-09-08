#
# Copyright (c) 2014 ELL-i co-operative
#
# Compile and link an application
#

TOP ?= $(shell pwd)/../../
MAKEDIR ?= $(TOP)make/

#
# Define the variant to build for
#
# PLATFORM := arduino
VARIANT  ?= ellduino

APP := test_ENCX24J600_begin

APP_OBJS ?= main.o $(APP).o $(VARIANT).o encX24j600_init.o

include $(TOP)make/app.mk

VPATH  += \
	../../libraries/CoAP/src/coap \
	../../libraries/CoAP/src/encX24j600 \

CXXFLAGS += \
	-I../../libraries/CoAP/src/encX24J600 \

