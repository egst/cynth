# This makefile generates the following by default:
# * ./build/dep/*: Dependency files.
#
# Actions:
# * all: Build everything.
#
# The following variables may be specified:
# * GPP: g++. GCC is needed for dependency generation.
# * DEPGEN_FLAGS: Additional dependency generation flags.

include setup.mk

gpp := $(or $(GPP),g++)

depgen_flags = $(DEPGEN_FLAGS)

obj_file   = $(if $(filter entry.cpp,$1),$(obj_dir_pi)entry$$(obj),$(1:$(src_dir)%.cpp=$(obj_dir_pi)%$$(obj)))
dep_file   = $(if $(filter entry.cpp,$1),$(dep_dir)entry.mk,$(1:$(src_dir)%.cpp=$(dep_dir)%.mk))
dep_target = $(call obj_file,$1) $(call dep_file,$1)

gen_deps = $(call depgen,$(gpp),$@,$<,$(call dep_target,$<),$(inc_paths),$(definitions),$(standard),$(depgen_flags))

.PHONY: all

all: $(dep_files)

$(dep_dir)%.mk: $(src_dir)%.cpp
	$(call prepare_dir,$@)
	$(gen_deps)

$(dep_dir)entry.mk: entry.cpp
	$(call prepare_dir,$@)
	$(gen_deps)
