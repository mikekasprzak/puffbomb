# - -------------------------------------------------------------------------------------------- - #
# OpenGL Platform Makefile --------------------------------------------------------------------- - #
# - -------------------------------------------------------------------------------------------- - #

# - -------------------------------------------------------------------------------------------- - #
# Include the system specific configuration ---------------------------------------------------- - #
include config.mak
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
CODE_DIRS		:=	$(SYSTEM_TARGET) External Library $(ENGINE) Game # Game/$(GAME_TARGET)
# - -------------------------------------------------------------------------------------------- - #
CONTENT_DIRS	:=	$(GAME_TARGET)
CONTENT_EXT		:=	.png .ogg .anim .font .form .map .body2d .mesh2d .body3d .mesh3d
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
CONST_CONTENT	:=	$(addprefix $(RELEASE_DIR),$(subst Content/$(SYSTEM_TARGET),,$(CONST_CONTENT)))

PLATFORM_CONTENT:=	$(foreach DIR,$(CONTENT_DIRS),$(foreach EXT,$(CONTENT_EXT),$(shell $(TreeTool) $(DIR) $(EXT))))
PLATFORM_CONTENT:=	$(addprefix $(RELEASE_DIR),$(foreach DIR,$(CONTENT_DIRS),$(subst $(DIR),,$(PLATFORM_CONTENT))))

# Target 3D files are .bin.mesh3d, not .blend.mesh3d ------------------------------------------- - #
PLATFORM_CONTENT:=	$(subst .blend.mesh3d,.bin.pack.mesh3d,$(PLATFORM_CONTENT))

# Target Texture files from PNG to TX ---------------------------------------------------------- - #
PLATFORM_CONTENT:=	$(subst .png,.pack.tx,$(PLATFORM_CONTENT))

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


# - -------------------------------------------------------------------------------------------- - #
all: makedirs $(RELEASE_DIR)/$(BINARY_TARGET)
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
	$(TextureTool) $< $(DATA_DIR)/$*.tx -fatten
	$(Compress) $(DATA_DIR)/$*.tx $@
# - -------------------------------------------------------------------------------------------- - #
# Specific unprocessed content ----------------------------------------------------------------- - #
$(RELEASE_DIR)/%: Content/$(GAME_TARGET)/% $(ALL_DEPEND)
	cp $< $@
# - -------------------------------------------------------------------------------------------- - #

	
# - -------------------------------------------------------------------------------------------- - #
-include $(.O_FILES:.o=.o.d)
# - -------------------------------------------------------------------------------------------- - #
