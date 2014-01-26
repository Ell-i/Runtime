#
# Copyright (c) 2013 Ell-i co-operative
#
# Define make variables for the Emulator
#

VARIABLE_FILES := $(TOP)make/emulator.txt $(TOP)make/arduino.txt $(TOP)platform.txt

EXTRA_CFLAGS += \
        -DEMULATOR \
	-D__STM32F051__ \
	-Dmain=emulated_main \
	-I$(TOP)emulator/inc \
	-I$(TOP)cores/arduelli \
	-I$(TOP)system/stm32/inc \
	-I$(TOP)system/stm32/CMSIS/Include \
	-I$(TOP)variants/$(VARIANT) \

#
# No user serviceable parts below
#
ifeq ($(SCRIPTDIR),)
SCRIPTDIR=$(TOP)scripts/
endif

define expand
$(shell $(SCRIPTDIR)expand-arduino-ide-definition.sh $(1) $(VARIABLE_FILES))
endef

ifeq ($(shell uname -s),Darwin)
CC  := clang++ -x c++
CXX := clang++ -x c++
LD  := llvm-g++
else
CC  := g++
CXX := g++
LD  := g++ -m32 -march=i386
endif
AR  := ar
ELF2HEX := :

CFLAGS   := \
  $(subst -std=c99,-std=c++98,$(subst -mcpu=cortex-m0,,$(call expand,compiler.cmd.cc.flags)))

CXXFLAGS := \
  $(subst -std=gnu++0x,-std=c++98,$(subst -mcpu=cortex-m0,,$(call expand,compiler.cmd.cxx.flags)))

LDFLAGS  := -m32 -demangle
ARFLAGS  := $(call expand,compiler.cmd.ar.flags)

$(eval LIBS     = $(call expand,compiler.cmd.ld.libs))

CFLAGS   += $(EXTRA_CFLAGS)
CXXFLAGS += $(EXTRA_CFLAGS)

#
# Arrange segments
#
PRE_OBJS  := emulator_pre.o
POST_OBJS := emulator_post.o

#
# C++ standard library
#

LIBS += -lstdc++

#
# Additional system objects
#

SYSTEM_OBJS := emulator.o Register.o RCC.o FLASH.o GPIO.o TIM.o
VPATH += $(TOP)emulator/src
