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
# Add dependcies to system libraries, and application libraries
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

clean::
	rm -f $(APP)
	rm -f $(APP_OBJS)

ifeq ($(PLATFORM),hardware)

all:  $(APP) $(APP).hex $(APP).bin

clean::
	rm -f $(APP).hex
	rm -f $(APP).bin
	rm -f $(APP).lst
	rm -f make.map

$(APP):	$(APP_OBJS) $(SYSTEM_LIBS) $(LIBES_LIBS)
	$(LD) $(LDFLAGS) -o $@ $(APP_OBJS) $(LIBS)

#
# Define rules for producing .hex and .bin files
#

.PHONY:	.hex .bin

%.hex:	%
	$(ELF2HEX) $(E2HFLAGS) $< $@

%.bin:  %
	$(ELF2HEX) $(E2BFLAGS) $< $@

endif

ifeq ($(PLATFORM),emulator)

all:  $(APP) lib$(APP).so

clean::
	rm -f $(PRE_OBJS)
	rm -f $(POST_OBJS)
	rm -f lib$(APP).so

$(APP):	$(APP_OBJS) libsystem_$(VARIANT).a $(LIBES_LIBS) $(PRE_OBJS) $(POST_OBJS)
	$(LD) $(LDFLAGS) -o $@ $(PRE_OBJS) $(APP_OBJS) $(LIBS) $(POST_OBJS)

lib$(APP).so: $(APP_OBJS) libsystem_$(VARIANT).a $(LIBES_LIBS) $(PRE_OBJS) $(POST_OBJS)
	$(LD) $(LDFLAGS) $(SHAREDFLAGS) -o $@ $(PRE_OBJS) $(APP_OBJS) $(LIB_OBJS) \
		$(LIBS) $(POST_OBJS) $(HOST_LIBS)

libsystem_$(VARIANT).a:
	@make TOP=$(TOP) -f $(TOP)make/system_lib.mk all

endif

endif
