include ../setup.mk

#### CONFIG ####

GEN_SRC_FILES   = $(SRC)$(IMPL_PARSER)$(EXT_IMPL) $(SRC)$(IMPL_LEXER)$(EXT_IMPL)
GEN_FILES       = $(INC)$(HEAD_PARSER)$(EXT_HEAD) $(GEN_SRC_FILES)

# Generate basic dependencies (header files change -> recompile object files):
#GEN_DEPS       = mkdir -p $(dir $@); $(GCC) $(BASIC_OPTIONS) $(DEP_OPTIONS) -MM -MT '$1 $2' -MF $@ $<
GEN_DEPS       = mkdir -p $(dir $@); $(GCC) $(BASIC_OPTIONS) $(DEP_OPTIONS) -MM -MG -MT $1 -MF $@ $<
GEN_SRC_DEPS   = $(call GEN_DEPS,$(<:$(SRC)%$(EXT_IMPL)=$(BIN_SRC)%$(EXT_OBJ)))
GEN_ENTRY_DEPS = $(call GEN_DEPS,$(<:$(ENTRY)%$(EXT_IMPL)=$(BIN_ENTRY)%$(EXT_OBJ)))

# Generate lexer:
GEN_LEXER = $(FLEX) $(LEX_OPTIONS) -o $(SRC)$(IMPL_LEXER)$(EXT_IMPL) $(GEN)lexer.l

# Generate parser:
GEN_PARSER = $(BISON) $(BISON_OPTIONS) --defines=$(INC)$(HEAD_PARSER)$(EXT_HEAD) -o $(SRC)$(IMPL_PARSER)$(EXT_IMPL) $(GEN)parser.y

#### TARGETS ####

.PHONY: all clean

.all: $(GEN_FILES)

# Removing generated parser & lexer files:
clean:
	$(call INFO,Removing generated lexer implementation file...)
	rm -f $(SRC)$(IMPL_LEXER)$(EXT_IMPL)
	$(call INFO,Removing generated parser implementation file...)
	rm -f $(SRC)$(IMPL_PARSER)$(EXT_IMPL)
	$(call INFO,Removing generated parser header file...)
	rm -f $(INC)$(HEAD_PARSER)$(EXT_HEAD)

# Generating parser files:
$(SRC)$(IMPL_PARSER)$(EXT_IMPL) $(INC)$(HEAD_PARSER)$(EXT_HEAD): $(GEN)parser.y
	$(call INFO,Generating the parser...)
	$(GEN_PARSER)
	$(call INFO,Tweaking the generated parser a bit...)
	sed -i 's/yylhs.value.emplace< cynth::syn::[^ ]* > ();/yylhs.value.emplace< int > (); \/\/ Modified./g' $(SRC)$(IMPL_PARSER)$(EXT_IMPL)
#	$(call INFO,Moving the generated parser header file to the correct location...)
#	mv $(SRC)$(IMPL_PARSER)$(EXT_HEAD) $(INC)$(HEAD_PARSER)$(EXT_HEAD)

# Generating lexer files:
$(SRC)$(IMPL_LEXER)$(EXT_IMPL): $(GEN)lexer.l
	$(call INFO,Generating the lexer...)
	$(GEN_LEXER)
