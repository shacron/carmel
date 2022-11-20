BUILDDIR ?= build
SRCDIR := src
PROJECT := carmel

TARGET_OS ?= host
TARGET_CFLAGS ?=
PREFIX ?= export
HEADER_PREFIX ?= $(PREFIX)/include
LIB_PREFIX ?= $(PREFIX)/lib

COMMON_FLAGS := -Wall -Wthread-safety -g -O3 -MMD
LDFLAGS :=
LIBFLAGS :=
DEFINES :=
INCLUDES := -Iinclude
TEST_INCLUDES :=
DYLIB_EXT := so

ifeq ($(TARGET_OS),host)

TARGET_OS := $(shell uname -s | tr '[:upper:]' '[:lower:]')
include target/$(TARGET_OS).mk

else

DYLIB_EXT ?= so
CC ?= clang
CXX ?= clang++
AR ?= ar
LD ?= ld

endif # TARGET_OS

CONFIG_UNSAFE_STRING := 1

define config_add
ifeq ($$($(1)),1)
DEFINES += -D$(1:CONFIG_%=CARMEL_%)=1
endif
endef

# include config.mk
$(eval $(call config_add,CONFIG_UNSAFE_STRING))

CFLAGS := $(COMMON_FLAGS) $(TARGET_CFLAGS) -std=c11 -nostdinc
CXXFLAGS := $(COMMON_FLAGS) $(TARGET_CFLAGS) -std=c++17 -nostdinc -nostdinc++
TESTCFLAGS := $(COMMON_FLAGS) -std=c11
TESTCXXFLAGS := $(COMMON_FLAGS) -std=c++17

CCFILES :=
CFILES :=

include $(SRCDIR)/build.mk

OBJS := $(addprefix $(BUILDDIR)/,$(CFILES) $(CCFILES))
OBJS := $(OBJS:.c=.c.o)
OBJS := $(OBJS:.cc=.cc.o)
OBJS := $(OBJS:.cpp=.cpp.o)

$(PROJECT): $(BUILDDIR)/$(PROJECT).a

# install rules

$(LIB_PREFIX)/libc.a: $(BUILDDIR)/$(PROJECT).a
	@mkdir -p $(LIB_PREFIX)
	@cp $(BUILDDIR)/$(PROJECT).a $(LIB_PREFIX)/libc.a

$(HEADER_PREFIX)/%.h: include/%.h
	@mkdir -p $(dir $@)
	@cp $^ $@

ifeq ($(MAKECMDGOALS),install)
PUB_HEADERS := $(shell find include -name '*.h')
PUB_HEADERS := $(PUB_HEADERS:include/%=$(HEADER_PREFIX)/%)
endif


install: $(PUB_HEADERS) $(LIB_PREFIX)/libc.a

$(BUILDDIR)/$(PROJECT).a: $(OBJS)
	@echo " [ar]" $(notdir $@)
	@$(AR) -cr $@ $^

$(BUILDDIR)/$(PROJECT).$(DYLIB_EXT): $(OBJS)
	@echo " [dylib] " $@
	@$(LD) -o $@ $^ $(LIBFLAGS)

$(BUILDDIR)/%.c.o: %.c
	@mkdir -p $(dir $@)
	@echo " [cc]" $<
	@$(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -o $@ -c $<

.PHONY: clean
clean:
	@rm -rf $(BUILDDIR)

include $(wildcard $(OBJS:.o=.d))