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

SUBDIRS = \
    SPI \
    CoAP \

PLATFORM ?= arduino
# PLATFORM = emulator

.PHONY : $(SUBDIRS) all clean tests

all:	$(SUBDIRS)
all:	TARGET=all

clean:	$(SUBDIRS)
clean:	TARGET=clean

tests:	$(SUBDIRS)
tests:	TARGET=tests

#
# Call a submake in all subdirectories
#
# Set the following variables:
#   TOP:      Path to the the top-level compile directory, to find the makefiles etc
#   LIB:      Name for the library to build, corresponding to the subdirectory name
#   PLATFORM: The platform to build for, currently either arduino or emulator

$(SUBDIRS): %:
	if [ -f $*/Makefile ]; then \
		$(MAKE) -C $*  TOP=`pwd`/../ LIB=$@ \
			PLATFORM=$(PLATFORM) $(TARGET); \
	else \
		$(MAKE) -C $* -f `pwd`/../make/lib_default.mk TOP=`pwd`/../ LIB=$@ \
			PLATFORM=$(PLATFORM) $(TARGET); \
	fi
