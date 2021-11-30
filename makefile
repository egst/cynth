#### USER CONFIG ####

include config.mk

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

# Generate basic dependencies (header files change -> recompile object files):
#GEN_DEPS             = mkdir -p $(dir $@); $(GCC) $(BASIC_OPTIONS) $(DEP_OPTIONS) -MM -MG -MT $1 -MF $@ $<
GEN_DEPS             = mkdir -p $(dir $@); $(GCC) $(BASIC_OPTIONS) $(DEP_OPTIONS) -MM -MT '$1 $2' -MF $@ $<
GEN_SRC_DEPS         = $(call GEN_DEPS,$(<:$(SRC)%$(EXT_IMPL)=$(BIN_SRC)%$(EXT_OBJ)),$(<:$(SRC)%$(EXT_IMPL)=$(DEP_SRC)%$(EXT_DEP)))
GEN_ENTRY_DEPS       = $(call GEN_DEPS,$(<:$(ENTRY)%$(EXT_IMPL)=$(BIN_ENTRY)%$(EXT_OBJ)),$(<:$(ENTRY)%$(EXT_IMPL)=$(DEP_ENTRY)%$(EXT_DEP)))

# Generate indirect dependencies (header files change -> update depencencies again):
# Note: Not used anymore. Instead, the .mk file is added as a second dependant in the gcc comand directly.
GEN_INDIR_DEPS       = cat $@ | sed 's/$(subst /,\/,$1)/$(subst /,\/,$@)/' >> $@
GEN_INDIR_SRC_DEPS   = $(call GEN_INDIR_DEPS,$(@:$(DEP_SRC)%$(EXT_DEP)=$(BIN_SRC)%$(EXT_OBJ)))
GEN_INDIR_ENTRY_DEPS = $(call GEN_INDIR_DEPS,$(@:$(DEP_ENTRY)%$(EXT_DEP)=$(BIN_ENTRY)%$(EXT_OBJ)))

# Generate linkage dependencies (object files change -> relink executable files):
# Note: This could be very useful, but I can't come up with a solution that wouldn't involve some sort of manual
# dependency graph search. So for now all the .cpp files are linked together for every entry point.
define IMPL_DEPS
comm -12 <( \
    echo "$(SRC_FILES)" | tr ' ' '\n' | sed '/^$$/d' | sort \
) <( \
    cat dep/test.mk | tr ' ' '\n' | sort | uniq | grep '$(EXT_HEAD)$$' | sed 's/\$(EXT_HEAD)$$/\$(EXT_IMPL)/' | sed 's/^inc/src/' | sort \
)
endef
define GEN_LINK_DEPS
echo $$'$(@:$(DEP_ENTRY)%$(EXT_DEP)=$(BIN_DIST)%$(EXT_EXE)):\n$(@:$(DEP_ENTRY)%$(EXT_DEP)=$(BIN_ENTRY)%$(EXT_OBJ))\n'"$$( \
    $(IMPL_DEPS) \
)" | sed 's/\$(EXT_IMPL)$$/\$(EXT_OBJ)/' | sed 's/^$(subst /,\/,$(SRC))/$(subst /,\/,$(BIN_SRC))/' | \
tr '\n' ' ' | fold -s -w80 | sed '$$!s/$$/\\/' | sed '2,$$s/^/ /' | sed 's/ $$//' >> $@
endef
define DEEPER_DEPS
echo "$$($(IMPL_DEPS))" | sed 's/\$(EXT_IMPL)$$/\$(EXT_DEP)/' | sed 's/^$(subst /,\/,$(SRC))/$(subst /,\/,$(DEP_SRC))/' | \
xargs -I{} -d'\n' cat {}
endef

# Generate lexer:
GEN_LEXER = $(FLEX) $(LEX_OPTIONS) -o $(SRC)$(IMPL_LEXER)$(EXT_IMPL) $(GEN)lexer.l

# Generate parser:
GEN_PARSER = $(BISON) $(BISON_OPTIONS) --defines=$(INC)$(HEAD_PARSER)$(EXT_HEAD) -o $(SRC)$(IMPL_PARSER)$(EXT_IMPL) $(GEN)parser.y

#### TARGETS ####

.PHONY: all clean test clean-dist clean-bin clean-dep clean-gen

all: $(GEN_FILES) $(DEP_SRC_FILES) $(DEP_ENTRY_FILES) $(BIN_SRC_FILES) $(BIN_ENTRY_FILES) $(BIN_DIST_FILES)

clean: clean-dist clean-bin clean-dep
#clean-gen

test:
	$(DEEPER_DEPS)

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
#	$(call INFO,Moving the generated parser header file to the correct location...)
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

# TODO: Remove the `$(SRC_FILES)` once I figure out a way to filter out the implementation dependencies.
# Linking executable files:
#$(BIN_DIST)%$(EXT_EXE): $(BIN_ENTRY)%$(EXT_OBJ) $(BIN_SRC_FILES)
$(BIN_DIST)%$(EXT_EXE): $(BIN_ENTRY)%$(EXT_OBJ)
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

#include $(DEP_SRC_FILES) $(DEP_ENTRY_FILES)
