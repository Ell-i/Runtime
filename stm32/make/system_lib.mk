#
# Copyright (c) 2013-2014 ELL-i co-operative
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
#
# Compile and create the system libraries
#

TOP ?=../
MAKEDIR ?= $(TOP)make/

#
# Set up the compilation environment, recursively if needed
#
include $(MAKEDIR)combinations.mk

#
# Define system library objects.  Add new objects here.
#

ifeq ($(VARIANT),ellduino)
SYSTEM_TYPE = stm32f0
SYSTEM_OBJS += \
	startup_stm32f0xx.o \
	clock_stm32f0xx.o \
	system_stm32f0xx.o
endif
ifeq ($(VARIANT),stm32f0discovery)
SYSTEM_TYPE = stm32f0
SYSTEM_OBJS += \
	startup_stm32f0xx.o \
	clock_stm32f0xx.o \
	system_stm32f0xx.o
endif
ifeq ($(VARIANT),stm32f4discovery)
SYSTEM_TYPE = stm32f4
SYSTEM_OBJS += \
	startup_stm32f40xx.o \
	system_stm32f4xx.o
endif
ifeq ($(VARIANT),stm32f334nucleo)
SYSTEM_TYPE = stm32f3
SYSTEM_OBJS += \
	startup_stm32f334x8.o \
	system_stm32f3xx.o
endif

SYSTEM_OBJS += \
	system_init.o \
	$(VARIANT)_gpio.o \
	$(VARIANT)_timer.o \
	$(VARIANT)_usart.o \

#
# Define source directories
#

VPATH += $(TOP)system/stm32/src $(TOP)variants/$(VARIANT)

#
# Rules
#

ifeq ($(PLATFORM),hardware)
SYSTEM_LIB = $(TOP)variants/$(VARIANT)/lib$(SYSTEM_TYPE).a
endif
ifeq ($(PLATFORM),emulator)
SYSTEM_LIB = ./libsystem_$(VARIANT).a
endif

ifdef LOCAL_RULES

all:  $(SYSTEM_LIB)

clean::
	rm -f $(SYSTEM_LIB)
	rm -f $(SYSTEM_OBJS)

$(SYSTEM_LIB):	$(SYSTEM_OBJS)
	$(AR) $(ARFLAGS) $@ $(SYSTEM_OBJS)

endif
