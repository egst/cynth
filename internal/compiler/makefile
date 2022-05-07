include setup.mk

define help_text
This makefile generates the following by default:
* ./build/obj/{PLATFORM}/*: Intermediate object files.
* {ROOT}/build/{PLAFFORM}/compiler[.exe]: The final executable.
It can also generate these files on demand:
* ./build/dep/*: Dependency files.
* ./inc/parser.hpp, src/lexer.cpp, src/parser.cpp
* compile_commands.json: Clangd language server setup.

Actions:
* all: Build everything.
* generate: Generate parser and lexer.
* dependencies: Generate dependencies.
* clangd: Generate clangd config.
* clean-dependencies: Clean up dependencies.
* clean-generated: Clean up generated files. 
* clean-clangd: Clean up clangd config.
* clean-platform: Clean up only files related to the current platform.
* clean: Clean up everything but dependencies and generated source files.
* purge: Clean up everything.

The following variables may be specified:
* COMPILER (CXX): g++, clang++... Only tested on gcc and clang.
* COMPILER_TYPE: gcc, clang, msvc. The default is msvc on Windows and gcc otherwise.
* GPP: g++. GCC is needed for dependency generation. (Only during development.)
* FLEX: Flex lexer generator. (Only during development.)
* BISON: Bison parser generator. (Only during development.)
* CLANG_COMPILER: Clang C++ compiler for the clangd language server setup. Optional.
* PLATFORM: win, linux. Any other value is handled as linux.
* SRATE: Sample rate.
* INTEGRAL, FLOATING: Integral and floating point types.
* COMPILER_FLAGS (CXXFLAGS, CCFLAGS): Additional compiler flags.
* LINKER_FLAGS (LDFLAGS): Additional linkage flags.
* DEPGEN_FLAGS: Additional dependency generation flags.
* FLEX_FLAGS: Additional lexer generator flags.
* BISON_FLAGS: Additional parser generator flags.
* CLANGD_FLAGS: Additional clangd flags.
* CROSSCOMP: msys, ... No crosscompilation configuration if empty.
endef

GPP   ?= g++
FLEX  ?= flex
BISON ?= bison

gpp         = $(GPP)
flex        = $(FLEX)
bison       = $(BISON)
flex_flags  = $(FLEX_FLAGS)
bison_flags = $(BISON_FLAGS)

bison_flags += -Wcounterexamples

name          = compiler
dist_dir      = $(root)build/$(platform)/
executable    = $(dist_dir)$(name)$(exe)
parser_def    = grammar/parser.y
parser_head   = $(inc_dir)parser.hpp
parser_impl   = $(src_dir)parser.cpp
lexer_def     = grammar/lexer.l
lexer_impl    = $(src_dir)lexer.cpp
gen_files     = $(parser_head) $(parser_impl) $(lexer_impl)
obj_files     = $(src_files:$(src_dir)%.cpp=$(obj_dir)%$(obj)) $(obj_dir)entry$(obj)
clangd_config = compile_commands.json
libraries     =
lib_paths     =
optimization  = 0
#optimization  = 2

compile_unit = $(call compile,$(compiler),$(compiler_type),$@,$<,$(inc_paths),$(definitions),$(standard),$(optimization),$(compiler_flags))
link_exe     = $(call link,$(compiler),$(compiler_type),$@,$^,$(libraries),$(lib_paths),$(linker_flags))
clangd_cmd   = $(call clangd_write,$@,$(inc_paths),$(definitions),$(standard),$(clangd_flags))
gen_lexer    = $(flex) -o $(lexer_impl) $(flex_flags) $(lexer_def)
gen_parser   = $(bison) --defines=$(parser_head) -o $(parser_impl) $(bison_flags) $(parser_def)

.PHONY: all help generate clangd purge clean clean-platform clean-generated clean-dependencies clean-clangd

all: $(obj_files) $(executable)

help:
	$(info $(help_text))

generate: $(gen_files)

clangd: $(clangd_config)

clean-generated:
	$(foreach f,$(gen_files),$(call rm,$f))

clean-dependencies:
	$(call rmdir,$(dep_dir))

clean-clangd:
	$(call rm,$(clangd_config))

clean-platform:
	$(call rmdir,$(obj_dir))
	$(call rm,$(executable))

clean: clean-clangd
	$(call rmdir,$(build_dir))
	$(call rm,$(executable))

purge: clean clean-generated clean-dependencies

$(obj_dir)%$(obj): $(src_dir)%.cpp
	$(call prepare_dir,$@)
	$(compile_unit)

$(obj_dir)entry$(obj): entry.cpp
	$(call prepare_dir,$@)
	$(compile_unit)

$(executable): $(obj_files)
	$(call prepare_dir,$@)
	$(link_exe)

$(parser_head) $(parser_impl): $(parser_def)
	$(call prepare_dir,$@)
	$(gen_parser)
	# TODO: Avoid this.
	sed -i 's/yylhs.value.emplace< cynth::syn::[^ ]* > ();/yylhs.value.emplace< int > (); \/\/ Modified./g' $(parser_impl)
	#sed -i 's/yylhs.value.as< \(cynth::syn::[^ ]*\) > () = \([^;]*\);/yylhs.value.emplace< \1 > ( \2 ); \/\/ Modified./g' $(parser_impl)

$(lexer_impl): $(lexer_def)
	$(call prepare_dir,$@)
	$(gen_lexer)

$(clangd_config):
	$(clangd_cmd)

-include $(dep_files)
