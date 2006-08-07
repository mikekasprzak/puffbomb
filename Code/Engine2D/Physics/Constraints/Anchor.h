// - ------------------------------------------------------------------------------------------ - //
// Anchor //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Physics_Constraints_Constraint_Anchor_H__
#define __Engine2D_Physics_Constraints_Constraint_Anchor_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Util/ClassDesigner.h>
#include <Geometry/Vector.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cAnchor {
public:
	bool Enabled;
	Vector2D Point;

	size_t Index;
public:
	cAnchor() {
	}
	
	cAnchor( const size_t& _Index ) :
		Index( _Index )
	{
	}

public:
	inline void Lock( cDynamicNodes& Node ) {
		Point = Node.Pos( Index );
		Lock();
	};
		
	inline void Lock() {
		Enabled = true;
	};

	inline void Unlock() {
		Enabled = false;
	}

	// - -------------------------------------------------------------------------------------- - //
	inline bool IsActive() {
		return Enabled;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline void SetActive() {
		Enabled = true;
	}	
	// - -------------------------------------------------------------------------------------- - //
	inline void SetInactive() {
		Enabled = false;
	}	
	// - -------------------------------------------------------------------------------------- - //
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Physics_Constraints_Constraint_Anchor_H__ //
// - ------------------------------------------------------------------------------------------ - //