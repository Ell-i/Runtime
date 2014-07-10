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

APP := test_ENCX24J600_begin

APP_OBJS ?= main.o $(APP).o $(VARIANT).o

include $(TOP)make/app.mk

VPATH  += ../../libraries/CoAP/src/coap
CXXFLAGS += \
	-I../../libraries/CoAP/src/encX24J600 \

