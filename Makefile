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

CONFIG_UNSAFE_STRING := 1

define config_add
ifeq ($$($(1)),1)
DEFINES += -D$(1:CONFIG_%=CARMEL_%)=1
endif
endef

# include config.mk
$(eval $(call config_add,CONFIG_UNSAFE_STRING))

CFLAGS := $(COMMON_FLAGS) -std=c11 -nostdinc
CXXFLAGS := $(COMMON_FLAGS) -std=c++17 -nostdinc -nostdinc++

CCFILES :=
CFILES :=

include $(SRCDIR)/build.mk

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
	@$(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -o $@ -c $<

$(BUILDDIR)/%.cc.o: $(SRCDIR)/%.cc
	@mkdir -p $(dir $@)
	@echo "c++" $<
	@$(CXX) $(CXXFLAGS) $(DEFINES) $(INCLUDES) -o $@ -c $<

.PHONY: clean
clean:
	@rm -rf $(BUILDDIR)

include $(wildcard $(OBJS:.o=.d))