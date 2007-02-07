// - ------------------------------------------------------------------------------------------ - //
// Label //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Gui_Label_H__
#define __Gui_Label_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Geometry/Vector.h>
// - ------------------------------------------------------------------------------------------ - //
class cLabel
{
public:
	Vector2D Pos;
	
	bool IsPassive;
	int ActionID;
	
	int Group;
	
public:
	cLabel( const Vector2D& _Pos, const bool _IsPassive, const int _ActionID ) :
		Pos( _Pos ),
		IsPassive( _IsPassive ),
		ActionID( _ActionID ),
		Group( 0 )
	{
		
	}
	virtual ~cLabel()
	{
		
	}	
	virtual void Step()
	{
		
	}
	virtual void Draw( const Vector2D& Offset = Vector2D::Zero )
	{

	}
	// Selected Draw //
	virtual void SelDraw( const Vector2D& Offset = Vector2D::Zero )
	{
		
	}
	virtual void SelInit()
	{
		
	}

};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Gui_Label_H__ //
// - ------------------------------------------------------------------------------------------ - //
