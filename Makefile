CC ?= cc
CFLAGS ?= -Wall -Wextra -std=c99 -O3 -DWITH_TEST
LDFLAGS ?= 

BINDIR = bin
OUTNAME = test
SOURCES = strstarmatch.c
OBJECTS = $(SOURCES:%.c=$(BINDIR)/%.o)

export V := false
export CMD_PREFIX := @
ifeq ($(V),true)
	CMD_PREFIX :=
endif

all: dirs $(BINDIR)/$(OUTNAME)
	@echo "Build finished"

dirs:
	@echo "Creating directories"
	@mkdir -p $(BINDIR) $(dir $(OBJECTS))

clean:
	@echo "Deleting binaries"
	$(CMD_PREFIX)rm -f $(OBJECTS) $(BINDIR)/$(OUTNAME)

$(BINDIR)/%.o: %.c
	@echo "Compiling: $< -> $@"
	$(CMD_PREFIX)$(CC) $(CFLAGS) -c $< -o $@

$(BINDIR)/$(OUTNAME): $(OBJECTS)
	@echo "Linking: $@"
	$(CMD_PREFIX)$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJECTS)

.PHONY: all dirs clean
