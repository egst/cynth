include setup.mk

#### COMMANDS ####

# Compile an executable file:
COMPILE = mkdir -p $(dir $@); $(COMPILER) $(ALL_OPTIONS) -o $@ $^

# Compile an object file:
COMPILE_OBJ = mkdir -p $(dir $@); $(COMPILER) $(ALL_OPTIONS) -c -o $@ $<

# Link object files into an executable file:
LINK = mkdir -p $(dir $@); $(COMPILER) $(LINK_OPTIONS) -o $@ $^

#### TARGETS ####

BIN_SRC_FILES   = $(SRC_FILES:$(SRC)%$(EXT_IMPL)=$(BIN_SRC)%$(EXT_OBJ))
BIN_ENTRY_FILES = $(ENTRY_FILES:$(ENTRY)%$(EXT_IMPL)=$(BIN_ENTRY)%$(EXT_OBJ))
BIN_DIST_FILES  = $(ENTRY_FILES:$(ENTRY)%$(EXT_IMPL)=$(BIN_DIST)%$(EXT_EXE))

.PHONY: all clean test clean-dist clean-bin clean-dep clean-gen test

all: $(BIN_SRC_FILES) $(BIN_ENTRY_FILES) $(BIN_DIST_FILES)

compile: $(BIN_SRC_FILES) $(BIN_ENTRY_FILES)

link: $(BIN_DIST_FILES)

clean: clean-dist clean-bin clean-tests

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

# Removing test output files:
clean-tests:
	$(call INFO,Removing intermediate C test files...)
	rm -rf $(TESTS_C)
	$(call INFO,Removing debugging test executables...)
	rm -rf $(TESTS_DEBUG)
	$(call INFO,Removing complete test executables...)
	rm -rf $(TESTS_COMPL)

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
$(BIN_DIST)%$(EXT_EXE): $(BIN_ENTRY)%$(EXT_OBJ) $(BIN_SRC_FILES)
#$(BIN_DIST)%$(EXT_EXE): $(BIN_ENTRY)%$(EXT_OBJ)
	$(call INFO,Linking \"$(call FILE_NAME,$<)\" executable file...)
	$(LINK)

# Dependencies of generated files:
$(SRC)$(IMPL_PARSER): $(INC)$(HEAD_PARSER)$(EXT_HEAD)
$(SRC)$(IMPL_LEXER):  $(INC)$(HEAD_PARSER)$(EXT_HEAD)

# C synth code:
$(TEST_C)%.c: $(TEST_IN)%$(EXT_CYNTH) $(BIN_DIST)compiler
	mkdir -p $(dir $@)
	touch $@
	cat $< | $(BIN_DIST)compiler > $@

# A standalone debug synth program:
$(TEST_DEBUG)%$(EXT_EXE): $(TEST_C)%.c
	mkdir -p $(dir $@)
	touch $@
	cat $< | $(GCC) $(CYNTH_OPTIONS) -std=$(CYNTH_STD) -o $@ -xc - -lm

# TODO: Complete executable synth program.

#### DEPENDENCIES ####

-include $(DEP_SRC_FILES) $(DEP_ENTRY_FILES)
