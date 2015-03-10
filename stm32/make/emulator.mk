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
	-Wno-deprecated \

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
  $(subst -std=c99,-std=c++11,$(subst -mcpu=cortex-m0,,$(call expand,compiler.cmd.cc.flags)))

CXXFLAGS := \
  $(subst -std=gnu++0x,-std=c++11,$(subst -mcpu=cortex-m0,,$(call expand,compiler.cmd.cxx.flags)))

ARFLAGS  := $(call expand,compiler.cmd.ar.flags)

$(eval LIBS := \
  $(subst -lstm32f0,-lsystem_$(VARIANT), \
  $(subst -lstm32f4,-lsystem_$(VARIANT), \
  $(subst -lstm32f3,-lsystem_$(VARIANT), \
  $(call expand,compiler.cmd.ld.libs)))))



#The Cflags and LIBS are used for cpython extension module and cpython API in emulator
#Currently, the support is added for Linux only.
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
#EXTRA_CFLAGS += -I/opt/pym32/include/python2.7/ -I/lib/i386-linux-gnu/
EXTRA_CFLAGS += $(shell pkg-config --cflags python2)
EXTRA_CFLAGS += -pthread -fno-strict-aliasing -fwrapv -Wall -fPIC
LIBS        += $(shell pkg-config --libs python2) -lpthread -ldl -lutil -lm
#LIBS        += -L/opt/pym32/lib/ -L/lib/i386-linux-gnu/ -L/lib32 -L/usr/lib32
#LIBS        += -lpython2.7 -lpthread -ldl -lutil -lm
endif

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
LDFLAGS     := -m32 -march=i386 $(LD_SCRIPT)
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

#Emulator Object File
SYSTEM_OBJS := emulator.o

#Emulator Python Callback Module Object File
SYSTEM_OBJS += pythonCallback.o

#Emulator Register Object File
SYSTEM_OBJS += Register.o

#Emulator FLASH Object Files
SYSTEM_OBJS += FLASH.o
SYSTEM_OBJS +=  Register_FLASH_ACR.o Register_FLASH_KEYR.o Register_FLASH_OPTKEYR.o
SYSTEM_OBJS +=  Register_FLASH_SR.o Register_FLASH_CR.o

#Emulator PWR Object Files
SYSTEM_OBJS += PWR.o
SYSTEM_OBJS += Register_PWR_CR.o

#Emulator SCB Object Files
SYSTEM_OBJS += SCB.o
SYSTEM_OBJS += Register_SCB_CPUID.o Register_SCB_ICSR.o Register_SCB_VTOR.o

#Emulator TIM Object Files
SYSTEM_OBJS += TIM.o
SYSTEM_OBJS += Register_TIM_CR1.o Register_TIM_CR2.o Register_TIM_SMCR.o
SYSTEM_OBJS += Register_TIM_DIER.o Register_TIM_CCMR1.o Register_TIM_CCMR2.o
SYSTEM_OBJS += Register_TIM_CCER.o Register_TIM_BDTR.o Register_TIM_PSC.o
SYSTEM_OBJS += Register_TIM_ARR.o Register_TIM_CCR1.o Register_TIM_CCR2.o
SYSTEM_OBJS += Register_TIM_CCR3.o Register_TIM_CCR4.o

#Emulator RCC Object Files
SYSTEM_OBJS += RCC.o
SYSTEM_OBJS += Register_RCC_CR.o Register_RCC_PLLCFGR.o Register_RCC_CFGR.o
SYSTEM_OBJS += Register_RCC_CFGR.o Register_RCC_CIR.o Register_RCC_APB1RSTR.o
SYSTEM_OBJS += Register_RCC_AHB1ENR.o Register_RCC_AHBENR.o
SYSTEM_OBJS += Register_RCC_APB2ENR.o Register_RCC_APB1ENR.o
SYSTEM_OBJS += Register_RCC_APB2RSTR.o Register_RCC_BDCR.o
SYSTEM_OBJS += Register_RCC_CSR.o Register_RCC_AHBRSTR.o
SYSTEM_OBJS += Register_RCC_CFGR2.o Register_RCC_CFGR3.o Register_RCC_CR2.o

#Emulator GPIO Object Files
SYSTEM_OBJS += GPIO.o
SYSTEM_OBJS += Register_GPIO_PUPDR.o Register_GPIO_MODER.o Register_GPIO_IDR.o
SYSTEM_OBJS += Register_GPIO_ODR.o Register_GPIO_BSRR.o Register_GPIO_AFR.o Register_GPIO_BRR.o
SYSTEM_OBJS += Register_GPIO_BSRRL.o Register_GPIO_BSRRH.o

#Emulator USART Object Files
SYSTEM_OBJS += USART.o
SYSTEM_OBJS += Register_USART_BRR.o Register_USART_CR1.o Register_USART_CR2.o Register_USART_CR3.o
SYSTEM_OBJS += Register_USART_GTPR.o Register_USART_SR.o Register_USART_DR.o
SYSTEM_OBJS += Register_USART_ICR.o Register_USART_RTOR.o Register_USART_RQR.o
SYSTEM_OBJS += Register_USART_ISR.o Register_USART_RDR.o Register_USART_TDR.o

#Emulator SPI Object Files
SYSTEM_OBJS += SPI.o
SYSTEM_OBJS += Register_SPI_CR1.o Register_SPI_CR2.o Register_SPI_SR.o Register_SPI_DR.o

VPATH += $(TOP)emulator/src
