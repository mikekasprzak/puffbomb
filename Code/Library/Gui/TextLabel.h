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
	
public:
	
	cTextLabel(
		const Vector2D& _Pos,
		const bool _IsPassive,
		const int _ActionID, 
		const std::string& _Text,
		const Real _Scale,
		const int _Color
	) :
		cLabel( _Pos, _IsPassive, _ActionID, _Color, Gfx::RGBA( 55, 255, 55, 255 ) ),
		Text( _Text ),
		Scale( _Scale )
	{
		
	}
	~cTextLabel()
	{
		
	}
	void Step()
	{

	}
	void Draw( const Vector2D& Offset = Vector2D::Zero, const Gfx::Color _Color = Gfx::White() )
	{
		cFonts::FlangeLight.Write( Text, Pos + Offset, Scale, _Color );
	}
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Gui_TextLabel_H__ //
// - ------------------------------------------------------------------------------------------ - //
