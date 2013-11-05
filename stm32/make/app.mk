#
# Copyright (c) 2013 ELL-i co-operative
#
# Compile and link an application
#

ifeq ($(TOP),)
TOP=../
endif

ifeq ($(MAKEDIR),)
MAKEDIR=$(TOP)make/
endif

#
# Define the variant to build for
#
ifeq ($(VARIANT),)
VARIANT=ellduino
endif

#
# Set up the compilation environment, identical to the Arduino IDE,
# and include system lib building; we depend on system libraries
#
include $(MAKEDIR)system_libs.mk

#
# Define the app name
#

APP_NAME := main

#
# Define app library objects.  Add new objects here.
#

APP_OBJS := main.o sketch.o

#
# Rules
#

VPATH += $(TOP)tests $(TOP)cores/arduelli

all:  $(APP_NAME)

clean::
	rm -f $(APP_NAME)*
	rm -f $(APP_OBJS)
	rm -f make.map

$(APP_NAME):	$(APP_OBJS) $(SYSTEM_LIBS)
	$(LD) $(LDFLAGS) -o $@ $(APP_OBJS) $(SYSTEM_LIBS) $(LIBS)

