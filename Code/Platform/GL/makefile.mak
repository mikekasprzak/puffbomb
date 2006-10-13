# - -------------------------------------------------------------------------------------------- - #
# OpenGL Platform Makefile --------------------------------------------------------------------- - #
# - -------------------------------------------------------------------------------------------- - #

# - -------------------------------------------------------------------------------------------- - #
# Include the system specific configuration ---------------------------------------------------- - #
include config.mak
include Code/Game/$(GAME_TARGET)/Makefiles/game.mak
# - -------------------------------------------------------------------------------------------- - #
ToolChain		:=	Code/Tools/_ToolChain
# - -------------------------------------------------------------------------------------------- - #
# Include the platform configuration ----------------------------------------------------------- - #
include $(ToolChain)/$(PLATFORM)/platform.mak
# - -------------------------------------------------------------------------------------------- - #
# Common Calls/Tools executed for doing all kinds of work -------------------------------------- - #
include $(ToolChain)/tools.mak
# - -------------------------------------------------------------------------------------------- - #

# - -------------------------------------------------------------------------------------------- - #
TextureToolArgs	:=	-fatten
export TextureToolArgs
# - -------------------------------------------------------------------------------------------- - #


# - -------------------------------------------------------------------------------------------- - #
CODE_DIRS		:=	$(SYSTEM_TARGET) External Library $(ENGINE) Framework Game/JunkGame Game/$(GAME_TARGET)
# - -------------------------------------------------------------------------------------------- - #
CONTENT_DIRS	:=	$(GAME_TARGET)
CONTENT_EXT		:=	.png .ogg .anim .font .form .mesh3d .comp .coll
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
# - -------------------------------------------------------------------------------------------- - #

# - -------------------------------------------------------------------------------------------- - #
# *** PROCESSES TO RUN ON CONTENT NAMES *** #
# - -------------------------------------------------------------------------------------------- - #
# Target 3D files are .bin.mesh3d, not .blend.mesh3d ------------------------------------------- - #
PLATFORM_CONTENT:=	$(subst .blend.mesh3d,.bin.pack.mesh3d,$(PLATFORM_CONTENT))

# Remove any content that contains a ".Id" in it's path names ---------------------------------- - #
PLATFORM_CONTENT:=	$(filter-out $(foreach DIR,$(CONTENT_DIRS),$(shell $(PatternTool) $(DIR) .Id)),$(PLATFORM_CONTENT))

# Target Texture files from PNG to TX ---------------------------------------------------------- - #
PLATFORM_CONTENT:=	$(subst .png,.pack.tx,$(PLATFORM_CONTENT))

# Target Component and Collection files -------------------------------------------------------- - #
PLATFORM_CONTENT:=	$(subst .comp,.bin.pack.comp,$(PLATFORM_CONTENT))
PLATFORM_CONTENT:=	$(subst .coll,.bin.pack.coll,$(PLATFORM_CONTENT))
# - -------------------------------------------------------------------------------------------- - #

# - -------------------------------------------------------------------------------------------- - #
CONST_CONTENT	:=	$(addprefix $(RELEASE_DIR),$(subst Content/$(SYSTEM_TARGET),,$(CONST_CONTENT)))
PLATFORM_CONTENT:=	$(addprefix $(RELEASE_DIR),$(foreach DIR,$(CONTENT_DIRS),$(subst $(DIR),,$(PLATFORM_CONTENT))))

CONTENT			:=	$(CONST_CONTENT) $(PLATFORM_CONTENT)
# - -------------------------------------------------------------------------------------------- - #

ALL_DEPEND		:=	$(OUT_DIR)/makedirs

# - -------------------------------------------------------------------------------------------- - #
# - Target specific compiling, linking, and executing ------------------------------------------ - #
include $(ToolChain)/$(PLATFORM)/target.mak
# - -------------------------------------------------------------------------------------------- - #


# - -------------------------------------------------------------------------------------------- - #
define _makedirs
	$(MakeDir) $(sort $(RELEASE_DIR) $(dir $(.O_FILES)) $(dir $(CONTENT)) $(dir $(subst /Release,/Data,$(CONTENT))))
endef
# - -------------------------------------------------------------------------------------------- - #
makedirs:
	$(_makedirs)
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
$(RELEASE_DIR)/%.pack.tx: Content/$(GAME_TARGET)/%.png $(TextureTool) $(ALL_DEPEND)
	$(TextureTool) $< $(DATA_DIR)/$*.tx $(TextureToolArgs)
	$(Compress) $(DATA_DIR)/$*.tx $@
# - -------------------------------------------------------------------------------------------- - #
# Components ----------------------------------------------------------------------------------- - #
$(RELEASE_DIR)/%.bin.pack.comp: Content/$(GAME_TARGET)/%.comp $(ComponentTool) $(ALL_DEPEND)
	$(ComponentTool) $< $(DATA_DIR)/$*.bin.comp $@
#	$(DATA_DIR)/$*.sh
#	$(Compress) $(DATA_DIR)/$*.bin.comp $@
	
#	chmod +x $(DATA_DIR)/$*.sh
# - -------------------------------------------------------------------------------------------- - #
# Specific unprocessed content ----------------------------------------------------------------- - #
$(RELEASE_DIR)/%: Content/$(GAME_TARGET)/% $(ALL_DEPEND)
	cp $< $@
# - -------------------------------------------------------------------------------------------- - #

	
# - -------------------------------------------------------------------------------------------- - #
-include $(.O_FILES:.o=.o.d)
# - -------------------------------------------------------------------------------------------- - #
