#
# Copyright (c) 2014 ELL-i co-op.
#
# This is part of ELL-i software.
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
# Initial, dumb version of emulator testing script.
#

import ctypes
from subprocess import call

emulator = ctypes.CDLL("./emulator/ellduino/libtest_SPI_transfer.so")

emulator._Z5setupv();
emulator._Z4loopv();
