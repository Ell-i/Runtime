#
# Copyright (c) 2014 ELL-i co-operative.
#
# ELL-i software is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# ELL-i software is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# You should have received a copy of the GNU General Public License
# along with ELL-i software.  If not, see <http://www.gnu.org/licenses/>.
#
#

# Variants that we build the system lib for
# If you update these here, please be sure to make the same
# change into the SYSTEM_LIBS in system_libs.mk

VARIANTS = \
	ellduino \
	stm32f4discovery
#	stm32f0discovery \

.PHONY : $(VARIANTS) all clean tests

all:	$(VARIANTS)
all:	TARGET=all

clean::	$(VARIANTS)
clean::	TARGET=clean

$(VARIANTS): %:
	mkdir -p $*
	$(MAKE) -C $* -f $(TOP)make/system_lib.mk TOP=$(TOP) VARIANT=$@ PLATFORM=$(PLATFORM) $(TARGET)
