# /bin/sh is not sufficient for some commands in this makefile.
# Use any shell that supports heredocs and similar constructs in the bash syntax,
# e.g. <(...), $(...), `...`, <<<DOC...DOC, <<<"..." etc.
SHELL := /bin/bash

# C++ standard:
# (At least c++20.)
STD = c++20

# Directory names:
# (Including the trailing slash. Leave empty for the project root directory. Add leading slash for absolute paths.)
INC       = inc/
SRC       = src/
DEP_SRC   = dep/src/
DEP_ENTRY = dep/entry/
DEP_LINK  = dep/link/
BIN_SRC   = obj/src/
BIN_ENTRY = obj/entry/
BIN_DIST  = dist/
GEN       = gen/
TESTS     = tests/
ENTRY     = entry/

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
EXT_EXE   =
#EXT_EXE  = .exe
EXT_CYNTH = .cth

# Entry points:
# (Select entry point implementation files to compile to a final executable.)
# (Excluding the ENTRY directory and the EXT_IMPL extension.)
#ENTRY_POINTS += cynth
#ENTRY_POINTS += parser
#ENTRY_POINTS += interpreter
#ENTRY_POINTS += test
ENTRY_POINTS += compiler

# Compiler:
# (Tested with GCC 10, Clang 10 and 11.)
#COMPILER = g++-10
#COMPILER = clang++-10
COMPILER = clang++-11

# GCC (g++), Flex and Bison executable names/locations:
# (GCC must be installed even when compiling with Clang. It is used for dependencies generation.)
GCC   = g++
FLEX  = flex
BISON = bison

# Additional compiler options:
# (Do not set the -std, -I and -O options here.)
ADDITIONAL_OPTIONS  = -static -Wall -Wextra -pedantic
ADDITIONAL_OPTIONS += -Wno-missing-braces
ADDITIONAL_OPTIONS += -fdiagnostics-color=always
ADDITIONAL_OPTIONS += -ftemplate-backtrace-limit=0
ADDITIONAL_OPTIONS += -fvisibility-inlines-hidden
#ADDITIONAL_OPTIONS += -fsanitize=undefined

# More additional options:
# * linkage (with the chosen compiler)
# * dependency generation (with GCC)
# * flex lexer
# * bison parser
LINK_OPTIONS   = -fdiagnostics-color=always
LINK_OPTIONS  += -fvisibility-inlines-hidden
#LINK_OPTIONS  += -fsanitize=undefined
DEP_OPTIONS    =
FLEX_OPTIONS   =
BISON_OPTIONS  = -Wcounterexamples
