include setup.mk

#### TARGETS ####

.PHONY: all clean test clean-dist clean-bin clean-dep clean-gen

all: $(BIN_SRC_FILES) $(BIN_ENTRY_FILES) $(BIN_DIST_FILES)

deps: $(DEP_SRC_FILES) $(DEP_ENTRY_FILES)

compile: $(BIN_SRC_FILES) $(BIN_ENTRY_FILES)

link: $(BIN_DIST_FILES)

clean: clean-dist clean-bin

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

#### DEPENDENCIES ####

include $(DEP_SRC_FILES) $(DEP_ENTRY_FILES)
