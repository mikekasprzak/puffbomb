# - -------------------------------------------------------------------------------------------- - #
BUILT_TOOLS		:=	Output/Tools
# - -------------------------------------------------------------------------------------------- - #

# - -------------------------------------------------------------------------------------------- - #
# Tools ---------------------------------------------------------------------------------------- - #
export TreeTool			:=	Tools/TreeTool
export PatternTool		:=	Tools/PatternTool
export Run				:=	sh Tools/run
export Compress			:=	Tools/lzma e
export NVTextureTool	:=	Tools/NVTextureTool/NVCompress

export MakeDir			:=	mkdir -p
export ChangeDir		:=	cd
export Remove			:=	rm -fr
export Touch			:=	touch
 
export Echo				:=	echo -en
# - -------------------------------------------------------------------------------------------- - #
export TextureTool		:=	$(BUILT_TOOLS)/TextureTool/TextureTool$(PROGRAM_SUFFIX)
export Mesh3DTool		:=	$(BUILT_TOOLS)/Mesh3DBin/Mesh3DBin$(PROGRAM_SUFFIX)
export ComponentTool	:=	$(BUILT_TOOLS)/ComponentTool/ComponentTool$(PROGRAM_SUFFIX)
export CollectionTool	:=	$(BUILT_TOOLS)/CollectionTool/CollectionTool$(PROGRAM_SUFFIX)
# - -------------------------------------------------------------------------------------------- - #
