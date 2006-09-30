// - ------------------------------------------------------------------------------------------ - //
#include "SplashScreen.h"
// - ------------------------------------------------------------------------------------------ - //
#include <Graphics/Gfx.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Global.h>
#include <Platform/Global.h>
#include <Input/Input.h>
// - ------------------------------------------------------------------------------------------ - //
//extern int GetTime();
// - ------------------------------------------------------------------------------------------ - //
cSplashScreen::cSplashScreen() :
	Color( 0 ),
	Tex( "Textures/Menu/Sykhronics.pack.tx" )
{
	// Create Camera //
	Camera = new cCamera(
		Vector3D( 0.0, 0.0, cGlobal::HudZoom ),			// Pos
		Vector3D( 0.0, 0.0, 0.0 ),						// View
		Vector3D( 0.0, 1.0, 0.0 ),						// Up
		45.0,											// Field of View
		Platform::AspectRatio,							// Aspect Ratio
		1.0,											// NearClip
		100000.0,										// FarClip
		cGlobal::HudZoom,								// MinZoom
		cGlobal::HudZoom,								// MaxZoom
		cGlobal::HudZoom								// HudZoom
	 );

	int EndTime = 3600;
	
	Real HalfWidth = Tex.Width / 2;
	Real HalfHeight = Tex.Height / 2;

	TexVertex[0] = Vector3D( -HalfWidth, -HalfHeight, 0.0 );
	TexVertex[1] = Vector3D( HalfWidth, -HalfHeight, 0.0 );
	TexVertex[2] = Vector3D( HalfWidth, HalfHeight, 0.0 );
	TexVertex[3] = Vector3D( -HalfWidth, HalfHeight, 0.0 );

	TexUV[0] = Vector2D( 0.0, 1.0 );
	TexUV[1] = Vector2D( 1.0, 1.0 );
	TexUV[2] = Vector2D( 1.0, 0.0 );
	TexUV[3] = Vector2D( 0.0, 0.0 );

	TexIndices[0] = 0;
	TexIndices[1] = 1;
	TexIndices[2] = 2;
	TexIndices[3] = 3;

	Gfx::EnableTex2D();
	Gfx::EnableBlend();

	Work( EndTime );
	
	Gfx::DisableTex2D();
	Gfx::DisableBlend();
	
	Gfx::DeleteTexture( Tex.Id );
	
}
cSplashScreen::~cSplashScreen()
{
	delete Camera;
}
// - ------------------------------------------------------------------------------------------ - //
void cSplashScreen::Draw()
{
	Gfx::ClearColorDepth();

	Camera->Update();

	Gfx::DrawQuads(
		&TexVertex[0],
		&TexUV[0],
		TexIndices,
		4,
		Tex.Id,
		Gfx::RGBA( Color, Color, Color, 255 )
	); 
}
// - ------------------------------------------------------------------------------------------ - //
void cSplashScreen::Step()
{
	if( Color < 255 )
	{
		Color += 3;
	}
	if( Color > 255 )
	{
		Color = 255;
	}
}
// - ------------------------------------------------------------------------------------------ - //
