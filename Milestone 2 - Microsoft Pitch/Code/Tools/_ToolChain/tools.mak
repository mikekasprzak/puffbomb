# - -------------------------------------------------------------------------------------------- - #
BUILT_TOOLS		:=	Output/Tools
# - -------------------------------------------------------------------------------------------- - #

# - -------------------------------------------------------------------------------------------- - #
# Tools ---------------------------------------------------------------------------------------- - #
export TreeTool			:=	Tools/TreeTool
export PatternTool		:=	Tools/PatternTool
export Run				:=	sh Tools/run
export Compress			:=	Tools/lzma e

export MakeDir			:=	mkdir -p
export ChangeDir		:=	cd
export Remove			:=	rm -fr
export Touch			:=	touch

export Echo				:=	echo -en
# - -------------------------------------------------------------------------------------------- - #
export TextureTool		:=	$(BUILT_TOOLS)/TextureTool/TextureTool.exe
export Mesh3DTool		:=	$(BUILT_TOOLS)/Mesh3DBin/Mesh3DBin.exe
export ComponentTool	:=	$(BUILT_TOOLS)/ComponentTool/ComponentTool.exe
export CollectionTool	:=	$(BUILT_TOOLS)/CollectionTool/CollectionTool.exe
# - -------------------------------------------------------------------------------------------- - #
