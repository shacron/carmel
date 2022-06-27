BUILDDIR ?= build
SRCDIR := src
PROJECT := carmel

UNAME_S ?= $(shell uname -s)

COMMON_FLAGS := -Wall -Wthread-safety -g -O3 -MMD
LINKFLAGS :=
LIBFLAGS :=
DEFINES :=
INCLUDES := -Iinclude
DYLIB_EXT := so

ifeq ($(UNAME_S),Darwin)
include target/darwin.mk
endif

CFLAGS := $(COMMON_FLAGS) -std=c11 -nostdinc
CXXFLAGS := $(COMMON_FLAGS) -std=c++17 -nostdinc -nostdinc++
DEFINES := -DCARMEL_UNSAFE_STRING=1

CCFILES := \

CFILES := \
	$(SRCDIR)/stdlib/malloc.c \
	$(SRCDIR)/string/strerror.c \
	$(SRCDIR)/string.c \

OBJS := $(subst $(SRCDIR),$(BUILDDIR),$(CFILES) $(CCFILES))
OBJS := $(OBJS:.c=.c.o)
OBJS := $(OBJS:.cc=.cc.o)

$(PROJECT): $(BUILDDIR)/$(PROJECT).a $(BUILDDIR)/$(PROJECT).$(DYLIB_EXT)

TESTCFILES := $(SRCDIR)/main.c
TESTOBJS := $(subst $(SRCDIR),$(BUILDDIR),$(TESTCFILES))
TESTOBJS := $(TESTOBJS:.c=.c.o)

test: $(BUILDDIR)/test

$(BUILDDIR)/test: $(TESTOBJS)
	@echo "link" $@
	@$(LINK) -o $@ $^ $(LINKFLAGS)

$(BUILDDIR)/$(PROJECT).a: $(OBJS)
	@echo "archive" $@
	@$(ARCHIVE) -cr $@ $^

$(BUILDDIR)/$(PROJECT).$(DYLIB_EXT): $(OBJS)
	@echo "dylib" $@
	@$(LINK) -o $@ $^ $(LIBFLAGS)

$(BUILDDIR)/%.c.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@echo "cc " $<
	@$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

$(BUILDDIR)/%.cc.o: $(SRCDIR)/%.cc
	@mkdir -p $(dir $@)
	@echo "c++" $<
	@$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ -c $<

.PHONY: clean
clean:
	@rm -rf $(BUILDDIR)

include $(wildcard $(OBJS:.o=.d))