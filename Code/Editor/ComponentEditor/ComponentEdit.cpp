#ifdef EDITOR
// - ------------------------------------------------------------------------------------------ - //
#include "ComponentEdit.h"

#include <Util/DirectoryCache.h>

#include <Graphics/Gfx.h>
#include <Input/Input.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Global.h>

// For FPS test //
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
//	CurObj( 0 ),
	CurMeshFrame( 0 ),
	CurMeshAnim( 0 ),
	CurTexPreview( 0 ),
	NodeRadius( 6 ),
	BaseDirName( "../../../../Content/PuffBOMB/2D/" ),
	CurDirIdx( 0 )
{
	
	Camera->Aspect *= Real(0.75);
	Camera->Width *= Real(0.75);
	
	Camera->NearClip = Real( 1.0 );
	
	// Create Cameras //
	UVCamera = new cCamera(
		Vector3D( 128.0, 128.0, 400.0 ),				// Pos
		Vector3D( 0.0, 0.0, 0.0 ),						// View
		Vector3D( 0.0, 1.0, 0.0 ),						// Up
		45.0,											// Field of View
		Real( 1.0 ),									// Aspect Ratio
		1.0,											// NearClip
		100000.0,										// FarClip
		Global::HudZoom,								// MinZoom
		Global::HudZoom,								// MaxZoom
		Global::HudZoom,								// HudZoom
		Real( Global::ScreenW * 0.75 ),				// X
		Real( 0 ),										// Y
		Real( Global::ScreenW * UVWidth ),			// Width
		Real( Global::ScreenH * UVHeight )			// Height
	);
	
	Real PreviewHeight = UVHeight;

	if( Global::AspectRatio < Real( 0.79 ) )
	{
		PreviewHeight = 0.75;
		
		UVWidth = 0.33;
		UVHeight = 0.25;
	}
	
	PreviewCamera = new cCamera(
		Vector3D( 0.0, 0.0, Global::HudZoom * ( Real( 1 ) - PreviewHeight ) ),		// Pos
		Vector3D( 0.0, 0.0, 0.0 ),					// View
		Vector3D( 0.0, 1.0, 0.0 ),					// Up
		45.0,										// Field of View
		Global::AspectRatio * UVHeight,			// Aspect Ratio
		1.0,										// NearClip
		100000.0,									// FarClip
		Global::HudZoom,							// MinZoom
		Global::HudZoom,							// MaxZoom
		Global::HudZoom,							// HudZoom
		Real( Global::ScreenW * 0.75 ),			// X
		Real( Global::ScreenH * UVHeight ), 		// Y
		Real( Global::ScreenW * UVWidth ), 		// Width
		Real( Global::ScreenH * ( 1 - UVHeight ) ) // Height
	);
	
	Camera->Pos.z = Real( 800.0 );

	GridSize = 2048.0;

	TextureID.clear();
	TextureName.clear();
	
	FindCompDirs();
	
	// This inits the DynObj and AnimationSet so that they can use the same function that changes
	// between different components.
	DynObj = new Engine2D::cDynamicComponent();
	DynObj->Animator.AnimationSet = new Engine2D::cComponentAnimationSet();
		
	AnimationGenerator = new Engine2D::cAnimationGenerator( BaseDirName + CompDirs[ CurDirIdx ] );
	
	LoadComp();
	
	LoadCompTextures();
	
	UpdatePreview();


	Real GridDepthValue = 0.5;
	
	for( int idx = 0; idx < 13; ++idx )
	{
		UVGridDepth[idx] = GridDepthValue;
		
		GridDepthValue *= Real(2.0);
	}
	
	MeshGenerateUV();

	CurMode = NODE_MODE;

}
// - ------------------------------------------------------------------------------------------ - //
cComponentEdit::~cComponentEdit()
{
	delete UVCamera;
	delete PreviewCamera;
	
	delete DynObj->Animator.AnimationSet;
	delete DynObj;
	
	for( size_t idx = 0; idx < TextureID.size(); ++idx )
	{
		glDeleteTextures( 1, &TextureID[ idx ] );
	}
	
	delete AnimationGenerator;
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::Draw()
{
	Camera->Update();

//	Gfx::EnableDepth();
	Gfx::EnableTex2D();
	Gfx::EnableBlend();

	// Draw preview texture //
	if( !TextureName.empty() )
	{
		if( !AnimationGenerator->Animation[ CurMeshAnim ].Frame.empty() )
		{
			Gfx::DrawQuads(
				&PreviewTexVertex[0],
				&TexUV[0],
				TexIndices,
				4,
				TextureID[ AnimationGenerator->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].ImageIndex ],
				Gfx::RGBA( 255, 255, 255, 64 )
			);
		}
	}
	Gfx::DisableTex2D();

	Gfx::SetLineWidth( 1.0 );

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
		DynObj->Body.DrawNode( idx, false );
	}
	// Draw spheres //
	for( size_t idx = 0; idx < DynObj->Body.SphereSize(); ++idx )
	{
		DynObj->Body.DrawSphere( idx, false );
	}
	// Draw springs //
	for( size_t idx = 0; idx < DynObj->Body.SpringSize(); ++idx )
	{
		DynObj->Body.DrawSpring( idx, false );
	}
	// Draw mesh nodes //
	if(	!DynObj->Animator.AnimationSet->Animation[ CurMeshAnim ].Frame.empty() )
	{
		for( size_t idx = 0; idx < DynObj->Animator.AnimationSet->MeshPose[
									DynObj->Animator.AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].MeshPoseIndex 
									].Node.size(); ++idx )
		{
			Gfx::Circle(
				DynObj->Animator.AnimationSet->MeshPose[ DynObj->Animator.AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].MeshPoseIndex ].Node[ idx ].Pos,
				Real( 3 ),
				Gfx::RGBA(128, 128, 192, 192)
			);
		}
		// Draw faces //
		int LineColor = Gfx::RGBA(192, 192, 255, 192);
		
		for( size_t idx = 0; idx < DynObj->Animator.AnimationSet->MeshPose[ DynObj->Animator.AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].MeshPoseIndex ].Face.size(); ++idx )
		{
			Gfx::Line(
				DynObj->Animator.AnimationSet->MeshPose[ DynObj->Animator.AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].MeshPoseIndex ].Node[
					DynObj->Animator.AnimationSet->MeshPose[ DynObj->Animator.AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].MeshPoseIndex ].Face[ idx ].a
				].Pos,
				DynObj->Animator.AnimationSet->MeshPose[ DynObj->Animator.AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].MeshPoseIndex ].Node[
					DynObj->Animator.AnimationSet->MeshPose[ DynObj->Animator.AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].MeshPoseIndex ].Face[ idx ].b
				].Pos,
				LineColor
			);
	
			Gfx::Line(
				DynObj->Animator.AnimationSet->MeshPose[ DynObj->Animator.AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].MeshPoseIndex ].Node[
					DynObj->Animator.AnimationSet->MeshPose[ DynObj->Animator.AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].MeshPoseIndex ].Face[ idx ].b
				].Pos,
				DynObj->Animator.AnimationSet->MeshPose[ DynObj->Animator.AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].MeshPoseIndex ].Node[
					DynObj->Animator.AnimationSet->MeshPose[ DynObj->Animator.AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].MeshPoseIndex ].Face[ idx ].c
				].Pos,
				LineColor
			);
	
			Gfx::Line(
				DynObj->Animator.AnimationSet->MeshPose[ DynObj->Animator.AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].MeshPoseIndex ].Node[
					DynObj->Animator.AnimationSet->MeshPose[ DynObj->Animator.AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].MeshPoseIndex ].Face[ idx ].c
				].Pos,
				DynObj->Animator.AnimationSet->MeshPose[ DynObj->Animator.AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].MeshPoseIndex ].Node[
					DynObj->Animator.AnimationSet->MeshPose[ DynObj->Animator.AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].MeshPoseIndex ].Face[ idx ].a
				].Pos,
				LineColor
			);
		}
	}
	
	if( CurMode <= SPRING_MODE )
	{
		// Draw selected nodes //
		for( size_t idx = 0; idx < CurSelected.size(); ++idx )
		{
			DynObj->Body.DrawNode( CurSelected[ idx ], true );
		}
		// Draw selected spheres //
		for( size_t idx = 0; idx < CurSelected.size(); ++idx )
		{
			for( size_t SphereIdx = 0; SphereIdx < DynObj->Body.SphereSize(); ++SphereIdx )
			{
				if( CurSelected[idx] == DynObj->Body.Sphere( SphereIdx ).Index )
				{
					DynObj->Body.DrawSphere( SphereIdx, true );
				}
			}
		}
		// Draw selected springs //
		for( size_t SpringIdx = 0; SpringIdx < DynObj->Body.SpringSize(); ++SpringIdx )
		{
			for( size_t idx = 0; idx < CurSelected.size(); ++idx )
			{
				for( size_t i = idx + 1; i < CurSelected.size(); ++i )
				{
					if( DynObj->Body.Spring( SpringIdx ).IndexA == CurSelected[idx] )
					{
						if( DynObj->Body.Spring( SpringIdx ).IndexB == CurSelected[i] )
						{
							DynObj->Body.DrawSpring( SpringIdx, true );
						}
					}
					if( DynObj->Body.Spring( SpringIdx ).IndexB == CurSelected[idx] )
					{
						if( DynObj->Body.Spring( SpringIdx ).IndexA == CurSelected[i] )
						{
							DynObj->Body.DrawSpring( SpringIdx, true );
						}
					}
				}	
			}
		}
	}
	else if( CurMode == MESH_NODE_MODE || CurMode == PIVOT_HANDLE_MODE || CurMode == FACE_MODE )
	{
		if(	!DynObj->Animator.AnimationSet->Animation[ CurMeshAnim ].Frame.empty() )
		{
			
			// Draw selcted mesh nodes //
			for( size_t idx = 0; idx < CurSelected.size(); ++idx )
			{
				Gfx::Circle(
					DynObj->Animator.AnimationSet->MeshPose[ DynObj->Animator.AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].MeshPoseIndex ].Node[ CurSelected[idx] ].Pos,
					Real( 3 ),
					Gfx::RGBA(192, 192, 255, 192)
				);
			}
			
			if( CurMode != FACE_MODE )
			{
				if( !CurSelected.empty() && DynObj->Body.Nodes.Size() > 1 )
				{
					Vector2D TempPos = DynObj->Body.Nodes.Pos( 
						DynObj->Animator.AnimationSet->MeshPose[ DynObj->Animator.AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].MeshPoseIndex ].Node[ CurSelected[0] ].PivotIndex
					);
		
					Gfx::Circle(
						TempPos,
						Real( 3 ),
						Gfx::RGBA(255, 128, 255, 192)
					);
					
					TempPos = DynObj->Body.Nodes.Pos( 
						DynObj->Animator.AnimationSet->MeshPose[ DynObj->Animator.AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].MeshPoseIndex ].Node[ CurSelected[0] ].HandleIndex
					);
					
					Gfx::Circle(
						TempPos,
						Real( 3 ),
						Gfx::RGBA(128, 255, 255, 192)
					);
				}
			}
		}
	}
	
	Gfx::DisableBlend();
	
	PreviewDraw();
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::HudDraw()
{
	HudCamera->Update();

//	Gfx::DisableDepth();
	Gfx::EnableTex2D();
	Gfx::EnableBlend();
	
	DisplayText();
	
//	//  DISPLAYS FPS  //
//	std::stringstream Temp;
//	Temp << Global::FPS;
//	std::string TempString = Temp.str();
//	
//	Vector3D TempPos = Vector3D( Global::Left, Global::Top - Real( 45 ), 0.0 );
//
//	cFonts::FlangeLight.Write( TempString, TempPos, Real( 1.0 ), Gfx::RGBA( 184, 0, 0, 255 ) );
//	// -------------- //
//	Gfx::EnableDepth();
	Gfx::DisableBlend();
	Gfx::DisableTex2D();
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::PreviewDraw()
{
	PreviewCamera->Update();
	
	Gfx::SetLineWidth( 1.0 );
	
	Gfx::EnableTex2D();
	Gfx::EnableBlend();
	// Draw the Mesh2D //
	

	if( !DynObj->Animator.AnimationSet->Animation[ CurMeshAnim ].Frame.empty() )
	{
		DynObj->Animator.AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].Draw( DynObj->Body );
	}

	Gfx::DisableTex2D();

	// Draw the Body2D debug information //	
	DynObj->Body.DrawNodes();
	DynObj->Body.DrawSpheres();
	DynObj->Body.DrawSprings();
		
	Gfx::DisableBlend();

	UVDraw();
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::UVDraw()
{
	UVCamera->Update();

	Gfx::SetLineWidth( 1.0 );
	
	Gfx::EnableTex2D();
	Gfx::EnableBlend();

	if( !TextureName.empty() )
	{
		if( !AnimationGenerator->Animation[ CurMeshAnim ].Frame.empty() )
		{
			Gfx::DrawQuads(
				&TexVertex[0],
				&TexUV[0],
				TexIndices,
				4,
				TextureID[ AnimationGenerator->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].ImageIndex ],
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
		
	HudDraw();
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
		if( Global::AspectRatio < Real( 0.79 ) )
		{
			Scroll( Camera, Real( 1.33 ), Real( 1.33 ), Vector2D( Global::HudZoom, Global::HudZoom ) );
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

			//BodyScaleNode();
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

			//MeshScaleNode();
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

		if( Global::AspectRatio < Real( 0.79 ) )
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
		if( Global::AspectRatio < Real( 0.79 ) )
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
	if( CurMode == COMP_MESH_MODE )
	{
		MeshAddPose();
		MeshDeletePose();
		
		if( Button[ KEY_M ].Pressed() )
		{
			EditEventFlags |= flGlobalIncrease;
			
			for( size_t idx = 0; idx < DynObj->Animator.AnimationSet->Animation[ CurMeshAnim ].Frame.size(); ++idx )
			{
				MeshSwitchPose( idx );
			}
			
			EditEventFlags &= ~flGlobalIncrease;
		}
		else if( Button[ KEY_N ].Pressed() )
		{
			EditEventFlags |= flGlobalDecrease;
			
			for( size_t idx = 0; idx < DynObj->Animator.AnimationSet->Animation[ CurMeshAnim ].Frame.size(); ++idx )
			{
				MeshSwitchPose( idx );
			}
			
			EditEventFlags &= ~flGlobalDecrease;
		}
		
		ScaleAll();
	}
	else if( CurMode == COMP_BODY_MODE )
	{
		BodyAddPose();
		BodyDeletePose();
		
		if( Button[ KEY_M ].Pressed() )
		{
			EditEventFlags |= flGlobalIncrease;
			
			for( size_t idx = 0; idx < DynObj->Animator.AnimationSet->Animation[ CurMeshAnim ].Frame.size(); ++idx )
			{
				BodySwitchPose( idx );
			}
			
			EditEventFlags &= ~flGlobalIncrease;
		}
		else if( Button[ KEY_N ].Pressed() )
		{
			EditEventFlags |= flGlobalDecrease;
			
			for( size_t idx = 0; idx < DynObj->Animator.AnimationSet->Animation[ CurMeshAnim ].Frame.size(); ++idx )
			{
				BodySwitchPose( idx );
			}
			
			EditEventFlags &= ~flGlobalDecrease;
		}
		
		ScaleAll();
	}
	
	Undo();
	
	Save();
	
	SwitchMode();
	
	if( CurMode != COMP_MESH_MODE && CurMode != COMP_BODY_MODE )
	{
		BodySwitchPose( CurMeshFrame );
		MeshSwitchPose( CurMeshFrame );
	}
	MeshSwitchAnim();
	MeshSwitchFrame();
	
	SwitchComp();
	
	LastView = CurView;
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::LoadComp()
{
	delete DynObj->Animator.AnimationSet;
	delete DynObj;

	DynObj = new Engine2D::cDynamicComponent();
	DynObj->Animator.AnimationSet = new Engine2D::cComponentAnimationSet();
	
	DynObj->Animator.AnimationSet->LoadText( BaseDirName + CompDirs[ CurDirIdx ] + GetFileName() );

	if( DynObj->Animator.AnimationSet->BodyPose.empty() )
	{
		DynObj->Animator.AnimationSet->BodyPose.push_back( Engine2D::cBody2DPose() );
		
		for( size_t i = 0; i < AnimationGenerator->Animation.size(); ++i )
		{
			DynObj->Animator.AnimationSet->Animation.push_back( Engine2D::cComponentAnimation() );
			DynObj->Animator.AnimationSet->Animation[ i ].LoopPoint = 0;
			
			for( size_t idx = 0; idx < AnimationGenerator->Animation[ i ].Frame.size(); ++idx )
			{
				DynObj->Animator.AnimationSet->Animation[ i ].Frame.push_back( Engine2D::cComponentFrame() );
				DynObj->Animator.AnimationSet->Animation[ i ].Frame[ idx ].BodyPoseIndex = 0;
				DynObj->Animator.AnimationSet->Animation[ i ].Frame[ idx ].MeshPoseIndex = 0;
			}
		}
		DynObj->Animator.AnimationSet->MeshPose.push_back( Engine2D::cMesh2DPose() );
	}
	DynObj->Body = DynObj->Animator.AnimationSet->BodyPose[ 0 ];
	Pose = &DynObj->Animator.AnimationSet->BodyPose[ 0 ];
	
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::LoadCompTextures()
{
	for( size_t idx = 0; idx < TextureID.size(); ++idx )
	{
		glDeleteTextures( 1, &TextureID[ idx ] );
	}
	
	TextureID.clear();
	TextureName.clear();
			
	for( size_t idx = 0; idx < AnimationGenerator->ImagePool.size(); ++idx )
	{
		unsigned int TempID;
		glGenTextures( 1, &TempID );
		
		glBindTexture( GL_TEXTURE_2D, TempID );
		
		if( AnimationGenerator->ImagePool[ idx ].Image->flags & SDL_SRCALPHA )
		{
			// Make it an Alpha Texture //
		    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA8, AnimationGenerator->ImagePool[ idx ].Image->w,
			  AnimationGenerator->ImagePool[ idx ].Image->h, 0, GL_RGBA,
			  GL_UNSIGNED_BYTE, AnimationGenerator->ImagePool[ idx ].Image->pixels );

			gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGBA8, AnimationGenerator->ImagePool[ idx ].Image->w,
		      AnimationGenerator->ImagePool[ idx ].Image->h, GL_RGBA,
		       GL_UNSIGNED_BYTE, AnimationGenerator->ImagePool[ idx ].Image->pixels );
		}
		else
		{
			// No Alpha in this Texture //
		    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB8, AnimationGenerator->ImagePool[ idx ].Image->w,
			  AnimationGenerator->ImagePool[ idx ].Image->h, 0, GL_RGB,
			  GL_UNSIGNED_BYTE, AnimationGenerator->ImagePool[ idx ].Image->pixels );

			gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGB8, AnimationGenerator->ImagePool[ idx ].Image->w,
		      AnimationGenerator->ImagePool[ idx ].Image->h, GL_RGB,
		       GL_UNSIGNED_BYTE, AnimationGenerator->ImagePool[ idx ].Image->pixels );
		}
	
		TextureID.push_back( TempID );
		TextureName.push_back( AnimationGenerator->ImagePool[ idx ].FileName );
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::Save()
{
	if( Button[ KEY_LCTRL ] && Button[ KEY_S ].Pressed() && !IsSaved )
	{
		
		DynObj->Animator.AnimationSet->SaveText( BaseDirName + CompDirs[ CurDirIdx ] + GetFileName() );
		
		IsSaved = true;
	}
}
// - ------------------------------------------------------------------------------------------ - //
std::string cComponentEdit::GetFileName()
{
	std::string CompName = "Component.comp";
	std::string LastDirName = ( BaseDirName + CompDirs[ CurDirIdx ] ).substr( 0, ( BaseDirName + CompDirs[ CurDirIdx ] ).size() - 1 );
		
	size_t SlashPos = LastDirName.rfind( '/' );

	if( SlashPos != std::string::npos )
	{
		LastDirName = LastDirName.substr( SlashPos + 1 );
	}

	std::string SecLastDirName = ( BaseDirName + CompDirs[ CurDirIdx ] ).substr( 0, SlashPos );
	
	SlashPos = SecLastDirName.rfind( '/' );

	if( SlashPos != std::string::npos )
	{
		CompName = SecLastDirName.substr( SlashPos + 1 ) + LastDirName + ".comp";
	}
	else
	{
		CompName = "Component.comp";
	}
	
	return CompName;
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::FindCompDirs()
{
	cDirectoryCache DirCache( BaseDirName );
	
	for( size_t idx = 0; idx < DirCache.File.size(); ++idx )
	{
		if( DirCache.File[idx].find( "Id" ) != std::string::npos &&
			DirCache.File[idx].find( "Hold" ) != std::string::npos )
		{
			std::string TempDir = String::Directory( DirCache.File[idx] );
			
			TempDir = String::DirectorySlash( TempDir );
			
			bool IsNewComp = true;
			for( size_t i = 0; i < CompDirs.size(); ++i )
			{
				if( CompDirs[ i ] == TempDir )
				{
					IsNewComp = false;
					break;
				}			
			}
			if( IsNewComp )
			{
				CompDirs.push_back( TempDir );
			}
		}
	}	
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::SwitchComp()
{
	if( IsSaved )
	{
		if( Button[ KEY_MINUS_PAD ].Pressed() )
		{
			if( CurDirIdx > 0 )
			{
				--CurDirIdx;
			}
			else
			{
				CurDirIdx = CompDirs.size() - 1;
			}
			delete AnimationGenerator;
			AnimationGenerator = new Engine2D::cAnimationGenerator( BaseDirName + CompDirs[ CurDirIdx ] );

			LoadComp();
			LoadCompTextures();
			
			CurMeshFrame = 0;
			CurMeshAnim = 0;
			CurTexPreview = 0;
			
			CurSelected.clear();
			UpdatePreview();			
			MeshGenerateUV();
		}
		else if( Button[ KEY_PLUS_PAD ].Pressed() )
		{
			if( CurDirIdx < CompDirs.size() - 1 )
			{
				++CurDirIdx;
			}
			else
			{
				CurDirIdx = 0;	
			}
			delete AnimationGenerator;
			AnimationGenerator = new Engine2D::cAnimationGenerator( BaseDirName + CompDirs[ CurDirIdx ] );

			LoadComp();
			LoadCompTextures();

			CurMeshFrame = 0;
			CurMeshAnim = 0;
			CurTexPreview = 0;

			CurSelected.clear();
			UpdatePreview();
			MeshGenerateUV();
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::UpdatePreview()
{
	if( !TextureName.empty() )
	{
		Real TempTexWidth = 256;
		Real TempTexHeight = 256;
		
		TempTexWidth *= DynObj->Animator.AnimationSet->MeshPose[ DynObj->Animator.AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].MeshPoseIndex ].TextureScale;
		TempTexHeight *= DynObj->Animator.AnimationSet->MeshPose[ DynObj->Animator.AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].MeshPoseIndex ].TextureScale;
		
		PreviewTexVertex[0] = Vector3D( -TempTexWidth, -TempTexHeight, 0.0 );
		PreviewTexVertex[1] = Vector3D( TempTexWidth, -TempTexHeight, 0.0 );
		PreviewTexVertex[2] = Vector3D( TempTexWidth, TempTexHeight, 0.0 );
		PreviewTexVertex[3] = Vector3D( -TempTexWidth, TempTexHeight, 0.0 );
	}
}
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
