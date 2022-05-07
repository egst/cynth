root = ../../

include $(root)make/setup.mk

default_sample_rate   = 44.1
default_integral_type = int
default_floating_type = float

srate    = $(or $(SRATE),$(default_sample_rate))
integral = $(or $(INTEGRAL),$(default_integral_type))
floating = $(or $(FLOATING),$(default_floating_type))

inc_dir      = inc/
src_dir      = src/
dep_dir      = dep/
build_dir    = build/
obj_dir      = $(build_dir)obj/$(platform)/
obj_dir_pi   = $(build_dir)obj/$$(platform)/
src_files    = $(call nested,$(src_dir),.cpp)
dep_files    = $(src_files:$(src_dir)%.cpp=$(dep_dir)%.mk) $(dep_dir)entry.mk
inc_paths    = $(inc_dir)
standard     = c++20
definitions  = CTH_SRATE=$(srate)
definitions += CTH_INTEGRAL=$(integral)
definitions += CTH_FLOATING=$(floating)

# ESL:
inc_paths += $(root)internal/esl/inc/
