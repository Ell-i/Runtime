#
# Copyright (c) 2014 ELL-i co-operative
#
# Compile and link a library
#

TOP ?=../
MAKEDIR ?= $(TOP)make/

#
# Define app library objects.  Add new objects here.
#
CXX_SRC := $(wildcard *.cpp)
C_SRC   := $(wildcard *.c  )

LIB_OBJS := $(CXX_SRC:.cpp=.o) $(C_SRC:.c=.o)

include $(MAKEDIR)lib.mk

