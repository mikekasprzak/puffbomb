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
	
	DisplayMode();
	
	DisplayInfo();
	DisplayCompInfo();
}
// - ------------------------------------------------------------------------------------------ - //
void cCollectionEdit::DisplayMode()
{
/*	// Displays the current mesh edit mode //
	// - -------------------------------------------------------------------------------------- - //
	Real FontSize = 0.5;
	int Color = Gfx::RGBA( 255, 100, 100, 255 );
	Vector3D ModePos = Vector3D( Global::Right - Real( 250 ), Global::Top - Real( 30 ), 0.0 );
		
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
				"Spring Mode",
				ModePos,
				FontSize,
				Color
			);
			break;
		}
		case MESH_NODE_MODE:
		{
			cFonts::FlangeLight.Write(
				"MeshNode Mode",
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
		case COMPONENT_MODE:
		{
			cFonts::FlangeLight.Write(
				"Component Mode",
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
	}*/
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

/*	cFonts::FlangeLight.Write(
		"Current Pose",
		Vector3D( Global::Right - Real( 600 ), Global::Top - Real( 30 ), 0.0 ),
		Real( 0.5 ),
		gfx::RGBA( 100, 255, 100, 255 )
	);
	
	std::stringstream Temp;

	Temp << CurPose;

	cFonts::FlangeLight.Write(
		Temp.str(),
		Vector3D( Global::Right - Real( 400 ), Global::Top - Real( 30 ), 0.0 ),
		Real( 0.5 ),
		gfx::RGBA( 100, 255, 100, 255 )
	);


	Temp.str(std::string());
*/
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
