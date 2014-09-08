#
# Copyright (c) 2014 ELL-i co-operative
#
# Compile and link a library
#

TOP ?=../

MAKEDIR ?= $(TOP)make/

#
# Set up the compilation environment, recursively if needed
#
# XXX Recursive calling not tested, so this reduces in
#     practise to a call to $(PLATFORM).mk  Or at least
#     that is the only tested case
#
include $(MAKEDIR)combinations.mk

#
# Set up the compilation environment, identical to the Arduino IDE,
# and include system lib building; we depend on system libraries
#
include $(MAKEDIR)system_libs_inc.mk

#
# Define app library objects.  Add new objects here.
#
CXX_SRC := \
	$(wildcard $(TOP)libraries/$(LIB)/src/*.cpp) \
	$(wildcard $(TOP)libraries/$(LIB)/src/variants/$(VARIANT)*.cpp)
C_SRC   := \
	$(wildcard $(TOP)libraries/$(LIB)/src/*.c) \
	$(wildcard $(TOP)libraries/$(LIB)/src/variants/$(VARIANT)*.c)

LIB_OBJS_TMP := $(subst $(TOP)libraries/$(LIB)/src/,,$(CXX_SRC:.cpp=.o) $(C_SRC:.c=.o))
LIB_OBJS     := $(subst variants/,,$(LIB_OBJS_TMP))

#
# For compilation
#
LIB_INC_FLAGS = -I$(TOP)libraries/$(LIB)/src
CFLAGS   += $(LIB_INC_FLAGS)
CXXFLAGS += $(LIB_INC_FLAGS)

#
# Rules
#

ifdef LOCAL_RULES

VPATH += $(TOP)libraries/$(LIB)/src $(TOP)libraries/$(LIB)/src/variants $(TOP)cores/arduelli

all:  lib$(LIB).a

clean::
	rm -f lib$(LIB).a
	rm -f $(LIB_OBJS)

lib$(LIB).a: $(LIB_OBJS)
	$(AR) cr lib$(LIB).a $(LIB_OBJS)

endif
