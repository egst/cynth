#### USER CONFIG ####

include config.mk

#### HELPER FUNCTIONS ####

FILE_NAME = $(basename $(notdir $1))

TITLE = @echo $(TPUT_BLUE)$1$(TPUT_RESET)
SUCC  = @echo $(TPUT_GREEN)$1$(TPUT_RESET)
INFO  = @echo $(TPUT_GRAY)$1$(TPUT_RESET)
WARN  = @echo $(TPUT_YELLOW)$1$(TPUT_RESET)
ERROR = @echo $(TPUT_RED)$1$(TPUT_RESET)

#### CONFIG ####

TPUT_RED    = $$(tput setaf 9)
TPUT_GREEN  = $$(tput setaf 2)
TPUT_YELLOW = $$(tput setaf 3)
TPUT_BLUE   = $$(tput setaf 6)
TPUT_GRAY   = $$(tput setaf 8)
TPUT_RESET  = $$(tput sgr0)

# TODO: Make this recursive to any depth.
SRC_FILES       = $(wildcard $(SRC)*$(EXT_IMPL))
SRC_FILES      += $(wildcard $(SRC)*/*$(EXT_IMPL))
SRC_FILES      += $(wildcard $(SRC)*/*/*$(EXT_IMPL))
SRC_FILES      += $(wildcard $(SRC)*/*/*/*$(EXT_IMPL))
SRC_FILES      += $(wildcard $(SRC)*/*/*/*/*$(EXT_IMPL))
SRC_FILES      += $(wildcard $(SRC)*/*/*/*/*/*$(EXT_IMPL))
SRC_FILES      += $(GEN_SRC_FILES)

# Note: The O2 optimization might be necessary to avoid problems with long mangled names of complex variant types.
BASIC_OPTIONS = -I$(INC) -std=$(STD)
OPTIMIZATIONS = -O2
ALL_OPTIONS   = $(BASIC_OPTIONS) $(ADDITIONAL_OPTIONS) $(OPTIMIZATIONS)

#### COMMANDS ####

# Compile an executable file:
COMPILE = mkdir -p $(dir $@); $(COMPILER) $(ALL_OPTIONS) -o $@ $^

# Compile an object file:
COMPILE_OBJ = mkdir -p $(dir $@); $(COMPILER) $(ALL_OPTIONS) -c -o $@ $<

# Link object files into an executable file:
LINK = mkdir -p $(dir $@); $(COMPILER) $(LINK_OPTIONS) -o $@ $^
