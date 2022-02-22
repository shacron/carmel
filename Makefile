BUILDDIR ?= build
SRCDIR := src
PROJECT := carmel

SDK := macosx
ARCH := arm64

CC := $(shell xcrun -sdk $(SDK) -find clang)
CXX := $(shell xcrun -sdk $(SDK) -find clang++)
ARCHIVE := $(shell xcrun -sdk $(SDK) -find ar)
LINK := $(shell xcrun -sdk $(SDK) -find ld)
MINVER := -macosx_version_min 12.1

COMMON_FLAGS := -Wall -Wthread-safety -g -O0 -MMD
CFLAGS := $(COMMON_FLAGS) -std=c11 -nostdinc
CXXFLAGS := $(COMMON_FLAGS) -std=c++17 -nostdinc -nostdinc++
DEFINES := -DCARMEL_UNSAFE_STRING=1
LINKFLAGS := $(MINVER) -lSystem
LIBFLAGS := $(MINVER) -dylib -lSystem -L/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/lib
#LINKLIBS := -lpthreads

INCLUDES := -Iinclude \

CCFILES := \

CFILES := \
	$(SRCDIR)/stdlib/malloc.c \
	$(SRCDIR)/string/strerror.c \
	$(SRCDIR)/string.c \

OBJS := $(subst $(SRCDIR),$(BUILDDIR),$(CFILES) $(CCFILES))
OBJS := $(OBJS:.c=.c.o)
OBJS := $(OBJS:.cc=.cc.o)

$(PROJECT): $(BUILDDIR)/$(PROJECT).a $(BUILDDIR)/$(PROJECT).dylib

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

$(BUILDDIR)/$(PROJECT).dylib: $(OBJS)
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