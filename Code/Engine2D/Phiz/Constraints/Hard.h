// - ------------------------------------------------------------------------------------------ - //
// Hard //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Phiz_Constraint_Hard_H__
#define __Phiz_Constraint_Hard_H__
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include <Geometry/Vector.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
class cHard {
public:
	bool Enabled;
	
	Vector2D Point;

	// Indices at the end for consistency //
	size_t Index;
public:
	cHard() {
	}
	
	cHard( const size_t& _Index ) :
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
		//return Flags & flActive;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline void SetActive() {
		Enabled = true;
		//Flags |= flActive;
	}	
	// - -------------------------------------------------------------------------------------- - //
	inline void SetInactive() {
		Enabled = false;
		//Flags &= ~flActive;
	}	
	// - -------------------------------------------------------------------------------------- - //

};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Phiz_Constraint_Hard_H__ //
// - ------------------------------------------------------------------------------------------ - //
