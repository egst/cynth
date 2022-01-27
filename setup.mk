# User config:
include config.mk

#### EXTERNAL LIBRARIES ####

## ASIO ##

ASIO_NAME = asio

ASIO_SRC += asio/common/asio.cpp
ASIO_SRC += asio/host/asiodrivers.cpp
ASIO_SRC += asio/host/pc/asiolist.cpp

ASIO_LIB += uuid
ASIO_LIB += ksuser
ASIO_LIB += ole32
ASIO_LIB += winww

ASIO_INC += asio/common/
ASIO_INC += asio/host/
ASIO_INC += asio/host/pc/

ASIO_OBJ  = $(BIN_EXTERN)$(ASIO_NAME)$(EXT_OBJ)
ASIO_SRC := $(ASIO_SRC:%=$(EXTERN)%)
ASIO_INC := $(ASIO_INC:%=-I$(EXTERN)%)
ASIO_LIB := $(ASIO_LIB:%=-l%)

EXTERN_INC += $(ASIO_INC)
EXTERN_OBJ += $(ASIO_OBJ)

#### MACRO DEFINITIONS ####

DEFS += CTH_PLATFORM=CTH_PLATFORM_$(PLATFORM)
DEFS += CTH_DRIVERAPI=CTH_DRIVERAPI_$(DRIVERAPI)
DEFS += CTH_SYNTHOUT=CTH_SYNTHOUT_$(SYNTHOUT)

#### CONFIG ####

empty =
space = ${empty} ${empty}
define newline


endef

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
ENTRY_FILES     = $(ENTRY_POINTS:%=$(ENTRY)%$(EXT_IMPL))
DEP_SRC_FILES   = $(SRC_FILES:$(SRC)%$(EXT_IMPL)=$(DEP_SRC)%$(EXT_DEP))
DEP_ENTRY_FILES = $(ENTRY_FILES:$(ENTRY)%$(EXT_IMPL)=$(DEP_ENTRY)%$(EXT_DEP))

CYNTH_LIB = -lm

OPT_STD    = -std=$(STD)
OPT_OPTIM  = -O2
OPT_DEF    = $(DEFS:%=-D%)
OPT_LOCINC = -I$(INC)
OPT_INC    = $(OPT_LOCINC) $(EXTERN_INC)

COMP_OPTIONS       += $(OPT_STD) $(OPT_OPTIM) $(OPT_INC) $(OPT_DEF)
LINK_OPTIONS       +=
CYNTH_COMP_OPTIONS += -std=$(CYNTH_STD)

CROSSCOMP_OPTIONS += $(CROSSCOMP_INC:%=-I%)

#### COMMANDS ####

ifeq ($(OS), Windows_NT)
SPATH = $(subst /,\,$1)
MKDIR = if not exist $(call SPATH,$1) mkdir $(call SPATH,$1)
RM    = del /q $(call SPATH,$1)
RMDIR = rd /q /s $(call SPATH,$1)
else
SPATH = $(subst /,\,$1)
MKDIR = mkdir -p $(call SPATH,$1)
RM    = rm -f $(call SPATH,$1)
RMDIR = rm -rf $(call SPATH,$1)
endif

CREATE_DIR = $(call MKDIR,$(dir $(call SPATH,$@)))

#LINES = $(subst ${space},${newline},$1)
#LINES = $(subst ${space},\n,$1)
LINES = $(subst ${newline},\n,$1)

FILE_NAME = $(basename $(notdir $1))

TITLE = @echo $(TPUT_BLUE)$1$(TPUT_RESET)
SUCC  = @echo $(TPUT_GREEN)$1$(TPUT_RESET)
INFO  = @echo $(TPUT_GRAY)$1$(TPUT_RESET)
WARN  = @echo $(TPUT_YELLOW)$1$(TPUT_RESET)
ERROR = @echo $(TPUT_RED)$1$(TPUT_RESET)
