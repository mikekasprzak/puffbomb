#ifdef EDITOR
// - ------------------------------------------------------------------------------------------ - //
#include "CollectionEdit.h"

#include <Graphics/Gfx.h>
#include <Input/Input.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Platform/Global.h>
// - ------------------------------------------------------------------------------------------ - //
using namespace Input;
// - ------------------------------------------------------------------------------------------ - //
cCollectionEdit::cCollectionEdit()
{

}
// - ------------------------------------------------------------------------------------------ - //
cCollectionEdit::~cCollectionEdit()
{


}
// - ------------------------------------------------------------------------------------------ - //
void cCollectionEdit::Draw()
{
	Gfx::EnableTex2D();
	Gfx::EnableBlend();
		

	Gfx::DisableTex2D();

	glLineWidth( 1.0 );

	DrawGrid( Camera, CurrentGridDepth, 40.0, true, GridDepth );
		
	Gfx::DisableBlend();
}
// - ------------------------------------------------------------------------------------------ - //
void cCollectionEdit::HudDraw()
{
	
}
// - ------------------------------------------------------------------------------------------ - //
void cCollectionEdit::Step()
{
	CurMousePos = CalcMousePos();

	if( Button[ MOUSE_1 ].Pressed() )
	{
		OldMousePos = CurMousePos;
	}

	// Handles scrolling around the map
	Scroll( Camera );
	
	// Handles the zooming in and out of a map
	Zoom( Real( 64.0 ), Camera );
}
// - ------------------------------------------------------------------------------------------ - //
Vector2D cCollectionEdit::CalcMousePos()
{
	Vector2D tempMousPos = Vector2D(
			Real( ( int( Mouse.x * Real( cGlobal::HudW ) ) )
			- ( -Camera->Pos.x / Real( Camera->Pos.z / cGlobal::HudZoom ) )
			- ( Real(cGlobal::HudW >> 1) ) )
			* Real( Camera->Pos.z / cGlobal::HudZoom ),
			Real( ( int( -Mouse.y * Real( cGlobal::HudH ) ) )
			+ ( Camera->Pos.y / Real( Camera->Pos.z / cGlobal::HudZoom ) )
			+ ( cGlobal::HudH >> 1 ) )
			* Real( Camera->Pos.z / cGlobal::HudZoom )
	);
	return tempMousPos;
}
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
