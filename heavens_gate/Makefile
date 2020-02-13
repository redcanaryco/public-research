# Usage:
# make        # compile all binary
# make clean  # remove ALL binaries and objects

.SUFFIXES:

LFLAGS = $(BITNESS) -static
CFLAGS = $(BITNESS) -fPIC -ffunction-sections -fdata-sections $(INCLUDES)

OBJDIR ?= build/_X86_32

SRCS ?=
OBJS := $(addprefix $(OBJDIR)/, $(addsuffix .o,$(basename $(SRCS))))
OBJS := $(subst src/,,$(OBJS))
BINS := heavens_gate

ifneq ($(STRACE),)
TEST_PREFIX = strace -f
endif

$(OBJDIR):
	mkdir -p $(OBJDIR)

heavens_gate: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $(OBJDIR)/$@
	strip -s $(OBJDIR)/heavens_gate

$(OBJDIR)/syscall64.o:
	$(CC) $(CFLAGS) -c src/syscall64.S -o $@

$(OBJDIR)/%.o: src/%.S
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

__all: $(OBJDIR) $(BINS)
	@:

all:
	$(MAKE) SRCS="src/main.c src/syscall64.S" BITNESS=-m32 OBJDIR=build/_X86_32 __all
	$(MAKE) SRCS="src/main.c src/syscall32.c" BITNESS=-m64 OBJDIR=build/_X86_64 __all

clean:
	rm -rvf build/*

test:
	$(TEST_PREFIX) build/_X86_64/heavens_gate
	$(TEST_PREFIX) build/_X86_32/heavens_gate
	CONFUSE_STRACE=1 $(TEST_PREFIX) build/_X86_32/heavens_gate


.DEFAULT_GOAL := all

.PHONY = all __all clean test heavens_gate
