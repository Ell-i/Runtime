#
# Copyright (c) 2013 Ell-i co-operative
#
# Extract make variables from the Arduino IDE specifications
#

VARIABLE_FILES := $(TOP)make/arduino.txt $(TOP)platform.txt

EXTRA_CFLAGS += \
	-D__STM32F051__ \
	-I$(TOP)cores/arduelli \
	-I$(TOP)system/stm32/inc \
	-I$(TOP)system/stm32/CMSIS/Include \

#
# No user serviceable parts below
#

ifeq ($(SCRIPTDIR),)
SCRIPTDIR=$(TOP)scripts/
endif

define expand
$(shell $(SCRIPTDIR)expand-arduino-ide-definition.sh $(1) $(VARIABLE_FILES))
endef

CC  	 := $(call expand,compiler.cmd.cc)
CXX      := $(call expand,compiler.cmd.cxx)
LD       := $(call expand,compiler.cmd.ld)
AR       := $(call expand,compiler.cmd.ar)
ELF2HEX  := $(call expand,compiler.cmd.elf2hex)

CFLAGS   := $(call expand,compiler.cmd.cc.flags)
CXXFLAGS := $(call expand,compiler.cmd.cxx.flags)
LDFLAGS  := $(call expand,compiler.cmd.ld.flags)
ARFLAGS  := $(call expand,compiler.cmd.ar.flags)
EHFLAGS  := $(call expand,compiler.cmd.elf2hex.flags)


LIBS     := $(call expand,compiler.cmd.ld.libs)

CFLAGS   += $(EXTRA_CFLAGS)
CXXFLAGS += $(EXTRA_CFLAGS)

#
# Figure out the GCC installation directories to locate libc.a
#

LIBGCC_LIBRARY := \
	$(shell $(CC) -print-libgcc-file-name)

LIBS += $(LIBGCC_LIBRARY)
