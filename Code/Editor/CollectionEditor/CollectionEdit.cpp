#ifdef EDITOR
// - ------------------------------------------------------------------------------------------ - //
#include "CollectionEdit.h"

#include <Graphics/Gfx.h>
#include <Input/Input.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Global.h>
// - ------------------------------------------------------------------------------------------ - //
using namespace Input;
// - ------------------------------------------------------------------------------------------ - //
cCollectionEdit::cCollectionEdit()
{
	Camera->Pos.z = Global::HudZoom;
	
	Physics.ZeroGravity();
	
	Log( LOG_HIGHEST_LEVEL, "Collection editor physics created" );

	Collection.Component.push_back( Engine2D::cDynamicComponent() );
	
	Collection.Component[ 0 ].AnimationSet = new Engine2D::cComponentAnimationSet();
	
	Collection.Component[ 0 ].AnimationSet->LoadBinary( "2D/Hamster/Body/HamsterBody.bin.comp" );

	Collection.Component[ 0 ].Body = Collection.Component[ 0 ].AnimationSet->BodyPose[ 0 ];

		
}
// - ------------------------------------------------------------------------------------------ - //
cCollectionEdit::~cCollectionEdit()
{

}
// - ------------------------------------------------------------------------------------------ - //
void cCollectionEdit::Draw()
{
	Camera->Update();
	
	Gfx::EnableTex2D();
	Gfx::DisableDepth();
	Gfx::EnableBlend();

	Gfx::DisableTex2D();

	// Draw our collection //
	Collection.Draw();
	Collection.DebugDraw();

	Gfx::SetLineWidth( 1.0 );

	DrawGrid( Camera, CurrentGridDepth, 40.0, true, GridDepth );
	
		
	DrawSelBox();

	Gfx::DisableBlend();
	
	HudDraw();
}
// - ------------------------------------------------------------------------------------------ - //
void cCollectionEdit::HudDraw()
{
	HudCamera->Update();
	
	Gfx::EnableTex2D();
	Gfx::EnableBlend();
	
	DisplayText();
	
	Gfx::DisableBlend();	
	Gfx::DisableTex2D();
}
// - ------------------------------------------------------------------------------------------ - //
void cCollectionEdit::Step()
{
	// Makes my physics active //
	Physics.SetActive();
	// Step our collection (intenal physics system, based on physics above) //
	Collection.Step();
	
	CurMousePos = CalcMousePos();

	if( Button[ MOUSE_1 ].Pressed() )
	{
		OldMousePos = CurMousePos;
	}

	// Handles scrolling around the map
	Scroll( Camera );
	
	// Handles the zooming in and out of a map
	Zoom( Real( 64.0 ), Camera );
	
	Undo();
}
// - ------------------------------------------------------------------------------------------ - //
Vector2D cCollectionEdit::CalcMousePos()
{
	Vector2D tempMousPos = Vector2D(
			Real( ( int( Mouse.x * Real( Global::HudW ) ) )
			- ( -Camera->Pos.x / Real( Camera->Pos.z / Global::HudZoom ) )
			- ( Real(Global::HudW >> 1) ) )
			* Real( Camera->Pos.z / Global::HudZoom ),
			Real( ( int( -Mouse.y * Real( Global::HudH ) ) )
			+ ( Camera->Pos.y / Real( Camera->Pos.z / Global::HudZoom ) )
			+ ( Global::HudH >> 1 ) )
			* Real( Camera->Pos.z / Global::HudZoom )
	);
	return tempMousPos;
}
// - ------------------------------------------------------------------------------------------ - //
void cCollectionEdit::Undo()
{
	// Resets the zoom
	if ( Button[ KEY_TAB ].Pressed() )
	{
		Camera->Pos.x = 0.0;
		Camera->Pos.y = 0.0;
		Camera->Pos.z = Global::HudZoom;
		
		Camera->View.x = Camera->Pos.x;
		Camera->View.y = Camera->Pos.y;
		Camera->View.z = 0.0;
	}	
}
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
