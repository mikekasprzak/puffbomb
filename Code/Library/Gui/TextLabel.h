// - ------------------------------------------------------------------------------------------ - //
// TextLabel //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Gui_TextLabel_H__
#define __Gui_TextLabel_H__
// - ------------------------------------------------------------------------------------------ - //
#include "Label.h"
#include <Font/Fonts.h>
#include <Graphics/Gfx.h>
#include <string>
// - ------------------------------------------------------------------------------------------ - //
class cTextLabel : public cLabel
{
public:
	std::string Text;
	Real Scale;	
	int Color;
	
	int SelColor;
	
public:
	
	cTextLabel(
		const Vector2D& _Pos,
		const bool _IsPassive,
		const int _ActionID, 
		const std::string& _Text,
		const Real _Scale,
		const int _Color
	) :
		cLabel( _Pos, _IsPassive, _ActionID ),
		Text( _Text ),
		Scale( _Scale ),
		Color( _Color )
	{
		SelColor = Gfx::RGBA( 0, 192, 0, 255 );
	}

	void Draw()
	{
		cFonts::FlangeLight.Write( Text, Pos, Scale, Color );
	}
	
	void SelDraw()
	{
		cFonts::FlangeLight.Write( Text, Pos, Scale, SelColor );
	}
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Gui_TextLabel_H__ //
// - ------------------------------------------------------------------------------------------ - //
