#ifdef EDITOR
// - ------------------------------------------------------------------------------------------ - //
#include "CollectionEdit.h"

#include <Graphics/Gfx.h>
#include <Font/Fonts.h>
#include <Util/String.h>
#include <Platform/Global.h>
// - ------------------------------------------------------------------------------------------ - //
#include <sstream>
// - ------------------------------------------------------------------------------------------ - //
void cCollectionEdit::DisplayText()
{
	
	DisplayMode();
	
	DisplayComponentInfo();
}
// - ------------------------------------------------------------------------------------------ - //
void cCollectionEdit::DisplayMode()
{
/*	// Displays the current mesh edit mode //
	// - -------------------------------------------------------------------------------------- - //
	Real FontSize = 0.5;
	int Color = Gfx::RGBA( 255, 100, 100, 255 );
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
void cCollectionEdit::DisplayComponentInfo()
{
	cFonts::FlangeLight.Write(
		"Collection Editor",
		Vector3D( cGlobal::Left + Real( 20 ), cGlobal::Top - Real( 30 ), 0.0 ),
		Real( 0.5 ),
		Gfx::RGBA( 100, 100, 255, 255 )
	);

/*	cFonts::FlangeLight.Write(
		"Current Pose",
		Vector3D( cGlobal::Right - Real( 600 ), cGlobal::Top - Real( 30 ), 0.0 ),
		Real( 0.5 ),
		gfx::RGBA( 100, 255, 100, 255 )
	);
	
	std::stringstream Temp;

	Temp << CurPose;

	cFonts::FlangeLight.Write(
		Temp.str(),
		Vector3D( cGlobal::Right - Real( 400 ), cGlobal::Top - Real( 30 ), 0.0 ),
		Real( 0.5 ),
		gfx::RGBA( 100, 255, 100, 255 )
	);


	Temp.str(std::string());
*/
	
}
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
