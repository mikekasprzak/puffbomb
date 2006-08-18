#ifdef EDITOR
// - ------------------------------------------------------------------------------------------ - //
#include "Mesh2DEdit.h"
#include <Graphics/Gfx.h>
#include <Input/Input.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Platform/Global.h>
// - ------------------------------------------------------------------------------------------ - //
#include <SDL/SDL.h>

// For FPS test //
#include <Platform/Global.h>
#include <Font/Fonts.h>
#include <sstream>
// ------------ //

using namespace Input;
// - ------------------------------------------------------------------------------------------ - //
cMesh2DEdit::cMesh2DEdit() :
	ScrollSpeed( 3.0 ),
	CurrentObject( 0 ),
	CurrentNode( 0 ),
	CurrentSpring( 0 ),
	CurrentFace( 0 ),
//	SnapToGrid( false ),
	LeftClicked( false ),
	SpringPlacement( false ),
	isPaste( false ),
	isDelete( false ),
	EditMode( 0 ),
	CurLayer( 0 ),
//	OldMousePos( Real(0.0), Real(0.0) ),
//	isGroupMove( false ),
//	UVScale( 256 ),
	CurUVGridDepth( 0 ),
//	UVWidth( 0.25 ),
//	UVHeight( 0.4 ),
//	UVZoomOffsetX( 144.5 ),
//	UVZoomOffsetY( 232 ),
	UVScrollMouseX( 0 ),
	UVScrollMouseY( 0 ),
	UVMiddleClick( false ),
	UVMiddleClickLast( false ),
	isUVGroupMove( false ),
	SnapToUVGrid( false )
{	

	// Create Cameras //
	UVCamera = new cCamera(
		Vector3D( 128.0, 128.0, 400.0 ),
		Vector3D( 0.0, 0.0, 0.0 ),
		Vector3D( 0.0, 1.0, 0.0 ),
		45.0,
		Platform::AspectRatio,
		1.0,
		100000.0,
		cGlobal::HudZoom,
		cGlobal::HudZoom,
		cGlobal::HudZoom
	 );

	PreviewCamera = new cCamera(
		Vector3D( 0.0, 0.0, 500.0 ),
		Vector3D( 0.0, 0.0, 0.0 ),
		Vector3D( 0.0, 1.0, 0.0 ),
		45.0,
		Platform::AspectRatio,
		1.0,
		100000.0,
		cGlobal::HudZoom,
		cGlobal::HudZoom,
		cGlobal::HudZoom
	 );
	
	Camera->Pos.z = Real( 800.0 );
	Log( LOG_HIGHEST_LEVEL, "Mesh2DEdit Constructor (Editor) " );

	//CurrentDir = "../../../../Content/PuffBOMB/";
	OpenCMesh( CurrentDir );

	SphereCheck();
	
	for( size_t idx = 0; idx < Mesh2DInfo.size(); ++idx )
	{
		cDisplayMesh tempTexObj;
		DisplayMesh.push_back( tempTexObj );
	}
	
	OpenDMesh( CurrentDir );
	
	for( size_t idx = 0; idx < Mesh2DInfo.size(); ++idx )
	{
		CurrentObject = idx;
		ActiveAction();
		
		Mesh2DInfo[CurrentObject].isSaved = true;
	}
	
	CurrentObject = 0;
	
	LayerCheck();
	
	GridSize = 2048.0;
	
	TEXa = Vector3D( 0.0, 0.0, 0.0 );
	TEXb = Vector3D( UVScale, 0.0, 0.0 );
	TEXc = Vector3D( UVScale, UVScale, 0.0 );
	TEXd = Vector3D( 0.0, UVScale, 0.0 );	
	UVa = Vector2D( 1.0, 0.0 );
	UVb = Vector2D( 0.0, 0.0 );
	UVc = Vector2D( 1.0, 1.0 );
	UVd = Vector2D( 0.0, 1.0 );
	
	//UVOrigin = Vector2D( -( UVScale / Real( 2 ) ), -( UVScale / Real( 2 ) ) );
	
	Real GridDepthValue = 0.5;
	
	for( int idx = 0; idx < 13; ++idx )
	{
		UVGridDepth[idx] = GridDepthValue;
		
		GridDepthValue *= Real(2.0);
	}

	Log( LOG_HIGHEST_LEVEL, "Object.size() = " << Object.size() );
	Log( LOG_HIGHEST_LEVEL, "DisplayMesh.size() = " << DisplayMesh.size() );
	
	CalcUVZoomOffset();
	
}
// - ------------------------------------------------------------------------------------------ - //
cMesh2DEdit::~cMesh2DEdit()
{
	Log( LOG_EDITOR_CREATE, "~cMesh2DEdit()" );

	delete UVCamera;
	Log( LOG_EDITOR_CREATE, "UVCamera Deleted" );
	delete PreviewCamera;
	Log( LOG_EDITOR_CREATE, "PreviewCamera Deleted" );

	for( size_t idx = 0; idx < TextureID.size(); ++idx )
	{
		if( TextureID[idx] != 0 )
		{
			Log( LOG_EDITOR_INFO, "Deleting TextureID" );
			glDeleteTextures( 1, &TextureID[idx] );
		}
	}
	Log( LOG_EDITOR_CREATE, "EndOf ~cMesh2DEdit()" );
}
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::Draw()
{
	if( CheckViewOne() )
	{
		if( LastView != CurView )
		{
			SetGridArray( CurrentGridDepth, GridDepth );
		}		
		DrawGrid( Camera, CurrentGridDepth, 40.0, true, GridDepth );
	}

	if( Object[ CurrentObject ].size() > 0 )
	{
		// Draw Objects //
		DrawMesh();
		
		if( SnapToGrid )
		{
			if( EditMode == SPHERE_MODE || EditMode == NODE_MODE || EditMode == SPRING_MODE )
			{
				for( size_t idx = 0; idx < CurSelected.size(); ++idx )
				{ 
					DrawColSnapToGrid( CurSelected[idx] );
				}
			}
			else if( EditMode == DISPLAY_NODE_MODE )
			{
				for( size_t idx = 0; idx < CurSelected.size(); ++idx )
				{ 
					DrawDisSnapToGrid( CurSelected[idx] );
				}	
			}
		}
		DrawSelected();

		DrawSpringPlacement();
	}
	
	// Displays all the text //
	
	DrawGroupAction();
	
}	
// - ------------------------------------------------------------------------------------------ - //	
void cMesh2DEdit::DrawPreview()
{
	DrawOrigin();

	if( Object[ CurrentObject ].size() > 0 )
	{
		//DrawMesh();
		// Draw Texture //
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);

		glBindTexture( GL_TEXTURE_2D, TextureID[ DisplayMesh[CurrentObject].TextureIdx ] );

		glColor3ub( 255, 255, 255 );
		for( size_t i = 0; i < DrawLayers.size(); ++i )
		{
			for( size_t idx = 0; idx < DisplayMesh[ CurrentObject ].Face.size(); ++idx )
			{
				if( DisplayMesh[ CurrentObject ].Face[idx].Layer == DrawLayers[i] )
				{
					gfx::Face( 
						DisplayMesh[ CurrentObject ].Pos( DisplayMesh[ CurrentObject ].Face[idx].Vertex.a ),
						DisplayMesh[ CurrentObject ].Pos( DisplayMesh[ CurrentObject ].Face[idx].Vertex.b ),
						DisplayMesh[ CurrentObject ].Pos( DisplayMesh[ CurrentObject ].Face[idx].Vertex.c ),
						DisplayMesh[ CurrentObject ].Face[idx].UV.a,
						DisplayMesh[ CurrentObject ].Face[idx].UV.b,
						DisplayMesh[ CurrentObject ].Face[idx].UV.c
					);
				}
			}
		}
		glDisable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);

	}
}
// - ------------------------------------------------------------------------------------------ - //	
void cMesh2DEdit::HudDraw()
{
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);

	glDisable( GL_DEPTH_TEST );

	DisplayText();
	
	
		
//  DISPLAYS FPS  //
//	std::stringstream Temp;
//	Temp << Platform::FPS;
//	std::string TempString = Temp.str();
//	
//	Vector3D TempPos = Vector3D( cGlobal::Left, cGlobal::Top - Real( 45 ), 0.0 );
//
//	cFonts::FlangeLight.Write( TempString, TempPos, Real( 1.0 ), gfx::RGBA( 184, 0, 0, 255 ) );
// -------------- //
	
	glEnable( GL_DEPTH_TEST );

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);

//	DrawPreviewBox();
}
// - ------------------------------------------------------------------------------------------ - //	
void cMesh2DEdit::DrawTextureCoord()
{
	// Displays the current texture on a quad in the bottom right of the screen
	if( DisplayMesh[CurrentObject].TextureIdx != -1
		&& !DisplayMesh[ CurrentObject ].Face.empty()
		&& EditMode == TEXTURE_MODE )
	{
				
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);

		glBindTexture( GL_TEXTURE_2D, TextureID[DisplayMesh[CurrentObject].TextureIdx] );
		
		glColor3ub( 255, 255, 255 );

		gfx::Face( TEXb, TEXa, TEXc, UVc, UVa, UVd );
		gfx::Face( TEXa, TEXd, TEXc, UVd, UVa, UVb );
		
		glDisable(GL_BLEND);
		glDisable( GL_TEXTURE_2D );

		DisDrawUV();
	}
	
	if( CheckViewThree( UVHeight ) )
	{
		
		if( LastView != CurView )
		{
			SetGridArray( CurUVGridDepth, UVGridDepth );
		}		
		DrawGrid( UVCamera, CurUVGridDepth, 32.0, true, UVGridDepth );
		
		if( EditMode == TEXTURE_MODE )
		{
			if( !isUVGroupMove )
			{
				DrawDisSelectUV();
			}
			DisMoveUV();
		}
	}
}	
// - ------------------------------------------------------------------------------------------ - //	
void cMesh2DEdit::Step()
{
	LastView = CurView;
	
	
	if( !Button[ KEY_LCTRL ] )
	{
		if( CheckViewOne() )
		{
			// Handles scrolling around the map
			Scroll( Camera );
	
			// Handles the zooming in and out of a map
			Zoom( Real( 32.0 ), Camera );
		}
	}
	
	// Saves Current Mesh
	SaveCurrentMesh();
	
	// Switch between current mesh being displayed
	SwitchMesh();

	// Resets the Zoom and will contain the whole undo system and keys	
	Undo();
	
	// Changes the current mesh editor mode
	SwitchMode();

	if( CheckViewOne() )
	{
		CurView = 1;
		if( EditMode == NODE_MODE )
		{
			ColAddNode();
		}
	
		if( Object[ CurrentObject ].size() > 0 )
		{
			// Allows you to move the current node to a different position
			if( EditMode == NODE_MODE )
			{
				ColDeleteNode();
				
				ColLockNode();
				
				if( !Button[ KEY_LSHIFT ] )
				{
					ColMass( Real(1.0) );
				}
				else
				{
					ColMass( Real(0.1) );
				}
			}
			else if( EditMode == SPHERE_MODE )
			{

				if( HasSphere[ CurrentNode ] )
				{
					if( !Button[ KEY_LSHIFT ] )
					{
						ColRadius( Real(1.0) );
					}
					else
					{
						ColRadius( Real(0.1) );
					}
				}
				ColAddSphere();
				ColDeleteSphere();
			}
			else if( EditMode == SPRING_MODE )
			{
				SelectSpring();
				SwitchSpring();
				ColAddSpring();
				ColDeleteSpring();
			}	
			else if( EditMode == DISPLAY_NODE_MODE )
			{
				DisAddNode();
				DisDeleteNode();
				if( !isGroupMove )
				{
					DisSelectNode();
				}
				DisMoveNode();
			}
			else if( EditMode == PIVOT_HANDLE_MODE )
			{
				DisSetPivot();
				DisSetHandle();
				DisSelectNode();
			}
			else if( EditMode == FACE_MODE )
			{
				DisSelectNode();
				DisAddFace();
				DisDeleteFace();
				SwitchFace();
				
				DisChangeLayer();
			}
			else if( EditMode == TEXTURE_MODE )
			{
				SwitchFace();
				DisSelectFace();
			}
			if( EditMode == SPHERE_MODE || EditMode == NODE_MODE || EditMode == SPRING_MODE )
			{
				if( !isGroupMove )
				{
					ColSelectNode();
				}		
			}
				
			if( EditMode == SPHERE_MODE || EditMode == NODE_MODE )
			{
				SwitchNode();
					
				ColMoveNode();
				ColCopy();
				ColPaste();
			}
		}
	}
	else if( CheckViewTwo( UVHeight ) )
	{
		CurView = 2;
		// Handles scrolling around the map
		Scroll( PreviewCamera );

		// Handles the zooming in and out of the preview
		Zoom( Real( 32.0 ), PreviewCamera );
	}
	else if( CheckViewThree( UVHeight ) )
	{
		CurView = 3;
		if( EditMode == TEXTURE_MODE )
		{
			if( CheckViewThree( UVHeight ) )
			{
				if( !isUVGroupMove )
				{
					DisSelectUV();
				}
				DisMoveUV();

				ZoomUV();
				
				ScrollUV();
			}
		}
	}
	if( EditMode == TEXTURE_MODE )
	{
		DisChangeTexture();
		
		DisAddTexture();
		DisDeleteTexture();

		DisRotateUVRGB();
		DisRotateUV();
		DisInvertUV();
		
		DisChangeLayer();
	}
}	
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::DrawPreviewBox()
{
	gfx::Line(
		Real( ( cGlobal::ScreenW * Real( 0.3745 ) ) ),
		Real( -cGlobal::ScreenH ),
		Real( Camera->Pos.z / cGlobal::HudZoom ),
		Real( ( cGlobal::ScreenW * Real( 0.3745 ) ) ),
		Real( cGlobal::ScreenH ),
		Real( Camera->Pos.z / cGlobal::HudZoom ),
		gfx::RGB( 0, 127, 127 )
	);
}	
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::SwitchMesh()
{	
	if ( Button[ KEY_LEFT ].Pressed() )
	{
		if( CurrentObject > 0 )
		{
			--CurrentObject;
		}
		else
		{
			CurrentObject = Object.size() - 1;
		}
		CurrentNode = 0;
		CurSelected.clear();

		CurrentSpring = 0;
		CurrentFace = 0;
		
		SphereCheck();
		LayerCheck();
	}
	else if ( Button[ KEY_RIGHT ].Pressed() )
	{
		if( CurrentObject < Object.size() - 1 )
		{
			++CurrentObject;
		}
		else
		{
			CurrentObject = 0;	
		}
		CurrentNode = 0;
		CurSelected.clear();

		CurrentSpring = 0;
		CurrentFace = 0;
		
		SphereCheck();
		LayerCheck();
	}	
}
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::DrawMesh()
{
	// Draw Texture //
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	
	glBindTexture( GL_TEXTURE_2D, TextureID[ DisplayMesh[CurrentObject].TextureIdx ] );
	
	glColor3ub( 128, 128, 128 );
	
	for( size_t idx = 0; idx < DisplayMesh[ CurrentObject ].Face.size(); ++idx )
	{
		for( size_t i = 0; i < DrawLayers.size(); ++i )
		{
			if( DisplayMesh[ CurrentObject ].Face[idx].Layer == DrawLayers[i] &&
				DisplayMesh[ CurrentObject ].Face[idx].Layer != CurLayer )
			{
				gfx::Face( 
					DisplayMesh[ CurrentObject ].Pos( DisplayMesh[ CurrentObject ].Face[idx].Vertex.a ),
					DisplayMesh[ CurrentObject ].Pos( DisplayMesh[ CurrentObject ].Face[idx].Vertex.b ),
					DisplayMesh[ CurrentObject ].Pos( DisplayMesh[ CurrentObject ].Face[idx].Vertex.c ),
					DisplayMesh[ CurrentObject ].Face[idx].UV.a,
					DisplayMesh[ CurrentObject ].Face[idx].UV.b,
					DisplayMesh[ CurrentObject ].Face[idx].UV.c
				);
			}
		}
	}
	glColor3ub( 255, 255, 255 );
	
	for( size_t idx = 0; idx < DisplayMesh[ CurrentObject ].Face.size(); ++idx )
	{
		if( DisplayMesh[ CurrentObject ].Face[idx].Layer == CurLayer )
		{
			gfx::Face( 
				DisplayMesh[ CurrentObject ].Pos( DisplayMesh[ CurrentObject ].Face[idx].Vertex.a ),
				DisplayMesh[ CurrentObject ].Pos( DisplayMesh[ CurrentObject ].Face[idx].Vertex.b ),
				DisplayMesh[ CurrentObject ].Pos( DisplayMesh[ CurrentObject ].Face[idx].Vertex.c ),
				DisplayMesh[ CurrentObject ].Face[idx].UV.a,
				DisplayMesh[ CurrentObject ].Face[idx].UV.b,
				DisplayMesh[ CurrentObject ].Face[idx].UV.c
			);
		}
	}

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	
	// Draw Springs //
	for( size_t idx = 0; idx < Object[ CurrentObject ].Spring.size(); ++idx )
	{
		DrawSpring( gfx::RGB( 255, 255, 0 ), idx );
	}
	// Draw Spheres //
	for( size_t idx = 0; idx < Object[ CurrentObject ].Sphere.size(); ++idx )
	{
		DrawSphere( gfx::RGB( 255, 0, 0 ), idx );
	}
	// Draw Collision Nodes //
	for( size_t idx = 0; idx < Object[ CurrentObject ].size(); ++idx )
	{
		DrawNode( gfx::RGB( 127, 255, 0 ), idx );
	}
	glLineWidth( 4 );
	// Draw Hard Nodes //
	for( size_t i = 0; i < Object[ CurrentObject ].Hard.size(); ++i )
	{
		if( Object[ CurrentObject ].Hard[i].Enabled )
		{
			DrawNode( gfx::RGB( 0, 255, 0 ), Object[ CurrentObject ].Hard[i].Index );
		}
	}
	glLineWidth( 1.5 );
	
	// Draw Display Nodes //
	for( size_t idx = 0; idx < DisplayMesh[ CurrentObject ].size(); ++idx )
	{
		gfx::Circle( 
			DisplayMesh[ CurrentObject ].Pos( idx ), 1, gfx::RGB( 192, 192, 192 ) );
	}
	// Draw Faces //
	for( size_t idx = 0; idx < DisplayMesh[ CurrentObject ].Face.size(); ++idx )
	{
		if( DisplayMesh[ CurrentObject ].Face[idx].Layer == CurLayer )
		{
			gfx::Line( 
				DisplayMesh[ CurrentObject ].Pos( DisplayMesh[ CurrentObject ].Face[idx].Vertex.a ),
				DisplayMesh[ CurrentObject ].Pos( DisplayMesh[ CurrentObject ].Face[idx].Vertex.b ),
				gfx::RGB( 177, 177, 177 )
			);
			gfx::Line( 
				DisplayMesh[ CurrentObject ].Pos( DisplayMesh[ CurrentObject ].Face[idx].Vertex.b ),
				DisplayMesh[ CurrentObject ].Pos( DisplayMesh[ CurrentObject ].Face[idx].Vertex.c ),
				gfx::RGB( 177, 177, 177 )
			);
			gfx::Line( 
				DisplayMesh[ CurrentObject ].Pos( DisplayMesh[ CurrentObject ].Face[idx].Vertex.c ),
				DisplayMesh[ CurrentObject ].Pos( DisplayMesh[ CurrentObject ].Face[idx].Vertex.a ),
				gfx::RGB( 177, 177, 177 )
			);
		}
		else
		{
			gfx::Line( 
				DisplayMesh[ CurrentObject ].Pos( DisplayMesh[ CurrentObject ].Face[idx].Vertex.a ),
				DisplayMesh[ CurrentObject ].Pos( DisplayMesh[ CurrentObject ].Face[idx].Vertex.b ),
				gfx::RGB( 100, 100, 100 )
			);
			gfx::Line( 
				DisplayMesh[ CurrentObject ].Pos( DisplayMesh[ CurrentObject ].Face[idx].Vertex.b ),
				DisplayMesh[ CurrentObject ].Pos( DisplayMesh[ CurrentObject ].Face[idx].Vertex.c ),
				gfx::RGB( 100, 100, 100 )
			);
			gfx::Line( 
				DisplayMesh[ CurrentObject ].Pos( DisplayMesh[ CurrentObject ].Face[idx].Vertex.c ),
				DisplayMesh[ CurrentObject ].Pos( DisplayMesh[ CurrentObject ].Face[idx].Vertex.a ),
				gfx::RGB( 100, 100, 100 )
			);
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::SwitchMode()
{
	if ( Button[ KEY_1 ].Pressed() )
	{
		ToggleColToDis( NODE_MODE );
		EditMode = NODE_MODE;
	}
	else if ( Button[ KEY_2 ].Pressed() )
	{
		ToggleColToDis( SPHERE_MODE );
		EditMode = SPHERE_MODE;
	}
	else if ( Button[ KEY_3 ].Pressed() )
	{
		ToggleColToDis( SPRING_MODE );
		EditMode = SPRING_MODE;
	}
	else if ( Button[ KEY_4 ].Pressed() )
	{
		ToggleColToDis( DISPLAY_NODE_MODE );
		EditMode = DISPLAY_NODE_MODE;
	}
	else if ( Button[ KEY_5 ].Pressed() )
	{
		ToggleColToDis( PIVOT_HANDLE_MODE );
		EditMode = PIVOT_HANDLE_MODE;
	}
	else if ( Button[ KEY_6 ].Pressed() )
	{
		ToggleColToDis( FACE_MODE );
		EditMode = FACE_MODE;
	}
	else if ( Button[ KEY_7 ].Pressed() )
	{
		ToggleColToDis( TEXTURE_MODE );
		CurSelected.clear();
		EditMode = TEXTURE_MODE;
	}
	else if ( Button[ KEY_8 ].Pressed() )
	{
		ToggleColToDis( DRAWING_ORDER_MODE );
		EditMode = DRAWING_ORDER_MODE;
	}
	else if ( Button[ KEY_9 ].Pressed() )
	{
		EditMode = SUPER_MODE;
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::DrawSelected()
{
	glLineWidth( 4 );

	if( EditMode == NODE_MODE )
	{
		DrawNode( gfx::RGB( 0, 127, 255 ), CurrentNode );

		if( HasSphere[ CurrentNode ] )
		{
			for( size_t idx = 0; idx < Object[ CurrentObject ].Sphere.size(); idx++ ) {
				if ( Object[ CurrentObject ].Sphere[ idx ].Index == CurrentNode ) {
					DrawSphere( gfx::RGB( 0, 70, 127 ), idx );
				}
			}
		}
	}
	else if( EditMode == SPHERE_MODE )
	{
		DrawNode( gfx::RGB( 0, 70, 127 ), CurrentNode );

		if( HasSphere[ CurrentNode ] )
		{
			for( size_t idx = 0; idx < Object[ CurrentObject ].Sphere.size(); idx++ ) {
				if ( Object[ CurrentObject ].Sphere[ idx ].Index == CurrentNode ) {
					DrawSphere( gfx::RGB( 0, 127, 255 ), idx );
				}
			}
		}
	}
	else if( EditMode == SPRING_MODE )
	{
		if( Object[ CurrentObject ].Spring.size() > 0 )
		{
			DrawSpring( gfx::RGB( 0, 127, 255 ), CurrentSpring );
		}
	}
	else if( EditMode == DISPLAY_NODE_MODE || EditMode == PIVOT_HANDLE_MODE )
	{
		if( DisplayMesh[ CurrentObject ].size() > 0 )
		{
			// Draws the currently selected Display Node //
			gfx::Circle( 
				DisplayMesh[ CurrentObject ].Pos( CurrentNode ),
				1,
				gfx::RGB( 0, 127, 255 ) );
			// Draws the Handle //
			DrawNode( gfx::RGB( 127, 0, 127 ),
				DisplayMesh[ CurrentObject ].Handle( CurrentNode ) );

			if( HasSphere[ DisplayMesh[ CurrentObject ].Handle( CurrentNode ) ] )
			{
				for( size_t idx = 0; idx < Object[ CurrentObject ].Sphere.size(); idx++ ) {
					if ( int( Object[ CurrentObject ].Sphere[ idx ].Index ) ==
						 DisplayMesh[ CurrentObject ].Handle( CurrentNode ) ) {
						DrawSphere( gfx::RGB( 127, 0, 127 ), idx );
					}
				}
			}
			// Draws the Pivot //
			DrawNode( gfx::RGB( 0, 127, 127 ),
				DisplayMesh[ CurrentObject ].Pivot( CurrentNode ) );

			if( HasSphere[ DisplayMesh[ CurrentObject ].Pivot( CurrentNode ) ] )
			{
				for( size_t idx = 0; idx < Object[ CurrentObject ].Sphere.size(); idx++ ) {
					if ( int( Object[ CurrentObject ].Sphere[ idx ].Index ) ==
						 DisplayMesh[ CurrentObject ].Pivot( CurrentNode ) ) {
						DrawSphere( gfx::RGB( 0, 127, 127 ), idx );
					}
				}
			}
		}
	}
	else if( EditMode == FACE_MODE || EditMode == TEXTURE_MODE )
	{
		if( DisplayMesh[ CurrentObject ].Face.size() > 0 )
		{	
			gfx::Line( 
				DisplayMesh[ CurrentObject ].Pos(
					DisplayMesh[ CurrentObject ].Face[CurrentFace].Vertex.a ),
				DisplayMesh[ CurrentObject ].Pos(
					DisplayMesh[ CurrentObject ].Face[CurrentFace].Vertex.b ),
				gfx::RGB( 0, 0, 150 )
			);
			gfx::Line( 
				DisplayMesh[ CurrentObject ].Pos(
					DisplayMesh[ CurrentObject ].Face[CurrentFace].Vertex.b ),
				DisplayMesh[ CurrentObject ].Pos(
					DisplayMesh[ CurrentObject ].Face[CurrentFace].Vertex.c ),
				gfx::RGB( 0, 0, 150 )
			);
			gfx::Line( 
				DisplayMesh[ CurrentObject ].Pos(
					DisplayMesh[ CurrentObject ].Face[CurrentFace].Vertex.c ),
				DisplayMesh[ CurrentObject ].Pos(
					DisplayMesh[ CurrentObject ].Face[CurrentFace].Vertex.a ),
				gfx::RGB( 0, 0, 150 )
			);
			
			// Draws the currently selected Face Node 0 //
			gfx::Circle( 
				DisplayMesh[ CurrentObject ].Pos(
					DisplayMesh[ CurrentObject ].Face[CurrentFace].Vertex.a ),
				1,
				gfx::RGB( 150, 0, 0 ) );
			// Draws the currently selected Face Node 1 //
			gfx::Circle( 
				DisplayMesh[ CurrentObject ].Pos(
					DisplayMesh[ CurrentObject ].Face[CurrentFace].Vertex.b ),
				1,
				gfx::RGB( 0, 150, 0 ) );
			// Draws the currently selected Face Node 2 //
			gfx::Circle( 
				DisplayMesh[ CurrentObject ].Pos(
					DisplayMesh[ CurrentObject ].Face[CurrentFace].Vertex.c ),
				1,
				gfx::RGB( 0, 0, 150 ) );
		}
	}
	glLineWidth( 1.5 );
}
// - ------------------------------------------------------------------------------------------ - //
Vector2D cMesh2DEdit::CalcMousePos()
{
	Vector2D tempMousPos = Vector2D(
			Real( ( int( Mouse.x * Real( cGlobal::HudW ) ) )
			- ( -Camera->Pos.x / Real( Camera->Pos.z / cGlobal::HudZoom ) )
			- ( ( Real(cGlobal::HudW) * Real( 0.75 ) ) / Real(2) ) )
			* Real( Camera->Pos.z / cGlobal::HudZoom ),
			Real( ( int( -Mouse.y * Real( cGlobal::HudH ) ) )
			+ ( Camera->Pos.y / Real( Camera->Pos.z / cGlobal::HudZoom  ) )
			+ ( cGlobal::HudH >> 1 ) )
			* Real( Camera->Pos.z / cGlobal::HudZoom )
	);

	return tempMousPos;
}
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::ActiveAction()
{
	cDisplayMesh tempTexObj;
		DisplayMesh.push_back( tempTexObj );

	Mesh2DInfo[CurrentObject].UndoObject.push_back(
		cCompleteMesh( Object[ CurrentObject ], tempTexObj )
	);
	
	Mesh2DInfo[CurrentObject].UndoObject.back().DisplayMesh = DisplayMesh[ CurrentObject ];
	
	Mesh2DInfo[CurrentObject].isSaved = false;
	if( Mesh2DInfo[CurrentObject].UndoObject.size() > 1 )
	{
		Mesh2DInfo[CurrentObject].RedoObject.clear();
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::Undo()
{
	// Resets the zoom
	if ( Button[ KEY_TAB ].Pressed() )
	{
		Scale = Real::One;

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
		PreviewCamera->Pos.z = 500;
		
		PreviewCamera->View.x = PreviewCamera->Pos.x;
		PreviewCamera->View.y = PreviewCamera->Pos.y;
		PreviewCamera->View.z = 0.0;


	//	UVOrigin = Vector2D( -( UVScale / Real( 2 ) ), -( UVScale / Real( 2 ) ) );
	//	UVZoom = Real( -612.0 );
	}
	
	if( Button[ KEY_LCTRL ] )
	{
		// Undo the last action //
		if( Button[ KEY_Z ].Pressed() )
		{
			if( Mesh2DInfo[CurrentObject].UndoObject.size() > 1 )
			{
				Mesh2DInfo[CurrentObject].RedoObject.push_back(
					Mesh2DInfo[CurrentObject].UndoObject.back()
				);

				Mesh2DInfo[CurrentObject].UndoObject.pop_back();
				
				if( !Mesh2DInfo[CurrentObject].UndoObject.empty() )
				{
					Object[ CurrentObject ] =
						Mesh2DInfo[CurrentObject].UndoObject.back().SphereObject;
					DisplayMesh[ CurrentObject ] =
						Mesh2DInfo[CurrentObject].UndoObject.back().DisplayMesh;
					CurrentSpring = 0;
					CurrentNode = 0;
					CurrentFace = 0;
				}
				if( EditMode != TEXTURE_MODE )
				{
					CurSelected.clear();
				}
				SphereCheck();
			}
		}
		// Redo the undo action //
		if( Button[ KEY_Y ].Pressed() )
		{	
			if( !Mesh2DInfo[CurrentObject].RedoObject.empty() )
			{
				Mesh2DInfo[CurrentObject].UndoObject.push_back(
					Mesh2DInfo[CurrentObject].RedoObject.back()
				);
				Mesh2DInfo[CurrentObject].RedoObject.pop_back();
				
				Object[ CurrentObject ] = Mesh2DInfo[CurrentObject].UndoObject.back().SphereObject;
				DisplayMesh[ CurrentObject ] =
					Mesh2DInfo[CurrentObject].UndoObject.back().DisplayMesh;
				CurrentSpring = 0;
				CurrentNode = 0;
				SphereCheck();
			}
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::DrawGroupAction()
{
	if( CheckViewOne() )
	{
		if( !isGroupMove )
		{
			if( EditMode == NODE_MODE || EditMode == SPHERE_MODE || EditMode == SPRING_MODE )
			{	
				DrawColSelect();
			}
			else if( EditMode == DISPLAY_NODE_MODE || EditMode == FACE_MODE )
			{
				DrawDisSelect();
			}
			else if( EditMode == TEXTURE_MODE )
			{
				DrawDisSelectFace();	
			}
		}
	}
	// Draw Selected Nodes //
	if( EditMode == NODE_MODE || EditMode == SPRING_MODE )
	{
		for( size_t idx = 0; idx < CurSelected.size(); ++idx )
		{
			DrawNode( gfx::RGB( 0, 200, 100 ), CurSelected[idx] );
			if( HasSphere[ CurSelected[idx] ] )
			{
				for( size_t sphere = 0; sphere < Object[ CurrentObject ].size(); ++sphere )
				{
					if ( Object[ CurrentObject ].Sphere[ sphere ].Index == CurSelected[idx] )
					{
						DrawSphere( gfx::RGB( 0, 100, 50 ), sphere );
					}
				}
			}
		}
	}
	else if( EditMode == SPHERE_MODE )
	{	
		for( size_t idx = 0; idx < CurSelected.size(); ++idx )
		{
			DrawNode( gfx::RGB( 0, 100, 50 ), CurSelected[idx] );
			if( HasSphere[ CurSelected[idx] ] )
			{
				for( size_t sphere = 0; sphere < Object[ CurrentObject ].size(); ++sphere )
				{
					if ( Object[ CurrentObject ].Sphere[ sphere ].Index == CurSelected[idx] )
					{
						DrawSphere( gfx::RGB( 0, 200, 100 ), sphere );
					}
				}
			}
		}
	}
	else if( EditMode == DISPLAY_NODE_MODE || EditMode == FACE_MODE )
	{	
		for( size_t idx = 0; idx < CurSelected.size(); ++idx )
		{
			gfx::Circle( 
				DisplayMesh[ CurrentObject ].Pos( CurSelected[idx] ),
				1,
				gfx::RGB( 0, 100, 50 ) );
		}
	}
	else if( EditMode == TEXTURE_MODE )
	{	
		for( size_t idx = 0; idx < CurSelected.size(); ++idx )
		{
			gfx::Line( 
				DisplayMesh[ CurrentObject ].Pos(
					DisplayMesh[ CurrentObject ].Face[ CurSelected[idx] ].Vertex.a ),
				DisplayMesh[ CurrentObject ].Pos(
					DisplayMesh[ CurrentObject ].Face[ CurSelected[idx] ].Vertex.b ),
				gfx::RGB( 0, 150, 50 )
			);
			gfx::Line( 
				DisplayMesh[ CurrentObject ].Pos(
					DisplayMesh[ CurrentObject ].Face[ CurSelected[idx] ].Vertex.b ),
				DisplayMesh[ CurrentObject ].Pos(
					DisplayMesh[ CurrentObject ].Face[ CurSelected[idx] ].Vertex.c ),
				gfx::RGB( 0, 150, 50 )
			);
			gfx::Line( 
				DisplayMesh[ CurrentObject ].Pos(
					DisplayMesh[ CurrentObject ].Face[ CurSelected[idx] ].Vertex.c ),
				DisplayMesh[ CurrentObject ].Pos(
					DisplayMesh[ CurrentObject ].Face[ CurSelected[idx] ].Vertex.a ),
				gfx::RGB( 0, 150, 50 )
			);
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::ToggleColToDis( int Mode )
{
	if( EditMode < 3 && Mode >= 3 )
	{
		CurSelected.clear();
		CurrentSpring = 0;
		CurrentNode = 0;
	}
	else if( EditMode >= 3 && Mode < 3 )
	{
		CurSelected.clear();
		CurrentSpring = 0;
		CurrentNode = 0;
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::KeepWithinBox()
{
	
}
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
