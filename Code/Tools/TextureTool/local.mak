# - -------------------------------------------------------------------------------------------- - #
ifeq ($(HOST_PLATFORM),GL)
LIBS			:=	-Lmingw32/lib -lmingw32 -lSDLmain -lSDL -lSDL_image -lpng 
else
LIBS			:=	-lSDLmain -lSDL -lSDL_image -lpng 
endif
# - -------------------------------------------------------------------------------------------- - #
CODE_DIRS		:=	External/Lzma \
					Library/Util \
					Library/FileIO 
