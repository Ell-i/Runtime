#
# Copyright (c) 2014 ELL-i co-operative
#
# Define non-core library include paths
#

LIBES      := $(subst $(TOP)libraries/,,$(wildcard $(TOP)libraries/*))
LIBES_LIBS := $(patsubst %,lib%.a,$(LIBES))
LIBS       := $(LIBES_LIBS) $(LIBS)

CFLAGS    += $(patsubst %,-I$(TOP)libraries/%,$(LIBES)/src)
CXXFLAGS  += $(patsubst %,-I$(TOP)libraries/%,$(LIBES)/src)

ifdef LOCAL_RULES

.PHONY: $(LIBES)

all:	$(LIBES)
all:	TARGET=all

clean:: $(LIBES)
clean::	TARGET=clean

$(LIBES): %:
	@if [ -f $(TOP)libraries/$@/Makefile ]; then \
		echo "make -C $(PLATFORM)/$(VARIANT) -f $(TOP)libraries/$@/Makefile"; \
		$(MAKE) -f $(TOP)libraries/$@/Makefile LIB=lib$@.a \
			LOCAL_RULES=TRUE TOP=$(TOP) PLATFORM=$(PLATFORM) VARIANT=$(VARIANT) $(TARGET); \
	else \
		echo "make -C $(PLATFORM)/$(VARIANT) -f $(TOP)make/lib.mk LIB=lib$@.a"; \
		$(MAKE) -f $(TOP)make/lib.mk LIB=lib$@.a \
			LOCAL_RULES=TRUE TOP=$(TOP) PLATFORM=$(PLATFORM) VARIANT=$(VARIANT) $(TARGET); \
	fi

endif
