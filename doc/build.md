# Build procedures

## Overview

In general, all QuaLLa build targets require the following tools, libraries and SDKs:

- CMake 3.26 or later
- LLVM/Clang 17 or later
- Latest Rust (rustup and cargo)

Various targets have additional requirements that are listed below.

The easiest way to build the QuaLLa from sources is by using the CI Toolchains.
CI Toolchain is a Docker image that includes all requirements for a particular target.
Please see [GitHub Workflow](../.github/workflows/build.yml) for details on where to get 
the toolchains (registry URL, naming, etc).

*Please note that if you have QuaLLA Plus version of the source code you can add '+plus' 
to all target names below (e.g arm64-android-lanai+plus) to enable Plus features.*

## Android arm64 Targets (Snapdragon 8 Gen 3) 

Android target requirements:

- Android NDK r26b or later
- QNN SDK 2.16 or later

### Using CI toolchain

```
$ git clone --recursive https://github.qualcomm.com/qualla/qualla.git
Cloning into 'qualla'...

$ cd qualla/
qualla $ ./ci/run-build.sh arm64-android-lanai
```

### Directly with CMake

```
$ git clone --recursive https://github.qualcomm.com/qualla/qualla.git
Cloning into 'qualla'...
 
$ cd qualla/
qualla $ export NDK=/usr/lib/android-sdk/ndk-r26
qualla $ export QNN_SDK_ROOT=/opt/qnn
qualla $ cmake --preset arm64-android-lanai+plus-release
...
qualla $ cmake --build build-arm64-android-lanai-release
...
```

## Windows arm64 Targets (Hamoa)

Windows target requirements:

For MinGW-based builds:

- LLVM-MinGW toolchain

For native Widows10/11 arm64 builds

- MS Visual Studio 2022 or later (Community Edition or Pro)
- MSVC arm64 standard and runtime libraries
- Clang compiler for Visual Studio
- Latest Git Bash

### MinGW builds with CI toolchain

```
$ git clone --recursive https://github.qualcomm.com/qualla/qualla.git
Cloning into 'qualla'...

$ cd qualla/
qualla $ ./ci/run-build.sh arm64-mingw-hamoa
```

### Windows builds with CI scripts

These instructions should be executed from Git Bash shell.

```
$ git clone --recursive https://github.qualcomm.com/qualla/qualla.git
Cloning into 'qualla'...

$ cd qualla/
qualla $ ./ci/run-build.cmd arm64-win10-hamoa
```

## Ubuntu x64 Targets (22.04, 20.04)

### x64 builds with CI toolchain

```
$ git clone --recursive https://github.qualcomm.com/qualla/qualla.git
Cloning into 'qualla'...

$ cd qualla/
qualla $ ./ci/run-build.sh x64-ubuntu-2204
```
