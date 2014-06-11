#
# Copyright (c) 2014 ELL-i co-operative
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
#
# Compile and link a library
#

TOP     ?= ../
MAKEDIR ?= $(TOP)make/

#
# Define the variant to build for
#
PLATFORM ?= arduino
VARIANT  ?= ellduino

#
# Set up the compilation environment, identical to the Arduino IDE,
# and include system lib building; we depend on system libraries
#
include $(MAKEDIR)$(PLATFORM).mk
include $(MAKEDIR)system_libs_inc.mk
include $(MAKEDIR)libs_inc.mk

#
# Rules
#

VPATH += $(TOP)cores/arduelli

all:  $(LIB).a

clean::
	rm -f $(LIB).a
	rm -f $(LIB_OBJS)

$(LIB).a: $(LIB_OBJS)
	$(AR) cr $(LIB).a $(LIB_OBJS)

