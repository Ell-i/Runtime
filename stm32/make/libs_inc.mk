#
# Copyright (c) 2014 ELL-i co-operative
#
# Define non-core library include paths
#

ifdef LOCAL_RULES

# XXX TBD This is wrong, use libs, not wildcarding
CFLAGS    += $(patsubst %,-I%,$(wildcard $(TOP)libraries/*/.))
CXXFLAGS  += $(patsubst %,-I%,$(wildcard $(TOP)libraries/*/.))

LIBS      += \
	$(TOP)build/$(PLATFORM)/$(VARIANT)/libSPI.a \
#	$(TOP)build/$(PLATFORM)/$(VARIANT)/libCoAP.a


all:	$(LIBS)
all:	TARGET=all

clean::	$(LIBS)
clean::	TARGET=clean

$(LIBS): %:
	@make -C $(TOP)build/$(PLATFORM)/$(VARIANT) -f $(TOP)make/lib.mk LIB=SPI \
		LOCAL_RULES=TRUE TOP=$(TOP) PLATFORM=$(PLATFORM) VARIANT=$(VARIANT) $(TARGET)
# XXX replace "SPI" above with the right thing

endif
