// - ------------------------------------------------------------------------------------------ - //
// MenuManager //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __MenuFlow_PuffBOMB_MenuManager_H__
#define __MenuFlow_PuffBOMB_MenuManager_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Gui/WindowManager.h>
// - ------------------------------------------------------------------------------------------ - //
#include <ClassicSaveData.h>
// - ------------------------------------------------------------------------------------------ - //
class cMenuManager : public cWindowManager
{
public:
	cClassicSaveData* ClassicSaveData;

	bool BreakLoop;
	
	unsigned int CurForm;
	unsigned int LastForm;
	
	unsigned int SuperFlowState;
	
	int TransTime;
	Real LastZOffset;
	Real CurZOffset;
	
	int CurLevelPivot;
	int LevelsPerPage;
	int LevelsOnPage;
	
	Vector3D MiniMapTexVertex[ 4 ];
	Vector2D MiniMapTexUV[ 4 ];
	unsigned int MiniMapTexIndices[ 4 ];
	cTexture MiniMapTex;
	std::string MiniMapName;

public:
	cMenuManager( cClassicSaveData* _ClassicSaveData );
	~cMenuManager();

public:
	void Step();
	void Draw();

public:
	void UpdateMiniMap();
	
	void UpdateClassicLevelSelect();
	void CompletedTest( size_t idx, size_t LastTextLabelIdx );
	
};
// - ------------------------------------------------------------------------------------------ - //
#endif // MenuManager // 
// - ------------------------------------------------------------------------------------------ - //
