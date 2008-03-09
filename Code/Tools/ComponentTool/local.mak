# - -------------------------------------------------------------------------------------------- - #
# Libraries to link against (including -l) ----------------------------------------------------- - #
ifeq ($(HOST_PLATFORM),GL)
LIBS			:=	-Lmingw32/lib -lmingw32 -lSDLmain -lSDL -lSDL_image -lopengl32 -lglu32
else
LIBS			:=	-lSDLmain -lSDL -lSDL_image -lGL -lGLU
endif
# - -------------------------------------------------------------------------------------------- - #

# - -------------------------------------------------------------------------------------------- - #
# Defines required for building ---------------------------------------------------------------- - #
# Example: _LZMA_PROB32 RICHARD
DEFINES			:=	EDITOR
# - -------------------------------------------------------------------------------------------- - #

# - -------------------------------------------------------------------------------------------- - #
INCLUDE_DIRS	:=	Code/Engine2D
# - -------------------------------------------------------------------------------------------- - #

# - -------------------------------------------------------------------------------------------- - #
# Directories to pull other code from ---------------------------------------------------------- - #
# Example: External/Lzma
CODE_DIRS		:=	Engine2D/DynamicComponent \
					Engine2D/Physics \
					Engine2D/PassiveObject \
					Engine2D/Impulse \
					Engine2D/StaticObject \
					Engine2D/Zone \
					Platform/GL/Graphics \
					External \
					Library/Geometry \
					Library/Math \
					Library/FileIO \
					Library/Util \
					Library/Animation \
# - -------------------------------------------------------------------------------------------- - #
# Explicit files from the source tree to grab (if directory masks aren't good enough) ---------- - #
# Example: External/Lzma/LzmaDecode.cpp
CODE_FILES		:=	Engine2D/Engine2D_Current.cpp \
# - -------------------------------------------------------------------------------------------- - #
