#
# Copyright (c) 2013-2014 ELL-i co-operative
#
# Compile and link an application
#

TOP ?=$(shell pwd)/../
MAKEDIR ?= $(TOP)make/

#
# Set up the compilation environment, recursively if needed
#
include $(MAKEDIR)combinations.mk

#
# Add dependcies to system libraries, and applicatoin libraries
#
include $(MAKEDIR)system_libs_inc.mk
include $(MAKEDIR)libs_inc.mk

#
# Define the app name
#

APP ?= sketch

#
# Define app library objects.  Add new objects here.
#

APP_OBJS ?= main.o $(APP).o $(VARIANT).o


#
# Rules
#

VPATH += $(TOP)cores/arduelli $(TOP)variants/$(VARIANT) $(APPLICATION_SRC_DIR)

ifdef LOCAL_RULES

all:  $(APP) $(APP).hex $(APP).bin

clean::
	rm -f $(APP)
	rm -f $(APP).hex
	rm -f $(APP).bin
	rm -f $(APP).lst
	rm -f $(APP_OBJS)
	rm -f $(PRE_OBJS)
	rm -f $(POST_OBJS)
	rm -f make.map

$(APP):	$(APP_OBJS) $(SYSTEM_LIBS) $(PRE_OBJS) $(POST_OBJS)
	$(LD) $(LDFLAGS) -o $@ $(PRE_OBJS) $(APP_OBJS) $(LIBS) $(POST_OBJS)

#
# Define rules for producing .hex and .bin files
#

.PHONY:	.hex .bin

%.hex:	%
	$(ELF2HEX) $(E2HFLAGS) $< $@

%.bin:  %
	$(ELF2HEX) $(E2BFLAGS) $< $@

endif
