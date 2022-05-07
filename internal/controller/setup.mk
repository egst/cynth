root = ../../

include $(root)make/setup.mk

default_driver        = $(if $(filter win,$(platform)),asio,stdout)
default_sample_rate   = 44.1
default_integral_type = int
default_floating_type = float

driver   = $(or $(DRIVER),$(default_driver))
srate    = $(or $(SRATE),$(default_sample_rate))
integral = $(or $(INTEGRAL),$(default_integral_type))
floating = $(or $(FLOATING),$(default_floating_type))

driver := $(call lc,$(driver))

inc_dir      = inc/
src_dir      = src/
dep_root_dir = dep/
dep_dir      = $(dep_root_dir)$(platform)/$(driver)/
build_dir    = build/
obj_dir      = $(build_dir)obj/$(platform)/$(driver)/
src_files    = $(call nested,$(src_dir),.cpp)
dep_files    = $(src_files:$(src_dir)%.cpp=$(dep_dir)%.mk) $(dep_dir)entry.mk
standard     = c++20
inc_paths    = $(inc_dir)
definitions  = CTH_SRATE=$(srate)
definitions += CTH_INTEGRAL=$(integral)
definitions += CTH_FLOATING=$(floating)
definitions += CTH_PLATFORM=CTH_PLATFORM_$(call uc,$(platform))
definitions += CTH_DRIVER_API=CTH_DRIVER_API_$(call uc,$(driver))

# ESL:
inc_paths += $(root)internal/esl/inc/

# Computer:
inc_paths += $(root)internal/computer/inc/

# ASIO:
inc_paths += $(root)external/asio/common/
inc_paths += $(root)external/asio/host/
inc_paths += $(root)external/asio/host/pc/

# Rapid YAML:
inc_paths += $(root)external/rapidyaml/

# Ultralight:
inc_paths += $(root)external/ultralight/$(platform)/include/
