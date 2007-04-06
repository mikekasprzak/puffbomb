# - -------------------------------------------------------------------------------------------- - #
# OpenGL Platform Makefile --------------------------------------------------------------------- - #
# - -------------------------------------------------------------------------------------------- - #

# - -------------------------------------------------------------------------------------------- - #
# Include the system specific configuration ---------------------------------------------------- - #
include config.mak
include Code/Game/$(GAME_TARGET)/Makefiles/game.mak
# - -------------------------------------------------------------------------------------------- - #
ToolChain		:=	Code/Makefiles
# - -------------------------------------------------------------------------------------------- - #
# Include the platform configuration ----------------------------------------------------------- - #
include $(ToolChain)/$(PLATFORM)/platform.mak
# - -------------------------------------------------------------------------------------------- - #
# Common Calls/Tools executed for doing all kinds of work -------------------------------------- - #
include $(ToolChain)/tools.mak
# - -------------------------------------------------------------------------------------------- - #

# - -------------------------------------------------------------------------------------------- - #
TextureToolArgs		:=	-fatten
#-half
export TextureToolArgs
# - -------------------------------------------------------------------------------------------- - #
CompTextureToolArgs	:=	-fatten
# -white
export CompTextureToolArgs
# - -------------------------------------------------------------------------------------------- - #


# - -------------------------------------------------------------------------------------------- - #
CODE_DIRS		:=	$(SYSTEM_TARGET) External Library $(ENGINE) Framework Game/JunkGame Game/$(GAME_TARGET)
# - -------------------------------------------------------------------------------------------- - #
CONTENT_DIRS	:=	$(GAME_TARGET)
CONTENT_EXT		:=	.png .ogg .anim .font .form .mesh3d .comp .coll .map .pack.tx
# - -------------------------------------------------------------------------------------------- - #


# - -------------------------------------------------------------------------------------------- - #
ifndef LOG_LEVEL
LOG_LEVEL		:=	0
endif
# - -------------------------------------------------------------------------------------------- - #
DEFINES			+=	LOG_LEVEL=$(LOG_LEVEL) _LZMA_PROB32
# - -------------------------------------------------------------------------------------------- - #


# - -------------------------------------------------------------------------------------------- - #
# Editor Support ------------------------------------------------------------------------------- - #
ifdef EDITOR
CODE_DIRS		+=	Editor
DEFINES			+=	EDITOR
endif
# - -------------------------------------------------------------------------------------------- - #


# - -------------------------------------------------------------------------------------------- - #
OUT_DIR			:=	Output/$(GAME_TARGET)/$(PLATFORM)

OBJ_DIR			:=	$(OUT_DIR)/obj
DATA_DIR		:=	$(OUT_DIR)/Data
RELEASE_DIR		:=	$(OUT_DIR)/Release
# - -------------------------------------------------------------------------------------------- - #
CODE_DIRS		:=	$(addprefix Code/,$(CODE_DIRS))
CONTENT_DIRS	:=	$(addprefix Content/,$(CONTENT_DIRS))
# - -------------------------------------------------------------------------------------------- - #
INCLUDE_DIRS	:=	$(addprefix -I ,$(INCLUDE_DIRS))
LIB_DIRS		:=	$(addprefix -L ,$(LIB_DIRS))
DEFINES			:=	$(addprefix -D,$(DEFINES))
CODE_FLAGS		:=	$(CODE_FLAGS) $(DEFINES)
# - -------------------------------------------------------------------------------------------- - #
.CPP_FILES		:=	$(foreach VAR,$(CODE_DIRS),$(shell $(TreeTool) $(VAR) .cpp .c) )
# - -------------------------------------------------------------------------------------------- - #
.O_FILES		:=	$(addsuffix .o,$(addprefix $(OUT_DIR)/obj/,$(.CPP_FILES)))
# - -------------------------------------------------------------------------------------------- - #

# - -------------------------------------------------------------------------------------------- - #
CONST_CONTENT	:=	$(wildcard Content/$(SYSTEM_TARGET)/*)
PLATFORM_CONTENT:=	$(foreach DIR,$(CONTENT_DIRS),$(foreach EXT,$(CONTENT_EXT),$(shell $(TreeTool) $(DIR) $(EXT))))
SH_CONTENT		:=	$(foreach DIR,$(CONTENT_DIRS),$(shell $(TreeTool) $(DIR) .comp))
# - -------------------------------------------------------------------------------------------- - #

# - -------------------------------------------------------------------------------------------- - #
# *** PROCESSES TO RUN ON CONTENT NAMES *** #
# - -------------------------------------------------------------------------------------------- - #
# Target 3D files are .bin.mesh3d, not .blend.mesh3d ------------------------------------------- - #
PLATFORM_CONTENT:=	$(subst .blend.mesh3d,.bin.pack.mesh3d,$(PLATFORM_CONTENT))

# Remove any content that contains a ".Id" in it's path names ---------------------------------- - #
PLATFORM_CONTENT:=	$(filter-out $(foreach DIR,$(CONTENT_DIRS),$(shell $(PatternTool) $(DIR) .Id)),$(PLATFORM_CONTENT))

# Target Texture files from PNG to TX ---------------------------------------------------------- - #
PLATFORM_CONTENT:=	$(subst .png,.pack.dds.tx,$(PLATFORM_CONTENT))

# Target Component and Collection files -------------------------------------------------------- - #
PLATFORM_CONTENT:=	$(subst .comp,.bin.comp,$(PLATFORM_CONTENT))
PLATFORM_CONTENT:=	$(subst .coll,.coll,$(PLATFORM_CONTENT))

PLATFORM_CONTENT:=	$(subst .map,.map,$(PLATFORM_CONTENT))

# Shell scripts generated by component files #
SH_CONTENT		:=	$(subst .comp,.done.sh,$(SH_CONTENT))
# - -------------------------------------------------------------------------------------------- - #

# - -------------------------------------------------------------------------------------------- - #
# Trim off content search folders #
CONST_CONTENT	:=	$(addprefix $(RELEASE_DIR),$(subst Content/$(SYSTEM_TARGET),,$(CONST_CONTENT)))
PLATFORM_CONTENT:=	$(addprefix $(RELEASE_DIR),$(foreach DIR,$(CONTENT_DIRS),$(subst $(DIR),,$(PLATFORM_CONTENT))))
SH_CONTENT		:=	$(addprefix $(DATA_DIR),$(foreach DIR,$(CONTENT_DIRS),$(subst $(DIR),,$(SH_CONTENT))))

SH_CONTENT_DIRS	:=	$(sort $(dir $(SH_CONTENT)))
SH_CONTENT		:=	$(foreach DIR,$(SH_CONTENT_DIRS),$(firstword $(filter $(DIR)%,$(SH_CONTENT))))

# Content List #
CONTENT			:=	$(CONST_CONTENT) $(PLATFORM_CONTENT) $(SH_CONTENT)
# - -------------------------------------------------------------------------------------------- - #

ALL_DEPEND		:=	$(OUT_DIR)/makedirs

# - -------------------------------------------------------------------------------------------- - #
# - Target specific compiling, linking, and executing ------------------------------------------ - #
include $(ToolChain)/$(PLATFORM)/target.mak
# - -------------------------------------------------------------------------------------------- - #

noop:
	@echo E: $(SH_CONTENT)

# - -------------------------------------------------------------------------------------------- - #
define _makedirs
	$(MakeDir) $(sort $(RELEASE_DIR) $(dir $(.O_FILES)) $(dir $(CONTENT)) $(dir $(subst /Release,/Data,$(CONTENT))))
endef
# - -------------------------------------------------------------------------------------------- - #
makedirs:
	@echo Creating directories...
	@$(_makedirs)
# - -------------------------------------------------------------------------------------------- - #
$(OUT_DIR)/makedirs:
	$(_makedirs)
	$(Touch) $@
# - -------------------------------------------------------------------------------------------- - #
# An attempt at making "update" update the D files "
#
#makedees:
#	$(Remove) $(.O_FILES:.o=.d)
#	$(Touch) $(OUT_DIR)/makedees
# - -------------------------------------------------------------------------------------------- - #
#$(OUT_DIR)/makedees:
#	$(Remove) $(.O_FILES:.o=.d)
#	$(Touch) $@
# - -------------------------------------------------------------------------------------------- - #


.phony: makedirs clean cleanall all update run

# - -------------------------------------------------------------------------------------------- - #
all: makedirs $(RELEASE_DIR)/$(BINARY_TARGET)
# - -------------------------------------------------------------------------------------------- - #
# An attempt at making "update" update the D files "
#
#_update_stage1: makedirs makedees
#	@echo Success!!!!!!!!
#_update_stage2: _update_stage1 $(.O_FILES:.o=.o.d)
#	@echo Success!!!!
#update: _update_stage1 _update_stage2
#	@echo Success!
# - -------------------------------------------------------------------------------------------- - #
update: makedirs
# - -------------------------------------------------------------------------------------------- - #
clean:
	$(Remove) $(OBJ_DIR)
	$(_makedirs)
# - -------------------------------------------------------------------------------------------- - #
cleanall: 
	$(Remove) $(OUT_DIR)
# - -------------------------------------------------------------------------------------------- - #
cleancontent: 
	$(Remove) $(RELEASE_DIR)
	$(Remove) $(DATA_DIR)
# - -------------------------------------------------------------------------------------------- - #


# - -------------------------------------------------------------------------------------------- - #
# Static Content Copying ----------------------------------------------------------------------- - #
$(RELEASE_DIR)/%: Content/$(SYSTEM_TARGET)/% $(ALL_DEPEND)
	cp $< $@
# - -------------------------------------------------------------------------------------------- - #	


# - -------------------------------------------------------------------------------------------- - #
# 3D Meshes ------------------------------------------------------------------------------------ - #
$(RELEASE_DIR)/%.bin.pack.mesh3d: Content/$(GAME_TARGET)/%.blend.mesh3d $(Mesh3DTool) $(ALL_DEPEND)
	$(Mesh3DTool) $< $(DATA_DIR)/$*.bin.mesh3d
	$(Compress) $(DATA_DIR)/$*.bin.mesh3d $@
# - -------------------------------------------------------------------------------------------- - #
# Textures ------------------------------------------------------------------------------------- - #
$(RELEASE_DIR)/%.pack.dds.tx: Content/$(GAME_TARGET)/%.png $(TextureTool) $(ALL_DEPEND)
	$(NVTextureTool) -bc2 $< $(DATA_DIR)/$*.dds.tx
	$(Compress) $(DATA_DIR)/$*.dds.tx $@
# - -------------------------------------------------------------------------------------------- - #
#$(RELEASE_DIR)/%.pack.tx: Content/$(GAME_TARGET)/%.png $(TextureTool) $(ALL_DEPEND)
#	$(TextureTool) $< $(DATA_DIR)/$*.tx $(TextureToolArgs)
#	$(Compress) $(DATA_DIR)/$*.tx $@
# - -------------------------------------------------------------------------------------------- - #
# Components ----------------------------------------------------------------------------------- - #
$(RELEASE_DIR)/%.bin.comp: Content/$(GAME_TARGET)/%.comp $(ComponentTool) $(ALL_DEPEND)
	$(ComponentTool) $< $(DATA_DIR)/$*.bin.comp $@
	cp $(DATA_DIR)/$*.bin.comp $@

#	$(DATA_DIR)/$*.sh
#	$(Compress) $(DATA_DIR)/$*.bin.comp $@	
#	chmod +x $(DATA_DIR)/$*.sh
# - -------------------------------------------------------------------------------------------- - #
# Run generated shell scripts from the component stage
$(DATA_DIR)/%.done.sh: $(DATA_DIR)/%.sh
	$<
	$(Touch) $@
#$(DATA_DIR)/Content/$(GAME_TARGET)/%.done.sh
# - -------------------------------------------------------------------------------------------- - #
# Collections ---------------------------------------------------------------------------------- - #
$(RELEASE_DIR)/%.coll: Content/$(GAME_TARGET)/%.coll $(CollectionTool) $(ALL_DEPEND)
	cp $< $@
# - -------------------------------------------------------------------------------------------- - #
# Maps ----------------------------------------------------------------------------------------- - #
$(RELEASE_DIR)/%.map: Content/$(GAME_TARGET)/%.map $(MapTool) $(ALL_DEPEND)
	cp $< $@
# - -------------------------------------------------------------------------------------------- - #
# Specific unprocessed content ----------------------------------------------------------------- - #
$(RELEASE_DIR)/%: Content/$(GAME_TARGET)/% $(ALL_DEPEND)
	cp $< $@
# - -------------------------------------------------------------------------------------------- - #

	
# - -------------------------------------------------------------------------------------------- - #
-include $(.O_FILES:.o=.o.d)
# - -------------------------------------------------------------------------------------------- - #
