#
# Copyright (c) 2014 ELL-i co-operative
#
# Define system lib and dependencies
#

#
# Define the system libraries.  Add a new one for each variant.
# If you update these here, please be sure to make the same
# change into the VARIANTS in system_libs.mk
#
SYSTEM_LIBS := \
    $(TOP)variants/ellduino/libstm32f0.a \
    $(TOP)variants/stm32f334nucleo/libstm32f3.a \
    $(TOP)variants/stm32f4discovery/libstm32f4.a
#   $(TOP)variants/stm32f0discovery/libstm32f0.a \


#
# Rules
#

all:  $(SYSTEM_LIBS)

clean::
	make -C $(TOP)build TOP=$(TOP) -f $(TOP)make/system_libs.mk clean

$(SYSTEM_LIBS):
	make -C $(TOP)build TOP=$(TOP) -f $(TOP)make/system_libs.mk all


