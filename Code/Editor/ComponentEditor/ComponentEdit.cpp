#ifdef EDITOR
// - ------------------------------------------------------------------------------------------ - //
#include "ComponentEdit.h"

#include <Graphics/Gfx.h>
#include <Input/Input.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Platform/Global.h>
// - ------------------------------------------------------------------------------------------ - //
using namespace Input;
// - ------------------------------------------------------------------------------------------ - //
cComponentEdit::cComponentEdit() :
	CurObj( 0 ),
	CurPose( 0 ),
	NodeRadius( 3 )
{
	// Create Cameras //
	UVCamera = new cCamera(
		Vector3D( 128.0, 128.0, 400.0 ),				// Pos
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
	
	Real PreviewHeight = UVHeight;

	if( Platform::AspectRatio < Real( 0.79 ) )
	{
		PreviewHeight = 0.75;
		
		UVWidth = 0.33;
		UVHeight = 0.25;
	}
	
	PreviewCamera = new cCamera(
		Vector3D( 0.0, 0.0, cGlobal::HudZoom * ( Real( 1 ) - PreviewHeight ) ),		// Pos
		Vector3D( 0.0, 0.0, 0.0 ),					// View
		Vector3D( 0.0, 1.0, 0.0 ),					// Up
		45.0,										// Field of View
		Platform::AspectRatio,						// Aspect Ratio
		1.0,										// NearClip
		100000.0,									// FarClip
		cGlobal::HudZoom,							// MinZoom
		cGlobal::HudZoom,							// MaxZoom
		cGlobal::HudZoom							// HudZoom
	);
	
	Camera->Pos.z = Real( 800.0 );

	GridSize = 2048.0;
	

	DynObj.push_back( Engine2D::cDynamicObject() );
	DynObj[ 0 ].AnimationSet = new Engine2D::cComponentAnimationSet();
	DynObj[ 0 ].AnimationSet->Pose.push_back( Engine2D::cBody2DPose() );
		
	DynObj[ 0 ].Body = DynObj[ 0 ].AnimationSet->Pose[ 0 ];
	Pose = &DynObj[ 0 ].AnimationSet->Pose[ 0 ];
/*
	DynObj[ 0 ].Body.AddNode();
	DynObj[ 0 ].Body.AddNode();
	DynObj[ 0 ].Body.AddNode();

	DynObj[ 0 ].Body.SetPos( 0, Vector2D( 50.0, 20.0 ) );
	DynObj[ 0 ].Body.SetPos( 1, Vector2D( 20.0, 50.0 ) );
*/
	CurMode = NODE_MODE;
}
// - ------------------------------------------------------------------------------------------ - //
cComponentEdit::~cComponentEdit()
{
	delete UVCamera;
	delete PreviewCamera;
	
	delete DynObj[ 0 ].AnimationSet;
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::Draw()
{
	Gfx::EnableTex2D();
	Gfx::EnableBlend();

	// Draw Mesh2D stuff here //


	Gfx::DisableTex2D();

	glLineWidth( 1.0 );
	
	if( !isGroupMove )
	{
		if( CheckViewOne() )
		{
			DrawSelBox();
		}
	}
	
	DrawGrid( Camera, CurrentGridDepth, 40.0, true, GridDepth );	
		
	// Draw nodes //
	for( size_t idx = 0; idx < Pose->Node.size(); ++idx )
	{
		DynObj[ CurObj ].Body.DrawNode( idx, false );
	}
	// Draw selected nodes //
	for( size_t idx = 0; idx < CurSelected.size(); ++idx )
	{
		DynObj[ CurObj ].Body.DrawNode( CurSelected[ idx ], true );
	}
	// Draw spheres //
	for( size_t idx = 0; idx < DynObj[ CurObj ].Body.SphereSize(); ++idx )
	{
		DynObj[ CurObj ].Body.DrawSphere( idx, false );
	}
	// Draw selected spheres //
	for( size_t idx = 0; idx < CurSelected.size(); ++idx )
	{
		for( size_t SphereIdx = 0; SphereIdx < DynObj[ CurObj ].Body.SphereSize(); ++SphereIdx )
		{
			if( CurSelected[idx] == DynObj[ CurObj ].Body.Sphere( SphereIdx ).Index )
			{
				DynObj[ CurObj ].Body.DrawSphere( SphereIdx, true );
			}
		}
	}
	// Draw springs //
	for( size_t idx = 0; idx < DynObj[ CurObj ].Body.SpringSize(); ++idx )
	{
		DynObj[ CurObj ].Body.DrawSpring( idx, false );
	}
	// Draw selected springs //
	for( size_t SpringIdx = 0; SpringIdx < DynObj[ CurObj ].Body.SpringSize(); ++SpringIdx )
	{
		for( size_t idx = 0; idx < CurSelected.size(); ++idx )
		{
			for( size_t i = idx + 1; i < CurSelected.size(); ++i )
			{
				if( DynObj[ CurObj ].Body.Spring( SpringIdx ).IndexA == CurSelected[idx] )
				{
					if( DynObj[ CurObj ].Body.Spring( SpringIdx ).IndexB == CurSelected[i] )
					{
						DynObj[ CurObj ].Body.DrawSpring( SpringIdx, true );
					}
				}
				if( DynObj[ CurObj ].Body.Spring( SpringIdx ).IndexB == CurSelected[idx] )
				{
					if( DynObj[ CurObj ].Body.Spring( SpringIdx ).IndexA == CurSelected[i] )
					{
						DynObj[ CurObj ].Body.DrawSpring( SpringIdx, true );
					}
				}
			}	
		}
	}

	Gfx::DisableBlend();
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::HudDraw()
{
	Gfx::EnableTex2D();
	Gfx::EnableBlend();
	
	DisplayText();
	
//	//  DISPLAYS FPS  //
//	std::stringstream Temp;
//	Temp << Platform::FPS;
//	std::string TempString = Temp.str();
//	
//	Vector3D TempPos = Vector3D( cGlobal::Left, cGlobal::Top - Real( 45 ), 0.0 );
//
//	cFonts::FlangeLight.Write( TempString, TempPos, Real( 1.0 ), Gfx::RGBA( 184, 0, 0, 255 ) );
//	// -------------- //
	Gfx::DisableBlend();
	Gfx::DisableTex2D();
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::PreviewDraw()
{
	
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::UVDraw()
{
	glLineWidth( 1.0 );
	
	Gfx::EnableTex2D();
	Gfx::EnableBlend();
	
	Gfx::DisableTex2D();
	
	if( !isGroupMove )
	{
		if( CheckViewThree( UVHeight ) )
		{
			DrawSelBox();
		}
	}

	DrawGrid( UVCamera, CurrentGridDepth, 40.0, true, GridDepth );

	Gfx::DisableBlend();
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::Step()
{
	if( CheckViewOne() )
	{
		CurView = 1;
		CurMousePos = CalcMousePos();

		if( Button[ MOUSE_1 ].Pressed() )
		{
			OldMousePos = CurMousePos;
		}

		// Handles scrolling around the map
		if( Platform::AspectRatio < Real( 0.79 ) )
		{
			Scroll( Camera, Real( 1.33 ), Real( 1.33 ), Vector2D( cGlobal::HudZoom, cGlobal::HudZoom ) );
		}
		else
		{
			Scroll( Camera );
		}
		
		if( !Button[ KEY_LSHIFT ] && !Button[ KEY_LCTRL ] )
		{
			// Handles the zooming in and out of a map
			Zoom( Real( 32.0 ), Camera );
		}	
		if( CurMode == NODE_MODE )
		{
			if( !isGroupMove )
			{
				BodySelectNode();
			
				BodyAddNode();
				
				BodyDeleteNode();
				
				if( Button[ KEY_LSHIFT ] )
				{
					BodyMass( Real( 0.1 ) );
				}
				else
				{
					BodyMass( Real( 1 ) );
				}
			}
			BodyMoveNode();

			BodyScaleNode();
		}
		else if( CurMode == SPHERE_MODE )
		{
			if( !isGroupMove )
			{
				BodySelectNode();
			
				BodyAddSphere();
				
				BodyDeleteSphere();
					
				if( Button[ KEY_LSHIFT ] )
				{
					BodyRadius( Real( 0.1 ) );
				}
				else
				{
					BodyRadius( Real( 1 ) );
				}
			}
			BodyMoveNode();
		}
		else if( CurMode == SPRING_MODE )
		{
			BodySelectNode();
			
			BodyAddSpring();

			BodyDeleteSpring();
		}
	}
	else if( CheckViewTwo( UVHeight ) )
	{
		CurView = 2;
		CurMousePos = CalcMousePos();

		if( Platform::AspectRatio < Real( 0.79 ) )
		{
			Scroll( PreviewCamera, Real( 0.325 ), Real( 0.25 ), Vector2D( UVZoomOffsetX, UVZoomOffsetY ) );
		}
		else
		{
			Scroll(
				PreviewCamera,
				Real( UVWidth * Real( Real( 1 ) + UVWidth ) / Real( 2 ) ),
				Real( UVHeight * Real( Real( 1 ) + UVHeight ) / Real( 2 ) ),
				Vector2D( UVZoomOffsetX, UVZoomOffsetY )
			);
		}
		// Handles the zooming in and out of the preview
		Zoom( Real( 32.0 ), PreviewCamera );
	}
	else if( CheckViewThree( UVHeight ) )
	{
		CurView = 3;
		CurMousePos = CalcUVMousePos();
		
		if( Button[ MOUSE_1 ].Pressed() )
		{
			OldMousePos = CurMousePos;
		}

		// Handles scrolling around the map
		if( Platform::AspectRatio < Real( 0.79 ) )
		{
			Scroll( UVCamera, Real( 0.33 ), Real( 0.25 ), Vector2D( UVZoomOffsetX, UVZoomOffsetY ) );
		}
		else
		{
			Scroll( UVCamera, UVWidth, UVHeight, Vector2D( UVZoomOffsetX, UVZoomOffsetY ) );
		}

		// Handles the zooming in and out of a map
		Zoom( Real( 32.0 ), UVCamera );
	}

	if( CurMode == COMPONENT_MODE )
	{
		BodyAddPose();
		BodyDeletePose();
	}		
	
	Undo();
	
	SwitchMode();
	SwitchPose();
	
	LastView = CurView;
}
// - ------------------------------------------------------------------------------------------ - //
Vector2D cComponentEdit::CalcMousePos()
{
	Vector2D tempMousPos;
	if( Platform::AspectRatio < Real( 0.79 ) )
	{
		tempMousPos = Vector2D(
				Real( ( int( Mouse.x * Real( cGlobal::HudW * Real( 1.33 ) ) ) )
				- ( -Camera->Pos.x / Real( Camera->Pos.z / cGlobal::HudZoom ) )
				- ( ( Real(cGlobal::HudW) * Real( 1.33 ) ) / Real(2) ) )
				* Real( Camera->Pos.z / cGlobal::HudZoom ),
				Real( ( int( -Mouse.y * Real( cGlobal::HudH * Real( 1.33 ) ) ) )
				+ ( Camera->Pos.y / Real( Camera->Pos.z / cGlobal::HudZoom ) )
				+ ( ( Real(cGlobal::HudH * Real( 0.75 ) ) * Real( 1.33 ) ) / Real(2) ) )
				* Real( Camera->Pos.z / cGlobal::HudZoom )
		);
	}
	else
	{
		tempMousPos = Vector2D(
				Real( ( int( Mouse.x * Real( cGlobal::HudW ) ) )
				- ( -Camera->Pos.x / Real( Camera->Pos.z / cGlobal::HudZoom ) )
				- ( ( Real(cGlobal::HudW) * Real( 0.75 ) ) / Real(2) ) )
				* Real( Camera->Pos.z / cGlobal::HudZoom ),
				Real( ( int( -Mouse.y * Real( cGlobal::HudH ) ) )
				+ ( Camera->Pos.y / Real( Camera->Pos.z / cGlobal::HudZoom  ) )
				+ ( cGlobal::HudH >> 1 ) )
				* Real( Camera->Pos.z / cGlobal::HudZoom )
		);
	}
	
	return tempMousPos;
}
// - ------------------------------------------------------------------------------------------ - //
Vector2D cComponentEdit::CalcUVMousePos()
{
	Vector2D tempMousPos;
	if( Platform::AspectRatio < Real( 0.79 ) )
	{
		tempMousPos = Vector2D(
			Real( ( int( Mouse.x * Real( cGlobal::HudW * Real( 0.33 ) ) ) )
			- ( -UVCamera->Pos.x / Real( UVCamera->Pos.z / UVZoomOffsetX ) )
			- ( ( Real(cGlobal::HudW) * Real( 0.33 ) ) ) )
			* Real( UVCamera->Pos.z / UVZoomOffsetX ) / UVScale + Real( 1 )
			+ ( ( UVCamera->Pos.z - Real( 122 ) ) / Real( 122 ) ),
			Real( ( int( -Mouse.y * Real( cGlobal::HudH ) * Real( 0.25 ) )
			+ ( UVCamera->Pos.y / Real( UVCamera->Pos.z / UVZoomOffsetY ) )
			+ ( ( cGlobal::HudH * Real( 0.25 ) ) ) )
			* Real( UVCamera->Pos.z / UVZoomOffsetY ) ) / UVScale - Real( 1 )
			- ( ( UVCamera->Pos.z - Real( 611 ) ) / Real( 611 ) )
		);
	}
	else
	{
		tempMousPos =  Vector2D(
			Real( ( int( Mouse.x * Real( cGlobal::HudW * UVWidth ) ) )
			- ( -UVCamera->Pos.x / Real( UVCamera->Pos.z / UVZoomOffsetX ) )
			- ( ( Real(cGlobal::HudW) * UVWidth ) ) )
			* Real( UVCamera->Pos.z / UVZoomOffsetX ) / UVScale + Real( 1 )
			+ ( ( UVCamera->Pos.z - Real( 611 ) ) / Real( 611 ) ),
			Real( ( int( -Mouse.y * Real( cGlobal::HudH ) * UVHeight )
			+ ( UVCamera->Pos.y / Real( UVCamera->Pos.z / UVZoomOffsetY ) )
			+ ( ( cGlobal::HudH * UVHeight ) ) )
			* Real( UVCamera->Pos.z / UVZoomOffsetY ) ) / UVScale - Real( 1 )
			- ( ( UVCamera->Pos.z - Real( 618 ) ) / Real( 618 ) )
		);
	}

	tempMousPos *= UVScale;

	return tempMousPos;
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::Undo()
{
	// Resets the zoom
	if ( Button[ KEY_TAB ].Pressed() )
	{
		Camera->Pos.x = 0.0;
		Camera->Pos.y = 0.0;
		Camera->Pos.z = Real( 800.0 );
		
		Camera->View.x = Camera->Pos.x;
		Camera->View.y = Camera->Pos.y;
		Camera->View.z = 0.0;

		UVCamera->Pos.x = 128.0;
		UVCamera->Pos.y = 128.0;
		UVCamera->Pos.z = 400.0;
		
		UVCamera->View.x = UVCamera->Pos.x;
		UVCamera->View.y = UVCamera->Pos.y;
		UVCamera->View.z = 0.0;

		PreviewCamera->Pos.x = 0.0;
		PreviewCamera->Pos.y = 0.0;
		if( Platform::AspectRatio < Real( 0.79 ) )
		{
			PreviewCamera->Pos.z = cGlobal::HudZoom * ( Real( 1 ) - Real( 0.75 ) );
		}
		else
		{
			PreviewCamera->Pos.z = cGlobal::HudZoom * ( Real( 1 ) - UVHeight );
		}	
		
		PreviewCamera->View.x = PreviewCamera->Pos.x;
		PreviewCamera->View.y = PreviewCamera->Pos.y;
		PreviewCamera->View.z = 0.0;
	}	
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::ActiveAction()
{
	
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::SwitchMode()
{	
	unsigned int LastMode = CurMode;
	
	if( Button[ KEY_1 ].Pressed() )
	{
		CurMode = NODE_MODE;
	}
	else if( Button[ KEY_2 ].Pressed() )
	{
		CurMode = SPHERE_MODE;
	}
	else if( Button[ KEY_3 ].Pressed() )
	{
		CurMode = SPRING_MODE;
	}
	else if( Button[ KEY_0 ].Pressed() )
	{
		CurMode = COMPONENT_MODE;	
	} 
	if( LastMode <= SPRING_MODE && CurMode <= SPRING_MODE )
	{
		
	}
	else
	{
		CurSelected.clear();
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::BodyAddPose()
{
	if( Button[ KEY_0_PAD ].Pressed() || Button[ KEY_A ].Pressed() )
	{
		std::vector< Engine2D::cBody2DPose > TempPose;
		for( size_t idx = 0; idx < DynObj[ CurObj ].AnimationSet->Pose.size(); ++idx )
		{
			TempPose.push_back( DynObj[ CurObj ].AnimationSet->Pose[ idx ] );
			
			if( idx == CurPose )
			{
				TempPose.push_back( DynObj[ CurObj ].AnimationSet->Pose[ CurPose ] );
			}
		}
		DynObj[ CurObj ].AnimationSet->Pose.clear();
		DynObj[ CurObj ].AnimationSet->Pose.swap( TempPose );
		
		CurPose++;
	
		DynObj[ CurObj ].Body = DynObj[ CurObj ].AnimationSet->Pose[ CurPose ];
		Pose = &DynObj[ CurObj ].AnimationSet->Pose[ CurPose ];

		CurMode = NODE_MODE;
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::BodyDeletePose()
{
	if( Button[ KEY_DELETE ].Pressed() && DynObj[ CurObj ].AnimationSet->Pose.size() > 1 )
	{
		std::vector< Engine2D::cBody2DPose > TempPose;
		for( size_t idx = 0; idx < DynObj[ CurObj ].AnimationSet->Pose.size(); ++idx )
		{
			if( idx != CurPose )
			{
				TempPose.push_back( DynObj[ CurObj ].AnimationSet->Pose[ idx ] );
			}
		}
		DynObj[ CurObj ].AnimationSet->Pose.clear();
		DynObj[ CurObj ].AnimationSet->Pose.swap( TempPose );
		
		CurPose = DynObj[ CurObj ].AnimationSet->Pose.size() - 1;
	
		DynObj[ CurObj ].Body = DynObj[ CurObj ].AnimationSet->Pose[ CurPose ];
		Pose = &DynObj[ CurObj ].AnimationSet->Pose[ CurPose ];
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::SwitchPose()
{
	if ( Button[ KEY_LEFT ].Pressed() )
	{
		if( CurPose > 0 )
		{
			--CurPose;
		}
		else
		{
			CurPose = DynObj[ CurObj ].AnimationSet->Pose.size() - 1;
		}
		
		DynObj[ CurObj ].Body = DynObj[ CurObj ].AnimationSet->Pose[ CurPose ];
		Pose = &DynObj[ CurObj ].AnimationSet->Pose[ CurPose ];
		CurSelected.clear();
	}
	else if ( Button[ KEY_RIGHT ].Pressed() )
	{
		if( CurPose < DynObj[ CurObj ].AnimationSet->Pose.size() - 1 )
		{
			++CurPose;
		}
		else
		{
			CurPose = 0;	
		}
		
		DynObj[ CurObj ].Body = DynObj[ CurObj ].AnimationSet->Pose[ CurPose ];
		Pose = &DynObj[ CurObj ].AnimationSet->Pose[ CurPose ];
		CurSelected.clear();
	}
}
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
