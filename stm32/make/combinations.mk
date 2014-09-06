#
# Copyright (c) 2014 ELL-i co-operative.
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
# A "meta" makefile that recursively calls first itself, and then
# another makefile, for all platforms and variants
#
# The behaviour depends on whether $(PLATFORM) and/or $(VARIANT) is defined:
# - if $(PLATFORM) is not defined, then iterate over the defined
#   $(PLATFORMS), recursively calling itself with the $(PLATFORM) set
# - if the $(PLATFORM) is defined but the $(VARIANT) is not defined,
#   then iterate over the defined $(VARIANTS), recursively calling itself
#   with both the platform and variant set
# - if both are set, then call recursively the real makefile with both
#   $(PLATFORM) and $(VARIANT) set


PLATFORMS = \
	hardware \
	emulator \

#
# Define the system libraries.  Add a new one for each variant.
# If you update these here, please be sure to make the same
# change into the VARIANTS below
#
SYSTEM_LIBS := \
    $(TOP)variants/ellduino/libstm32f0.a \
    $(TOP)variants/stm32f4discovery/libstm32f4.a \
#   $(TOP)variants/stm32f0discovery/libstm32f0.a \

VARIANTS = \
	ellduino \
	stm32f4discovery \

MAKE_TARGETS = all clean tests

MAKEFILE := $(realpath $(firstword $(MAKEFILE_LIST)))

.PHONY : $(PLATFORMS) $(VARIANTS) $(MAKE_TARGETS)

#
# If the $(PLATFORM) is not set when getting here, we iterate
# over the platforms defined above, recursively calling ourselves
#

ifeq ($(PLATFORM),)

#
# Rules for iterating over the platforms
#

all:	$(PLATFORMS)
all:	TARGET=all

clean::	$(PLATFORMS)
clean::	TARGET=clean

tests:	$(PLATFORMS)
tests:	TARGET=tests

$(PLATFORMS): %:
	@$(MAKE) -f $(MAKEFILE) TOP=$(TOP) VARIANT=$(VARIANT) PLATFORM=$@ $(TARGET)

else

#
# If the $(VARIANT) is not set when getting here, we iterate
# over the varians, recursively calling ourselves
#

ifeq ($(VARIANT),)

#
# Rules for iterating over the variants
#

all:	$(VARIANTS)
all:	TARGET=all

clean::	$(VARIANTS)
clean::	TARGET=clean

tests:	$(VARIANTS)
tests:	TARGET=tests

$(VARIANTS): %:
	@$(MAKE) -f $(MAKEFILE) TOP=$(TOP) PLATFORM=$(PLATFORM) VARIANT=$@ $(TARGET)

else

ifndef LOCAL_RULES

#
# Now recursively building for the given platform and variant, calling the actual leaf make
#

$(info )
$(info *********************************************************)
$(info **** In $(PLATFORM)/$(VARIANT))
$(info *********************************************************)
$(info )

all:
	@mkdir -p $(PLATFORM)/$(VARIANT)
	@$(MAKE) -C $(PLATFORM)/$(VARIANT) -f $(MAKEFILE) \
		LOCAL_RULES=TRUE TOP=$(TOP) PLATFORM=$(PLATFORM) VARIANT=$(VARIANT) all

clean:
	@if [ -d $(PLATFORM)/$(VARIANT) ]; then \
		$(MAKE) -C $(PLATFORM)/$(VARIANT) -f $(MAKEFILE) \
			LOCAL_RULES=TRUE TOP=$(TOP) PLATFORM=$(PLATFORM) VARIANT=$(VARIANT) clean; \
		echo "cd ../..; rmdir -p $(PLATFORM)/$(VARIANT)"; \
		rmdir -p $(PLATFORM)/$(VARIANT) || true; \
	fi

tests:
	@$(MAKE) -C $(PLATFORM)/$(VARIANT) -f $(MAKEFILE) \
		LOCAL_RULES=TRUE TOP=$(TOP) PLATFORM=$(PLATFORM) VARIANT=$(VARIANT) tests

else

#
# We are now in the leaf of the recursion, where the real things
# happen.  Hence, we define LOCAL_RULES, which means that the other
# makefiles here are also allowed to define their own rules.
#
# During the branches of the recursion they should not define any
# local rules, since those would just define spurious dependencies
#

#
# Set up the compilation environment for the $(PLATFORM) and $(VARIANT)
#

include $(MAKEDIR)$(PLATFORM).mk

endif
endif
endif
