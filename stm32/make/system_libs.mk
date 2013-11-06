#
# Copyright (c) 2013 ELL-i co-operative
#
# Compile and create the system libraries
#

ifeq ($(MAKEDIR),)
MAKEDIR=$(TOP)make/
endif

#
# Set up the compilation environment, identical to the Arduino IDE
#
include $(MAKEDIR)$(TARGET).mk

#
# Define system library objects.  Add new objects here.
#

SYSTEM_OBJS += system_stm32f0xx.o startup_stm32f0xx.o

#
# Define the system libraries.  Add a new one for each variant.
#
SYSTEM_LIBS := \
    $(TOP)variants/ellduino/lib/libstm32f0.a \
    $(TOP)variants/stm32f0discovery/lib/libstm32f0.a

#
# Define source directories
#

VPATH += $(TOP)system/stm32/src $(TOP)variants/$(VARIANT)

#
# Rules
#

all:  $(SYSTEM_LIBS)

clean::
	rm -f $(SYSTEM_LIBS)
	rm -f $(SYSTEM_OBJS)

$(SYSTEM_LIBS):	$(SYSTEM_OBJS)
	$(AR) $(ARFLAGS) $@ $(SYSTEM_OBJS)

