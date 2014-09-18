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
# include $(MAKEDIR)system_libs_inc.mk

LIBASE = $(subst .a,,$(subst lib,,$(LIB)))

#
# Define app library objects.  Add new objects here.
#
ifeq ($(LIB_OBJS),)

CXX_SRC := \
	$(wildcard $(TOP)libraries/$(LIBASE)/src/*.cpp) \
	$(wildcard $(TOP)libraries/$(LIBASE)/src/variants/$(VARIANT)*.cpp)
C_SRC   := \
	$(wildcard $(TOP)libraries/$(LIBASE)/src/*.c) \
	$(wildcard $(TOP)libraries/$(LIBASE)/src/variants/$(VARIANT)*.c)

LIB_OBJS_TMP := $(subst $(TOP)libraries/$(LIBASE)/src/,,$(CXX_SRC:.cpp=.o) $(C_SRC:.c=.o))
LIB_OBJS     := $(subst variants/,,$(LIB_OBJS_TMP))

endif

#
# For compilation
#
LIB_INC_FLAGS = -I$(TOP)libraries/$(LIBASE)/src
CFLAGS   += $(LIB_INC_FLAGS)
CXXFLAGS += $(LIB_INC_FLAGS)

#
# Rules
#

ifdef LOCAL_RULES

VPATH += $(TOP)libraries/$(LIBASE)/src $(TOP)libraries/$(LIBASE)/src/variants $(TOP)cores/arduelli

all:  $(LIB)

clean::
	rm -f $(LIB)
	rm -f $(LIB_OBJS)

$(LIB): $(LIB_OBJS)
	$(AR) cr $(LIB) $(LIB_OBJS)

endif
