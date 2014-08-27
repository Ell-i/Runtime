#
# Copyright (c) 2013-2014 Ell-i co-operative
#
# Define make variables for the Emulator
#

VARIABLE_FILES := $(TOP)make/emulator.txt $(TOP)make/$(VARIANT).txt $(TOP)platform.txt $(TOP)boards.txt

ifeq ($(SCRIPTDIR),)
SCRIPTDIR=$(TOP)scripts/
endif

define expand
$(shell $(SCRIPTDIR)expand-arduino-ide-definition.sh $(1) $(VARIABLE_FILES))
endef

$(eval EXTRA_CFLAGS_FROM_BUILD := $(call expand,$(VARIANT).build.extra_flags))

EXTRA_CFLAGS += \
        -DEMULATOR \
	$(EXTRA_CFLAGS_FROM_BUILD) \
	-Dmain=emulated_main \
	-I$(TOP)emulator/inc \
	-I$(TOP)cores/arduelli \
	-I$(TOP)system/stm32/inc \
	-I$(TOP)system/stm32/CMSIS/Include \
	-I$(TOP)variants/$(VARIANT) \
	-Wno-deprecated-register \

#
# No user serviceable parts below
#

LD_LINKER_FILE := $(SCRIPTDIR)/elf_i386.xc

ifeq ($(shell uname -s),Darwin)
CC  := clang++ -x c++
CXX := clang++ -x c++
LD  := llvm-g++
LD_SCRIPT :=
else
CC  := g++
CXX := g++
LD  := g++ -m32 -march=i386
LD_SCRIPT := -Xlinker -T -Xlinker $(LD_LINKER_FILE)
endif
AR  := ar
ELF2HEX := :

CFLAGS   := \
  $(subst -std=c99,-std=c++98,$(subst -mcpu=cortex-m0,,$(call expand,compiler.cmd.cc.flags)))

CXXFLAGS := \
  $(subst -std=gnu++0x,-std=c++98,$(subst -mcpu=cortex-m0,,$(call expand,compiler.cmd.cxx.flags)))

ARFLAGS  := $(call expand,compiler.cmd.ar.flags)

$(eval LIBS := \
  $(subst -lstm32f0,-lsystem_$(VARIANT),$(subst -lstm32f4,-lsystem_$(VARIANT),$(call expand,compiler.cmd.ld.libs))))

CFLAGS   += $(EXTRA_CFLAGS)
CXXFLAGS += $(EXTRA_CFLAGS)

#
# Linking segments and shared library creation
#
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
PRE_OBJS    := emulator_pre.o
POST_OBJS   := emulator_post.o
SHAREDFLAGS := -Wl,-dylib -Wl,-macosx_version_min -Wl,10.8
LDFLAGS     := -m32 -Wl,-arch -Wl,i386 $(LD_SCRIPT)
else
LDFLAGS  := -m32 -march=i386 $(LD_SCRIPT)
SHAREDFLAGS := -shared -Xlinker --export-dynamic
DYLD        = $(LD)
endif

#
# C++ standard library
#

LIBS += -lstdc++

#
# Additional system objects
#

SYSTEM_OBJS := emulator.o Register.o  GPIO.o TIM.o USART.o SPI.o
SYSTEM_OBJS += PWR.o SCB.o RCC.o FLASH.o
SYSTEM_OBJS += Register_RCC_CFGR.o
SYSTEM_OBJS += Register_GPIO_PUPDR.o Register_GPIO_MODER.o Register_GPIO_IDR.o
SYSTEM_OBJS += Register_GPIO_ODR.o Register_GPIO_BSRR.o Register_GPIO_AFR.o Register_GPIO_BRR.o
VPATH += $(TOP)emulator/src
