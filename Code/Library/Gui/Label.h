// - ------------------------------------------------------------------------------------------ - //
// Label //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Gui_Label_H__
#define __Gui_Label_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Geometry/Vector.h>
#include <Graphics/Gfx.h>
// - ------------------------------------------------------------------------------------------ - //
class cLabel
{
public:
	Vector2D Pos;
	
	bool IsPassive;
	int ActionID;

	Gfx::Color Color;
	Gfx::Color SelColor;
	
	int Group;
	bool Visible;
	
public:
	cLabel( const Vector2D& _Pos, const bool _IsPassive, const int _ActionID, Gfx::Color _Color, Gfx::Color _SelColor ) :
		Pos( _Pos ),
		IsPassive( _IsPassive ),
		ActionID( _ActionID ),
		Color( _Color ),
		SelColor( _SelColor ),
		Group( 0 ),
		Visible( true )
	{
		
	}
	virtual ~cLabel()
	{
		
	}	
	virtual void Step()
	{
		
	}
	virtual void Draw( const Vector2D& Offset = Vector2D::Zero, const Gfx::Color _Color = Gfx::White() )
	{

	}
	virtual void SelInit()
	{
		
	}
	virtual class cAniLabel* AniLabel()
	{
		return 0;
	}
	virtual class cTextLabel* TextLabel()
	{
		return 0;
	}

};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Gui_Label_H__ //
// - ------------------------------------------------------------------------------------------ - //
