# build options for macOS and other Darwin targets

UROOT ?= $(HOME)/local/homebrew
SDK := macosx
ARCH := arm64

CC := $(shell xcrun -sdk $(SDK) -find clang)
CXX := $(shell xcrun -sdk $(SDK) -find clang++)
ARCHIVE := $(shell xcrun -sdk $(SDK) -find ar)
LINK := $(shell xcrun -sdk $(SDK) -find ld)
MINVER := -macosx_version_min 12.1

CC := clang
CXX := clang++
ARCHIVE := ar
LINK := ld

LINKFLAGS := $(MINVER) -lSystem
LIBFLAGS := $(MINVER) -dylib -lSystem -L/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/lib
#LINKLIBS := -lpthreads
