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

TOP ?= $(shell pwd)/../../
MAKEDIR ?= $(TOP)make/

APP := robot_library

APP_OBJS := $(APP).o $(VARIANT).o

EXTRA_CFLAGS += \
	-I$(TOP)libraries/SPI/src/variants \

include $(TOP)make/app.mk

VPATH += \
	$(TOP)tests/robot_library \
#	$(TOP)libraries/CoAP/src/coap \
#	$(TOP)libraries/CoAP/src/encX24j600 \
#
#CXXFLAGS += \
#	-I$(TOP)libraries/CoAP/src/encX24J600 \
#	-I$(TOP)libraries/CoAP/src \
#	-I$(TOP)libraries/SPI/src \
