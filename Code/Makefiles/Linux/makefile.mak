# - -------------------------------------------------------------------------------------------- - #
# Linux Platform Makefile ---------------------------------------------------------------------- - #
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
CODE_DIRS		:=	$(SYSTEM_TARGET) External Library $(ENGINE) Framework Game/JunkGame Game/$(GAME_TARGET)
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

ALL_DEPEND		:=	$(OUT_DIR)/makedirs

# - -------------------------------------------------------------------------------------------- - #
# - Target specific compiling, linking, and executing ------------------------------------------ - #
include $(ToolChain)/$(PLATFORM)/target.mak
# - -------------------------------------------------------------------------------------------- - #

# - -------------------------------------------------------------------------------------------- - #
define _makedirs
	$(MakeDir) $(sort $(RELEASE_DIR) $(dir $(.O_FILES)) )
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

.phony: makedirs clean update run

# - -------------------------------------------------------------------------------------------- - #
all: makedirs $(RELEASE_DIR)/$(BINARY_TARGET)
# - -------------------------------------------------------------------------------------------- - #
update: makedirs
# - -------------------------------------------------------------------------------------------- - #
clean:
	$(Remove) $(OBJ_DIR)
	$(_makedirs)
# - -------------------------------------------------------------------------------------------- - #

	
# - -------------------------------------------------------------------------------------------- - #
-include $(.O_FILES:.o=.o.d)
# - -------------------------------------------------------------------------------------------- - #
