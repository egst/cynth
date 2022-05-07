root = ../../

include $(root)make/setup.mk

define help_text
This makefile generates the following:
* ./build/obj/{PLATFORM}/*$(obj): Object files.

Actions:
* all: Build everything.
* clean-platform: Clean up only files related to the current platform.
* clean: Clean up everything.

The following variables may be specified:
* COMPILER (CXX): C++ compiler. Tested with GCC, Clang and MSVC.
* COMPILER_TYPE: gcc, clang, msvc. The default is msvc on Windows and gcc otherwise.
* PLATFORM: win, linux. Any other value is handled as linux.
* DRIVER: asio, stdout.
* COMPILER_FLAGS (CXXFLAGS, CCFLAGS): Additional compiler flags.
endef

default_driver = $(if $(filter win,$(platform)),asio,stdout)

driver = $(or $(DRIVER),$(default_driver))
driver := $(call lc,$(driver))

build_dir    = build/
obj_dir      = $(build_dir)obj/$(platform)/
obj_files    = common/asio$(obj)
obj_files   += host/asiodrivers$(obj)
obj_files   += host/pc/asiolist$(obj)
inc_paths    = common/
inc_paths   += host/
inc_paths   += host/pc/
#standard     = c++14
standard     = c++20
#optimization = 2
optimization = 3

compile_unit = $(call compile,$(compiler),$(compiler_type),$@,$<,$(inc_paths),,$(standard),$(optimization),$(compiler_flags))

obj_files := $(obj_files:%=$(obj_dir)%)

.PHONY: all help purge clean clean-platform

ifeq ($(driver), asio)

all: $(obj_files)

$(obj_dir)%$(obj): %.cpp
	$(call prepare_dir,$@)
	$(compile_unit)

else

all:

endif

help:
	$(info $(help_text))

clean:
	$(call rmdir,$(build_dir))

clean-platform:
	$(call rmdir,$(obj_dir))

purge: clean
