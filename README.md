# Carmel

## Warning
This is a WORK IN PROGRESS. If you are looking for production-ready code, there are much better candidates than this project.

## A simple C standard library

This project contains a basic, partial implementation of the C standard library. The intended use is for embedded targets and other low-overhead code. As such, it does not plan to support localization, time zones, math libraries, and other big-system things. The implemented functions are very basic and unoptimized.

## Usage

### Prerequisites

This code has been tested to build with `make` and `clang` on macOS and Linux.

### Building

    make -j <num>

Produce a static library, `carmel.a`. This static library is targeted to the host machine. This is useful for testing but not for cross-compilation to the intended target.

To cross-compile, override the build options in `Makefile` The makefile includes many variables named `BLD_something` that expect to be overriden via the command line or environment. Use them to point to the target toolchain and define the necessary flags.

    make -j <num> \
        BLD_TARGET_CC=/path/to/cc \
        BLD_TARGET_AR=/path/to/llvm-ar \
        BLD_TARGET_CFLAGS="-target arm-linux-none -march=armv7 -mfloat-abi=hard"

Adding `BUILD=debug` to the make command line or your environment will build with code optimizations disabled, for better symbolic debugging. Other overrideable options can control the build output. See the makefile for details.

    make install

Installing copies the C standard headers as well as a copy of the static library (renamed to libc.a) to the install destination. These can be controlled by `BLD_TARGET_INCDIR` and `BLD_TARGET_LIBDIR`, respectively.

### Linking

The linking code must provide an implementation of the platform functions defined in `src/inc/carmel/platform.h`. These perform platform-specific low-level tasks that cannot be implemented by this library.

### Testing

    make test

This builds the test app for unit testing. The test target also builds a special version of the library named `carmel_test.a`. This library prefixes all public symbols with `carmel_` (ex: `carmel_strlen`). This allows the test app to call the standard system libc functions while testing.


## Questions

### Why does this exist?

This is mostly a place for me to gather code that I end up rewriting often, and also just some fun writing the functions that we all depend on day to day.

### Will there be MY_DESIRED_FEATURE?

Probably not. I hope to do some general code optimization, and specific ones for arm and arm64, and possibly riscv.

### Should I contribute code?

I appreciate bug fixes. I am not looking for feature code from others, since that would defeat the purpose of this project. Maybe one day when it's more complete.

### Should I torpedo your hiring process because I found this code?

Definitely. Or you could talk to me about it.

## License

The code is licensed under the MIT License. The short version that you can use this code for any purpose, but should retain the copyright notice in the source.

All code is Copyright (c) 2022-2023 Shac Ron.
