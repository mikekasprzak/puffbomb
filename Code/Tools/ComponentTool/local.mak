# - -------------------------------------------------------------------------------------------- - #
# Libraries to link against (including -l) ----------------------------------------------------- - #
LIBS			:=	-Lmingw32/lib -lmingw32 -lSDLmain -lSDL -lSDL_image -lopengl32 -lglu32
# - -------------------------------------------------------------------------------------------- - #

# - -------------------------------------------------------------------------------------------- - #
# Defines required for building ---------------------------------------------------------------- - #
# Example: _LZMA_PROB32 RICHARD
DEFINES			:=	EDITOR NODRAW
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
					External/Triangulate3 \
					Library/Geometry
# - -------------------------------------------------------------------------------------------- - #
# Explicit files from the source tree to grab (if directory masks aren't good enough) ---------- - #
# Example: External/Lzma/LzmaDecode.cpp
CODE_FILES		:=	Library/Util/ScriptParser.cpp \
					Platform/GL/Graphics/Gfx.cpp
# - -------------------------------------------------------------------------------------------- - #
