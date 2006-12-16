// - ------------------------------------------------------------------------------------------ - //
// PassiveObject //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Engine_PassiveObject_H__
#define __Engine2D_Engine_PassiveObject_H__
// - ------------------------------------------------------------------------------------------ - //
#include <string>
// - ------------------------------------------------------------------------------------------ - //
#include <Geometry/Vector.h>
#include <Physics/Physics.h>

#include <Animation/Animator.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cPassiveObject {
public:
	Vector2D Pos;
	
	int Argument;
	bool Active;
	
	cAnimator Animator;

public:
	// Bounding rectangle //
	cPhysics::BoundingRectType BoundingRect;
	// Draw it //
	void DrawBoundingRect( const bool Selected = false ) const;

public:
	cPassiveObject() :
		Argument( 0 ),
		Active( true )
	{
	}
	
	cPassiveObject( const Vector2D& _Pos, int _Argument = 0 ) :
		Pos( _Pos ),
		Argument( _Argument ),
		Active( true )
	{
		BoundingRect = Engine2D::cPhysics::BoundingRectType::Pair( _Pos - Vector2D( 16, 16 ), _Pos + Vector2D( 16, 16 ) );
	}

	cPassiveObject( const std::string& AnimationName, const Vector2D& _Pos, int _Argument = 0 ) :
		Pos( _Pos ),
		Argument( _Argument ),
		Active( true ),
		Animator( AnimationName )
	{
		BoundingRect = Engine2D::cPhysics::BoundingRectType::Pair( _Pos - Vector2D( 16, 16 ), _Pos + Vector2D( 16, 16 ) );
	}
	
	virtual ~cPassiveObject()
	{
		
	}

public:	
	void Draw();
	void DebugDraw() const;
	
	virtual bool Work();

	inline bool IsActive() {
		return Active;
	}
	
	inline void Activate() {
		Active = true;
	}

	inline void Deactivate() {
		Active = false;
	}

public:
	// Messanging //
	virtual int Message( int Msg, class cDynamicComponent* const Sender );
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Engine_PassiveObject_H__ //
// - ------------------------------------------------------------------------------------------ - //
