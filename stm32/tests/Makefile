#
# Copyright (c) 2013 ELL-i co-operative.
#

TARGETS = \
    test_pinMode \

.PHONY : $(TARGETS) all clean

all:	$(TARGETS)
all:	TARGET=all

clean:	$(TARGETS)
clean:	TARGET=clean

$(TARGETS): %:
	$(MAKE) -C $* -f `pwd`/../make/app.mk TOP=`pwd`/../ APP=$@ TARGET=arduino $(TARGET)

