#
# Copyright (c) 2014 ELL-i co-operative
#
# Define non-core library include paths
#

CFLAGS    += $(patsubst %,-I%,$(wildcard $(TOP)libraries/*/src/.))
CXXFLAGS  += $(patsubst %,-I%,$(wildcard $(TOP)libraries/*/src/.))

LIBS      += $(wildcard $(TOP)libraries/*/*.a)



