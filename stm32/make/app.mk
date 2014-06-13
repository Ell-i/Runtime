#
# Copyright (c) 2013-2014 ELL-i co-operative
#
# Compile and link an application
#

TOP ?=../
MAKEDIR ?= $(TOP)make/

#
# Define the variant to build for
#
VARIANT ?= ellduino

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

APP ?= sketch

#
# Define app library objects.  Add new objects here.
#

APP_OBJS ?= main.o $(APP).o $(VARIANT).o

#
# Libraries to be included
#
ifeq ($(PLATFORM) $(shell uname -s),emulator Darwin)
APP_LIBS := $(LIBS) $(POST_OBJS) $(EMULATOR_LIBS)
else
ifeq ($(LD),arm-none-eabi-ld)
APP_LIBS :=--start-group $(LIBS) --end-group $(POST_OBJS) $(EMULATOR_LIBS)
else
APP_LIBS := -Wl,--start-group $(LIBS) -Wl,--end-group $(POST_OBJS) $(EMULATOR_LIBS)
endif
endif

#
# Rules
#

VPATH += $(TOP)cores/arduelli $(TOP)variants/$(VARIANT)

all:  $(APP) $(APP).hex

clean::
	rm -f $(APP)
	rm -f $(APP).hex
	rm -f $(APP).lst
	rm -f $(APP_OBJS)
	rm -f $(PRE_OBJS)
	rm -f $(POST_OBJS)
	rm -f make.map

$(APP):	$(APP_OBJS) $(SYSTEM_LIBS) $(PRE_OBJS) $(POST_OBJS)
	$(LD) $(LDFLAGS) -o $@ $(PRE_OBJS) $(APP_OBJS) $(APP_LIBS)

#
# Define rules for producing .hex files
#

.PHONY:	.hex

%.hex:	%
	$(ELF2HEX) $(EHFLAGS) $< $@
