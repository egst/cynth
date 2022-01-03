include setup.mk

#### CONFIG ####

DEP_SRC_FILES   = $(SRC_FILES:$(SRC)%$(EXT_IMPL)=$(DEP_SRC)%$(EXT_DEP))
DEP_ENTRY_FILES = $(ENTRY_FILES:$(ENTRY)%$(EXT_IMPL)=$(DEP_ENTRY)%$(EXT_DEP))

GEN_DEPS       = mkdir -p $(dir $@); $(GCC) $(BASIC_OPTIONS) $(DEP_OPTIONS) -MM -MT '$1 $2' -MF $@ $<
GEN_SRC_DEPS   = $(call GEN_DEPS,$(<:$(SRC)%$(EXT_IMPL)=$(BIN_SRC)%$(EXT_OBJ)),$(<:$(SRC)%$(EXT_IMPL)=$(DEP_SRC)%$(EXT_DEP)))
GEN_ENTRY_DEPS = $(call GEN_DEPS,$(<:$(ENTRY)%$(EXT_IMPL)=$(BIN_ENTRY)%$(EXT_OBJ)),$(<:$(ENTRY)%$(EXT_IMPL)=$(DEP_ENTRY)%$(EXT_DEP)))

#### TARGETS ####

.PHONY: all clean

all: $(DEP_SRC_FILES) $(DEP_ENTRY_FILES)

# Removing dependency files:
clean:
	$(call INFO,Removing source dependency files...)
	rm -rf $(DEP_SRC)
	$(call INFO,Removing entry dependency files...)
	rm -rf $(DEP_ENTRY)

# Source files dependencies:
$(DEP_SRC)%$(EXT_DEP): $(SRC)%$(EXT_IMPL)
	$(call INFO,Updating \"$(call FILE_NAME,$<)\" source dependencies...)
	$(GEN_SRC_DEPS)

# Entry-point files dependencies:
$(DEP_ENTRY)%$(EXT_DEP): $(ENTRY)%$(EXT_IMPL)
	$(call INFO,Updating \"$(call FILE_NAME,$<)\" entry dependencies...)
	$(GEN_ENTRY_DEPS)
