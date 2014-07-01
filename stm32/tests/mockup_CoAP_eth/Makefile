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
PLATFORM := emulator
VARIANT  ?= ellduino

#
# Set up the compilation environment, identical to the Arduino IDE,
# and include system lib building; we depend on system libraries
#
include $(MAKEDIR)$(PLATFORM).mk
include $(MAKEDIR)system_libs_inc.mk
include $(MAKEDIR)libs_inc.mk

#
# Define the app name
#

APP := mockup_CoAP_eth

#
# Define app library objects.  Add new objects here.
#

APP_OBJS ?= $(APP).o $(VARIANT).o


#
# Rules
#

VPATH += $(TOP)cores/arduelli $(TOP)variants/$(VARIANT)

all:  $(APP)

clean::
	rm -f $(APP)
	rm -f $(APP).hex
	rm -f $(APP).lst
	rm -f $(APP_OBJS)
	rm -f $(PRE_OBJS)
	rm -f $(POST_OBJS)
	rm -f make.map

$(APP):	$(APP_OBJS) $(SYSTEM_LIBS) $(PRE_OBJS) $(POST_OBJS) $(LIBS)
	$(LD) $(LDFLAGS) -o $@ $(PRE_OBJS) $(APP_OBJS) $(LIBS) $(POST_OBJS) $(EMULATOR_LIBS) -lpcap

tests:  $(APP)
	./$(APP) coap.pcap | tcpdump -r -
