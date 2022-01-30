# /bin/sh is not sufficient for some commands in this makefile.
# Use any shell that supports heredocs and similar constructs in the bash syntax,
# e.g. <(...), $(...), `...`, <<<DOC...DOC, <<<"..." etc.
#SHELL := /bin/bash
# Update: None of these constructs are needed anymore.

# C++ standard:
# (At least c++20.)
STD = c++20

# C standard for the generated C code:
# Support of the GNU C dialect required.
SYNTH_STD = gnu17

PLATFORM = WINDOWS
#PLATFORM = LINUX

#DRIVERAPI = STDOUT
DRIVERAPI = ASIO

#SYNTHOUT = DEBUG
SYNTHOUT = STAT

# Header locations and additional options for crosscompilation. (optional)
# These are currently only used to generate compilation_commands.json for the clangd language server
# and are usefull when working (editing) from Linux while targeting Windows with ASIO.
CLANGD_COMPILER   = clang++
CROSSCOMP_OPTIONS = -target x86_64-w64-mingw32 -fms-extensions
CROSSCOMP_INC    += /mnt/c/msys64/mingw64/include/c++/10.1.0
CROSSCOMP_INC    += /mnt/c/msys64/mingw64/include/c++/10.1.0/backward
CROSSCOMP_INC    += /mnt/c/msys64/mingw64/include/c++/10.1.0/x86_64-w64-mingw32
CROSSCOMP_INC    += /mnt/c/msys64/mingw64/x86_64-w64-mingw32/include
CROSSCOMP_INC    += /mnt/c/msys64/mingw64/lib/clang/10.0.0/include

# Directory names:
# (Including the trailing slash. Leave empty for the project root directory. Add leading slash for absolute paths.)
INC            = inc/
EXTERN         = ext/
SRC            = src/
DEP_SRC        = dep/src/
DEP_ENTRY      = dep/entry/
DEP_LINK       = dep/link/
BIN_SRC        = obj/src/
BIN_ENTRY      = obj/entry/
BIN_EXTERN     = obj/ext/
BIN_DIST       = dist/
GEN            = gen/
ENTRY          = entry/
TEST_IN        = tests/in/
TEST_C_DEBUG   = tests/out/c/debug/
TEST_C_STAT    = tests/out/c/static/
TEST_BIN_DEBUG = tests/out/bin/debug/
TEST_BIN_STAT  = tests/out/bin/static/
TEST_BIN_COMPL = tests/out/bin/complete/

# Generated files location:
# (Excluding the SRC or INC directory and the EXT_IMPL or EXT_HEAD extension.)
IMPL_LEXER  = lexer
IMPL_PARSER = parser
HEAD_PARSER = parser

# File extensions:
# (Including the leading dot. Leave empty for extensionless files.)
EXT_IMPL  = .cpp
EXT_HEAD  = .hpp
EXT_DEP   = .mk
#EXT_DEP  = .d
EXT_OBJ   = .o
#EXT_EXE   =
EXT_EXE  = .exe
EXT_CYNTH = .cth

# Entry points:
# (Select entry point implementation files to compile to a final executable.)
# (Excluding the ENTRY directory and the EXT_IMPL extension.)
ENTRY_POINTS += compiler
#ENTRY_POINTS += test
#ENTRY_POINTS += control

# Compiler:
# (Tested with GCC 10, Clang 10 and 11.)
#COMPILER = g++
#COMPILER = g++-10
COMPILER = clang++
#COMPILER = clang++-10
#COMPILER = clang++-11
# Note: This is just to work around some path problems on my machine:
#COMPILER = C:\msys64\mingw64\bin\clang++

# GCC (gcc and g++), Flex and Bison executable names/locations:
# (GCC must be installed even when compiling with Clang. It is used for dependencies generation.)
GCC   = gcc
GPP   = g++
FLEX  = flex
BISON = bison

# Compiler options:
# (Do not set the -std, -I and -O options here.)
COMP_OPTIONS  = -static -Wall -Wextra -pedantic
COMP_OPTIONS += -Wno-missing-braces
COMP_OPTIONS += -fdiagnostics-color=always
COMP_OPTIONS += -ftemplate-backtrace-limit=0
COMP_OPTIONS += -fvisibility-inlines-hidden
#COMP_OPTIONS += -fsanitize=undefined
#COMP_OPTIONS += -pthread

# More options:
# * linkage (with the chosen compiler)
# * dependency generation (with GCC)
# * flex lexer
# * bison parser
LINK_OPTIONS       += -fdiagnostics-color=always
LINK_OPTIONS       += -fvisibility-inlines-hidden
#LINK_OPTIONS      += -fsanitize=undefined
DEP_OPTIONS        +=
FLEX_OPTIONS       +=
BISON_OPTIONS      += -Wcounterexamples

# Generated Cynth program compilation options:
# (Do not set the -std and -I options here.)
SYNTH_COMP_OPTIONS += -Wall -O2
SYNTH_COMP_OPTIONS += -Wno-unused-variable
SYNTH_COMP_OPTIONS += -Wno-unused-but-set-variable
SYNTH_COMP_OPTIONS += -Wno-unused-label

# Macro definitions:
DEFS +=
