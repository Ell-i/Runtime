#
# Copyright (c) 2013-2014 ELL-i co-operative
#
# Compile and link an application
#

TOP ?= ../../
MAKEDIR ?= $(TOP)make/

#
# Define the variant to build for
#
PLATFORM := arduino
VARIANT  ?= ellduino

APP := test_CoAP_no_threads

APP_OBJS ?= main.o ../../libraries/CoAP/coap_input.o $(APP).o $(VARIANT).o

include $(TOP)make/app.mk
