############################################################
# carmel build system
# variables named BLD_* are expected to be derived from a
# higher-level make invocation, if present.
############################################################

SDKDIR ?= ../sdk
PROJECT := carmel
SRCDIR := src

BLD_BASEDIR ?= build
BLD_TARGET_LIBDIR ?= $(BLD_BASEDIR)/lib
BLD_TARGET_OBJDIR ?= $(BLD_BASEDIR)/obj
BLD_HOST_OS ?= $(shell uname -s)

BLD_TARGET_CFLAGS ?=
PREFIX ?= export
BLD_TARGET_INCDIR ?= $(PREFIX)/include
BLD_TARGET_LIBDIR ?= $(PREFIX)/lib

COMMON_FLAGS := -Wall -Wthread-safety -g -O0 -MMD
DEFINES :=
INCLUDES := -Iinclude -I$(SRCDIR)/inc

BLD_TARGET_CC ?= clang
BLD_TARGET_AR ?= ar
BLD_TARGET_NM ?= nm
BLD_TARGET_LD ?= clang
ifeq ($(BLD_HOST_OS),Darwin)
# Unfortunately Xcode doesn't ship with a useful objcopy equivalent.
# Use llvm-objcopy if present. This only affects the test build.
BLD_TARGET_OBJCOPY ?= $(SDKDIR)/tools/Darwin/bin/llvm-objcopy
else
BLD_TARGET_OBJCOPY ?= objcopy
endif

CFLAGS := $(COMMON_FLAGS) -std=c11 -nostdinc
TEST_CFLAGS := $(COMMON_FLAGS) -std=c11
CFILES :=
LDFLAGS := $(BLD_TARGET_LDFLAGS)


############################################################
# build config options
############################################################

# config options list
# C23 - include c23 standard functions
# THREAD_LOCAL - runtime supports thread_local variables
# UNSAFE_STRING - enable string functions that are unsafe

OPTIONS := \
	THREAD_LOCAL \
	UNSAFE_STRING \

DEFINES := $(addprefix -DCARMEL_,$(addsuffix =1,$(OPTIONS)))

include $(SRCDIR)/build.mk

OBJS := $(addprefix $(BLD_TARGET_OBJDIR)/,$(CFILES))
OBJS := $(OBJS:.c=.c.o)

$(PROJECT): $(BLD_BASEDIR)/$(PROJECT).a

############################################################
# install rules
############################################################

$(BLD_TARGET_LIBDIR)/libc.a: $(BLD_BASEDIR)/$(PROJECT).a
	@mkdir -p $(BLD_TARGET_LIBDIR)
	@cp $(BLD_BASEDIR)/$(PROJECT).a $(BLD_TARGET_LIBDIR)/libc.a

$(BLD_TARGET_INCDIR)/%.h: include/%.h
	@mkdir -p $(dir $@)
	@cp $^ $@

ifeq ($(MAKECMDGOALS),$(filter $(MAKECMDGOALS),install install_headers))
PUB_HEADERS := $(shell find include -name '*.h')
PUB_HEADERS := $(PUB_HEADERS:include/%=$(BLD_TARGET_INCDIR)/%)
endif

install_headers: $(PUB_HEADERS)

install: install_headers $(BLD_TARGET_LIBDIR)/libc.a

############################################################
# build rules
############################################################

$(BLD_BASEDIR)/$(PROJECT).a: $(OBJS)
	@echo " [ar]" $(notdir $@)
	@$(BLD_TARGET_AR) -cr $@ $^

$(BLD_TARGET_OBJDIR)/test/%.c.o: test/%.c
	@mkdir -p $(dir $@)
	@echo " [cc]" $<
	@$(BLD_TARGET_CC) $(TEST_CFLAGS) $(TEST_INCLUDES) -o $@ -c $<

$(BLD_TARGET_OBJDIR)/%.c.o: %.c
	@mkdir -p $(dir $@)
	@echo " [cc]" $<
	@$(BLD_TARGET_CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -o $@ -c $<

############################################################
# testable build rules
############################################################

TEST_CFILES :=
TEST_INCLUDES := -Isrc/inc

include test/build.mk

TEST_OBJS := $(addprefix $(BLD_TARGET_OBJDIR)/,$(TEST_CFILES))
TEST_OBJS := $(TEST_OBJS:.c=.c.o)

RENAME_FILE := $(BLD_BASEDIR)/$(PROJECT)_rename.txt



$(BLD_BASEDIR)/$(PROJECT)_test.a: $(BLD_BASEDIR)/$(PROJECT).a
	@nm $^ | sed -n 's/[0-9a-f]* T \(_.*\)/\1 _carmel\1/p' > $(RENAME_FILE)
	@$(BLD_TARGET_OBJCOPY) --redefine-syms=$(RENAME_FILE) $^ $@

$(BLD_BASEDIR)/test: $(TEST_OBJS) $(BLD_BASEDIR)/$(PROJECT)_test.a
	@$(BLD_TARGET_LD) $(TEST_CFLAGS) $(LDFLAGS) -o $@ $^

test: $(BLD_BASEDIR)/test


############################################################
# clean rules
############################################################

.PHONY: clean
clean:
	@rm -rf $(BLD_BASEDIR)

include $(wildcard $(OBJS:.o=.d))