#### MODIFIABLE CONFIG ####

# C++ standard:
# (At least c++20.)
STD = c++20

# Directory names:
# (Including the trailing slash. Leave empty for the project root directory. Add leading slash for absolute paths.)
INC       = inc/
SRC       = src/
DEP_SRC   = dep/src/
DEP_ENTRY = dep/
BIN_SRC   = obj/src/
BIN_ENTRY = obj/
BIN_DIST  = dist/
GEN       = gen/
TESTS     = tests/
ENTRY     = entry/
#ENTRY    =

# Generated files location:
# (Excluding the SRC/INC directory and the EXT_IMPL/EXT_HEAD extension.)
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
ENTRY_POINTS += interpreter
#ENTRY_POINTS += test

# Compiler:
# (Tested on GCC and Clang.)
#COMPILER = g++
COMPILER = clang++

# GCC (g++), Flex and Bison executable names/locations:
# (GCC must be installed even when compiling with Clang. It is used for dependencies generation.)
GCC   = g++
FLEX  = flex
BISON = bison

# Additional compiler options:
# (Do not set the -std, -I and -O options here.)
ADDITIONAL_OPTIONS  = -static -Wall -Wextra -Wno-missing-braces -pedantic -fdiagnostics-color=always
ADDITIONAL_OPTIONS += -ftemplate-backtrace-limit=0
#ADDITIONAL_OPTIONS += -fsanitize=undefined
ADDITIONAL_OPTIONS += -fvisibility-inlines-hidden

# More additional options:
# * linkage (with the chosen compiler)
# * dependency generation (with GCC)
# * flex lexer
# * bison parser
LINK_OPTIONS   = -fdiagnostics-color=always
#LINK_OPTIONS  += -fsanitize=undefined
LINK_OPTIONS  += -fvisibility-inlines-hidden
DEP_OPTIONS    =
FLEX_OPTIONS   =
BISON_OPTIONS  = -Wcounterexamples

#### HELPER FUNCTIONS ####

FILE_NAME = $(basename $(notdir $1))

TITLE = @echo $(TPUT_BLUE)$1$(TPUT_RESET)
SUCC  = @echo $(TPUT_GREEN)$1$(TPUT_RESET)
INFO  = @echo $(TPUT_GRAY)$1$(TPUT_RESET)
WARN  = @echo $(TPUT_YELLOW)$1$(TPUT_RESET)
ERROR = @echo $(TPUT_RED)$1$(TPUT_RESET)

#### INTERNAL CONFIG ####

TPUT_RED    = $$(tput setaf 9)
TPUT_GREEN  = $$(tput setaf 2)
TPUT_YELLOW = $$(tput setaf 3)
TPUT_BLUE   = $$(tput setaf 6)
TPUT_GRAY   = $$(tput setaf 8)
TPUT_RESET  = $$(tput sgr0)

GEN_SRC_FILES   = $(SRC)$(IMPL_PARSER)$(EXT_IMPL) $(SRC)$(IMPL_LEXER)$(EXT_IMPL)
GEN_FILES       = $(INC)$(HEAD_PARSER)$(EXT_HEAD) $(GEN_SRC_FILES)
# TODO: Maybe make this recursive to any depth.
SRC_FILES       = $(wildcard $(SRC)*$(EXT_IMPL))
SRC_FILES      += $(wildcard $(SRC)*/*$(EXT_IMPL))
SRC_FILES      += $(wildcard $(SRC)*/*/*$(EXT_IMPL))
SRC_FILES      += $(wildcard $(SRC)*/*/*/*$(EXT_IMPL))
SRC_FILES      += $(GEN_SRC_FILES)
ENTRY_FILES     = $(ENTRY_POINTS:%=$(ENTRY)%$(EXT_IMPL))
BIN_SRC_FILES   = $(SRC_FILES:$(SRC)%$(EXT_IMPL)=$(BIN_SRC)%$(EXT_OBJ))
BIN_ENTRY_FILES = $(ENTRY_FILES:$(ENTRY)%$(EXT_IMPL)=$(BIN_ENTRY)%$(EXT_OBJ))
DEP_SRC_FILES   = $(SRC_FILES:$(SRC)%$(EXT_IMPL)=$(DEP_SRC)%$(EXT_DEP))
DEP_ENTRY_FILES = $(ENTRY_FILES:$(ENTRY)%$(EXT_IMPL)=$(DEP_ENTRY)%$(EXT_DEP))
BIN_DIST_FILES  = $(ENTRY_FILES:$(ENTRY)%$(EXT_IMPL)=$(BIN_DIST)%$(EXT_EXE))

# Note: The O2 optimization might be necessary to avoid problems with long mangled names of complex variant types.
BASIC_OPTIONS = -I$(INC) -std=$(STD)
OPTIMIZATIONS = -O2
ALL_OPTIONS   = $(BASIC_OPTIONS) $(ADDITIONAL_OPTIONS) $(OPTIMIZATIONS)

# Compile an executable file:
COMPILE = mkdir -p $(dir $@); $(COMPILER) $(ALL_OPTIONS) -o $@ $^

# Compile an object file:
COMPILE_OBJ = mkdir -p $(dir $@); $(COMPILER) $(ALL_OPTIONS) -c -o $@ $<

# Link object files into an executable file:
LINK = mkdir -p $(dir $@); $(COMPILER) $(LINK_OPTIONS) -o $@ $^

# Generate dependencies:
#GEN_DEPS       = mkdir -p $(dir $@); $(GCC) $(BASIC_OPTIONS) $(DEP_OPTIONS) -MM -MG -MT $1 -MF $@ $<
GEN_DEPS       = mkdir -p $(dir $@); $(GCC) $(BASIC_OPTIONS) $(DEP_OPTIONS) -MM -MT $1 -MF $@ $<
GEN_SRC_DEPS   = $(call GEN_DEPS,$(<:$(SRC)%$(EXT_IMPL)=$(BIN_SRC)%$(EXT_OBJ)))
GEN_ENTRY_DEPS = $(call GEN_DEPS,$(<:$(ENTRY)%$(EXT_IMPL)=$(BIN_ENTRY)%$(EXT_OBJ)))

# Generate lexer:
GEN_LEXER = $(FLEX) $(LEX_OPTIONS) -o $(SRC)$(IMPL_LEXER)$(EXT_IMPL) $(GEN)lexer.l

# Generate parser:
GEN_PARSER = $(BISON) $(BISON_OPTIONS) --defines=$(INC)$(HEAD_PARSER)$(EXT_HEAD) -o $(SRC)$(IMPL_PARSER)$(EXT_IMPL) $(GEN)parser.y

#### TARGETS ####

.PHONY: all clean clean-dist clean-bin clean-dep clean-gen

all: $(GEN_FILES) $(DEP_SRC_FILES) $(DEP_ENTRY_FILES) $(BIN_SRC_FILES) $(BIN_ENTRY_FILES) $(BIN_DIST_FILES)

clean: clean-dist clean-bin clean-dep clean-gen

# Generating lexer files:
$(SRC)$(IMPL_LEXER)$(EXT_IMPL): $(GEN)lexer.l
	$(call INFO,Generating the lexer...)
	$(GEN_LEXER)

# Generating parser files:
$(SRC)$(IMPL_PARSER)$(EXT_IMPL) $(INC)$(HEAD_PARSER)$(EXT_HEAD): $(GEN)parser.y
	$(call INFO,Generating the parser...)
	$(GEN_PARSER)
	$(call INFO,Tweaking the generated parser a bit...)
	sed -i 's/yylhs.value.emplace< cynth::ast::[^ ]* > ();/yylhs.value.emplace< int > (); \/\/ Modified./g' $(SRC)$(IMPL_PARSER)$(EXT_IMPL)
#	$(call INFO,Moving the generater parser header file to the correct location...)
#	mv $(SRC)$(IMPL_PARSER)$(EXT_HEAD) $(INC)$(HEAD_PARSER)$(EXT_HEAD)

# Source files dependencies:
$(DEP_SRC)%$(EXT_DEP): $(SRC)%$(EXT_IMPL)
	$(call INFO,Updating \"$(call FILE_NAME,$<)\" source dependencies...)
	$(GEN_SRC_DEPS)

# Entry-point files dependencies:
$(DEP_ENTRY)%$(EXT_DEP): $(ENTRY)%$(EXT_IMPL)
	$(call INFO,Updating \"$(call FILE_NAME,$<)\" entry dependencies...)
	$(GEN_ENTRY_DEPS)

# Compiling source files:
$(BIN_SRC)%$(EXT_OBJ): $(SRC)%$(EXT_IMPL)
	$(call INFO,Compiling \"$(call FILE_NAME,$<)\" source object file...)
	$(COMPILE_OBJ)

# Compiling entry-point files:
$(BIN_ENTRY)%$(EXT_OBJ): $(ENTRY)%$(EXT_IMPL)
	$(call INFO,Compiling \"$(call FILE_NAME,$<)\" entry object file...)
	$(COMPILE_OBJ)

# TODO: All source object files are linked together regardless of whether the corresponding header is included or not.
# Linking executable files:
$(BIN_DIST)%$(EXT_EXE): $(BIN_ENTRY)%$(EXT_OBJ) $(BIN_SRC_FILES)
	$(call INFO,Linking \"$(call FILE_NAME,$<)\" executable file...)
	$(LINK)

# Removing executable files:
clean-dist:
	$(call INFO,Removing executable binary files...)
	rm -rf $(BIN_DIST)

# Removing object files:
clean-bin:
	$(call INFO,Removing intermediate binary source files...)
	rm -rf $(BIN_SRC)
	$(call INFO,Removing intermediate binary entry files...)
	rm -rf $(BIN_ENTRY)

# Removing dependency files:
clean-dep:
	$(call INFO,Removing source dependency files...)
	rm -rf $(DEP_SRC)
	$(call INFO,Removing entry dependency files...)
	rm -rf $(DEP_ENTRY)

# Removing generated parser & lexer files:
clean-gen:
	$(call INFO,Removing generated lexer implementation file...)
	rm -f $(SRC)$(IMPL_LEXER)$(EXT_IMPL)
	$(call INFO,Removing generated parser implementation file...)
	rm -f $(SRC)$(IMPL_PARSER)$(EXT_IMPL)
	$(call INFO,Removing generated parser header file...)
	rm -f $(INC)$(HEAD_PARSER)$(EXT_HEAD)

# Dependencies of generated files:
$(SRC)$(IMPL_PARSER): $(INC)$(HEAD_PARSER)$(EXT_HEAD)
$(SRC)$(IMPL_LEXER):  $(INC)$(HEAD_PARSER)$(EXT_HEAD)

#### DEPENDENCIES ####

include $(DEP_SRC_FILES) $(DEP_ENTRY_FILES)
