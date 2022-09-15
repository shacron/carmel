# build options for Linux targets

ARCH := $(shell uname -m)

DYLIB_EXT := so

CC := clang
CXX := clang++
ARCHIVE := ar
LINK := ld

