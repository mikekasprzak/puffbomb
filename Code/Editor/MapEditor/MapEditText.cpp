#ifdef EDITOR
// - ------------------------------------------------------------------------------------------ - //
#include "MapEdit.h"
#include <Font/Fonts.h>
// - ------------------------------------------------------------------------------------------ - //
#include <iomanip>
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::DisplayText()
{
	if( CurMode == ZONE_MODE )
	{
//		if( Game->Zone.size() > 0 ) // Removed because of game dependency //
		{
			DisplayZoneInfo();
		}
	}
	else if( CurMode == OBJECT_MODE )
	{
		if( MapObject.size() > 0 )
		{
			DisplayMesh2DInfo();
		}
	}

	DisplaySavedStatus();

	DisplayMapName();
	DisplayMesh3dName();
	
/*	
	Real FontSize = 0.5;
	Real XShift = 4;
	Real YShift = 55;
	Real XPos = 0;
	
	int Color = gfx::RGBA( 255, 255, 255, 255 );
	XPos += XShift;
	
	// Displays the current working directory //
	// - -------------------------------------------------------------------------------------- - //
	cFonts::FlangeLight.Write(
		CurrentDir,
		Vector3D( cGlobal::Left + XPos, cGlobal::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
*/

}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::DisplaySavedStatus()
{
	// Displays the if the current map requires saving or not //
	// - ---------------------------------------------------------------------------------- - //
	if( isSaved == false )
	{
		cFonts::FlangeLight.Write(
			"*",
			Vector3D( cGlobal::Left, cGlobal::Top - Real( 50 ), 0.0 ),
			Real( 1.0 ),
			gfx::RGBA( 255, 255, 255, 255 )
		);
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::DisplayHelp()
{
	Real LeftCenter = cGlobal::Left / Real( 2 );
	
	
	Real FontSize = 0.5;
	Real XShift = 120;
	Real YShift = 100;
	Real XPos = 50;
	
	Real NewLine = 30;
	
	int Color = gfx::RGBA( 255, 255, 255, 255 );
	
	cFonts::FlangeLight.Write(
		"--------------------------------------Keys--------------------------------------",
		Vector3D( LeftCenter + XPos, cGlobal::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;
	cFonts::FlangeLight.Write(
		"F1                           Toggles the help menu",
		Vector3D( LeftCenter + XPos, cGlobal::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;
	cFonts::FlangeLight.Write(
		"F2                          Toggles between Mesh and Map editors",
		Vector3D( LeftCenter + XPos, cGlobal::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;
	cFonts::FlangeLight.Write(
		"F3                          Toggles between Game and editor",
		Vector3D( LeftCenter + XPos, cGlobal::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;
	cFonts::FlangeLight.Write(
		"Wheel                  Zooms in and out of the map",
		Vector3D( LeftCenter + XPos, cGlobal::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;
	cFonts::FlangeLight.Write(
		"Left | Right            Switches the current mesh",
		Vector3D( LeftCenter + XPos, cGlobal::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;
	cFonts::FlangeLight.Write(
		"Tab                          Resets the zoom and origin",
		Vector3D( LeftCenter + XPos, cGlobal::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	
	YShift += NewLine;
	cFonts::FlangeLight.Write(
		"Ctrl + Z                     Undo an active action",
		Vector3D( LeftCenter + XPos, cGlobal::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	
	YShift += NewLine;
	cFonts::FlangeLight.Write(
		"Ctrl + Y                     Redo an active action",
		Vector3D( LeftCenter + XPos, cGlobal::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	
	YShift += NewLine;
	cFonts::FlangeLight.Write(
		"Ctrl + S                     Save current map file",
		Vector3D( LeftCenter + XPos, cGlobal::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	
	YShift += NewLine;
	cFonts::FlangeLight.Write(
		"LClick                               Select, move, or de-select mesh",
		Vector3D( LeftCenter + XPos, cGlobal::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	
	YShift += NewLine;
	cFonts::FlangeLight.Write(
		"Ctrl + LClick                de-select mesh or meshes",
		Vector3D( LeftCenter + XPos, cGlobal::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	
	YShift += NewLine;
	cFonts::FlangeLight.Write(
		"Shift + LClick             Add mesh to selected group",
		Vector3D( LeftCenter + XPos, cGlobal::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	
	YShift += NewLine;
	cFonts::FlangeLight.Write(
		"A | Pad 0                       Adds a new mesh",
		Vector3D( LeftCenter + XPos, cGlobal::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;
	cFonts::FlangeLight.Write(
		"Delete                        Deletes currently selected mesh, zone, mesh3d",
		Vector3D( LeftCenter + XPos, cGlobal::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;
	cFonts::FlangeLight.Write(
		"Ctrl + Insert                     Copy currently selected body2d and mesh2d",
		Vector3D( LeftCenter + XPos, cGlobal::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;
	cFonts::FlangeLight.Write(
		"Ctrl + C                       Copy currently selected mesh",
		Vector3D( LeftCenter + XPos, cGlobal::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;
	cFonts::FlangeLight.Write(
		"Shift + Insert                 Pastes copied meshes",
		Vector3D( LeftCenter + XPos, cGlobal::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;
	cFonts::FlangeLight.Write(
		"Ctrl + V                             Pastes copied meshes",
		Vector3D( LeftCenter + XPos, cGlobal::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;
	cFonts::FlangeLight.Write(
		"Pad +|-                     Switches between the current model",
		Vector3D( LeftCenter + XPos, cGlobal::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;
	cFonts::FlangeLight.Write(
		"1                                               Switches to Object Mode",
		Vector3D( LeftCenter + XPos, cGlobal::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;
	cFonts::FlangeLight.Write(
		"2                                         Switches to Zone Mode",
		Vector3D( LeftCenter + XPos, cGlobal::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;
	cFonts::FlangeLight.Write(
		"3                                 Switches to Tile Mode",
		Vector3D( LeftCenter + XPos, cGlobal::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;
	cFonts::FlangeLight.Write(
		"Q | W                             Switches the current Zone ID",
		Vector3D( LeftCenter + XPos, cGlobal::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
	YShift += NewLine;
	cFonts::FlangeLight.Write(
		"Z | X                          Switches The current Zone Arg",
		Vector3D( LeftCenter + XPos, cGlobal::Top - YShift, 0.0 ),
		FontSize,
		Color
	);

/*		
	
//	TempLocation.y -= newline;
//	TTFTextOut( "F + 1                         - Sets Focus 1", EditorFont, &TempLocation );
//
//	TempLocation.y -= newline;
//	TTFTextOut( "F + 2                         - Sets Focus 2", EditorFont, &TempLocation );

*/
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::DisplayMesh2DInfo()
{
	Real FontSize = 0.5;
	Real XShift = 120;
	Real YShift = 40;
	Real XPos = 0;
	
	int Color = gfx::RGBA( 255, 255, 255, 255 );
	
	// Displays the current object number //
	// - -------------------------------------------------------------------------------------- - //
	std::stringstream Temp;
	
	cFonts::FlangeLight.Write(
		"Object #",
		Vector3D( cGlobal::Left + XPos, cGlobal::Bottom + YShift, 0.0 ),
		FontSize,
		Color
	);
	
	Temp << CurrentObject;

	cFonts::FlangeLight.Write(
		Temp.str(),
		Vector3D( cGlobal::Left + XPos, cGlobal::Bottom + Real( 6 ), 0.0 ),
		FontSize,
		Color
	);
	XPos += XShift;
	Temp.str(std::string());
	
	// Displays the X location of the object //
	// - -------------------------------------------------------------------------------------- - //
	cFonts::FlangeLight.Write(
		"Object X",
		Vector3D( cGlobal::Left + XPos, cGlobal::Bottom + YShift, 0.0 ),
		FontSize,
		Color
	);
	
	Temp << MapObject[CurrentObject].Pos.x;
	TempString = Temp.str();

	cFonts::FlangeLight.Write(
		Temp.str(),
		Vector3D( cGlobal::Left + XPos, cGlobal::Bottom + Real( 6 ), 0.0 ),
		FontSize,
		Color
	);

	XPos += XShift;
	Temp.str(std::string());

	// Displays the Y location of the object //
	// - -------------------------------------------------------------------------------------- - //
	cFonts::FlangeLight.Write(
		"Object Y",
		Vector3D( cGlobal::Left + XPos, cGlobal::Bottom + YShift, 0.0 ),
		FontSize,
		Color
	);
	
	Temp << MapObject[CurrentObject].Pos.y;
	TempString = Temp.str();

	cFonts::FlangeLight.Write(
		Temp.str(),
		Vector3D( cGlobal::Left + XPos, cGlobal::Bottom + Real( 6 ), 0.0 ),
		FontSize,
		Color
	);
	// - -------------------------------------------------------------------------------------- - //

	XPos += XShift;

	if( int( CurrentObject ) == Focus1 )
	{
		// Displays Focus 1 //
		// - ---------------------------------------------------------------------------------- - //
		cFonts::FlangeLight.Write(
			"Focus 1",
			Vector3D( cGlobal::Left + XPos, cGlobal::Bottom + YShift, 0.0 ),
			FontSize,
			Color
		);
	}
	XPos += XShift;

	if( int( CurrentObject ) == Focus2 )
	{
		// Displays Focus 2 //
		// - ---------------------------------------------------------------------------------- - //
		cFonts::FlangeLight.Write(
			"Focus 2",
			Vector3D( cGlobal::Left + XPos, cGlobal::Bottom + YShift, 0.0 ),
			FontSize,
			Color
		);
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::DisplayZoneInfo()
{
	Real FontSize = 0.5;
	Real XShift = 120;
	Real YShift = 40;
	Real XPos = 0;
	
	int Color = gfx::RGBA( 255, 255, 255, 255 );
	std::stringstream Temp;
	
	// Displays the current zone number //
	// - -------------------------------------------------------------------------------------- - //
	cFonts::FlangeLight.Write(
		"Zone #",
		Vector3D( cGlobal::Left + XPos, cGlobal::Bottom + YShift, 0.0 ),
		FontSize,
		Color
	);
	
	Temp << CurZone;

	cFonts::FlangeLight.Write(
		Temp.str(),
		Vector3D( cGlobal::Left + XPos, cGlobal::Bottom + Real( 6 ), 0.0 ),
		FontSize,
		Color
	);
	XPos += XShift;
	Temp.str(std::string());
	// Displays the ID of the zone //
	// - -------------------------------------------------------------------------------------- - //
	cFonts::FlangeLight.Write(
		"Zone ID",
		Vector3D( cGlobal::Left + XPos, cGlobal::Bottom + YShift, 0.0 ),
		FontSize,
		Color
	);
	
//	Temp << Game->Zone[ CurZone ].Id;

	cFonts::FlangeLight.Write(
		Temp.str(),
		Vector3D( cGlobal::Left + XPos, cGlobal::Bottom + Real( 6 ), 0.0 ),
		FontSize,
		Color
	);
	XPos += XShift;
	Temp.str(std::string());
	// Displays the ARG of the zone //
	// - -------------------------------------------------------------------------------------- - //
	cFonts::FlangeLight.Write(
		"Zone Arg",
		Vector3D( cGlobal::Left + XPos, cGlobal::Bottom + YShift, 0.0 ),
		FontSize,
		Color
	);
	
//	Temp << Game->Zone[ CurZone ].Argument;

	cFonts::FlangeLight.Write(
		Temp.str(),
		Vector3D( cGlobal::Left + XPos, cGlobal::Bottom + Real( 6 ), 0.0 ),
		FontSize,
		Color
	);
	XPos += XShift;
	XPos += XShift;
	Temp.str(std::string());
	// Displays the ID Description //
	// - -------------------------------------------------------------------------------------- - //
	cFonts::FlangeLight.Write(
		"ID Description",
		Vector3D( cGlobal::Left + XPos, cGlobal::Bottom + YShift, 0.0 ),
		FontSize,
		Color
	);
	
//	Temp << ZoneDesc[ Game->Zone[ CurZone ].Id ];

	cFonts::FlangeLight.Write(
		Temp.str(),
		Vector3D( cGlobal::Left + XPos, cGlobal::Bottom + Real( 6 ), 0.0 ),
		FontSize,
		Color
	);
	XPos += XShift;
	Temp.str(std::string());
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::DisplayMapName()
{
	Real FontSize = 0.5;
	Real XShift = 30;
	Real YShift = 25;
	Real XPos = 0;
	
	int Color = gfx::RGBA( 255, 255, 255, 255 );
	XPos += XShift;
	
	// Displays the current map name //
	// - -------------------------------------------------------------------------------------- - //
	cFonts::FlangeLight.Write(
		MapName,
		Vector3D( cGlobal::Left + XPos, cGlobal::Top - YShift, 0.0 ),
		FontSize,
		Color
	);
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::DisplayMesh3dName()
{
	if( !ModelNameList.empty() )
	{
		Real FontSize = 0.5;
		Real XShift = 4;
		Real YShift = 55;
		Real XPos = 0;
		
		int Color = gfx::RGBA( 255, 255, 255, 255 );
		XPos += XShift;
		
		// Displays the current mesh3d name //
		// - -------------------------------------------------------------------------------------- - //
		cFonts::FlangeLight.Write(
			ModelNameList[CurModel],
			Vector3D( cGlobal::Left + XPos, cGlobal::Top - YShift, 0.0 ),
			FontSize,
			Color
		);
	}
}
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
