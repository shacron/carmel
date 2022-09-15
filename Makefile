BUILDDIR ?= build
SRCDIR := src
PROJECT := carmel

UNAME_S ?= $(shell uname -s)

COMMON_FLAGS := -Wall -Wthread-safety -g -O3 -MMD
LINKFLAGS :=
LIBFLAGS :=
DEFINES :=
INCLUDES := -Iinclude
TEST_INCLUDES :=
DYLIB_EXT := so

ifeq ($(UNAME_S),Darwin)
include target/darwin.mk
else
ifeq ($(UNAME_S),Linux)
include target/linux.mk
endif
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
TESTCFLAGS := $(COMMON_FLAGS) -std=c11
TESTCXXFLAGS := $(COMMON_FLAGS) -std=c++17

CCFILES :=
CFILES :=

include $(SRCDIR)/build.mk

OBJS := $(addprefix $(BUILDDIR)/,$(CFILES) $(CCFILES))
OBJS := $(OBJS:.c=.c.o)
OBJS := $(OBJS:.cc=.cc.o)
OBJS := $(OBJS:.cpp=.cpp.o)

# $(PROJECT): $(BUILDDIR)/$(PROJECT).a $(BUILDDIR)/$(PROJECT).$(DYLIB_EXT)
$(PROJECT): $(BUILDDIR)/$(PROJECT).a

TESTCXXFILES :=
include test/build.mk
TESTOBJS := $(addprefix $(BUILDDIR)/,$(TESTCXXFILES))
TESTOBJS := $(TESTOBJS:.cpp=.cpp.o)

test unit: $(BUILDDIR)/unit

$(BUILDDIR)/unit: $(TESTOBJS) $(BUILDDIR)/$(PROJECT).a
	@echo "link" $@
	@$(LINK) -o $@ $^ $(LINKFLAGS) -lgtest -lc++ -lc -alias_list test/alias.txt

$(BUILDDIR)/$(PROJECT).a: $(OBJS)
	@echo "archive" $@
	@$(ARCHIVE) -cr $@ $^

$(BUILDDIR)/$(PROJECT).$(DYLIB_EXT): $(OBJS)
	@echo "dylib" $@
	@$(LINK) -o $@ $^ $(LIBFLAGS)

$(BUILDDIR)/%.c.o: %.c
	@mkdir -p $(dir $@)
	@echo "cc " $<
	@$(CC) $(CFLAGS) $(DEFINES) $(INCLUDES) -o $@ -c $<

$(BUILDDIR)/test/%.cpp.o: test/%.cpp
	@mkdir -p $(dir $@)
	@echo "c++" $<
	@$(CXX) $(TESTCXXFLAGS) $(DEFINES) $(TEST_INCLUDES) -o $@ -c $<

$(BUILDDIR)/%.cc.o: %.cc
$(BUILDDIR)/%.cpp.o: %.cpp
	@mkdir -p $(dir $@)
	@echo "c++" $<
	@$(CXX) $(CXXFLAGS) $(DEFINES) $(INCLUDES) -o $@ -c $<

.PHONY: clean
clean:
	@rm -rf $(BUILDDIR)

include $(wildcard $(OBJS:.o=.d))