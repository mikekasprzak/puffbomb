#ifdef EDITOR
// - ------------------------------------------------------------------------------------------ - //
#include "CollectionEdit.h"

#include <Graphics/Gfx.h>
#include <Font/Fonts.h>
#include <Util/String.h>
#include <Global.h>
// - ------------------------------------------------------------------------------------------ - //
#include <sstream>
// - ------------------------------------------------------------------------------------------ - //
void cCollectionEdit::DisplayText()
{
	if( CurMode == COLL_STATIC_COMP )
	{

	}
	else if( CurMode == COLL_DYNAMIC_COMP )
	{
		
	}
	else if( CurMode == COLL_NODE_LINK )
	{
		if( !CurSelected.empty() && !Collection.NodeLink.empty() )
		{
			int TempIdx = -1;
			for( size_t idx = 0; idx < Collection.NodeLink.size(); ++idx )
			{
				if( Collection.NodeLink[ idx ].ObjectA == CurSelComp )
				{
					if( Collection.NodeLink[ idx ].IndexA == CurSelected[ 0 ] )
					{
						TempIdx = idx;
					}
				}
				if( Collection.NodeLink[ idx ].ObjectB == CurSelComp )
				{
					if( Collection.NodeLink[ idx ].IndexB == CurSelected[ 0 ] )
					{
						TempIdx = idx;
					}
				}
			}
			
			if( TempIdx != -1 )
			{
			
				Real FontSize = 0.5;
				Real XShift = 140;
				Real YShift = 40;
				Real XPos = 0;
				Real YPos = 0;
			
				int Color = Gfx::RGBA( 255, 255, 255, 255 );
				std::stringstream Temp;
		
				XPos += XShift + Real( 20 );
		
				// Displays the Strength //
				// - -------------------------------------------------------------------------- - //
				cFonts::FlangeLight.Write(
					"Strength",
					Vector3D( Global::Left + XPos, Global::Bottom + YPos + YShift, 0.0 ),
					FontSize,
					Color
				);
				
				Temp << Collection.NodeLink[ TempIdx ].Strength;
			
				cFonts::FlangeLight.Write(
					Temp.str(),
					Vector3D( Global::Left + XPos, Global::Bottom + YPos + Real( 6 ), 0.0 ),
					FontSize,
					Color
				);
				XPos += XShift;
				Temp.str(std::string());
				// Displays the Break Point //
				// - -------------------------------------------------------------------------- - //
				cFonts::FlangeLight.Write(
					"BreakPoint",
					Vector3D( Global::Left + XPos, Global::Bottom + YPos + YShift, 0.0 ),
					FontSize,
					Color
				);
				
				Temp << Collection.NodeLink[ TempIdx ].BreakPoint;
			
				cFonts::FlangeLight.Write(
					Temp.str(),
					Vector3D( Global::Left + XPos, Global::Bottom + YPos + Real( 6 ), 0.0 ),
					FontSize,
					Color
				);
			}
		}	
	}
	else if( CurMode == COLL_HARD_NODE )
	{
		if( !CurSelected.empty() && !Collection.NodeAnchor.empty() )
		{
			int TempIdx = -1;
			for( size_t idx = 0; idx < Collection.NodeAnchor.size(); ++idx )
			{
				if( Collection.NodeAnchor[ idx ].Object == CurSelComp )
				{
					if( Collection.NodeAnchor[ idx ].Index == CurSelected[ 0 ] )
					{
						TempIdx = idx;
					}
				}
			}
			
			if( TempIdx != -1 )
			{
			
				Real FontSize = 0.5;
				Real XShift = 140;
				Real YShift = 40;
				Real XPos = 0;
				Real YPos = 0;
			
				int Color = Gfx::RGBA( 255, 255, 255, 255 );
				std::stringstream Temp;
		
				XPos += XShift + Real( 20 );
		
				// Displays the Strength //
				// - -------------------------------------------------------------------------- - //
				cFonts::FlangeLight.Write(
					"Strength",
					Vector3D( Global::Left + XPos, Global::Bottom + YPos + YShift, 0.0 ),
					FontSize,
					Color
				);
				
				Temp << Collection.NodeAnchor[ TempIdx ].Strength;
			
				cFonts::FlangeLight.Write(
					Temp.str(),
					Vector3D( Global::Left + XPos, Global::Bottom + YPos + Real( 6 ), 0.0 ),
					FontSize,
					Color
				);
				XPos += XShift;
				Temp.str(std::string());
				// Displays the Break Point //
				// - -------------------------------------------------------------------------- - //
				cFonts::FlangeLight.Write(
					"BreakPoint",
					Vector3D( Global::Left + XPos, Global::Bottom + YPos + YShift, 0.0 ),
					FontSize,
					Color
				);
				
				Temp << Collection.NodeAnchor[ TempIdx ].BreakPoint;
			
				cFonts::FlangeLight.Write(
					Temp.str(),
					Vector3D( Global::Left + XPos, Global::Bottom + YPos + Real( 6 ), 0.0 ),
					FontSize,
					Color
				);
			}
		}
	}

	DisplayMode();
	
	DisplayInfo();
	DisplayCompInfo();
}
// - ------------------------------------------------------------------------------------------ - //
void cCollectionEdit::DisplayMode()
{
	// Displays the current edit mode //
	// - -------------------------------------------------------------------------------------- - //
	Real FontSize = 0.5;
	int Color = Gfx::RGBA( 255, 100, 100, 255 );
	Vector3D ModePos = Vector3D( Global::Right - Real( 250 ), Global::Top - Real( 30 ), 0.0 );
		
	switch( CurMode )
	{ 
		case COLL_STATIC_COMP:
		{
			cFonts::FlangeLight.Write(
				"Static Comp Mode",
				ModePos,
				FontSize,
				Color
			);
			break;
		}
		case COLL_DYNAMIC_COMP:
		{
			cFonts::FlangeLight.Write(
				"Dyn Comp Mode",
				ModePos,
				FontSize,
				Color
			);
			break;
		}
		case COLL_NODE_LINK:
		{
			cFonts::FlangeLight.Write(
				"Node Link Mode",
				ModePos,
				FontSize,
				Color
			);
			break;
		}
		case COLL_HARD_NODE:
		{
			cFonts::FlangeLight.Write(
				"Hard Node Mode",
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
void cCollectionEdit::DisplayInfo()
{
	Real FontSize = 0.5;
	int Color = Gfx::RGBA( 100, 100, 255, 255 );
	Vector3D ModePos = Vector3D( Global::Left + Real( 20 ), Global::Top - Real( 30 ), 0.0 );
	
	cFonts::FlangeLight.Write(
		"Collection Editor",
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

	if( !CollectionPath.empty() )
	{
		cFonts::FlangeLight.Write(
			CollectionPath[ CurColl ],
			Vector3D( Global::Left + Real( 6 ), Global::Top - Real( 60 ), 0.0 ),
			Real( 0.5 ),
			Gfx::RGBA( 100, 255, 100, 255 )
		);
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cCollectionEdit::DisplayCompInfo()
{
	Real FontSize = 0.5;
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
	);
/*	
	if( CurSelected.size() > 0 )
	{
		XPos += XShift;
		Temp.str(std::string());

		// Displays the X location of the node //
		// - ---------------------------------------------------------------------------------- - //
		cFonts::FlangeLight.Write(
			"Node X",
			Vector3D( Global::Left + XPos, Global::Bottom + YPos + YShift, 0.0 ),
			FontSize,
			Color
		);
		
		Temp << Pose->Node[ CurSelected[0] ].Pos.x;
	
		cFonts::FlangeLight.Write(
			Temp.str(),
			Vector3D( Global::Left + XPos, Global::Bottom + YPos + Real( 6 ), 0.0 ),
			FontSize,
			Color
		);
		XPos += XShift;
		Temp.str(std::string());
		// Displays the Y location of the node //
		// - ---------------------------------------------------------------------------------- - //
		cFonts::FlangeLight.Write(
			"Node Y",
			Vector3D( Global::Left + XPos, Global::Bottom + YPos + YShift, 0.0 ),
			FontSize,
			Color
		);
		
		Temp << Pose->Node[ CurSelected[0] ].Pos.y;
	
		cFonts::FlangeLight.Write(
			Temp.str(),
			Vector3D( Global::Left + XPos, Global::Bottom + YPos + Real( 6 ), 0.0 ),
			FontSize,
			Color
		);
		XPos += XShift;
		Temp.str(std::string());
		// Displays the current mass //
		// - ---------------------------------------------------------------------------------- - //
		cFonts::FlangeLight.Write(
			"Mass",
			Vector3D( Global::Left + XPos, Global::Bottom + YPos + YShift, 0.0 ),
			FontSize,
			Color
		);
		
		Temp << Pose->Node[ CurSelected[0] ].Mass;
	
		cFonts::FlangeLight.Write(
			Temp.str(),
			Vector3D( Global::Left + XPos, Global::Bottom + YPos + Real( 6 ), 0.0 ),
			FontSize,
			Color
		);
		XPos += XShift;
		Temp.str(std::string());
		// Displays the total mass //
		// - ---------------------------------------------------------------------------------- - //
		cFonts::FlangeLight.Write(
			"Total Mass",
			Vector3D( Global::Left + XPos, Global::Bottom + YPos + YShift, 0.0 ),
			FontSize,
			Color
		);
		
		//Temp << Body2D[ CurBody ].Nodes.TotalMass;
		Temp << DynObj->Body.Nodes.TotalMass;
	
		cFonts::FlangeLight.Write(
			Temp.str(),
			Vector3D( Global::Left + XPos, Global::Bottom + YPos + Real( 6 ), 0.0 ),
			FontSize,
			Color
		);
	} */
}
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
