#ifdef EDITOR
// - ------------------------------------------------------------------------------------------ - //
#include "ComponentEdit.h"

#include <Graphics/Gfx.h>
#include <Font/Fonts.h>
#include <Util/String.h>
#include <Platform/Global.h>
// - ------------------------------------------------------------------------------------------ - //
#include <sstream>
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::DisplayText()
{
	if( !Body2D.empty() )
	{
		if( CurMode == NODE_MODE )
		{
			DisplayNodeInfo();
		}
		else if( CurMode == SPHERE_MODE )
		{	
			DisplaySphereInfo();
		}
		else if( CurMode == SPRING_MODE )
		{	

		}
	}
	
	DisplayMode();
	cFonts::FlangeLight.Write(
		"Component Editor",
		Vector3D( cGlobal::Left + Real( 20 ), cGlobal::Top - Real( 30 ), 0.0 ),
		Real( 0.5 ),
		gfx::RGBA( 100, 100, 255, 255 )
	);
	
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::DisplayNodeInfo()
{
	if( CurSelected.size() > 0 )
	{
		Real FontSize = 0.5;
		Real XShift = 120;
		Real YShift = 40;
		Real XPos = 0;
		Real YPos = 0;
		
		if( Platform::AspectRatio < Real( 0.79 ) )
		{
			YPos = cGlobal::HudH * 0.25;
		}
		int Color = gfx::RGBA( 255, 255, 255, 255 );
		std::stringstream Temp;
		
		// Displays the current node number //
		// - ---------------------------------------------------------------------------------- - //
		cFonts::FlangeLight.Write(
			"Node #",
			Vector3D( cGlobal::Left + XPos, cGlobal::Bottom + YPos + YShift, 0.0 ),
			FontSize,
			Color
		);
		
		Temp << CurSelected[0];
	
		cFonts::FlangeLight.Write(
			Temp.str(),
			Vector3D( cGlobal::Left + XPos, cGlobal::Bottom + YPos + Real( 6 ), 0.0 ),
			FontSize,
			Color
		);
		XPos += XShift;
		Temp.str(std::string());
		// Displays the X location of the node //
		// - ---------------------------------------------------------------------------------- - //
		cFonts::FlangeLight.Write(
			"Node X",
			Vector3D( cGlobal::Left + XPos, cGlobal::Bottom + YPos + YShift, 0.0 ),
			FontSize,
			Color
		);
		
		Temp << Body2D[ CurBody ].Nodes.Pos( CurSelected[0] ).x;
	
		cFonts::FlangeLight.Write(
			Temp.str(),
			Vector3D( cGlobal::Left + XPos, cGlobal::Bottom + YPos + Real( 6 ), 0.0 ),
			FontSize,
			Color
		);
		XPos += XShift;
		Temp.str(std::string());
		// Displays the Y location of the node //
		// - ---------------------------------------------------------------------------------- - //
		cFonts::FlangeLight.Write(
			"Node Y",
			Vector3D( cGlobal::Left + XPos, cGlobal::Bottom + YPos + YShift, 0.0 ),
			FontSize,
			Color
		);
		
		Temp << Body2D[ CurBody ].Nodes.Pos( CurSelected[0] ).y;
	
		cFonts::FlangeLight.Write(
			Temp.str(),
			Vector3D( cGlobal::Left + XPos, cGlobal::Bottom + YPos + Real( 6 ), 0.0 ),
			FontSize,
			Color
		);
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::DisplaySphereInfo()
{
	if( CurSelected.size() > 0 && Body2D[ CurBody ].Sphere.size() > 0 )
	{
		Real FontSize = 0.5;
		Real XShift = 120;
		Real YShift = 40;
		Real XPos = 0;
		Real YPos = 0;
		
		if( Platform::AspectRatio < Real( 0.79 ) )
		{
			YPos = cGlobal::HudH * 0.25;
		}
		int Color = gfx::RGBA( 255, 255, 255, 255 );
		std::stringstream Temp;
		
		int SphereIdx = -1;
		for( size_t idx = 0; idx < Body2D[ CurBody ].Sphere.size(); ++idx )
		{
			if( CurSelected[0] == Body2D[ CurBody ].Sphere[ idx ].Index )
			{
				SphereIdx = idx;
				break;
			}
		}
		
		if( SphereIdx != -1 )
		{
			// Displays the current sphere number //
			// - ---------------------------------------------------------------------------------- - //
			cFonts::FlangeLight.Write(
				"Sphere#",
				Vector3D( cGlobal::Left + XPos, cGlobal::Bottom + YPos + YShift, 0.0 ),
				FontSize,
				Color
			);
			
			Temp << SphereIdx;
		
			cFonts::FlangeLight.Write(
				Temp.str(),
				Vector3D( cGlobal::Left + XPos, cGlobal::Bottom + YPos + Real( 6 ), 0.0 ),
				FontSize,
				Color
			);
			XPos += XShift;
			Temp.str(std::string());
			// Displays the sphere radius //
			// - ---------------------------------------------------------------------------------- - //
			cFonts::FlangeLight.Write(
				"Radius",
				Vector3D( cGlobal::Left + XPos, cGlobal::Bottom + YPos + YShift, 0.0 ),
				FontSize,
				Color
			);
			
			Temp << Body2D[ CurBody ].Sphere[ SphereIdx ].Radius;
		
			cFonts::FlangeLight.Write(
				Temp.str(),
				Vector3D( cGlobal::Left + XPos, cGlobal::Bottom + YPos + Real( 6 ), 0.0 ),
				FontSize,
				Color
			);
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::DisplayMode()
{
	// Displays the current mesh edit mode //
	// - -------------------------------------------------------------------------------------- - //
	Real FontSize = 0.5;
	int Color = gfx::RGBA( 255, 100, 100, 255 );
	Vector3D ModePos = Vector3D( cGlobal::Right - Real( 250 ), cGlobal::Top - Real( 30 ), 0.0 );
		
	switch( CurMode )
	{ 
		case NODE_MODE:
		{
			cFonts::FlangeLight.Write(
				"BodyNode Mode",
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
//				"Pivot Handle Mode",
				"Spring Mode",
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
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
