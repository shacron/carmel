# build options for macOS and other Darwin targets

UROOT ?= $(HOME)/local/homebrew
SDK := macosx
ARCH := $(shell uname -m)

DYLIB_EXT := dylib
SYSLIBS := /Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/lib

CC := $(shell xcrun -sdk $(SDK) -find clang)
CXX := $(shell xcrun -sdk $(SDK) -find clang++)
ARCHIVE := $(shell xcrun -sdk $(SDK) -find ar)
LINK := $(shell xcrun -sdk $(SDK) -find ld)
# MINVER := -macosx_version_min 12.1

CC := clang
CXX := clang++
ARCHIVE := ar
LINK := ld

TEST_INCLUDES += -I$(UROOT)/Cellar/googletest/1.12.0/include
LINKFLAGS := -L$(SYSLIBS) -L$(UROOT)/lib
LIBFLAGS := $(MINVER) -dylib -lSystem -L$(SYSLIBS)
#LINKLIBS := -lpthreads
