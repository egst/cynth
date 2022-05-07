include make/setup.mk

define help_text
This makefile generates the following by default:
* build/{PLATFORM}/compiler$(exe): Cynth transpiler.
* build/{PLATFORM}/{DRIVER}/controller/dep$(slib): Control program dependencies.
* build/{PLATFORM}/{DRIVER}/controller/entry$(obj): Control program entry point.
* build/{PLATFORM}/controller/*$(dlib): Control program dynamic libraries.
* internal/(compiler|controller)/build/*, external/(asio)/build/*: Intermediate module files.
It can also generate these files on demand:
* build/workspace/*

Actions:
* clean-platform-external/{MODULE}, clean-platform-internal/{MODULE}:
    Clean up individual modules, but only files related to the current platform.
* clean-external/{MODULE}, clean-internal/{MODULE}:
    Clean up individual modules but keep dependencies and generated files.
* purge-external/{MODULE}, purge-internal/{MODULE}:
    Clean up individual modules completely.
* clean-platform: Clean up only files related to the current platform.
* clean: Clean up everything but dependencies and generated source files.
* purge: Clean up everything.
* clean-build: Clean the final build files, keep intermediate build files in modules.
* clean-platform-build: Like clean-build but only files related to the current platform.
* clean-workspace: Clean the workspace folder.
* external/{MODULE}, internal/{MODULE}: Build individual modules.
* all: Build everything.
* workspace: Build a workspace folder.
The clean actions only remove platform-dependant files, that are not shipped with the source code,
while the purge actions remove all generated files.

The following variables may be specified for the workspace generation:
* COMPILER (CXX): g++, clang++, cl...
* COMPILER_TYPE: gcc, clang, msvc. The default is msvc on Windows and gcc otherwise.
* PLATFORM: win, linux. Any other value is handled as linux.
* DRIVER: asio, stdout.
* SRATE: Sample rate.
* INTEGRAL, FLOATING: Integral and floating point types.
* COMPILER_FLAGS (CXXFLAGS, CCFLAGS): Additional compiler flags.
* LINKER_FLAGS (LDFLAGS): Additional linkage flags.
* WORKSPACE: Generated workspace location. build/workspace/ by default. The trailing slash is optional.
endef

pass_args  = $(if $(compiler),COMPILER='$(compiler)',)
pass_args += $(if $(compiler_type),COMPILER_TYPE='$(compiler_type)',)
pass_args += $(if $(platform),PLATFORM='$(platform)',)
pass_args += $(if $(driver),DRIVER='$(driver)',)
pass_args += $(if $(srate),SRATE='$(srate)',)
pass_args += $(if $(integral),INTEGRAL='$(integral)',)
pass_args += $(if $(floating),FLOATING='$(floating)',)
pass_args += $(if $(compiler_flags),COMPILER_FLAGS='$(compiler_flags)',)
pass_args += $(if $(linker_flags),LINKER_FLAGS='$(linker_flags)',)

default_driver        = $(if $(filter win,$(platform)),asio,stdout)
default_sample_rate   = 44.1
default_integral_type = int
default_floating_type = float
default_workspace     = build/workspace/

driver    = $(or $(DRIVER),$(default_driver))
srate     = $(or $(SRATE),$(default_sample_rate))
integral  = $(or $(INTEGRAL),$(default_integral_type))
floating  = $(or $(FLOATING),$(default_floating_type))
workspace = $(or $(WORKSPACE),$(default_workspace))

driver    := $(call lc,$(driver))
workspace := $(call lc,$(workspace))

ifeq ($(compiler_type),msvc)
clib = $(slib)
else
clib = $(dlib)
endif

cynth_compiler   = compiler$(exe)
controller_dir   = controller/
controller_dep   = dep$(clib)
controller_entry = entry$(obj)
#controller_libs  = *$(dlib)

modules    = external/asio internal/compiler internal/controller
build_root = build/
build_dir  = $(build_root)$(platform)/

clean_platform_modules = $(modules:%=clean-platform-%)
clean_modules          = $(modules:%=clean-%)
purge_modules          = $(modules:%=purge-%)

.PHONY: all help $(modules) workspace purge clean $(clean_modules) $(clean_platform_modules) $(purge_modules) clean-build clean-workspace

all: $(modules)

help:
	$(info $(help_text))

clean-platform: $(clean_platform_modules) clean-platform-build

clean: $(clean_modules) clean-build

purge: $(purge_modules) clean-build

clean-build:
	$(call rmdir,$(build_root))

clean-platform-build:
	$(call rmdir,$(build_dir))

clean-workspace:
	$(call rmdir,$(workspace))

$(clean_modules): %:
	$(MAKE) -C $(call spath,$(@:clean-%=%)) clean

$(clean_platform_modules): %:
	$(MAKE) -C $(call spath,$(@:clean-platform-%=%)) clean-platform

$(purge_modules): %:
	$(MAKE) -C $(call spath,$(@:purge-%=%)) purge

$(modules): %:
	$(MAKE) -C $(call spath,$@) $(pass_args)

internal/controller: external/asio

workspace: internal/compiler internal/controller make/compose.mk make/setup.mk examples
	$(call rmdir,$(workspace))
	$(call mkdir,$(workspace))
	$(call mkdir,$(workspace)bin/$(controller_dir))
	$(call cp,make/compose.mk,$(workspace)makefile)
	$(call cp,make/setup.mk,$(workspace)setup.mk)
	$(call cp,$(build_root)$(platform)/$(cynth_compiler),$(workspace)bin/$(cynth_compiler))
	$(call cpdir,$(build_root)$(platform)/$(controller_dir),$(workspace)bin/$(controller_dir))
	$(call cpdir,$(build_root)$(platform)/$(driver)/$(controller_dir),$(workspace)bin/$(controller_dir))
	$(call cpdir,examples,$(workspace)examples)

