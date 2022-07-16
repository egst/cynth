include setup.mk

define help_text
This makefile generates the following by default:
* ./build/obj/{PLATFORM}/*: Intermediate object files.
* {ROOT}/build/{PLAFFORM}/{DRIVER}/controller/entry$(obj): Entry point.
* {ROOT}/build/{PLAFFORM}/{DRIVER}/controller/dep$(slib):
	Import libraries (Windows only) and possibly other object files combined.
	This file might be skipped if no implementation files are used in this module.
* {ROOT}/build/{PLAFFORM}/controller/*$(dlib): Dynamic libraries.
It can also generate these files on demand:
* compile_commands.json: Clangd language server setup.

Actions:
* all: Build everything.
* clangd: Generate clangd config.
* clean-platform-dependencies: Clean up dependencies related to the current platform (and driver).
* clean-dependencies: Clean up all dependencies.
* clean-clangd: Clean up clangd config.
* clean-platform: Clean up only files related to the current platform.
* clean: Clean up everything but dependencies and generated source files.
* purge: Clean up everything.

The following variables may be specified:
* COMPILER (CXX): g++, clang++, cl...
* COMPILER_TYPE: gcc, clang, msvc. The default is msvc on Windows and gcc otherwise.
* ARCHIVER: ar (Linux), gcc-ar, llvm-ar, lib (Windows).
* ARCHIVER_TYPE: ar, lib. The default is lib on Windows and ar otherwise.
* CLANGPP: Clang C++ compniler for the clangd language server setup. Optional.
* PLATFORM: win, linux. Any other value is handled as linux.
* DRIVER: asio, stdout.
* SRATE: Sample rate.
* INTEGRAL, FLOATING: Integral and floating point types.
* COMPILER_FLAGS (CXXFLAGS, CCFLAGS): Additional compiler flags.
* CLANGD_FLAGS: Additional clangd flags.
* CROSSCOMP: msys, ... No crosscompilation configuration if empty.
* CROSSCOMP_FLAGS: Customized flags instead of the CROSSCOMP above.
endef

DRIVER ?= $(if $(filter win,$(platform)),asio,stdout)
$(driver) = $(DRIVER)

name          = controller
dist_dir      = $(root)build/$(platform)/
dist_drv_dir  = $(dist_dir)$(driver)/
dist_dep      = $(dist_drv_dir)$(name)/dep$(slib)
dist_entry    = $(dist_drv_dir)$(name)/entry$(obj)
dist_dlib_dir = $(dist_dir)$(name)/

clangd_config = compile_commands.json
obj_files     = $(obj_dir)entry$(obj)
libraries     =
lib_paths     =
dlibs         =
optimization  = 2
#optimization  = 3

ifeq ($(os), win)
libraries += user32
endif

# ASIO:
ifeq ($(driver), asio)
asio_path  = $(root)external/asio/build/obj/$(platform)/
obj_files += $(asio_path)common/asio$(obj)
obj_files += $(asio_path)host/asiodrivers$(obj)
obj_files += $(asio_path)host/pc/asiolist$(obj)
#libraries += advapi32$(dlib) ksuser$(dlib) ole32$(dlib) user32$(dlib) uuid$(dlib) winmm$(dlib)
#libraries += advapi32$(slib) ksuser$(slib) ole32$(slib) user32$(slib) uuid$(slib) winmm$(slib)
libraries += advapi32 ksuser ole32 user32 uuid winmm
endif

# Ultralight:
ul_path    = $(root)external/ultralight/$(platform)/
ul_dpath   = $(ul_path)bin/
ul_dlibs   = $(ul_dpath)$(lib)AppCore$(dlib)
ul_dlibs  += $(ul_dpath)$(lib)Ultralight$(dlib)
ul_dlibs  += $(ul_dpath)$(lib)UltralightCore$(dlib)
ul_dlibs  += $(ul_dpath)$(lib)WebCore$(dlib)
dlibs     += $(ul_dlibs)
libraries += Ultralight UltralightCore WebCore AppCore
ifeq ($(platform), win)
lib_paths += $(ul_path)lib
else
lib_paths += $(ul_path)bin
endif

# Libremidi:
definitions += LIBREMIDI_HEADER_ONLY=1
#definitions += LIBREMIDI_JACK=1
ifeq ($(platform), win)
definitions += LIBREMIDI_WINMM=1
libraries   += winmm
else
definitions += LIBREMIDI_ALSA=1
libraries   += asound
# TODO: Libraries on Linux are ignored right now.
endif

dist_dlib       = $(patsubst %,$(dist_dlib_dir)%,$(notdir $1))
dlib_from       = $(patsubst $(dist_dlib_dir)%,$($1_dpath)%,$2)
dist_dlibs_from = $(foreach f,$($1_dlibs),$(call dist_dlib,$f))
dist_dlibs      = $(foreach f,$(dlibs),$(call dist_dlib,$f))

compile_unit = $(call compile,$(compiler),$(compiler_type),$@,$<,$(inc_paths),$(definitions),$(standard),$(optimization),$(compiler_flags))

ifeq ($(compiler_type), msvc)
compose_flags = /IGNORE:4006
link_dep = $(call compose_lib,$(archiver),$@,$^,$(libraries),$(lib_paths),$(compose_flags))
else
link_dep = $(call compose_ar,$(archiver),$@,$^)
endif

clangd_cmd = $(call clangd_write,$@,$(inc_paths),$(definitions),$(standard),$(clangd_flags) $(crosscomp_flags))

.PHONY: all help clangd purge clean clean-dist clean-platform clean-platform-dependencies clean-dependencies clean-clangd

#test:
#	echo '$(dist_dlibs)'
#	echo '$(call dist_dlibs_from,ul)'

all: $(dist_dep) $(dist_entry) $(dist_dlibs)

help:
	$(info $(help_text))

clangd: $(clangd_config)

clean-platform-dependencies:
	$(call rmdir,$(dep_dir))

clean-dependencies:
	$(call rmdir,$(dep_root_dir))

clean-clangd:
	$(call rm,$(clangd_config))

clean-dist:
	$(call rm,$(dist_dep))
	$(call rm,$(dist_entry))
	$(call rmdir,$(dist_dlib_dir))

clean-platform: clean-dist
	$(call rmdir,$(obj_dir))

clean: clean-dist clean-clangd
	$(call rmdir,$(build_dir))

purge: clean clean-dependencies

$(call dist_dlibs_from,ul): %:
	$(call prepare_dir,$@)
	$(call cp,$(call dlib_from,ul,$@),$@)

$(obj_dir)entry$(obj): entry.cpp
	$(call prepare_dir,$@)
	$(compile_unit)

$(dist_dep): $(obj_files)
	$(call prepare_dir,$@)
	$(link_dep)

$(dist_entry): $(obj_dir)entry$(obj)
	$(call prepare_dir,$@)
	$(call cp,$^,$(dist_entry))

dlibs:
	$(foreach l,$(dlib_files),$(call cp,$l,$(call dist_dlib_file,$l)) && )

$(clangd_config):
	$(clangd_cmd)

-include $(dep_files)
