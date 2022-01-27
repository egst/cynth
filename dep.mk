include setup.mk

#### CONFIG ####

GEN_DEPS = $(GPP) $(COMP_OPTIONS) $(DEP_OPTIONS) -MM -MT '$1 $2' -MF $@ $<

GEN_SRC_DEPS   = $(call GEN_DEPS,$(<:$(SRC)%$(EXT_IMPL)=$(BIN_SRC)%$(EXT_OBJ)),$(<:$(SRC)%$(EXT_IMPL)=$(DEP_SRC)%$(EXT_DEP)))
GEN_ENTRY_DEPS = $(call GEN_DEPS,$(<:$(ENTRY)%$(EXT_IMPL)=$(BIN_ENTRY)%$(EXT_OBJ)),$(<:$(ENTRY)%$(EXT_IMPL)=$(DEP_ENTRY)%$(EXT_DEP)))

#### TARGETS ####

.PHONY: all clean

all: $(DEP_SRC_FILES) $(DEP_ENTRY_FILES)

# Removing dependency files:
clean:
	$(call INFO,Removing source dependency files...)
	$(RMDIR,$(DEP_SRC))
	$(call INFO,Removing entry dependency files...)
	$(RMDIR,$(DEP_ENTRY))

# Source files dependencies:
$(DEP_SRC)%$(EXT_DEP): $(SRC)%$(EXT_IMPL)
	$(call INFO,Updating \"$(call FILE_NAME,$<)\" source dependencies...)
	$(CREATE_DIR)
	$(GEN_SRC_DEPS)

# Entry-point files dependencies:
$(DEP_ENTRY)%$(EXT_DEP): $(ENTRY)%$(EXT_IMPL)
	$(call INFO,Updating \"$(call FILE_NAME,$<)\" entry dependencies...)
	$(CREATE_DIR)
	$(GEN_ENTRY_DEPS)
