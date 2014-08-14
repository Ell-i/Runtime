#
# Copyright (c) 2014 ELL-i co-operative
#
# Define system lib and dependencies
#

#
# Rules
#

ifdef LOCAL_RULES

all:  $(SYSTEM_LIBS)

clean::
	@make TOP=$(TOP) -f $(TOP)make/system_lib.mk clean

$(SYSTEM_LIBS):
	@make TOP=$(TOP) -f $(TOP)make/system_lib.mk all

endif
