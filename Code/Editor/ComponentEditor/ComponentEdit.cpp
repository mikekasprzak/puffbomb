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
	//DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].BodyPoseIndex( 0 ),
	//CurMeshPose( 0 ),
	CurMeshFrame( 0 ),
	CurMeshAnim( 0 ),
	CurTexPreview( 0 ),
	NodeRadius( 6 ),
	AnimationGenerator( "../../../../Content/PuffBOMB/2D/Hamster/Body/" ),
	CurDir( "../../../../Content/PuffBOMB/2D/Hamster/Body/" )
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
	
	TextureID.clear();
	TextureName.clear();
	
	LoadComp();
	
	LoadCompTextures();
	
	if( !TextureName.empty() )
	{
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
	
	for( size_t idx = 0; idx < TextureID.size(); ++idx )
	{
		glDeleteTextures( 1, &TextureID[ idx ] );
	}
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
	if(	!DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame.empty() )
	{
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
		if(	!DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame.empty() )
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
	if( CurMode == COMP_MESH_MODE )
	{
		MeshAddPose();
		MeshDeletePose();
	}
	else if( CurMode == COMP_BODY_MODE )
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
	DynObj[ CurObj ].AnimationSet->MeshPose.push_back( Engine2D::cMesh2DPose() );
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
}
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
