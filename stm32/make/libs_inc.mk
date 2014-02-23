#
# Copyright (c) 2014 ELL-i co-operative
#
# Define non-core library include paths
#

CFLAGS    += $(patsubst %,-I%,$(wildcard $(TOP)libraries/*/.))
CXXFLAGS  += $(patsubst %,-I%,$(wildcard $(TOP)libraries/*/.))

LIBS      += $(wildcard $(TOP)libraries/*/*.a)

