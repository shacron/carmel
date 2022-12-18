############################################################
# carmel build system
# variables named BLD_* are expected to be derived from a
# higher-level make invocation, if present.
############################################################

PROJECT := carmel
SRCDIR := src

BLD_BASEDIR ?= build
BLD_TARGET_LIBDIR ?= $(BLD_BASEDIR)/lib
BLD_TARGET_OBJDIR ?= $(BLD_BASEDIR)/obj

BLD_TARGET_CFLAGS ?=
PREFIX ?= export
BLD_TARGET_INCDIR ?= $(PREFIX)/include
BLD_TARGET_LIBDIR ?= $(PREFIX)/lib

COMMON_FLAGS := -Wall -Wthread-safety -g -O3 -MMD
DEFINES :=
INCLUDES := -Iinclude -I$(SRCDIR)/inc

BLD_TARGET_CC ?= clang
BLD_TARGET_AR ?= ar

CFLAGS := $(COMMON_FLAGS) $(BLD_TARGET_CFLAGS) -std=c11 -nostdinc
CFILES :=


############################################################
# build config options
############################################################

# todo, make this more dynamic
DEFINES += -DCARMEL_UNSAFE_STRING=1 -DCARMEL_THREAD_LOCAL=1


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

$(BLD_TARGET_OBJDIR)/%.c.o: %.c
	@mkdir -p $(dir $@)
	@echo " [cc]" $<
	@$(BLD_TARGET_CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -o $@ -c $<

############################################################
# clean rules
############################################################

.PHONY: clean
clean:
	@rm -rf $(BLD_BASEDIR)

include $(wildcard $(OBJS:.o=.d))