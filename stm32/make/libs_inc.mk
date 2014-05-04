#
# Copyright (c) 2014 ELL-i co-operative
#
# Define non-core library include paths
#

CFLAGS    += $(patsubst %,-I%,$(wildcard $(TOP)libraries/*/src/.))
CXXFLAGS  += $(patsubst %,-I%,$(wildcard $(TOP)libraries/*/src/.))

CFLAGS    += $(patsubst %,-I%,$(wildcard $(TOP)libraries/CoAP/arch/*/.))
CXXFLAGS  += $(patsubst %,-I%,$(wildcard $(TOP)libraries/CoAP/arch/*/.))

LIBS      += $(wildcard $(TOP)libraries/*/*.a)
LIBS      += $(wildcard $(TOP)libraries/CoAP/arch/*/*.a)
# LIBS      += $(TOP)libraries/SPI/ellduino_spi.o


