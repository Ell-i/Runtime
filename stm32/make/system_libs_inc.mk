#
# Copyright (c) 2014 ELL-i co-operative
#
# Define system lib and dependencies
#

#
# Define the system libraries.  Add a new one for each variant.
# If you update these here, please be sure to make the same
# chainge in system_libs.mk, too.
#
SYSTEM_LIBS := \
    $(TOP)variants/ellduino/libstm32f0.a \
    $(TOP)variants/stm32f0discovery/libstm32f0.a

#
# Rules
#

all:  $(SYSTEM_LIBS)

clean::
	make -C $(TOP)build -f ../make/system_libs.mk PLATFORM=$(PLATFORM) VARIANT=$(VARIANT) clean

$(SYSTEM_LIBS):
	make -C $(TOP)build -f ../make/system_libs.mk PLATFORM=$(PLATFORM) VARIANT=$(VARIANT) all


