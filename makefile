include setup.mk

#### CONFIG ####

BIN_SRC_FILES   = $(SRC_FILES:$(SRC)%$(EXT_IMPL)=$(BIN_SRC)%$(EXT_OBJ))
BIN_ENTRY_FILES = $(ENTRY_FILES:$(ENTRY)%$(EXT_IMPL)=$(BIN_ENTRY)%$(EXT_OBJ))
BIN_DIST_FILES  = $(ENTRY_FILES:$(ENTRY)%$(EXT_IMPL)=$(BIN_DIST)%$(EXT_EXE))

#### COMMANDS ####

COMPILE = $(COMPILER) -c -o $(call SPATH,$@) $(COMP_OPTIONS) $(call SPATH,$<)
COMPILE = $(COMPILER) -c -o $(call SPATH,$@) $(COMP_OPTIONS) $(call SPATH,$<)
LINK    = $(COMPILER) $(LINK_OPTIONS) -o $(call SPATH,$@) $(call SPATH,$^)

COMPILE_SYNTH_DEBUG = $(GCC) $(CYNTH_COMP_OPTIONS) -o $(call SPATH,$@) $(call SPATH,$<) $(CYNTH_LIB)
COMPILE_SYNTH_STAT  = $(GCC) $(CYNTH_COMP_OPTIONS) -c -o $(call SPATH,$@) $(call SPATH,$<)
COMPILE_SYNTH_COMPL = $(GPP) $(COMP_OPTIONS) -o $(call SPATH,$@) $(call SPATH,$<) $(call SPATH,$(ENTRY)control$(EXT_IMPL)) $(CYNTH_LIB)

#### TARGETS ####

.PHONY: all clean test clean-dist clean-bin clean-dep clean-gen clean-flags test

all: $(BIN_SRC_FILES) $(BIN_ENTRY_FILES) $(BIN_DIST_FILES) $(EXTERN_OBJ)

compile: $(BIN_SRC_FILES) $(BIN_ENTRY_FILES)

link: $(BIN_DIST_FILES)

clean: clean-dist clean-bin clean-tests clean-clangd

test:

# Removing executable files:
clean-dist:
	$(call INFO,Removing executable binary files...)
	$(call RMDIR,$(BIN_DIST))

# Removing object files:
clean-bin:
	$(call INFO,Removing intermediate binary source files...)
	$(call RMDIR,$(BIN_SRC))
	$(call INFO,Removing intermediate binary entry files...)
	$(call RMDIR,$(BIN_ENTRY))

# Removing test output files:
clean-tests:
	$(call INFO,Removing intermediate C test files...)
	$(call RMDIR,$(TESTS_C))
	$(call INFO,Removing debugging test executables...)
	$(call RMDIR,$(TESTS_DEBUG))
	$(call INFO,Removing complete test executables...)
	$(call RMDIR,$(TESTS_COMPL))

# Removing clangd config:
clean-clangd:
	$(call INFO,Removing clangd config...)
	$(call RM,compile_commands.json)

# Compiling source files:
$(BIN_SRC)%$(EXT_OBJ): $(SRC)%$(EXT_IMPL)
	$(call INFO,Compiling \"$(call FILE_NAME,$<)\" source object file...)
	$(CREATE_DIR)
	$(COMPILE)

# Compiling entry-point files:
$(BIN_ENTRY)%$(EXT_OBJ): $(ENTRY)%$(EXT_IMPL)
	$(call INFO,Compiling \"$(call FILE_NAME,$<)\" entry object file...)
	$(CREATE_DIR)
	$(COMPILE)

# TODO: Remove the `$(SRC_FILES)` once I figure out a way to filter out the implementation dependencies.
# Linking executable files:
$(BIN_DIST)%$(EXT_EXE): $(BIN_ENTRY)%$(EXT_OBJ) $(BIN_SRC_FILES)
#$(BIN_DIST)%$(EXT_EXE): $(BIN_ENTRY)%$(EXT_OBJ)
	$(call INFO,Linking \"$(call FILE_NAME,$<)\" executable file...)
	$(CREATE_DIR)
	$(LINK)

## EXTERNAL LIBRARIES ##

$(ASIO_OBJ): $(ASIO_SRC)
	$(call INFO,Compiling the ASIO library...)
	$(CREATE_DIR)
	$(COMPILER) -c -std=c++20 -O2 -o $(call SPATH,$@) $(call SPATH,$(ASIO_INC)) $(call SPATH,$<) $(ASIO_LIB)

## GENERATED ##

# Dependencies of generated files:
$(SRC)$(IMPL_PARSER): $(INC)$(HEAD_PARSER)$(EXT_HEAD)
$(SRC)$(IMPL_LEXER):  $(INC)$(HEAD_PARSER)$(EXT_HEAD)

## TESTS ##

# C synth code:
$(TEST_C)%.c: $(TEST_IN)%$(EXT_CYNTH) $(BIN_DIST)compiler
	$(CREATE_DIR)
	cat $(call SPATH,$<) | $(call SPATH,$(BIN_DIST)compiler) > $(call SPATH,$@)

# A standalone debug synth program:
$(TEST_DEBUG)%$(EXT_EXE): $(TEST_C)%.c
	$(CREATE_DIR)
	$(COMPILE_CYNTH_DEBUG)

# A (statically) linkable synth program.
$(TEST_SYNTH)%$(EXT_OBJ): $(TEST_C)%.c
	$(CREATE_DIR)
	$(COMPILE_CYNTH_STAT)

# A complete executable synth program.
$(TEST_COMPL)%$(EXT_EXE): $(TEST_SYNTH)%.o
	$(CREATE_DIR)
	$(COMPILE_CYNTH_COMPL)

## CLANGD ##

CLANGD_CMD = $(CLANGD_COMPILER) -std=$(STD) $(OPT_INC) $(OPT_DEF) $(CROSSCOMP_OPTIONS)

define CLANGD_ENTRY
{
        \"directory\": \"$(shell pwd)\",
        \"file\":      \"$1\",
        \"command\":   \"$(CLANGD_CMD)\"
    },
endef

define CLANGD_CFG
[
    $(foreach E,$1,$(call CLANGD_ENTRY,$E))
]
endef

compile_commands.json:
	$(call INFO,Assembling clangd config...)
	echo "$(call LINES,$(call CLANGD_CFG,$(ENTRY_FILES)))" > $(call SPATH,$@)

#"command": "/usr/bin/clang++ -std=c++20 -Iinc/ -Iext/asio/common/ -Iext/asio/host/ -Iext/asio/host/pc/ -DCTH_PLATFORM=CTH_PLATFORM_WINDOWS -DCTH_DRIVERAPI=CTH_DRIVERAPI_ASIO -DCTH_SYNTHOUT=CTH_SYNTHOUT_STAT -target x86_64-w64-mingw32 -fms-extensions -I/mnt/c/msys64/mingw64/include/c++/10.1.0 -I/mnt/c/msys64/mingw64/include/c++/10.1.0/backward -I/mnt/c/msys64/mingw64/include/c++/10.1.0/x86_64-w64-mingw32 -I/mnt/c/msys64/mingw64/x86_64-w64-mingw32/include -I/mnt/c/msys64/mingw64/lib/clang/10.0.0/include"

#### DEPENDENCIES ####

-include $(DEP_SRC_FILES) $(DEP_ENTRY_FILES)
