#
# Copyright (c) 2014 ELL-i co-operative
#
# Compile and link a library
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

#
# Define include directories XXX THIS IS WRONG!
#
CFLAGS    += -Isrc -I$(wildcard arch/*)
CXXFLAGS  += -Isrc -I$(wildcard arch/*)

#
# Define app library objects.  Add new objects here.
#
CXX_SRC := $(wildcard src/*.cpp arch/*/*.cpp)
C_SRC   := $(wildcard src/*.c   arch/*/*.c)

LIB_OBJS := $(CXX_SRC:.cpp=.o) $(C_SRC:.c=.o)

#
# Rules
#

VPATH += $(TOP)cores/arduelli

all:  $(LIB).a

clean::
	rm -f $(LIB).a
	rm -f $(LIB_OBJS)

$(LIB).a: $(LIB_OBJS)
	$(AR) cr $(LIB).a $(LIB_OBJS)

