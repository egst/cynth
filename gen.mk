include setup.mk

#### CONFIG ####

GEN_SRC_FILES   = $(SRC)$(IMPL_PARSER)$(EXT_IMPL) $(SRC)$(IMPL_LEXER)$(EXT_IMPL)
GEN_FILES       = $(INC)$(HEAD_PARSER)$(EXT_HEAD) $(GEN_SRC_FILES)

#### COMMANDS ####

GEN_LEXER  = $(FLEX) $(LEX_OPTIONS) -o $(SRC)$(IMPL_LEXER)$(EXT_IMPL) $(GEN)lexer.l
GEN_PARSER = $(BISON) $(BISON_OPTIONS) --defines=$(INC)$(HEAD_PARSER)$(EXT_HEAD) -o $(SRC)$(IMPL_PARSER)$(EXT_IMPL) $(GEN)parser.y

#### TARGETS ####

.PHONY: all clean

all: $(GEN_FILES)

# Removing generated parser & lexer files:
clean:
	$(call INFO,Removing generated lexer implementation file...)
	$(call RM,$(SRC)$(IMPL_LEXER)$(EXT_IMPL))
	$(call INFO,Removing generated parser implementation file...)
	$(call RM,$(SRC)$(IMPL_PARSER)$(EXT_IMPL))
	$(call INFO,Removing generated parser header file...)
	$(call RM,$(INC)$(HEAD_PARSER)$(EXT_HEAD))

# Generating parser files:
$(SRC)$(IMPL_PARSER)$(EXT_IMPL) $(INC)$(HEAD_PARSER)$(EXT_HEAD): $(GEN)parser.y
	$(call INFO,Generating the parser...)
	$(GEN_PARSER)
	$(call INFO,Tweaking the generated parser a bit...)
	sed -i 's/yylhs.value.emplace< cynth::syn::[^ ]* > ();/yylhs.value.emplace< int > (); \/\/ Modified./g' $(SRC)$(IMPL_PARSER)$(EXT_IMPL)
	# TODO:
	#sed -i 's/yylhs.value.as< \(cynth::syn::[^ ]*\) > () = \([^;]*\);/yylhs.value.emplace< \1 > ( \2 ); \/\/ Modified./g' $(SRC)$(IMPL_PARSER)$(EXT_IMPL)

# Generating lexer files:
$(SRC)$(IMPL_LEXER)$(EXT_IMPL): $(GEN)lexer.l
	$(call INFO,Generating the lexer...)
	$(GEN_LEXER)
