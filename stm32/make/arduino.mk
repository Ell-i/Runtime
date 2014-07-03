#
# Copyright (c) 2013 Ell-i co-operative
#
# Extract make variables from the Arduino IDE specifications
#

VARIABLE_FILES := $(TOP)make/$(VARIANT).txt $(TOP)platform.txt

define expand
$(shell $(SCRIPTDIR)expand-arduino-ide-definition.sh $(1) $(VARIABLE_FILES))
endef

$(eval EXTRA_CFLAGS_FROM_BUILD := $(call exapand,$(VARIANT).build.extra_flags))

EXTRA_CFLAGS += \
	$(EXTRA_CFLAGS_FROM_BUILD) \
	-I$(TOP)cores/arduelli \
	-I$(TOP)system/stm32/inc \
	-I$(TOP)system/stm32/CMSIS/Include \
	-I$(TOP)variants/$(VARIANT)

#
# No user serviceable parts below
#

ifeq ($(SCRIPTDIR),)
SCRIPTDIR=$(TOP)scripts/
endif

$(eval CC  	:= $(call expand,compiler.cmd.cc))
$(eval CXX      := $(call expand,compiler.cmd.cxx))
$(eval LD       := $(call expand,compiler.cmd.ld))
$(eval AR       := $(call expand,compiler.cmd.ar))
$(eval ELF2HEX  := $(call expand,compiler.cmd.elf2hex))

$(eval CFLAGS   := $(call expand,compiler.cmd.cc.flags))
$(eval CXXFLAGS := $(call expand,compiler.cmd.cxx.flags))
$(eval LDFLAGS  := $(call expand,compiler.cmd.ld.flags))
$(eval ARFLAGS  := $(call expand,compiler.cmd.ar.flags))
$(eval EHFLAGS  := $(call expand,compiler.cmd.elf2hex.flags))

$(eval LIBS     = $(call expand,compiler.cmd.ld.libs))

CFLAGS   += $(EXTRA_CFLAGS)
CXXFLAGS += $(EXTRA_CFLAGS)

#
# Figure out the GCC installation directories to locate libc.a
#

LIBGCC_LIBRARY := \
	$(shell $(CC) $(CFLAGS) -print-libgcc-file-name)

LIBS += $(LIBGCC_LIBRARY)
