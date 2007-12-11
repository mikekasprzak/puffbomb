#ifdef EDITOR
// - ------------------------------------------------------------------------------------------ - //
#include "Mesh2DEdit.h"

#include <String/String.h>
#include <Font/Fonts.h>
// - ------------------------------------------------------------------------------------------ - //
#include <iomanip>
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::DisplayText()
{
	if( Object[ CurrentObject ].size() > 0 )
	{
		if( EditMode == NODE_MODE || EditMode == SPHERE_MODE )
		{
			DisplayNodeInfo();
		
			if( HasSphere[ CurrentNode ] )
			{
				DisplaySphereInfo();
			}
		}
		else if( EditMode == SPRING_MODE )
		{	
			DisplaySpringInfo();
		}
		else if( EditMode == DISPLAY_NODE_MODE || EditMode == PIVOT_HANDLE_MODE )
		{	
			DisplayDisNodeInfo();
		}
		else if( EditMode == FACE_MODE )
		{	
			DisplayDisFaceInfo();
		}
		else if( EditMode == TEXTURE_MODE )
		{	
			DisplayDisFaceInfo();
			DisplayTextureInfo();
		}
		else if( EditMode == SUPER_MODE )
		{	
			DisplaySuperInfo();
		}
	}
	
	Real FontSize = 0.5;
	
	int Color = gfx::RGBA( 255, 255, 255, 255 );
	std::stringstream Temp;
	
	// Displays the Body2d name //
	// - ---------------------------------------------------------------------------------- - //
	Temp << "Name  -    " << String::BaseName( Mesh2DInfo[CurrentObject].MeshName );

	cFonts::FlangeLight.Write(
		Temp.str(),
		Vector3D( Global::Left, Global::Top - Real( 60 ), 0.0 ),
		FontSize,
		Color
	);
	
	DisplayMode();
	DisplaySavedStatus();
}
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::DisplayNodeInfo()
{	
	if( Object[ CurrentObject ].size() > 0 )
	{
		Real FontSize = 0.5;
		Real XShift = 120;
		Real YShift = 40;
		Real XPos = 0;
		
		int Color = gfx::RGBA( 255, 255, 255, 255 );
		std::stringstream Temp;
		
		// Displays the current node number //
		// - ---------------------------------------------------------------------------------- - //
		cFonts::FlangeLight.Write(
			"Node #",
			Vector3D( Global::Left + XPos, Global::Bottom + YShift, 0.0 ),
			FontSize,
			Color
		);
		
		Temp << CurrentNode;
	
		cFonts::FlangeLight.Write(
			Temp.str(),
			Vector3D( Global::Left + XPos, Global::Bottom + Real( 6 ), 0.0 ),
			FontSize,
			Color
		);
		XPos += XShift;
		Temp.str(std::string());
		// Displays the X location of the node //
		// - ---------------------------------------------------------------------------------- - //
		cFonts::FlangeLight.Write(
			"Node X",
			Vector3D( Global::Left + XPos, Global::Bottom + YShift, 0.0 ),
			FontSize,
			Color
		);
		
		Temp << Object[ CurrentObject ].Pos( CurrentNode ).x;
	
		cFonts::FlangeLight.Write(
			Temp.str(),
			Vector3D( Global::Left + XPos, Global::Bottom + Real( 6 ), 0.0 ),
			FontSize,
			Color
		);
		XPos += XShift;
		Temp.str(std::string());
		// Displays the Y location of the node //
		// - ---------------------------------------------------------------------------------- - //
		cFonts::FlangeLight.Write(
			"Node Y",
			Vector3D( Global::Left + XPos, Global::Bottom + YShift, 0.0 ),
			FontSize,
			Color
		);
		
		Temp << Object[ CurrentObject ].Pos( CurrentNode ).y;
	
		cFonts::FlangeLight.Write(
			Temp.str(),
			Vector3D( Global::Left + XPos, Global::Bottom + Real( 6 ), 0.0 ),
			FontSize,
			Color
		);
		XPos += XShift;
		Temp.str(std::string());
		// Displays the current mass //
		// - ---------------------------------------------------------------------------------- - //
		cFonts::FlangeLight.Write(
			"Mass",
			Vector3D( Global::Left + XPos, Global::Bottom + YShift, 0.0 ),
			FontSize,
			Color
		);
		
		Temp << Object[ CurrentObject ].Mass[ CurrentNode ];
	
		cFonts::FlangeLight.Write(
			Temp.str(),
			Vector3D( Global::Left + XPos, Global::Bottom + Real( 6 ), 0.0 ),
			FontSize,
			Color
		);
		XPos += XShift * Real( 4 );

		// Displays if the current node is hard //
		if( ColIsLocked( CurrentNode ) )
		{
			cFonts::FlangeLight.Write(
			"Hard Node",
			Vector3D( Global::Left + XPos, Global::Bottom + YShift, 0.0 ),
			FontSize,
			Color
			);
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::DisplaySphereInfo()
{
	for( size_t idx = 0; idx < Object[ CurrentObject ].Sphere.size(); idx++ )
	{
		if ( Object[ CurrentObject ].Sphere[ idx ].Index == CurrentNode )
		{
			Real FontSize = 0.5;
			Real XShift = 140;
			Real YShift = 40;
			Real XPos = 480;
			
			int Color = gfx::RGBA( 255, 255, 255, 255 );
			std::stringstream Temp;
			
			// Displays the Sphere Number //
			// - ------------------------------------------------------------------------------ - //
			cFonts::FlangeLight.Write(
				"Sphere #",
				Vector3D( Global::Left + XPos, Global::Bottom + YShift, 0.0 ),
				FontSize,
				Color
			);
			
			Temp << idx;
		
			cFonts::FlangeLight.Write(
				Temp.str(),
				Vector3D( Global::Left + XPos, Global::Bottom + Real( 6 ), 0.0 ),
				FontSize,
				Color
			);
			XPos += XShift;
			Temp.str(std::string());
				
			// Displays the Radius of the Sphere //
			// - ------------------------------------------------------------------------------ - //
			cFonts::FlangeLight.Write(
				"Radius",
				Vector3D( Global::Left + XPos, Global::Bottom + YShift, 0.0 ),
				FontSize,
				Color
			);
			
			Temp << Object[ CurrentObject ].Sphere[ idx ].Radius;
		
			cFonts::FlangeLight.Write(
				Temp.str(),
				Vector3D( Global::Left + XPos, Global::Bottom + Real( 6 ), 0.0 ),
				FontSize,
				Color
			);
		}	
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::DisplaySpringInfo()
{
	if( Object[ CurrentObject ].Spring.size() > 0 )
	{
		Real FontSize = 0.5;
		Real XShift = 140;
		Real YShift = 40;
		Real XPos = 0;
		
		int Color = gfx::RGBA( 255, 255, 255, 255 );
		std::stringstream Temp;
		
		// Displays current spring number //
		// - ---------------------------------------------------------------------------------- - //
		cFonts::FlangeLight.Write(
			"Spring #",
			Vector3D( Global::Left + XPos, Global::Bottom + YShift, 0.0 ),
			FontSize,
			Color
		);
		
		Temp << CurrentSpring;
	
		cFonts::FlangeLight.Write(
			Temp.str(),
			Vector3D( Global::Left + XPos, Global::Bottom + Real( 6 ), 0.0 ),
			FontSize,
			Color
		);
		XPos += XShift;
		Temp.str(std::string());
		// Displays current node A number //
		// - ---------------------------------------------------------------------------------- - //
		cFonts::FlangeLight.Write(
			"Node A",
			Vector3D( Global::Left + XPos, Global::Bottom + YShift, 0.0 ),
			FontSize,
			Color
		);
		
		Temp << Object[ CurrentObject ].Spring[CurrentSpring].IndexA;
	
		cFonts::FlangeLight.Write(
			Temp.str(),
			Vector3D( Global::Left + XPos, Global::Bottom + Real( 6 ), 0.0 ),
			FontSize,
			Color
		);
		XPos += XShift;
		Temp.str(std::string());
		// Displays current node B number //
		// - ---------------------------------------------------------------------------------- - //
		cFonts::FlangeLight.Write(
			"Node B",
			Vector3D( Global::Left + XPos, Global::Bottom + YShift, 0.0 ),
			FontSize,
			Color
		);
		
		Temp << Object[ CurrentObject ].Spring[CurrentSpring].IndexB;
	
		cFonts::FlangeLight.Write(
			Temp.str(),
			Vector3D( Global::Left + XPos, Global::Bottom + Real( 6 ), 0.0 ),
			FontSize,
			Color
		);
		XPos += XShift;
		Temp.str(std::string());
		// Displays current spring strength //
		// - ---------------------------------------------------------------------------------- - //
		cFonts::FlangeLight.Write(
			"Strength",
			Vector3D( Global::Left + XPos, Global::Bottom + YShift, 0.0 ),
			FontSize,
			Color
		);
		
		Temp << Object[ CurrentObject ].Spring[CurrentSpring].Strength;
	
		cFonts::FlangeLight.Write(
			Temp.str(),
			Vector3D( Global::Left + XPos, Global::Bottom + Real( 6 ), 0.0 ),
			FontSize,
			Color
		);
		XPos += XShift;
		Temp.str(std::string());
		// Displays current spring length //
		// - ---------------------------------------------------------------------------------- - //
		cFonts::FlangeLight.Write(
			"Length",
			Vector3D( Global::Left + XPos, Global::Bottom + YShift, 0.0 ),
			FontSize,
			Color
		);
		
		Temp << Object[ CurrentObject ].Spring[CurrentSpring].Length;
	
		cFonts::FlangeLight.Write(
			Temp.str(),
			Vector3D( Global::Left + XPos, Global::Bottom + Real( 6 ), 0.0 ),
			FontSize,
			Color
		);
		XPos += XShift;
		Temp.str(std::string());
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::DisplayDisNodeInfo()
{
	if( DisplayMesh[ CurrentObject ].size() > 0 )
	{
		Real FontSize = 0.5;
		Real XShift = 120;
		Real YShift = 40;
		Real XPos = 0;
		
		int Color = gfx::RGBA( 255, 255, 255, 255 );
		std::stringstream Temp;
		
		// Displays the current display node number //
		// - ---------------------------------------------------------------------------------- - //
		cFonts::FlangeLight.Write(
			"Node #",
			Vector3D( Global::Left + XPos, Global::Bottom + YShift, 0.0 ),
			FontSize,
			Color
		);
		
		Temp << CurrentNode;
	
		cFonts::FlangeLight.Write(
			Temp.str(),
			Vector3D( Global::Left + XPos, Global::Bottom + Real( 6 ), 0.0 ),
			FontSize,
			Color
		);
		XPos += XShift;
		Temp.str(std::string());
		// Displays the X location of the display node //
		// - ---------------------------------------------------------------------------------- - //
		cFonts::FlangeLight.Write(
			"Node X",
			Vector3D( Global::Left + XPos, Global::Bottom + YShift, 0.0 ),
			FontSize,
			Color
		);
		
		Temp << DisplayMesh[ CurrentObject ].Pos( CurrentNode ).x;
	
		cFonts::FlangeLight.Write(
			Temp.str(),
			Vector3D( Global::Left + XPos, Global::Bottom + Real( 6 ), 0.0 ),
			FontSize,
			Color
		);
		XPos += XShift;
		Temp.str(std::string());
		// Displays the Y location of the display node //
		// - ---------------------------------------------------------------------------------- - //
		cFonts::FlangeLight.Write(
			"Node Y",
			Vector3D( Global::Left + XPos, Global::Bottom + YShift, 0.0 ),
			FontSize,
			Color
		);
		
		Temp << DisplayMesh[ CurrentObject ].Pos( CurrentNode ).y;
	
		cFonts::FlangeLight.Write(
			Temp.str(),
			Vector3D( Global::Left + XPos, Global::Bottom + Real( 6 ), 0.0 ),
			FontSize,
			Color
		);
		XPos += XShift;
		Temp.str(std::string());
		// Displays the handle of the display node //
		// - ---------------------------------------------------------------------------------- - //
		cFonts::FlangeLight.Write(
			"Handle",
			Vector3D( Global::Left + XPos, Global::Bottom + YShift, 0.0 ),
			FontSize,
			Color
		);
		
		Temp << DisplayMesh[ CurrentObject ].Handle( CurrentNode );
	
		cFonts::FlangeLight.Write(
			Temp.str(),
			Vector3D( Global::Left + XPos, Global::Bottom + Real( 6 ), 0.0 ),
			FontSize,
			Color
		);
		XPos += XShift;
		Temp.str(std::string());
		// Displays the pivot of the display node //
		// - ---------------------------------------------------------------------------------- - //
		cFonts::FlangeLight.Write(
			"Pivot",
			Vector3D( Global::Left + XPos, Global::Bottom + YShift, 0.0 ),
			FontSize,
			Color
		);
		
		Temp << DisplayMesh[ CurrentObject ].Pivot( CurrentNode );
	
		cFonts::FlangeLight.Write(
			Temp.str(),
			Vector3D( Global::Left + XPos, Global::Bottom + Real( 6 ), 0.0 ),
			FontSize,
			Color
		);
		XPos += XShift;
		Temp.str(std::string());

	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::DisplayDisFaceInfo()
{
	Real FontSize = 0.5;
	Real XShift = 120;
	Real YShift = 40;
	Real XPos = 0;
	
	int Color = gfx::RGBA( 255, 255, 255, 255 );
	std::stringstream Temp;

	if( DisplayMesh[ CurrentObject ].Face.size() > 0 )
	{
	
		// Displays the first node in the face //
		// - ---------------------------------------------------------------------------------- - //
		cFonts::FlangeLight.Write(
			"Node 0",
			Vector3D( Global::Left + XPos, Global::Bottom + YShift, 0.0 ),
			FontSize,
			Color
		);
		
		Temp << DisplayMesh[ CurrentObject ].Face[CurrentFace].Vertex.a;
	
		cFonts::FlangeLight.Write(
			Temp.str(),
			Vector3D( Global::Left + XPos, Global::Bottom + Real( 6 ), 0.0 ),
			FontSize,
			Color
		);
		XPos += XShift;
		Temp.str(std::string());
		// Displays the second node in the face //
		// - ---------------------------------------------------------------------------------- - //
		cFonts::FlangeLight.Write(
			"Node 1",
			Vector3D( Global::Left + XPos, Global::Bottom + YShift, 0.0 ),
			FontSize,
			Color
		);
		
		Temp << DisplayMesh[ CurrentObject ].Face[CurrentFace].Vertex.b;
	
		cFonts::FlangeLight.Write(
			Temp.str(),
			Vector3D( Global::Left + XPos, Global::Bottom + Real( 6 ), 0.0 ),
			FontSize,
			Color
		);
		XPos += XShift;
		Temp.str(std::string());
		// Displays the third node in the face //
		// - ---------------------------------------------------------------------------------- - //
		cFonts::FlangeLight.Write(
			"Node 2",
			Vector3D( Global::Left + XPos, Global::Bottom + YShift, 0.0 ),
			FontSize,
			Color
		);
		
		Temp << DisplayMesh[ CurrentObject ].Face[CurrentFace].Vertex.c;
	
		cFonts::FlangeLight.Write(
			Temp.str(),
			Vector3D( Global::Left + XPos, Global::Bottom + Real( 6 ), 0.0 ),
			FontSize,
			Color
		);
		XPos += XShift;
		Temp.str(std::string());

		// Displays the layer of the face //
		// - ---------------------------------------------------------------------------------- - //
		cFonts::FlangeLight.Write(
			"Layer",
			Vector3D( Global::Left + XPos, Global::Bottom + YShift, 0.0 ),
			FontSize,
			Color
		);
		
		Temp << DisplayMesh[ CurrentObject ].Face[ CurrentFace ].Layer;
	
		cFonts::FlangeLight.Write(
			Temp.str(),
			Vector3D( Global::Left + XPos, Global::Bottom + Real( 6 ), 0.0 ),
			FontSize,
			Color
		);
		XPos += XShift;
		Temp.str(std::string());
	}
	// Displays the first node in the face //
	// - -------------------------------------------------------------------------------------- - //
	Temp << "Working Layer " << CurLayer;

	cFonts::FlangeLight.Write(
		Temp.str(),
		Vector3D( Global::Left + Real( 20 ), Global::Top - Real( 30 ), 0.0 ),
		FontSize,
		Color
	);
}
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::DisplayTextureInfo()
{
	if( DisplayMesh[ CurrentObject ].TextureIdx != -1 )
	{
		Real FontSize = 0.5;
		
		int Color = gfx::RGBA( 255, 255, 255, 255 );
		std::stringstream Temp;
		
		// Displays the texture name //
		// - ---------------------------------------------------------------------------------- - //
		Temp << "Texture Name - " << TextureName[DisplayMesh[ CurrentObject ].TextureIdx];
	
		cFonts::FlangeLight.Write(
			Temp.str(),
			Vector3D( Global::Left, Global::Top - Real( 90 ), 0.0 ),
			FontSize,
			Color
		);
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::DisplaySuperInfo()
{
	Real TotalMass = 0.0;
	for( size_t idx = 0; idx < Object[ CurrentObject ].size(); idx++ )
	{
		TotalMass += Object[ CurrentObject ].Mass[ idx ];
	}
	Real FontSize = 0.5;
	Real XShift = 120;
	Real YShift = 40;
	Real XPos = 0;
	
	int Color = gfx::RGBA( 255, 255, 255, 255 );
	std::stringstream Temp;
	
	// Displays the Total Mass of the object //
	// - -------------------------------------------------------------------------------------- - //
	cFonts::FlangeLight.Write(
		"Total Mass",
		Vector3D( Global::Left + XPos, Global::Bottom + YShift, 0.0 ),
		FontSize,
		Color
	);
	
	Temp << TotalMass;

	cFonts::FlangeLight.Write(
		Temp.str(),
		Vector3D( Global::Left + XPos, Global::Bottom + Real( 6 ), 0.0 ),
		FontSize,
		Color
	);
}
// - ------------------------------------------------------------------------------------------ - //

void cMesh2DEdit::DisplayMode()
{
	// Displays the current mesh edit mode //
	// - -------------------------------------------------------------------------------------- - //
	Real FontSize = 0.5;
	int Color = gfx::RGBA( 100, 255, 100, 255 );
	Vector3D ModePos = Vector3D( Global::Right - Real( 750 ), Global::Top - Real( 40 ), 0.0 );
		
	switch( EditMode )
	{ 
		case NODE_MODE:
		{
			cFonts::FlangeLight.Write(
				"Collision Node Mode",
				ModePos,
				FontSize,
				Color
			);
			break;
		}
		case SPHERE_MODE:
		{
			cFonts::FlangeLight.Write(
				"Sphere Mode",
				ModePos,
				FontSize,
				Color
			);
			break;
		}
		case SPRING_MODE:
		{
			cFonts::FlangeLight.Write(
				"Spring Mode",
				ModePos,
				FontSize,
				Color
			);
			break;
		}
		case DISPLAY_NODE_MODE:
		{
			cFonts::FlangeLight.Write(
				"Display Node Mode",
				ModePos,
				FontSize,
				Color
			);
			break;
		}
		case PIVOT_HANDLE_MODE:
		{
			cFonts::FlangeLight.Write(
				"Pivot Handle Mode",
				ModePos,
				FontSize,
				Color
			);
			break;
		}
		case FACE_MODE:
		{
			cFonts::FlangeLight.Write(
				"Face Mode",
				ModePos,
				FontSize,
				Color
			);
			break;
		}
		case TEXTURE_MODE:
		{
			cFonts::FlangeLight.Write(
				"Texture Mode",
				ModePos,
				FontSize,
				Color
			);
			break;
		}
		case DRAWING_ORDER_MODE:
		{
			cFonts::FlangeLight.Write(
				"Drawing Order Mode",
				ModePos,
				FontSize,
				Color
			);
			break;
		}
		case SUPER_MODE:
		{
			cFonts::FlangeLight.Write(
				"Super Mode",
				ModePos,
				FontSize,
				Color
			);
			break;
		}
		default:
		{
			break;	
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::DisplaySavedStatus()
{
	// Displays the if the current map requires saving or not //
	// - -------------------------------------------------------------------------------------- - //
	if( Mesh2DInfo[ CurrentObject ].isSaved == false )
	{
		cFonts::FlangeLight.Write(
			"*",
			Vector3D( Global::Left, Global::Top - Real( 50 ), 0.0 ),
			Real( 1.0 ),
			gfx::RGBA( 255, 255, 255, 255 )
		);
	}
/*
	if( Mesh2DInfo[ CurrentObject ].isSaved == false )
	{
		// Displays the if the current mesh requires saving or not //
		// - ---------------------------------------------------------------------------------- - //
		TempLocation = Vector3D( -( Global::HudW >> 1 ),
			( Global::HudH >> 1 ) - 32,
			0 );
	
		TTFTextOut( "*", EditorFont, &TempLocation );
	}
*/
}
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::DisplayHelp()
{
	Real LeftCenter = Global::Left / Real( 2 );
	
	Real FontSize = 0.5;
	Real XShift = 120;
	Real YShift = 100;
	Real XPos = 50;
	
	Real NewLine = 30;
	
	int Color = gfx::RGBA( 255, 255, 255, 255 );
	
	cFonts::FlangeLight.Write(
		"-----------------------------------Global Keys-----------------------------------",
		Vector3D( LeftCenter + XPos, Global::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;
	cFonts::FlangeLight.Write(
		"F1                           Toggles the help menu",
		Vector3D( LeftCenter + XPos, Global::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;
	cFonts::FlangeLight.Write(
		"F2                          Toggles between Mesh and Map editors",
		Vector3D( LeftCenter + XPos, Global::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;
	cFonts::FlangeLight.Write(
		"F3                          Toggles between Game and editor",
		Vector3D( LeftCenter + XPos, Global::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;
	cFonts::FlangeLight.Write(
		"Wheel                  Zooms in and out of the map",
		Vector3D( LeftCenter + XPos, Global::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;
	cFonts::FlangeLight.Write(
		"Left | Right            Switches the current mesh",
		Vector3D( LeftCenter + XPos, Global::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;
	cFonts::FlangeLight.Write(
		"Tab                          Resets the zoom and origin",
		Vector3D( LeftCenter + XPos, Global::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	
	YShift += NewLine;
	cFonts::FlangeLight.Write(
		"Ctrl + Z                     Undo an active action",
		Vector3D( LeftCenter + XPos, Global::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	
	YShift += NewLine;
	cFonts::FlangeLight.Write(
		"Ctrl + Y                     Redo an active action",
		Vector3D( LeftCenter + XPos, Global::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	
	YShift += NewLine;
	cFonts::FlangeLight.Write(
		"Ctrl + S                     Save current Body2d and Mesh2d file",
		Vector3D( LeftCenter + XPos, Global::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;

	cFonts::FlangeLight.Write(
		"1                          Collision Node Mode",
		Vector3D( LeftCenter + XPos, Global::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;

	cFonts::FlangeLight.Write(
		"2                           Sphere Mode",
		Vector3D( LeftCenter + XPos, Global::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;

	cFonts::FlangeLight.Write(
		"3                           Spring Mode",
		Vector3D( LeftCenter + XPos, Global::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;

	cFonts::FlangeLight.Write(
		"4                           Display Node Mode",
		Vector3D( LeftCenter + XPos, Global::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;

	cFonts::FlangeLight.Write(
		"5                           Pivot Handle Mode",
		Vector3D( LeftCenter + XPos, Global::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;

	cFonts::FlangeLight.Write(
		"6                           Face Mode",
		Vector3D( LeftCenter + XPos, Global::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;

	cFonts::FlangeLight.Write(
		"7                           Texture Mode",
		Vector3D( LeftCenter + XPos, Global::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;

	cFonts::FlangeLight.Write(
		"8                           Drawing Order Mode",
		Vector3D( LeftCenter + XPos, Global::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;

	cFonts::FlangeLight.Write(
		"9                           Super Mode",
		Vector3D( LeftCenter + XPos, Global::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;

	cFonts::FlangeLight.Write(
		"-----------------------------------Node Mode-----------------------------------",
		Vector3D( LeftCenter + XPos, Global::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;

	cFonts::FlangeLight.Write(
		"LClick                               Select, move, or de-select nodes",
		Vector3D( LeftCenter + XPos, Global::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;

	cFonts::FlangeLight.Write(
		"Ctrl + LClick                       de-select node or nodes",
		Vector3D( LeftCenter + XPos, Global::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;

	cFonts::FlangeLight.Write(
		"Shift + LClick                     Add node to selected group",
		Vector3D( LeftCenter + XPos, Global::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;

	cFonts::FlangeLight.Write(
		"Ctrl + Wheel                       Increases or decreases mass by 1.0",
		Vector3D( LeftCenter + XPos, Global::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;

	cFonts::FlangeLight.Write(
		"Ctrl + +|-                                  Increases or decreases mass by 1.0",
		Vector3D( LeftCenter + XPos, Global::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;

	cFonts::FlangeLight.Write(
		"Ctrl + Shift + Wheel             Increases or decreases mass by 0.1",
		Vector3D( LeftCenter + XPos, Global::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;

	cFonts::FlangeLight.Write(
		"Up | Down                          Switches the currently selected node",
		Vector3D( LeftCenter + XPos, Global::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;

	cFonts::FlangeLight.Write(
		"A | Pad 0                                 Adds a new node",
		Vector3D( LeftCenter + XPos, Global::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;

	cFonts::FlangeLight.Write(
		"Delete                                Deletes currently selected nodes and spheres",
		Vector3D( LeftCenter + XPos, Global::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;

	cFonts::FlangeLight.Write(
		"Ctrl + Insert                       Copy currently selected nodes and spheres",
		Vector3D( LeftCenter + XPos, Global::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;

	cFonts::FlangeLight.Write(
		"Ctrl + C                              Copy currently selected nodes and spheres",
		Vector3D( LeftCenter + XPos, Global::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;

	cFonts::FlangeLight.Write(
		"Shift + Insert                       Pastes copied nodes and spheres",
		Vector3D( LeftCenter + XPos, Global::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;

	cFonts::FlangeLight.Write(
		"Ctrl + V                              Pastes copied nodes and spheres",
		Vector3D( LeftCenter + XPos, Global::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;

	cFonts::FlangeLight.Write(
		"L                                           Toggles a node to lock or unlock to the scenary",
		Vector3D( LeftCenter + XPos, Global::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;

	cFonts::FlangeLight.Write(
		"----------------------------------Sphere Mode----------------------------------",
		Vector3D( LeftCenter + XPos, Global::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;

	cFonts::FlangeLight.Write(
		"LClick                                   Select, move, or de-select nodes",
		Vector3D( LeftCenter + XPos, Global::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;

	cFonts::FlangeLight.Write(
		"Ctrl + LClick                        de-select node or nodes",
		Vector3D( LeftCenter + XPos, Global::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;

	cFonts::FlangeLight.Write(
		"Shift + LClick                     Add node to selected group",
		Vector3D( LeftCenter + XPos, Global::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;

	cFonts::FlangeLight.Write(
		"Ctrl + Wheel                   Increases or decreases radius by 1.0",
		Vector3D( LeftCenter + XPos, Global::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;

	cFonts::FlangeLight.Write(
		"Ctrl + +|-                                Increases or decreases radius by 1.0",
		Vector3D( LeftCenter + XPos, Global::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;

	cFonts::FlangeLight.Write(
		"Ctrl + Shift + Wheel        Increases or decreases radius by 0.1",
		Vector3D( LeftCenter + XPos, Global::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;

	cFonts::FlangeLight.Write(
		"Ctrl + Shift + +|-             Increases or decreases radius by 0.1",
		Vector3D( LeftCenter + XPos, Global::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;

	cFonts::FlangeLight.Write(
		"Up | Down                       Switches the currently selected node",
		Vector3D( LeftCenter + XPos, Global::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;

	cFonts::FlangeLight.Write(
		"A | Pad 0                        Adds a new sphere to the current node",
		Vector3D( LeftCenter + XPos, Global::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;

	cFonts::FlangeLight.Write(
		"Delete                             Deletes currently selected spheres",
		Vector3D( LeftCenter + XPos, Global::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;

	cFonts::FlangeLight.Write(
		"-----------------------------------Spring Mode-----------------------------------",
		Vector3D( LeftCenter + XPos, Global::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;

	cFonts::FlangeLight.Write(
		"Up | Down                       Switches the currently selected spring",
		Vector3D( LeftCenter + XPos, Global::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;

	cFonts::FlangeLight.Write(
		"A | Pad 0                        Adds a new spring between selected nodes",
		Vector3D( LeftCenter + XPos, Global::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;

	cFonts::FlangeLight.Write(
		"Delete                                Deletes currently selected spring",
		Vector3D( LeftCenter + XPos, Global::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;

	cFonts::FlangeLight.Write(
		"------------------------------Display Node Mode------------------------------",
		Vector3D( LeftCenter + XPos, Global::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;
	cFonts::FlangeLight.Write(
		"LClick                              Select, move, or de-select nodes",
		Vector3D( LeftCenter + XPos, Global::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;
	cFonts::FlangeLight.Write(
		"Ctrl + LClick                    de-select node or nodes",
		Vector3D( LeftCenter + XPos, Global::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;
	cFonts::FlangeLight.Write(
		"Shift + LClick                  Add node to selected group",
		Vector3D( LeftCenter + XPos, Global::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;
	cFonts::FlangeLight.Write(
		"Up | Down                      Switches the currently selected node",
		Vector3D( LeftCenter + XPos, Global::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;
	cFonts::FlangeLight.Write(
		"A | Pad 0                         Adds a new node",
		Vector3D( LeftCenter + XPos, Global::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;
	cFonts::FlangeLight.Write(
		"Delete                             Deletes currently selected nodes",
		Vector3D( LeftCenter + XPos, Global::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;
	cFonts::FlangeLight.Write(
		"-------------------------------Pivot Handle Mode-------------------------------",
		Vector3D( LeftCenter + XPos, Global::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;
	cFonts::FlangeLight.Write(
		"LClick                              Selects nodes, and sets the pivot",
		Vector3D( LeftCenter + XPos, Global::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;
	cFonts::FlangeLight.Write(
		"RClick                               Sets the handle",
		Vector3D( LeftCenter + XPos, Global::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;
	cFonts::FlangeLight.Write(
		"-----------------------------------Face Mode-----------------------------------",
		Vector3D( LeftCenter + XPos, Global::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;
	cFonts::FlangeLight.Write(
		"LClick                            Select, move, or de-select nodes",
		Vector3D( LeftCenter + XPos, Global::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;
	cFonts::FlangeLight.Write(
		"Ctrl + LClick                  de-select node or nodes",
		Vector3D( LeftCenter + XPos, Global::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;
	cFonts::FlangeLight.Write(
		"Shift + LClick                Add node to selected group",
		Vector3D( LeftCenter + XPos, Global::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;
	cFonts::FlangeLight.Write(
		"Up | Down                    Switches the currently selected face",
		Vector3D( LeftCenter + XPos, Global::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;
	cFonts::FlangeLight.Write(
		"A | Pad 0                      Adds a new face ( Must have 3 nodes selected )",
		Vector3D( LeftCenter + XPos, Global::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;
	cFonts::FlangeLight.Write(
		"Delete                            Deletes all faces that are attached to the",
		Vector3D( LeftCenter + XPos, Global::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;
	cFonts::FlangeLight.Write(
		"----------------------------------Texture Mode----------------------------------",
		Vector3D( LeftCenter + XPos, Global::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;
	cFonts::FlangeLight.Write(
		"LClick                           Select, move, or de-select faces and uv coordinates",
		Vector3D( LeftCenter + XPos, Global::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;
	cFonts::FlangeLight.Write(
		"Ctrl + LClick                  de-select face or faces and uv coordinates",
		Vector3D( LeftCenter + XPos, Global::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;
	cFonts::FlangeLight.Write(
		"Shift + LClick                Add face and uv coordinates to selected group",
		Vector3D( LeftCenter + XPos, Global::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;
	cFonts::FlangeLight.Write(
		"A | Pad 0                        Adds a new texture",
		Vector3D( LeftCenter + XPos, Global::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;
	cFonts::FlangeLight.Write(
		"Delete                            Deletes the texture",
		Vector3D( LeftCenter + XPos, Global::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;
	cFonts::FlangeLight.Write(
		"Pad +|-                         Changes the current layer",
		Vector3D( LeftCenter + XPos, Global::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;
	cFonts::FlangeLight.Write(
		"F5 | F6                           Switches between the current texture",
		Vector3D( LeftCenter + XPos, Global::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;
	cFonts::FlangeLight.Write(
		"T                                     Rotates the uv coordinates by 180 degrees",
		Vector3D( LeftCenter + XPos, Global::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;
	cFonts::FlangeLight.Write(
		"R                                      Rotates the 1st, 2nd, and 3rd uv coordinate",
		Vector3D( LeftCenter + XPos, Global::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;
	cFonts::FlangeLight.Write(
		"I                                       Inverts the 1st, 2nd uv coordinate",
		Vector3D( LeftCenter + XPos, Global::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
}
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
