# - -------------------------------------------------------------------------------------------- - #
SYSTEM_TARGET	:=	Platform/$(PLATFORM)
BINARY_TARGET	:=	$(GAME_TARGET).exe
# - -------------------------------------------------------------------------------------------- - #

# - -------------------------------------------------------------------------------------------- - #
INCLUDE_DIRS	+=	Code/$(SYSTEM_TARGET) Code/$(ENGINE) Code/FlowElements Code/Library Code/External Code \
					/usr/local/include Code/Game/JunkGame Code/Game/$(GAME_TARGET)
# - -------------------------------------------------------------------------------------------- - #
LIB_DIRS		+=	/usr/local/lib
# - -------------------------------------------------------------------------------------------- - #

# - -------------------------------------------------------------------------------------------- - #
CODE_FLAGS		:=	-O2 -W -Wall -Wno-unused-variable
LINK_FLAGS		:=	
# - -------------------------------------------------------------------------------------------- - #
