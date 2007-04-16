// - ------------------------------------------------------------------------------------------ - //
// MenuFlow //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __MenuFlow_PuffBOMB_MenuFlow_H__
#define __MenuFlow_PuffBOMB_MenuFlow_H__
// - ------------------------------------------------------------------------------------------ - //
#include <MessageEntity.h>
#include "MenuFlowEngine.h"
#include <ClassicSaveData.h>
// - ------------------------------------------------------------------------------------------ - //
class cMenuFlow : public cMessageEntity { 
public:
	cMenuFlowEngine* Engine;

public:
	cMenuFlow( const std::string& FileName, cClassicSaveData* _ClassicSaveData );
	~cMenuFlow();

public:
	void Step();
	void Draw();
};
// - ------------------------------------------------------------------------------------------ - //
#endif // MenuFlow // 
// - ------------------------------------------------------------------------------------------ - //
