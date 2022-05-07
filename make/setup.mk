define newline


endef

empty =
space = $(empty) $(empty)

lines = $(subst ${newline},\n,$1)

lc = $(subst A,a,$(subst B,b,$(subst C,c,$(subst D,d,$(subst E,e,$(subst F,f,$(subst G,g,$(subst H,h,$(subst I,i,$(subst J,j,$(subst K,k,$(subst L,l,$(subst M,m,$(subst N,n,$(subst O,o,$(subst P,p,$(subst Q,q,$(subst R,r,$(subst S,s,$(subst T,t,$(subst U,u,$(subst V,v,$(subst W,w,$(subst X,x,$(subst Y,y,$(subst Z,z,$1))))))))))))))))))))))))))
uc = $(subst a,A,$(subst b,B,$(subst c,C,$(subst d,D,$(subst e,E,$(subst f,F,$(subst g,G,$(subst h,H,$(subst i,I,$(subst j,J,$(subst k,K,$(subst l,L,$(subst m,M,$(subst n,N,$(subst o,O,$(subst p,P,$(subst q,Q,$(subst r,R,$(subst s,S,$(subst t,T,$(subst u,U,$(subst v,V,$(subst w,W,$(subst x,X,$(subst y,Y,$(subst z,Z,$1))))))))))))))))))))))))))

file_name = $(basename $(notdir $1))

dir_path = $(patsubst %,%/,$(patsubst %/,%,$1))

prepare_dir = $(call mkdir,$(dir $1))

# Note: Currently, only Windows and Linux is supported.
# All operating systems other than Windows are assumed to be Linux.
ifeq ($(OS), Windows_NT)
os = win
else
os = linux
endif

ifeq ($(os), win)
default_compiler_type = msvc
default_archiver_type = lib
default_c_compiler    = cl
default_cpp_compiler  = cl
default_archiver      = lib
default_prefix        =
else
default_compiler_type = gcc
default_archiver_type = ar
default_c_compiler    = $(CC)
default_cpp_compiler  = $(CXX)
default_archiver      = $(AR)
default_prefix        = /usr/local/
endif

default_crosscomp_target = x86_64-w64-mingw32 -fms-extensions
default_msys_path        = /mnt/c/msys64/

platform         = $(or $(PLATFORM),$(os))
prefix           = $(or $(PREFIX),$(default_prefix))
compiler         = $(or $(COMPILER),$(default_cpp_compiler))
compiler_type    = $(or $(COMPILER_TYPE),$(default_compiler_type))
archiver         = $(or $(ARCHIVER),$(default_archiver))
archiver_type    = $(or $(ARCHIVER_TYPE),$(default_archiver_type))
compiler_flags   = $(or $(COMPILER_FLAGS),$(CXXFLAGS),$(CCFLAGS))
archiver_flags   = $(or $(ARCHIVER_FLAGS),$(ARFLAGS))
linker_flags     = $(or $(LINKER_FLAGS),$(LDFLAGS))
warnings         = $(or $(WARNINGS),minimal)
clang_compiler   = $(or $(CLANG_COMPILER),clang++)
crosscomp_target = $(or $(CROSSCOMP_TARGET),$(default_crosscomp_target))
crosscomp        = $(or $(CROSSCOMP),)
msys             = $(or $(MSYS),$(default_msys_path))

platform         := $(call lc,$(platform))
prefix           := $(call dir_path,$(prefix))
compiler_type    := $(call lc,$(compiler_type))
archiver_type    := $(call lc,$(archiver_type))
warnings         := $(call lc,$(warnings))
crosscomp_target := $(call lc,$(crosscomp_target))

ifeq ($(crosscomp), msys)
crosscomp_flags += -target $(crosscomp_target)
crosscomp_flags += -I$(msys)mingw64/include/c++/10.1.0
crosscomp_flags += -I$(msys)mingw64/include/c++/10.1.0/backward
crosscomp_flags += -I$(msys)mingw64/include/c++/10.1.0/x86_64-w64-mingw32
crosscomp_flags += -I$(msys)mingw64/x86_64-w64-mingw32/include
crosscomp_flags += -I$(msys)mingw64/lib/clang/10.0.0/include
endif

ifeq ($(os), win)
spath       = $(subst /,\,$1)
mkdir       = if not exist $(call spath,$1) mkdir $(call spath,$1)
rm          = if exist $(call spath,$1) del /q $(call spath,$1)
rmdir       = if exist $(call spath,$1) rd /q /s $(call spath,$1)
cat         = type $(call spath,$1)
cp          = copy /Y $(call spath,$1) $(call spath,$2)
cpdir       = xcopy /Y /E /I $(call spath,$1) $(call spath,$2)
encoding    = chcp 65001 &&
thread_lib  =
tput_red    =
tput_green  =
tput_yellow =
tput_blue   =
tput_gray   =
tput_reset  =
exe         = .exe
else
spath       = $1
mkdir       = mkdir -p $1
rm          = rm -f $1
rmdir       = rm -rf $1
cat         = cat $1
cp          = cp $1 $2
cpdir       = cp -r -T $1 $2
encoding    =
thread_lib  = -lpthread
tput_red    = $$(tput setaf 9)
tput_green  = $$(tput setaf 2)
tput_yellow = $$(tput setaf 3)
tput_blue   = $$(tput setaf 6)
tput_gray   = $$(tput setaf 8)
tput_reset  = $$(tput sgr0)
exe         =
endif

ifeq ($(compiler_type), msvc)
obj  = .obj
dlib = .dll
slib = .lib
lib  =
else
obj  = .o
dlib = .so
slib = .a
lib  = lib
endif

title = @echo $(tput_blue)$1$(tput_reset)
succ  = @echo $(tput_green)$1$(tput_reset)
info  = @echo $(tput_gray)$1$(tput_reset)
warn  = @echo $(tput_yellow)$1$(tput_reset)
error = @echo $(tput_red)$1$(tput_reset)

msvc_optim0  = /Od
msvc_optim1  = /O1
msvc_optim2  = /O2
msvc_optim3  = /O2
msvc_more    = /Zc:__cplusplus /bigobj /EHsc
ifeq ($(warnings), all)
msvc_warn    = /Wall
endif

other_optim0 = -O0
other_optim1 = -O1
other_optim2 = -O2
other_optim3 = -O3
other_more   =
ifeq ($(warnings), all)
other_warn   = -Wall -Wextra -pedantic
endif

ifeq ($(compiler_type), msvc)
compiler_flags += $(msvc_warn)
#linker_flags   += /wd4006
#compiler_flags += /wd{x} ...
else
compiler_flags += $(other_warn)
compiler_flags += -Wno-missing-braces
#compiler_flags += /wno-{x} ...
compiler_flags += -fdiagnostics-color=always
compiler_flags += -ftemplate-backtrace-limit=1
compiler_flags += -fvisibility-inlines-hidden
#compiler_flags += -fconcepts-diagnostics-depth=2
#compiler_flags += -fvisibility-inlines-hidden
endif

opt_std          = $(if $(filter msvc,$1),/std:$2,-std=$2)
opt_compile      = $(if $(filter msvc,$1),/c,-c)
opt_out          = $(if $(filter msvc,$1),/Fo$(call spath,$2),-o $2)
opt_include      = $(if $(filter msvc,$1),/I$(call spath,$2),-I$2)
opt_define       = $(if $(filter msvc,$1),/D$2,-D$2)
opt_optim        = $(if $(filter msvc,$1),$(msvc_optim$(2)),$(other_optim$(2)))
opt_pthread      = $(if $(filter msvc,$1),,-pthread)
opt_more         = $(if $(filter msvc,$1),$(msvc_more),$(other_more))
opt_link_pass    = $(if $(filter msvc,$1),/link,)
opt_link_out     = $(if $(filter msvc,$1),/OUT:$(call spath,$2),-o $2)
opt_link_library = $(if $(filter msvc,$1),$2.lib,-l$2)
opt_link_libpath = $(if $(filter msvc,$1),/LIBPATH:$(call spath,$2),-L$2)
#opt_link_pthread = $(if $(filter gcc,$1),-pthread,)
opt_link_pthread =
opt_link_dynamic = $(if $(filter msvc,$1),/DLL,-dynamic)

opt_link_rpath = -Wl,-rpath,$1
#opt_link_rpath = -Wl,-rpath=$1
opt_link_rpath_origin = $(call opt_link_rpath,'$$ORIGIN')

# args: program, type, output, input, include paths, definitions, standard, optimizations, other flags
compile = $(call spath,$1) $\
	$(call opt_compile,$2) $\
	$(call opt_more,$2) $\
	$(call opt_out,$2,$3) $\
	$(call opt_pthread,$2) $\
	$(call opt_std,$2,$7) $\
	$(call opt_optim,$2,$8) $\
	$(foreach o,$5,$(call opt_include,$2,$o)) $\
	$(foreach o,$6,$(call opt_define,$2,$o)) $\
	$(call spath,$4) $\
	$9

# args: program, type, output, input, libraries, library paths, other flags
link = $(call spath,$1) $\
	$(call spath,$4) $\
	$(foreach o,$5,$(call opt_link_library,$2,$o)) $\
	$(call opt_link_pass,$2) $\
	$(foreach o,$6,$(call opt_link_libpath,$2,$o)) $\
	$(call opt_link_pthread,$2) $\
	$(call opt_link_out,$2,$3) $\
	$7

# args: program, type, output, input, libraries, library paths, other flags
dynlink = $(call link,$1,$2,$3,$4,$5,$6,$7 $(call opt_link_dynamic,$2))

# args: program (lib), output, input, libraries, library paths, other flags
compose_lib = $(if $3$4,$(call spath,$1) /OUT:$(call spath,$2) $(4:%=%.lib) $(foreach o,$(call spath,$5),$(o:%=/LIBPATH:%)) $(call spath,$3) $6,)

# args: program (ar), output, input
compose_ar = $(if $3,$(call spath,$1) crs $2 $3,)

# args: program (gcc), output, input, target, include paths, definitions, standard, other flags
depgen = $(call spath,$1) -std=$7 $(5:%=-I%) $(6:%=-D%) $8 -MM -MT '$4' -MF $(call spath,$2) $(call spath,$3)

children = $(wildcard $1*$2)

nested = $\
	$(wildcard $1*$2) $\
	$(wildcard $1*/*$2) $\
	$(wildcard $1*/*/*$2) $\
	$(wildcard $1*/*/*/*$2) $\
	$(wildcard $1*/*/*/*/*$2) $\
	$(wildcard $1*/*/*/*/*/*$2) $\
	$(wildcard $1*/*/*/*/*/*/*$2) $\
	$(wildcard $1*/*/*/*/*/*/*/*$2)

define clangd_config_entry
{
        \"directory\": \"$(shell pwd)\",
        \"file\":      \"$1\",
        \"command\":   \"$2\"
    },
endef

define clangd_config_entries
[
    $(foreach e,$1,$(call clangd_config_entry,$e,$2))
]
endef

clangd_compile = $(call spath,$(clang_compiler)) -std=$(3) $(1:%=-I%) $(2:%=-D%) $4

# args: output, include paths, definitions, standard, other flags
clangd_write = $(encoding) echo "$(call lines,$(call clangd_config_entries,_,$(call clangd_compile,$2,$3,$4,$5)))" > $(call spath,$1)
