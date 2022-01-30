include setup.mk

#### CONFIG ####

BIN_SRC_FILES   = $(SRC_FILES:$(SRC)%$(EXT_IMPL)=$(BIN_SRC)$(TARGETDIR)%$(EXT_OBJ))
BIN_ENTRY_FILES = $(ENTRY_FILES:$(ENTRY)%$(EXT_IMPL)=$(BIN_ENTRY)$(TARGETDIR)%$(EXT_OBJ))
BIN_DIST_FILES  = $(ENTRY_FILES:$(ENTRY)%$(EXT_IMPL)=$(BIN_DIST)$(TARGETDIR)%$(EXT_EXE))

#### COMMANDS ####

COMPILE             = $(COMPILER) -c -o $(call SPATH,$@) $(COMP_OPTIONS) -pthread $(call SPATH,$<)
COMPILE             = $(COMPILER) -c -o $(call SPATH,$@) $(COMP_OPTIONS) -pthread $(call SPATH,$<)
LINK                = $(COMPILER) $(LINK_OPTIONS) -o $(call SPATH,$@) $(call SPATH,$^)
COMPILE_SYNTH_DEBUG = $(GCC) -o $(call SPATH,$@) $(SYNTH_COMP_OPTIONS) -pthread $(call SPATH,$<) $(SYNTH_LIB)
COMPILE_SYNTH_STAT  = $(GCC) -c -o $(call SPATH,$@) $(SYNTH_COMP_OPTIONS) -pthread $(call SPATH,$<)
COMPILE_CONTR       = $(COMPILER) -c -o $(call SPATH,$@) $(COMP_OPTIONS) -pthread $(call SPATH,$<)
COMPILE_COMPL       = $(GPP) -o $(call SPATH,$@) $(COMP_OPTIONS) -pthread $(call SPATH,$^) $(SYNTH_LIB) $(THREAD_LIB) $(ASIO_LIB)

#### TARGETS ####

.PHONY: all clean test clean-dist clean-bin clean-dep clean-gen clean-flags test

all: $(BIN_SRC_FILES) $(BIN_ENTRY_FILES) $(BIN_DIST_FILES) $(EXTERN_OBJ) $(OTHER_FILES)

compile: $(BIN_SRC_FILES) $(BIN_ENTRY_FILES)

link: $(BIN_DIST_FILES)

clean: clean-dist clean-bin clean-tests clean-clangd

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
	$(call INFO,Removing intermediate binary external library files...)
	$(call RMDIR,$(BIN_EXTERN))

# Removing test output files:
clean-tests:
	$(call INFO,Removing intermediate debug C test files...)
	$(call RMDIR,$(TEST_C_DEBUG))
	$(call INFO,Removing intermediate static linkage C test files...)
	$(call RMDIR,$(TEST_C_STAT))
	$(call INFO,Removing debug synth test executables...)
	$(call RMDIR,$(TEST_BIN_DEBUG))
	$(call INFO,Removing static linkage synth test binaries...)
	$(call RMDIR,$(TEST_BIN_STAT))
	$(call INFO,Removing complete synth test executables...)
	$(call RMDIR,$(TEST_BIN_COMPL))

# Removing clangd config:
clean-clangd:
	$(call INFO,Removing clangd config...)
	$(call RM,compile_commands.json)

# Compiling source files:
$(BIN_SRC)$(TARGETDIR)%$(EXT_OBJ): $(SRC)%$(EXT_IMPL)
	$(call INFO,Compiling \"$(call FILE_NAME,$<)\" source object file...)
	$(CREATE_DIR)
	$(COMPILE)

# Compiling entry-point files:
$(BIN_ENTRY)$(TARGETDIR)%$(EXT_OBJ): $(ENTRY)%$(EXT_IMPL)
	$(call INFO,Compiling \"$(call FILE_NAME,$<)\" entry object file...)
	$(CREATE_DIR)
	$(COMPILE)

# TODO: Remove the `$(SRC_FILES)` once I figure out a way to filter out the implementation dependencies.
# Linking executable files:
$(BIN_DIST)$(TARGETDIR)%$(EXT_EXE): $(BIN_ENTRY)$(TARGETDIR)%$(EXT_OBJ) $(BIN_SRC_FILES)
#$(BIN_DIST)$(TARGETDIR)%$(EXT_EXE): $(BIN_ENTRY)$(TARGETDIR)%$(EXT_OBJ)
	$(call INFO,Linking \"$(call FILE_NAME,$<)\" executable file...)
	$(CREATE_DIR)
	$(LINK)

## EXTERNAL LIBRARIES ##

$(BIN_EXTERN)$(TARGETDIR)asio/%$(EXT_OBJ): $(EXTERN)asio/%$(EXT_IMPL)
	$(call INFO,Compiling the ASIO library...)
	$(CREATE_DIR)
	$(COMPILER) -c -o $(call SPATH,$@) -std=c++20 -O2 -pthread $(call SPATH,$(ASIO_INC)) $(call SPATH,$<)

## GENERATED ##

# Dependencies of generated files:
$(SRC)$(IMPL_PARSER): $(INC)$(HEAD_PARSER)$(EXT_HEAD)
$(SRC)$(IMPL_LEXER):  $(INC)$(HEAD_PARSER)$(EXT_HEAD)

## TESTS ##

# C synth code (DEBUG or STAT):
$(TEST_C)%.c: $(TEST_IN)%$(EXT_CYNTH) $(BIN_DIST)$(TARGETDIR)compiler$(EXT_EXE)
	$(CREATE_DIR)
	$(ENCODING) $(call CAT,$<) | $(call SPATH,$(BIN_DIST)$(TARGETDIR)compiler$(EXT_EXE)) > $@

# A standalone debug synth program (DEBUG only):
ifeq ($(SYNTHOUT), DEBUG)
$(TEST_BIN_DEBUG)%$(EXT_EXE): $(TEST_C)%.c
	$(CREATE_DIR)
	$(COMPILE_SYNTH_DEBUG)
endif

# A statically linkable synth binary (STAT only):
ifeq ($(SYNTHOUT), STAT)
$(TEST_BIN_STAT)%$(EXT_OBJ): $(TEST_C)%.c
	$(CREATE_DIR)
	$(COMPILE_SYNTH_STAT)
endif

# A statically linkable control program (STAT only, but also DYN in the future):
$(BIN_ENTRY)$(TARGETDIR)control$(EXT_OBJ): $(ENTRY)control$(EXT_IMPL)
	$(CREATE_DIR)
	$(COMPILE_CONTR)

# A complete executable synth program (STAT only, but also DYN in the future):
ifeq ($(SYNTHOUT), STAT)
$(TEST_BIN_COMPL)%$(EXT_EXE): $(TEST_BIN_STAT)%$(EXT_OBJ) $(BIN_ENTRY)$(TARGETDIR)control$(EXT_OBJ) $(ASIO_OBJ)
	$(CREATE_DIR)
	$(COMPILE_COMPL)
endif

## CLANGD ##

CLANGD_CMD = $(CLANGD_COMPILER) -std=$(STD) $(OPT_INC) $(ASIO_INC) $(OPT_DEF) $(CROSSCOMP_OPTIONS)

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

$(COMPILE_COMMANDS):
	$(call INFO,Assembling clangd config...)
	$(ENCODING) echo "$(call LINES,$(call CLANGD_CFG,_))" > $(call SPATH,$@)
#	$(ENCODING) echo "$(call LINES,$(call CLANGD_CFG,$(ENTRY_FILES)))" > $(call SPATH,$@)

#"command": "/usr/bin/clang++ -std=c++20 -Iinc/ -Iext/asio/common/ -Iext/asio/host/ -Iext/asio/host/pc/ -DCTH_PLATFORM=CTH_PLATFORM_WINDOWS -DCTH_DRIVERAPI=CTH_DRIVERAPI_ASIO -DCTH_SYNTHOUT=CTH_SYNTHOUT_STAT -target x86_64-w64-mingw32 -fms-extensions -I/mnt/c/msys64/mingw64/include/c++/10.1.0 -I/mnt/c/msys64/mingw64/include/c++/10.1.0/backward -I/mnt/c/msys64/mingw64/include/c++/10.1.0/x86_64-w64-mingw32 -I/mnt/c/msys64/mingw64/x86_64-w64-mingw32/include -I/mnt/c/msys64/mingw64/lib/clang/10.0.0/include"

#### DEPENDENCIES ####

-include $(DEP_SRC_FILES) $(DEP_ENTRY_FILES)
