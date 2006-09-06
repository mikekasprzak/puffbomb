#ifdef EDITOR
// - ------------------------------------------------------------------------------------------ - //
#include "ComponentEdit.h"

#include <Graphics/Gfx.h>
#include <Input/Input.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Platform/Global.h>

// For FPS test //
//#include <Platform/Global.h>
//#include <Font/Fonts.h>
//#include <sstream>
// ------------ //
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>

// - ------------------------------------------------------------------------------------------ - //
using namespace Input;
// - ------------------------------------------------------------------------------------------ - //
cComponentEdit::cComponentEdit() :
	CurObj( 0 ),
	CurPose( 0 ),
	//CurMeshPose( 0 ),
	CurMeshFrame( 0 ),
	CurMeshAnim( 0 ),
	CurTexPreview( 0 ),
	NodeRadius( 6 ),
	AnimationGenerator( "../../../../Content/PuffBOMB/2D/Hamster/Body/" )
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
	
/*	DynObj.push_back( Engine2D::cDynamicComponent() );
	DynObj[ 0 ].AnimationSet = new Engine2D::cComponentAnimationSet();
	DynObj[ 0 ].AnimationSet->BodyPose.push_back( Engine2D::cBody2DPose() );
		
	DynObj[ 0 ].Body = DynObj[ 0 ].AnimationSet->BodyPose[ 0 ];
	Pose = &DynObj[ 0 ].AnimationSet->BodyPose[ 0 ];
	
	DynObj[ 0 ].AnimationSet->MeshPose.push_back( Engine2D::cMesh2DPose() );
*/
	TextureID.clear();
	TextureName.clear();
	
	LoadComp();
	
	LoadCompTextures();
	
	if( !TextureName.empty() )
	{
		//Real TempTexWidth = TexturePool.GetWidth( TextureName[ CurTexPreview ] ) / 2;
		//Real TempTexHeight = TexturePool.GetHeight( TextureName[ CurTexPreview ] ) / 2;
		
		Real TempTexWidth = 256;
		Real TempTexHeight = 256;
	
		PreviewTexVertex[0] = Vector3D( -TempTexWidth, -TempTexHeight, 0.0 );
		PreviewTexVertex[1] = Vector3D( TempTexWidth, -TempTexHeight, 0.0 );
		PreviewTexVertex[2] = Vector3D( TempTexWidth, TempTexHeight, 0.0 );
		PreviewTexVertex[3] = Vector3D( -TempTexWidth, TempTexHeight, 0.0 );

	}


	Real GridDepthValue = 0.5;
	
	for( int idx = 0; idx < 13; ++idx )
	{
		UVGridDepth[idx] = GridDepthValue;
		
		GridDepthValue *= Real(2.0);
	}

	CurMode = NODE_MODE;
	
}
// - ------------------------------------------------------------------------------------------ - //
cComponentEdit::~cComponentEdit()
{
	delete UVCamera;
	delete PreviewCamera;
	
	delete DynObj[ 0 ].AnimationSet;
	
//	delete AnimationGenerator;
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::Draw()
{
	Gfx::EnableTex2D();
	Gfx::EnableBlend();

	// Draw preview texture //
	if( !TextureName.empty() )
	{
		if( !AnimationGenerator.Animation[ CurMeshAnim ].Frame.empty() )
		{
			Gfx::DrawQuads(
				&PreviewTexVertex[0],
				&TexUV[0],
				TexIndices,
				4,
				TextureID[ AnimationGenerator.Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].ImageIndex ],
				Gfx::RGBA( 255, 255, 255, 64 )
			);
		}
	}
	Gfx::DisableTex2D();

	glLineWidth( 1.0 );

	Gfx::Rect(
			PreviewTexVertex[0],
			PreviewTexVertex[2],
			Gfx::RGBA( 64, 255, 64, 255 )
	);

	if( !isGroupMove )
	{
		if( CheckViewOne() )
		{
			DrawSelBox();
		}
	}
	
	DrawGrid( Camera, CurrentGridDepth, 32.0, true, UVGridDepth );
	
	// Draw nodes //
	for( size_t idx = 0; idx < Pose->Node.size(); ++idx )
	{
		DynObj[ CurObj ].Body.DrawNode( idx, false );
	}
	// Draw spheres //
	for( size_t idx = 0; idx < DynObj[ CurObj ].Body.SphereSize(); ++idx )
	{
		DynObj[ CurObj ].Body.DrawSphere( idx, false );
	}
	// Draw springs //
	for( size_t idx = 0; idx < DynObj[ CurObj ].Body.SpringSize(); ++idx )
	{
		DynObj[ CurObj ].Body.DrawSpring( idx, false );
	}
	// Draw mesh nodes //
//	for( size_t idx = 0; idx < DynObj[ CurObj ].AnimationSet->MeshPose[ CurMeshPose ].Node.size(); ++idx )
	for( size_t idx = 0; idx < DynObj[ CurObj ].AnimationSet->MeshPose[
								DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].MeshPoseIndex 
								].Node.size(); ++idx )
	{
		Gfx::Circle(
			DynObj[ CurObj ].AnimationSet->MeshPose[ DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].MeshPoseIndex ].Node[ idx ].Pos,
			Real( 3 ),
			Gfx::RGBA(128, 128, 192, 192)
		);
	}
	// Draw faces //
	int LineColor = Gfx::RGBA(192, 192, 255, 192);
	
	for( size_t idx = 0; idx < DynObj[ CurObj ].AnimationSet->MeshPose[ DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].MeshPoseIndex ].Face.size(); ++idx )
	{
		Gfx::Line(
			DynObj[ CurObj ].AnimationSet->MeshPose[ DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].MeshPoseIndex ].Node[
				DynObj[ CurObj ].AnimationSet->MeshPose[ DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].MeshPoseIndex ].Face[ idx ].a
			].Pos,
			DynObj[ CurObj ].AnimationSet->MeshPose[ DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].MeshPoseIndex ].Node[
				DynObj[ CurObj ].AnimationSet->MeshPose[ DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].MeshPoseIndex ].Face[ idx ].b
			].Pos,
			LineColor
		);

		Gfx::Line(
			DynObj[ CurObj ].AnimationSet->MeshPose[ DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].MeshPoseIndex ].Node[
				DynObj[ CurObj ].AnimationSet->MeshPose[ DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].MeshPoseIndex ].Face[ idx ].b
			].Pos,
			DynObj[ CurObj ].AnimationSet->MeshPose[ DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].MeshPoseIndex ].Node[
				DynObj[ CurObj ].AnimationSet->MeshPose[ DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].MeshPoseIndex ].Face[ idx ].c
			].Pos,
			LineColor
		);

		Gfx::Line(
			DynObj[ CurObj ].AnimationSet->MeshPose[ DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].MeshPoseIndex ].Node[
				DynObj[ CurObj ].AnimationSet->MeshPose[ DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].MeshPoseIndex ].Face[ idx ].c
			].Pos,
			DynObj[ CurObj ].AnimationSet->MeshPose[ DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].MeshPoseIndex ].Node[
				DynObj[ CurObj ].AnimationSet->MeshPose[ DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].MeshPoseIndex ].Face[ idx ].a
			].Pos,
			LineColor
		);
	}
	
	if( CurMode <= SPRING_MODE )
	{
		// Draw selected nodes //
		for( size_t idx = 0; idx < CurSelected.size(); ++idx )
		{
			DynObj[ CurObj ].Body.DrawNode( CurSelected[ idx ], true );
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
	}
	else if( CurMode == MESH_NODE_MODE || CurMode == PIVOT_HANDLE_MODE || CurMode == FACE_MODE )
	{
		// Draw selcted mesh nodes //
		for( size_t idx = 0; idx < CurSelected.size(); ++idx )
		{
			Gfx::Circle(
				DynObj[ CurObj ].AnimationSet->MeshPose[ DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].MeshPoseIndex ].Node[ CurSelected[idx] ].Pos,
				Real( 3 ),
				Gfx::RGBA(192, 192, 255, 192)
			);
		}
		
		if( CurMode != FACE_MODE )
		{
			if( !CurSelected.empty() && DynObj[ CurObj ].Body.Nodes.Size() > 1 )
			{
				Vector2D TempPos = DynObj[ CurObj ].Body.Nodes.Pos( 
					DynObj[ CurObj ].AnimationSet->MeshPose[ DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].MeshPoseIndex ].Node[ CurSelected[0] ].PivotIndex
				);
	
				Gfx::Circle(
					TempPos,
					Real( 3 ),
					Gfx::RGBA(255, 128, 255, 192)
				);
				
				TempPos = DynObj[ CurObj ].Body.Nodes.Pos( 
					DynObj[ CurObj ].AnimationSet->MeshPose[ DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].MeshPoseIndex ].Node[ CurSelected[0] ].HandleIndex
				);
				
				Gfx::Circle(
					TempPos,
					Real( 3 ),
					Gfx::RGBA(128, 255, 255, 192)
				);
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
	glLineWidth( 1.0 );
	
	Gfx::EnableTex2D();
	Gfx::EnableBlend();
	// Draw the Mesh2D //
	

	if( !DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame.empty() )
	{
		DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].Mesh.Draw( DynObj[ CurObj ].Body );
	}

	Gfx::DisableTex2D();

	// Draw the Body2D debug information //	
	DynObj[ CurObj ].Body.DrawNodes();
	DynObj[ CurObj ].Body.DrawSpheres();
	DynObj[ CurObj ].Body.DrawSprings();
		
	Gfx::DisableBlend();

}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::UVDraw()
{
	glLineWidth( 1.0 );
	
	Gfx::EnableTex2D();
	Gfx::EnableBlend();

	if( !TextureName.empty() )
	{
		if( !AnimationGenerator.Animation[ CurMeshAnim ].Frame.empty() )
		{
			Gfx::DrawQuads(
				&TexVertex[0],
				&TexUV[0],
				TexIndices,
				4,
				TextureID[ AnimationGenerator.Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].ImageIndex ],
				Gfx::White()
			);
		}
	}
	
	Gfx::DisableTex2D();
	
	if( !isGroupMove )
	{
		if( CheckViewThree( UVHeight ) )
		{
			DrawSelBox();
		}
	}

	DrawGrid( UVCamera, CurrentGridDepth, 32.0, true, UVGridDepth );

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
		else if( CurMode == MESH_NODE_MODE )
		{
			if( !isGroupMove )
			{
				MeshSelectNode();
			
				MeshAddNode();
				
				MeshDeleteNode();

			}
			MeshMoveNode();

			MeshScaleNode();
		}
		else if( CurMode == PIVOT_HANDLE_MODE )
		{
			MeshSetPivot();
			MeshSetHandle();
		}
		else if( CurMode == FACE_MODE )
		{
			MeshSelectNode();
			
			MeshAddFace();
			MeshDeleteFace();
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

/*	if( ( CurMode == NODE_MODE ) || ( CurMode == SPHERE_MODE ) || ( CurMode == SPRING_MODE ) )
	{
		SwitchTexture();	
	}*/
	else if( CurMode == COMPONENT_MODE )
	{
		BodyAddPose();
		BodyDeletePose();
	}
	
	Undo();
	
	SwitchMode();
	SwitchPose();
	SwitchMeshAnim();
	SwitchMeshPose();
	SwitchMeshFrame();
	
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
	if( CurMode == MESH_NODE_MODE || CurMode == FACE_MODE )
	{
		MeshGenerateUV();
	}
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
	else if( Button[ KEY_4 ].Pressed() )
	{
		CurMode = MESH_NODE_MODE;
	}
	else if( Button[ KEY_5 ].Pressed() )
	{
		CurMode = PIVOT_HANDLE_MODE;
	}
	else if( Button[ KEY_6 ].Pressed() )
	{
		CurMode = FACE_MODE;
	}
	else if( Button[ KEY_0 ].Pressed() )
	{
		CurMode = COMPONENT_MODE;	
	} 
	if( LastMode != CurMode )
	{
		if( LastMode <= SPRING_MODE && CurMode <= SPRING_MODE )
		{
			
		}
		else
		{
			CurSelected.clear();
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::BodyAddPose()
{
	if( Button[ KEY_0_PAD ].Pressed() || Button[ KEY_A ].Pressed() )
	{
		std::vector< Engine2D::cBody2DPose > TempPose;
		for( size_t idx = 0; idx < DynObj[ CurObj ].AnimationSet->BodyPose.size(); ++idx )
		{
			TempPose.push_back( DynObj[ CurObj ].AnimationSet->BodyPose[ idx ] );
			
			if( idx == CurPose )
			{
				TempPose.push_back( DynObj[ CurObj ].AnimationSet->BodyPose[ CurPose ] );
			}
		}
		DynObj[ CurObj ].AnimationSet->BodyPose.clear();
		DynObj[ CurObj ].AnimationSet->BodyPose.swap( TempPose );
		
		CurPose++;
	
		DynObj[ CurObj ].Body = DynObj[ CurObj ].AnimationSet->BodyPose[ CurPose ];
		Pose = &DynObj[ CurObj ].AnimationSet->BodyPose[ CurPose ];

		CurMode = NODE_MODE;
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::BodyDeletePose()
{
	if( Button[ KEY_DELETE ].Pressed() && DynObj[ CurObj ].AnimationSet->BodyPose.size() > 1 )
	{
		std::vector< Engine2D::cBody2DPose > TempPose;
		for( size_t idx = 0; idx < DynObj[ CurObj ].AnimationSet->BodyPose.size(); ++idx )
		{
			if( idx != CurPose )
			{
				TempPose.push_back( DynObj[ CurObj ].AnimationSet->BodyPose[ idx ] );
			}
		}
		DynObj[ CurObj ].AnimationSet->BodyPose.clear();
		DynObj[ CurObj ].AnimationSet->BodyPose.swap( TempPose );
		
		CurPose = DynObj[ CurObj ].AnimationSet->BodyPose.size() - 1;
	
		DynObj[ CurObj ].Body = DynObj[ CurObj ].AnimationSet->BodyPose[ CurPose ];
		Pose = &DynObj[ CurObj ].AnimationSet->BodyPose[ CurPose ];
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::SwitchPose()
{
	//if ( Button[ KEY_LEFT ].Pressed() )
	if( Button[ KEY_N ].Pressed() )
	{
		if( CurPose > 0 )
		{
			--CurPose;
		}
		else
		{
			CurPose = DynObj[ CurObj ].AnimationSet->BodyPose.size() - 1;
		}
		
		DynObj[ CurObj ].Body = DynObj[ CurObj ].AnimationSet->BodyPose[ CurPose ];
		Pose = &DynObj[ CurObj ].AnimationSet->BodyPose[ CurPose ];
		CurSelected.clear();
	}
	//else if ( Button[ KEY_RIGHT ].Pressed() )
	else if( Button[ KEY_M ].Pressed() )
	{
		if( CurPose < DynObj[ CurObj ].AnimationSet->BodyPose.size() - 1 )
		{
			++CurPose;
		}
		else
		{
			CurPose = 0;	
		}
		
		DynObj[ CurObj ].Body = DynObj[ CurObj ].AnimationSet->BodyPose[ CurPose ];
		Pose = &DynObj[ CurObj ].AnimationSet->BodyPose[ CurPose ];
		CurSelected.clear();
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::SwitchMeshAnim()
{
	if( Button[ KEY_O ].Pressed() )
	{
		if( CurMeshAnim > 0 )
		{
			--CurMeshAnim;
		}
		else
		{
			CurMeshAnim = AnimationGenerator.Animation.size() - 1;
		}
		CurMeshFrame = 0;
		CurSelected.clear();
		MeshGenerateUV();
		
/*		DynObj[ CurObj ].AnimationSet->MeshPose.clear();
		for( size_t idx = 0; idx < AnimationGenerator.Animation[ CurMeshAnim ].Frame.size(); ++idx )
		{
			DynObj[ CurObj ].AnimationSet->MeshPose.push_back( Engine2D::cMesh2DPose() );
		}*/
	}
	else if( Button[ KEY_P ].Pressed() )
	{
		if( CurMeshAnim < AnimationGenerator.Animation.size() - 1 )
		{
			++CurMeshAnim;
		}
		else
		{
			CurMeshAnim = 0;	
		}
		CurMeshFrame = 0;
		CurSelected.clear();
		MeshGenerateUV();
		
/*		DynObj[ CurObj ].AnimationSet->MeshPose.clear();
		for( size_t idx = 0; idx < AnimationGenerator.Animation[ CurMeshAnim ].Frame.size(); ++idx )
		{
			DynObj[ CurObj ].AnimationSet->MeshPose.push_back( Engine2D::cMesh2DPose() );
		}*/
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::SwitchMeshPose()
{
	if ( Button[ KEY_J ].Pressed() )  // CHANGE BUTTON
	{
		if( DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].MeshPoseIndex > 0 )
		{
			--DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].MeshPoseIndex;
		}
		else
		{
			DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].MeshPoseIndex = DynObj[ CurObj ].AnimationSet->MeshPose.size() - 1;
		}
		
		MeshGenerateUV();
		CurSelected.clear();
	}
	else if ( Button[ KEY_K ].Pressed() )
	{
		if( DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].MeshPoseIndex < DynObj[ CurObj ].AnimationSet->MeshPose.size() - 1 )
		{
			++DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].MeshPoseIndex;
		}
		else
		{
			DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].MeshPoseIndex = 0;	
		}
		
		MeshGenerateUV();
		CurSelected.clear();
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::SwitchMeshFrame()
{
	if ( Button[ KEY_LEFT ].Pressed() )  // CHANGE BUTTON
	{
		if( CurMeshFrame > 0 )
		{
			--CurMeshFrame;
		}
		else
		{
			CurMeshFrame = AnimationGenerator.Animation[ CurMeshAnim ].Frame.size() - 1;
		}
		
		MeshGenerateUV();
		CurSelected.clear();
	}
	else if ( Button[ KEY_RIGHT ].Pressed() )
	{
		if( CurMeshFrame < AnimationGenerator.Animation[ CurMeshAnim ].Frame.size() - 1 )
		{
			++CurMeshFrame;
		}
		else
		{
			CurMeshFrame = 0;	
		}
		
		MeshGenerateUV();
		CurSelected.clear();
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::SwitchTexture()
{
/*	if( !TextureName.empty() )
	{
		if( Button[ KEY_N ].Pressed() )
		{
			if( CurTexPreview > 0 )
			{
				CurTexPreview--;
			}
			else
			{
				CurTexPreview = TextureID.size() - 1;
			}
			//Real TempTexWidth = TexturePool.GetWidth( TextureName[ CurTexPreview ] ) / 2;
			//Real TempTexHeight = TexturePool.GetHeight( TextureName[ CurTexPreview ] ) / 2;
			Real TempTexWidth = 256;
			Real TempTexHeight = 256;

			PreviewTexVertex[0] = Vector3D( -TempTexWidth, -TempTexHeight, 0.0 );
			PreviewTexVertex[1] = Vector3D( TempTexWidth, -TempTexHeight, 0.0 );
			PreviewTexVertex[2] = Vector3D( TempTexWidth, TempTexHeight, 0.0 );
			PreviewTexVertex[3] = Vector3D( -TempTexWidth, TempTexHeight, 0.0 );
			
			DynObj[ CurObj ].AnimationSet->MeshPose[ CurMeshPose ].TextureID = TextureID[ CurTexPreview ];
		}
		else if( Button[ KEY_M ].Pressed() )
		{
			if( CurTexPreview < TextureID.size() - 1 )
			{
				CurTexPreview++;
			}
			else
			{
				CurTexPreview = 0;
			}
			
			//Real TempTexWidth = TexturePool.GetWidth( TextureName[ CurTexPreview ] ) / 2;
			//Real TempTexHeight = TexturePool.GetHeight( TextureName[ CurTexPreview ] ) / 2;
			Real TempTexWidth = 256;
			Real TempTexHeight = 256;

			PreviewTexVertex[0] = Vector3D( -TempTexWidth, -TempTexHeight, 0.0 );
			PreviewTexVertex[1] = Vector3D( TempTexWidth, -TempTexHeight, 0.0 );
			PreviewTexVertex[2] = Vector3D( TempTexWidth, TempTexHeight, 0.0 );
			PreviewTexVertex[3] = Vector3D( -TempTexWidth, TempTexHeight, 0.0 );
			
			DynObj[ CurObj ].AnimationSet->MeshPose[ CurMeshPose ].TextureID = TextureID[ CurTexPreview ];
		}
	}*/
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::LoadComp()
{
	DynObj.push_back( Engine2D::cDynamicComponent() );
	DynObj[ CurObj ].AnimationSet = new Engine2D::cComponentAnimationSet();
	DynObj[ CurObj ].AnimationSet->BodyPose.push_back( Engine2D::cBody2DPose() );
	
	DynObj[ CurObj ].Body = DynObj[ CurObj ].AnimationSet->BodyPose[ 0 ];
	Pose = &DynObj[ CurObj ].AnimationSet->BodyPose[ 0 ];
	
	
	for( size_t i = 0; i < AnimationGenerator.Animation.size(); ++i )
	{
		DynObj[ CurObj ].AnimationSet->Animation.push_back( Engine2D::cComponentAnimation() );
		DynObj[ CurObj ].AnimationSet->Animation[ i ].LoopPoint = 0;
		
		for( size_t idx = 0; idx < AnimationGenerator.Animation[ i ].Frame.size(); ++idx )
		{
			DynObj[ CurObj ].AnimationSet->Animation[ i ].Frame.push_back( Engine2D::cComponentFrame() );
			DynObj[ CurObj ].AnimationSet->Animation[ i ].Frame[ idx ].BodyPoseIndex = 0;
			DynObj[ CurObj ].AnimationSet->Animation[ i ].Frame[ idx ].MeshPoseIndex = 0;
		}
	}
//	DynObj[ CurObj ].AnimationSet->MeshPose.clear();
//	for( size_t idx = 0; idx < AnimationGenerator.Animation[ CurMeshAnim ].Frame.size(); ++idx )
//	{
	DynObj[ CurObj ].AnimationSet->MeshPose.push_back( Engine2D::cMesh2DPose() );
//	}
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::LoadCompTextures()
{
	for( size_t idx = 0; idx < AnimationGenerator.ImagePool.size(); ++idx )
	{
		unsigned int TempID;
		glGenTextures( 1, &TempID );
		
		glBindTexture( GL_TEXTURE_2D, TempID );
		
		if( AnimationGenerator.ImagePool[ idx ].Image->flags & SDL_SRCALPHA )
		{
			// Make it an Alpha Texture //
		    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA8, AnimationGenerator.ImagePool[ idx ].Image->w,
			  AnimationGenerator.ImagePool[ idx ].Image->h, 0, GL_RGBA,
			  GL_UNSIGNED_BYTE, AnimationGenerator.ImagePool[ idx ].Image->pixels );

			gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGBA8, AnimationGenerator.ImagePool[ idx ].Image->w,
		      AnimationGenerator.ImagePool[ idx ].Image->h, GL_RGBA,
		       GL_UNSIGNED_BYTE, AnimationGenerator.ImagePool[ idx ].Image->pixels );
		}
		else
		{
			// No Alpha in this Texture //
		    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB8, AnimationGenerator.ImagePool[ idx ].Image->w,
			  AnimationGenerator.ImagePool[ idx ].Image->h, 0, GL_RGB,
			  GL_UNSIGNED_BYTE, AnimationGenerator.ImagePool[ idx ].Image->pixels );

			gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGB8, AnimationGenerator.ImagePool[ idx ].Image->w,
		      AnimationGenerator.ImagePool[ idx ].Image->h, GL_RGB,
		       GL_UNSIGNED_BYTE, AnimationGenerator.ImagePool[ idx ].Image->pixels );
		}
	
		TextureID.push_back( TempID );
		TextureName.push_back( AnimationGenerator.ImagePool[ idx ].FileName );
	}

// glDeleteTextures( 1, &(idx->second.TextureId) );
	
}
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
