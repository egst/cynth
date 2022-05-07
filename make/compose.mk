include setup.mk

define help_text
This makefile compiles an executable file from the given cynth source file. The
resulting executable is located in the {TARGET} directory along with dynamic
libraries and possibly other resources. The whole {TARGET} directory can be
moved anywhere as a whole, but all the contents must stay inside.

Try it out:
	make INPUT=examples/demo/001.cth

To clean up, use:
	make clean

More options may be applied:
	make INPUT=input.cth COMPILER=clang++ TARGET=output/

The following options are accepted:
* INPUT: The input cynth source file.
* COMPILER (CXX): g++, clang++, cl...
* COMPILER_TYPE: gcc, clang, msvc. The default is msvc on Windows and gcc otherwise.
	Note: Clang works ok even with the gcc COMPILER_TYPE option and vice verca.
	It's only MSVC that needs to be specified explicitly.
* CYNTH_C_COMPILER: Must support the gnu17 dialect (e.g. gcc or clang). Default is gcc on Linux and clang on Windows.
* CYNTH_C_COMPILER_TYPE: Same as COMPILER_TYPE but for CYNTH_C_COMPILER.
* TARGET: Final executable files location. {WORKSPACE}/out/ by default. The trailing slash is optional.
* TMPDIR: Indermediate files location. Transpiled C files can be found here. The trailing slash is optional.
endef

ifeq ($(os), win)
default_cynth_c_compiler      = clang
default_cynth_c_compiler_type = clang
else
default_cynth_c_compiler      = gcc
default_cynth_c_compiler_type = gcc
endif

default_target = out/
default_tmpdir = tmp/

input                 = $(INPUT)
cynth_c_compiler      = $(or $(CYNTH_C_COMPILER),$(default_cynth_c_compiler))
cynth_c_compiler_type = $(or $(CYNTH_C_COMPILER_TYPE),$(default_cynth_c_compiler_type))
target                = $(or $(TARGET),$(default_target))
tmpdir                = $(or $(TMPDIR),$(default_tmpdir))

target := $(call dir_path,$(target))
tmpdir := $(call dir_path,$(tmpdir))

ifeq ($(compiler_type),msvc)
clib = $(slib)
else
clib = $(dlib)
endif

ifeq ($(compiler_type), msvc)
linker_flags += /ENTRY:mainCRTStartup
else
linker_flags += $(opt_link_rpath_origin)
endif

name           = cynth
executable     = $(target)$(name)$(exe)
bin_dir        = bin/
cynth_compiler = $(bin_dir)compiler$(exe)
controller_dir = $(bin_dir)controller/
definitions    =
standard       = gnu17
optimization   = 3

libraries =
lib_paths =
dlibs     =
sources   =

dist_dlib_dir   = $(target)
dlib_name       = $(patsubst $(lib)%,%,$(basename $(notdir $1)))
dist_dlib       = $(patsubst %,$(dist_dlib_dir)%,$(notdir $1))
dlib_from       = $(patsubst $(dist_dlib_dir)%,$($1_dpath)%,$2)
dist_dlibs_from = $(foreach f,$($1_dlibs),$(call dist_dlib,$f))
dist_dlibs      = $(foreach f,$(dlibs),$(call dist_dlib,$f))

sources += $(call children,$(controller_dir),$(obj)) $(call children,$(controller_dir),$(slib))

controller_dpath = $(controller_dir)
controller_dlibs = $(call children,$(controller_dir),$(dlib))
dlibs     += $(controller_dlibs)
lib_paths += $(controller_dpath)

ifeq ($(platform), linux)
libraries += $(call dlib_name,$(dlibs))
endif

ifneq ($(compiler_type),msvc)
libraries += m
endif

transpile_computer = $(encoding) $(call cat,$<) | $(call spath,$(cynth_compiler)) > $@
compile_computer   = $(call compile,$(cynth_c_compiler),$(cynth_c_compiler_type),$@,$<,,$(definitions),$(standard),$(optimization),)
link_result        = $(call link,$(compiler),$(compiler_type),$@,$^ $(sources),$(libraries),$(lib_paths),$(linker_flags))

.PHONY: all help clean $(call dist_dlibs_from,controller) $(tmpdir)computer.c $(tmpdir)computer$(obj) $(executable)

ifneq ($(input),)

all: $(executable) $(dist_dlibs)

$(call dist_dlibs_from,controller): %:
	$(call prepare_dir,$@)
	$(call cp,$(call dlib_from,controller,$@),$@)

$(tmpdir)computer.c: $(input)
	$(call prepare_dir,$@)
	$(transpile_computer)

$(tmpdir)computer$(obj): $(tmpdir)computer.c
	$(call prepare_dir,$@)
	$(compile_computer)

$(executable): $(tmpdir)computer$(obj)
	$(call prepare_dir,$@)
	$(link_result)

else

all: help

endif

clean:
	$(call rmdir,$(target))

help:
	$(info $(help_text))
