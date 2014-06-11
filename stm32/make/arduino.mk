#
# Copyright (c) 2013 Ell-i co-operative
#
# This is part of ELL-i software
#
# ELL-i software is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# ELL-i software is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with ELL-i software.  If not, see <http://www.gnu.org/licenses/>.
#
# Extract make variables from the Arduino IDE specifications
#

VARIABLE_FILES := $(TOP)make/arduino.txt $(TOP)platform.txt

EXTRA_CFLAGS += \
	-D__STM32F051__ \
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

define expand
$(shell $(SCRIPTDIR)expand-arduino-ide-definition.sh $(1) $(VARIABLE_FILES))
endef

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
