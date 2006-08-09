#ifdef EDITOR
// - ------------------------------------------------------------------------------------------ - //
#include "AnimationEdit.h"

#include <Graphics/Gfx.h>
#include <Font/Fonts.h>
#include <Util/String.h>
#include <Platform/Global.h>
// - ------------------------------------------------------------------------------------------ - //
#include <sstream>
// - ------------------------------------------------------------------------------------------ - //
void cAnimationEdit::DisplayText()
{
	if( CurFrame->Vertex.size() > 0 )
	{
		if( CurMode == NODE_MODE )
		{
			DisplayNodeInfo();
		}
		else if( CurMode == FACE_MODE )
		{	
			DisplayFaceInfo();
		}
		else if( CurMode == TEXTURE_MODE )
		{	
			DisplayFaceInfo();
			DisplayTextureInfo();
		}
	}
	
	DisplayMode();
}
// - ------------------------------------------------------------------------------------------ - //
void cAnimationEdit::DisplayNodeInfo()
{
	if( CurSelected.size() > 0 )
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
			Vector3D( cGlobal::Left + XPos, cGlobal::Bottom + YShift, 0.0 ),
			FontSize,
			Color
		);
		
		Temp << CurSelected[0];
	
		cFonts::FlangeLight.Write(
			Temp.str(),
			Vector3D( cGlobal::Left + XPos, cGlobal::Bottom + Real( 6 ), 0.0 ),
			FontSize,
			Color
		);
		XPos += XShift;
		Temp.str(std::string());
		// Displays the X location of the node //
		// - ---------------------------------------------------------------------------------- - //
		cFonts::FlangeLight.Write(
			"Node X",
			Vector3D( cGlobal::Left + XPos, cGlobal::Bottom + YShift, 0.0 ),
			FontSize,
			Color
		);
		
		Temp << CurFrame->Vertex[ CurSelected[0] ].Pos.x;
	
		cFonts::FlangeLight.Write(
			Temp.str(),
			Vector3D( cGlobal::Left + XPos, cGlobal::Bottom + Real( 6 ), 0.0 ),
			FontSize,
			Color
		);
		XPos += XShift;
		Temp.str(std::string());
		// Displays the Y location of the node //
		// - ---------------------------------------------------------------------------------- - //
		cFonts::FlangeLight.Write(
			"Node Y",
			Vector3D( cGlobal::Left + XPos, cGlobal::Bottom + YShift, 0.0 ),
			FontSize,
			Color
		);
		
		Temp << CurFrame->Vertex[ CurSelected[0] ].Pos.y;
	
		cFonts::FlangeLight.Write(
			Temp.str(),
			Vector3D( cGlobal::Left + XPos, cGlobal::Bottom + Real( 6 ), 0.0 ),
			FontSize,
			Color
		);
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cAnimationEdit::DisplayFaceInfo()
{
	
}
// - ------------------------------------------------------------------------------------------ - //
void cAnimationEdit::DisplayTextureInfo()
{
	
}
// - ------------------------------------------------------------------------------------------ - //
void cAnimationEdit::DisplayMode()
{
		// Displays the current mesh edit mode //
	// - -------------------------------------------------------------------------------------- - //
	Real FontSize = 0.5;
	int Color = gfx::RGBA( 100, 255, 100, 255 );
	Vector3D ModePos = Vector3D( cGlobal::Right - Real( 750 ), cGlobal::Top - Real( 40 ), 0.0 );
		
	switch( CurMode )
	{ 
		case NODE_MODE:
		{
			cFonts::FlangeLight.Write(
				"Node Mode",
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
		default:
		{
			break;	
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
