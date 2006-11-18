#ifdef EDITOR
// - ------------------------------------------------------------------------------------------ - //
#include "MapEdit.h"

#include <Graphics/Gfx.h>
#include <Font/Fonts.h>
#include <Util/String.h>
#include <Global.h>
// - ------------------------------------------------------------------------------------------ - //
#include <sstream>
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::DisplayText()
{
	if( CurMode == TILE_MODE )
	{
		Real FontSize = 0.5;
		int Color = Gfx::RGBA( 255, 100, 100, 255 );
		
		std::stringstream Temp;
	
		// Displays the current layer //
		// - ---------------------------------------------------------------------------------- - //
		cFonts::FlangeLight.Write(
			"CurLayer",
			Vector3D( Global::Left + Real( 6 ), Global::Top - Real( 90 ), 0.0 ),
			FontSize,
			Color
		);
		
		Temp << CurLayer;
	
		cFonts::FlangeLight.Write(
			Temp.str(),
			Vector3D( Global::Left + Real( 130 ), Global::Top - Real( 90 ), 0.0 ),
			FontSize,
			Color
		);
	}
	else if( CurMode == ZONE_MODE )
	{
		if( !Zone.empty() )
		{
			DisplayZoneInfo();
		}		
	}
	else if( CurMode == OBJECT_MODE )
	{
		
	}
	else if( CurMode == FREE_OBJECT_MODE )
	{
		
	}	
	else if( CurMode == PASSIVE_OBJECT_MODE )
	{
		
	}

	DisplayMode();
	
	DisplayInfo();
	DisplayMapInfo();
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::DisplayMode()
{
	// Displays the current edit mode //
	// - -------------------------------------------------------------------------------------- - //
	Real FontSize = 0.5;
	int Color = Gfx::RGBA( 255, 100, 100, 255 );
	Vector3D ModePos = Vector3D( Global::Right - Real( 250 ), Global::Top - Real( 30 ), 0.0 );
		
	switch( CurMode )
	{ 
		case TILE_MODE:
		{
			cFonts::FlangeLight.Write(
				"Tile Mode",
				ModePos,
				FontSize,
				Color
			);
			break;
		}
		case ZONE_MODE:
		{
			cFonts::FlangeLight.Write(
				"Zone Mode",
				ModePos,
				FontSize,
				Color
			);
			break;
		}
		case OBJECT_MODE:
		{
			cFonts::FlangeLight.Write(
				"Obj Mode",
				ModePos,
				FontSize,
				Color
			);
			break;
		}
		case FREE_OBJECT_MODE:
		{
			cFonts::FlangeLight.Write(
				"Free Obj Mode",
				ModePos,
				FontSize,
				Color
			);
			break;
		}
		case PASSIVE_OBJECT_MODE:
		{
			cFonts::FlangeLight.Write(
				"Passive Obj Mode",
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
void cMapEdit::DisplayInfo()
{
	Real FontSize = 0.5;
	int Color = Gfx::RGBA( 100, 100, 255, 255 );
	Vector3D ModePos = Vector3D( Global::Left + Real( 20 ), Global::Top - Real( 30 ), 0.0 );
	
	cFonts::FlangeLight.Write(
		"Map Editor",
		ModePos,
		FontSize,
		Color
	);

	if( !IsSaved )
	{
		cFonts::FlangeLight.Write(
			"*",
			Vector3D( Global::Left + Real( 1 ), Global::Top - Real( 56 ), 0.0 ),
			Real( 1.0 ),
			Gfx::RGBA( 255, 255, 255, 255 )
		);
	}

	// Map and Dir Name //
	if( !MapPath.empty() )
	{
		cFonts::FlangeLight.Write(
			MapPath[ CurMap ],
			Vector3D( Global::Left + Real( 6 ), Global::Top - Real( 60 ), 0.0 ),
			Real( 0.5 ),
			Gfx::RGBA( 100, 255, 100, 255 )
		);
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::DisplayMapInfo()
{
/*	Real FontSize = 0.5;
	Real XShift = 120;
	Real YShift = 40;
	Real XPos = 0;
	Real YPos = 0;

	int Color = Gfx::RGBA( 255, 255, 255, 255 );
	std::stringstream Temp;
	
	// Displays the current component size //
	// - ---------------------------------------------------------------------------------- - //
	cFonts::FlangeLight.Write(
		"CompSize",
		Vector3D( Global::Left + XPos, Global::Bottom + YPos + YShift, 0.0 ),
		FontSize,
		Color
	);
	
	Temp << Collection.Component.size();

	cFonts::FlangeLight.Write(
		Temp.str(),
		Vector3D( Global::Left + XPos, Global::Bottom + YPos + Real( 6 ), 0.0 ),
		FontSize,
		Color
	);*/
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::DisplayZoneInfo()
{
	Real FontSize = 0.5;
	Real XShift = 120;
	Real YShift = 40;
	Real XPos = 0;
	
	int Color = Gfx::RGBA( 255, 255, 255, 255 );
	std::stringstream Temp;
	
	// Displays the current zone number //
	// - -------------------------------------------------------------------------------------- - //
	cFonts::FlangeLight.Write(
		"Zone #",
		Vector3D( Global::Left + XPos, Global::Bottom + YShift, 0.0 ),
		FontSize,
		Color
	);
	
	Temp << CurZone;

	cFonts::FlangeLight.Write(
		Temp.str(),
		Vector3D( Global::Left + XPos, Global::Bottom + Real( 6 ), 0.0 ),
		FontSize,
		Color
	);
	XPos += XShift;
	Temp.str(std::string());
		
	// Displays the ID of the zone //
	// - -------------------------------------------------------------------------------------- - //
	cFonts::FlangeLight.Write(
		"Zone ID",
		Vector3D( Global::Left + XPos, Global::Bottom + YShift, 0.0 ),
		FontSize,
		Color
	);
	
	Temp << Zone[ CurZone ].Id;

	cFonts::FlangeLight.Write(
		Temp.str(),
		Vector3D( Global::Left + XPos, Global::Bottom + Real( 6 ), 0.0 ),
		FontSize,
		Color
	);
	XPos += XShift;
	Temp.str(std::string());
	// Displays the ARG of the zone //
	// - -------------------------------------------------------------------------------------- - //
	cFonts::FlangeLight.Write(
		"Zone Arg",
		Vector3D( Global::Left + XPos, Global::Bottom + YShift, 0.0 ),
		FontSize,
		Color
	);
	
	Temp << Zone[ CurZone ].Argument;

	cFonts::FlangeLight.Write(
		Temp.str(),
		Vector3D( Global::Left + XPos, Global::Bottom + Real( 6 ), 0.0 ),
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
		Vector3D( Global::Left + XPos, Global::Bottom + YShift, 0.0 ),
		FontSize,
		Color
	);
	
	Temp << ZoneDesc[ Zone[ CurZone ].Id ];

	cFonts::FlangeLight.Write(
		Temp.str(),
		Vector3D( Global::Left + XPos, Global::Bottom + Real( 6 ), 0.0 ),
		FontSize,
		Color
	);
	XPos += XShift;
	Temp.str(std::string());
}
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
