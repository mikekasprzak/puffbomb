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
/*	if( CurMode == COLL_STATIC_COMP )
	{

	}
	else if( CurMode == COLL_DYNAMIC_COMP )
	{
		
	}
	else if( CurMode == COLL_NODE_LINK )
	{
		
	}
	else if( CurMode == COLL_HARD_NODE )
	{
		
	}*/

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

/*
// Dir Name?
	if( !CollectionPath.empty() )
	{
		cFonts::FlangeLight.Write(
			CollectionPath[ CurColl ],
			Vector3D( Global::Left + Real( 6 ), Global::Top - Real( 60 ), 0.0 ),
			Real( 0.5 ),
			Gfx::RGBA( 100, 255, 100, 255 )
		);
	}*/
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
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
