#### MODIFIABLE CONFIG ####

# C++ standard:
# (At least c++20.)
STD = c++20

# Directory names:
# (Excluding any leading and trailing slashes.)
INC   = inc
SRC   = src
DEP   = dep
BIN   = bin
DIST  = dist
GEN   = gen
TESTS = tests

# Generated files location:
# (Excluding the SRC/INC directory and the extension.)
SRC_LEXER  = lexer
SRC_PARSER = parser
INC_PARSER = parser

# File extensions:
# (Including the dot. Leave empty for extensionless files.)
EXT_SRC   = .cpp
EXT_INC   = .hpp
EXT_DEP   = .mk
EXT_OBJ   = .o
EXT_EXE   =
EXT_CYNTH = .cth

# Entry points:
# (Entry-point source files are located in SRC root (src/*.cpp) and may be toggled here.)
# (Non-entry-point source files are located in SRC at least one level deep (src/*/*.cpp etc.).)
#ENTRY_POINTS += cynth
#ENTRY_POINTS += parser
ENTRY_POINTS += test

# Compiler:
# (Tested on GCC and Clang.)
# (GCC must be installed even when cmpiling with Clang. It is used for dependencies generation.)
# (Lex and Bison must also be installed. This is not configurable.)
COMPILER = g++
#COMPILER = clang

# Additional compiler options:
# (Do not set the -std, -I and O options here.)
ADDITIONAL_OPTIONS = -Wall -static
# TODO: Try -pedantic and -ansi.

#### HELPER CONSTANTS AND FUNCTIONS ####

TO_SRC     = $(1:%=$(SRC)/%$(EXT_SRC))
SRC_TO_OBJ = $(1:$(SRC)/%$(EXT_SRC)=$(BIN)/%$(EXT_OBJ))
SRC_TO_DEP = $(1:$(SRC)/%$(EXT_SRC)=$(DEP)/%$(EXT_DEP))
SRC_TO_EXE = $(1:$(SRC)/%$(EXT_SRC)=$(DIST)/%$(EXT_EXE))
FILE_NAME  = $(basename $(notdir $1))

TPUT_RED    = $$(tput setaf 9)
TPUT_GREEN  = $$(tput setaf 2)
TPUT_YELLOW = $$(tput setaf 3)
TPUT_BLUE   = $$(tput setaf 6)
TPUT_GRAY   = $$(tput setaf 8)
TPUT_RESET  = $$(tput sgr0)

TITLE = @echo $(TPUT_BLUE)[ $1 ]$(TPUT_RESET)
SUCC  = @echo $(TPUT_GREEN)$1$(TPUT_RESET)
INFO  = @echo $(TPUT_GRAY)$1$(TPUT_RESET)
WARN  = @echo $(TPUT_YELLOW)$1$(TPUT_RESET)
ERROR = @echo $(TPUT_RED)$1$(TPUT_RESET)

#### INTERNAL CONFIG ####

# TODO: Maybe make this recursive to any depth.
SRC_FILES   = $(wildcard $(SRC)/*/*$(EXT_SRC)) $(wildcard $(SRC)/*/*/*$(EXT_SRC))
ENTRY_FILES = $(call TO_SRC,$(ENTRY_POINTS))
OBJ_FILES   = $(call SRC_TO_OBJ,$(SRC_FILES))
DEP_FILES   = $(call SRC_TO_DEP,$(SRC_FILES)) $(call SRC_TO_DEP,$(ENTRY_FILES))
EXE_FILES   = $(call SRC_TO_EXE,$(ENTRY_FILES))

# Note: The O2 optimization might be necessary to avoid problems with long mangled names of complex variant types.
BASIC_OPTIONS = -I$(INC) -std=$(STD)
ALL_OPTIONS   = $(BASIC_OPTIONS) $(ADDITIONAL_OPTIONS) -O2

# Compile:
COMPILE = mkdir -p $(dir $@); $(COMPILER) $(ALL_OPTIONS) -o $@ $<

# Link:
LINK = mkdir -p $(dir $@); $(COMPILER) -o $@ $^

# Compile object file:
COMPILE_OBJ = mkdir -p $(dir $@); $(COMPILER) $(ALL_OPTIONS) -c -o $@ $<

# Generate dependencies:
GEN_DEPS = mkdir -p $(dir $@); g++ $(BASIC_OPTIONS) -MM -MG -MT $(call SRC_TO_OBJ,$<) -MF $@ $<

# Generate lexer:
GEN_LEXER = lex

# Generate parser:
GEN_PARSER = bison -Wcounterexamples -d

#### TARGETS ####

.PHONY: clean all dep obj exe

all: dep obj exe
	$(call SUCC,Done.)

clean:
	$(call INFO,Removing executable binary files...)
	rm -rf $(DIST)
	$(call INFO,Removing intermediate binary files...)
	rm -rf $(BIN)
	$(call INFO,Removing dependency files...)
	rm -rf $(DEP)
	$(call INFO,Removing generated lexer implementation file...)
	rm -f $(SRC)/$(SRC_LEXER)$(EXT_SRC)
	$(call INFO,Removing generated parser implementation file...)
	rm -f $(SRC)/$(SRC_PARSER)$(EXT_SRC)
	$(call INFO,Removing generated parser header file...)
	rm -f $(INC)/$(INC_PARSER)$(EXT_INC)
	$(call SUCC,Done.)

dep: $(DEP_FILES)

obj: $(OBJ_FILES) $(ENTRY_FILES)

exe: $(EXE_FILES)

$(DEP)/%$(EXT_DEP): $(SRC)/%$(EXT_SRC)
	$(call INFO,Updating \"$(call FILE_NAME,$<)\" dependencies...)
	$(GEN_DEPS)

$(BIN)/%$(EXT_OBJ): $(SRC)/%$(EXT_SRC)
	$(call INFO,Compiling \"$(call FILE_NAME,$<)\" object file...)
	$(COMPILE_OBJ)

# TODO: All object files except the entry-point ones are linked together regardless of whether the corresponding header is included or not.
$(DIST)/%$(EXT_EXE): $(BIN)/%$(EXT_OBJ) $(OBJ_FILES)
	$(call INFO,Linking \"$(call FILE_NAME,$<)\" executable file...)
	$(LINK)

#### DEPENDENCIES ####

include $(DEP_FILES)
