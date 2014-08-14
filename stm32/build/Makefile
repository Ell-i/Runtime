#
# Copyright (c) 2013-2014 ELL-i co-operative
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

all: 	sketch.cpp
	@APPLICATION_SRC_DIR=$(PWD) $(MAKE) -f ../make/app.mk all

clean:
	@APPLICATION_SRC_DIR=$(PWD) $(MAKE) -f ../make/app.mk clean

clobber: clean
	@echo
	@echo "*********************************************************"
	@echo "**** Removing sketch.cpp"
	@echo "*********************************************************"
	@echo
	rm -f sketch.cpp

sketch.cpp: Makefile
	@echo
	@echo "*********************************************************"
	@echo "**** Creating sketch.cpp"
	@echo "*********************************************************"
	@echo
	echo "#include <Arduino.h>" > sketch.cpp
	echo "void setup() {}"      >> sketch.cpp
	echo "void loop() {}"       >> sketch.cpp
