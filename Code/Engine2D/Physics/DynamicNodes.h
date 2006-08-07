// - ------------------------------------------------------------------------------------------ - //
// DynamicNodes //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Physics_DynamicNodes_H__
#define __Engine2D_Physics_DynamicNodes_H__
// - ------------------------------------------------------------------------------------------ - //
#include <vector>
// - ------------------------------------------------------------------------------------------ - //
#include <Util/Debug.h>

#include <Geometry/Vector.h>
#include <Physics/StateFlags.h>
#include <Physics/CollisionFlags.h>

//#include "Physics.h"
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cDynamicNodes {
	// - -------------------------------------------------------------------------------------- - //	
	std::vector< Vector2D > NodeA;
	std::vector< Vector2D > NodeB;
	
	std::vector< Vector2D > Force;
	std::vector< Real > Friction;
	std::vector< Real > _InvMass;
	// - -------------------------------------------------------------------------------------- - //	
public:
	std::vector< Real > Mass;
	Real TotalMass;

	cCollisionFlags Collision;
	cStateFlags State;

	int SleepClock;

public:
	// Constructor //
//	cDynamicNodes( size_t _Count ) :
//		NodeA( _Count ),
//		NodeB( _Count ),
//		Force( _Count ),
//		Friction( _Count ),
//		_InvMass( _Count ),
//		Mass( _Count )
//	{		
//		WakeUp();
//		
//		// Not really a nice spot to print this here, so remove this //
//		Log( LOG_PHIZOBJECT_INFO, "Node set created (" << _Count << ")" );
//	}
	
	// Destructor //
	~cDynamicNodes() {
	}
public:
	// - -------------------------------------------------------------------------------------- - //
	// Get the Current Position as a pointer //
	inline Vector2D* const Pos() {
		//return PosPtr;
		return &NodeA[ 0 ];
	}
	// - -------------------------------------------------------------------------------------- - //
	// Get the Current Position as an index, and return a reference so it may be changed //
	inline Vector2D& Pos( const size_t& _Index ) {
		return *(Pos() + _Index);
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Get the Old Position as a pointer //
	inline Vector2D* const Old() {
		//return OldPtr;
		return &NodeB[ 0 ];
	}
	// - -------------------------------------------------------------------------------------- - //
	// Get the Old Position as an index, and return a reference so it may be changed //
	inline Vector2D& Old( const size_t& _Index ) {
		return *(Old() + _Index);
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Get the Velocity //
	inline const Vector2D Velocity( const size_t& _Index ) {
		return Pos( _Index ) - Old( _Index );
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Get the Current Home Position as an index, and return a reference so it may be changed //
//	inline Vector2D& HomePos( const size_t& _Index ) {
//		return _HomePos[ _Index ];
//	}
	// - -------------------------------------------------------------------------------------- - //
	// Get the Old Home Position as an index, and return a reference so it may be changed //
//	inline Vector2D& HomeOld( const size_t& _Index ) {
//		return _HomeOld[ _Index ];
//	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Get the Current Mass as an index, and return a reference so it may be changed //
	inline Real& InvMass( const size_t& _Index ) {
		return _InvMass[ _Index ];
	}
	// - -------------------------------------------------------------------------------------- - //


	// - -------------------------------------------------------------------------------------- - //
	// Set the value of friction.  Friction doubles as the concept of fluid dynamic drag. //
	inline void SetFriction( const size_t& _Index, const Real& _Value ) {
		// Friction has the rule, that it cannot be set to higher than what it was //
		if ( _Value < Friction[ _Index ] )
			Friction[ _Index ] = _Value;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Reset the value of friction. //
	inline void ResetFriction( const size_t& _Index ) {
		Friction[ _Index ] = Real::One;
	}
	// - -------------------------------------------------------------------------------------- - //


	// - -------------------------------------------------------------------------------------- - //
	// 
	inline void AddForce( const size_t& _Index, const Vector2D& _Value ) {
		Force[ _Index ] += _Value;
	}
	// - -------------------------------------------------------------------------------------- - //


public:
	// - -------------------------------------------------------------------------------------- - //
	inline void Swap() {
		// exchange the position of the old with the current //
		NodeA.swap( NodeB );
	}
	// - -------------------------------------------------------------------------------------- - //
	inline void Step() {
		if ( SleepClock > 0 ) {
			Vector2D TotalMotion( Vector2D::Zero );
			Vector2D Velocity;
			
			// step physics for all DynamicNodes //
			for ( size_t idx = 0; idx < NodeA.size(); idx++ ) {
				// With added forces on the outside //
				Velocity = ((Pos( idx ) - Old( idx ) ) * Friction[ idx ]) + Force[ idx ];
				TotalMotion += Velocity;
				Old( idx ) = Pos( idx ) + Velocity;
				
				// With added forces on the inside //
				//Old( idx ) = Pos( idx ) + ((Pos( idx ) - Old( idx ) + Force[ idx ] ) * Friction[ idx ]);
				
				Reset( idx );
			}
			// Swap the Old and Pos, as they are now backwards //
			Swap();
		
			TotalMotion /= NodeA.size();
			Real Motion = TotalMotion.Manhattan();
			
			// Tweak the sleep clock //
			if ( Motion > Real( 0.2 ) )
				WakeUp();
			else
				SleepClock--;
		}		
	}
	// - -------------------------------------------------------------------------------------- - //
	inline void Reset( int Index ) {
//		Friction[ Index ] = cPhysics::Friction;
//		Force[ Index ] = cPhysics::Force;
	}
	// - -------------------------------------------------------------------------------------- - //
public:
	// - -------------------------------------------------------------------------------------- - //
	inline size_t Size() {
		return NodeA.size();
	}
	// - -------------------------------------------------------------------------------------- - //


	
	// - -------------------------------------------------------------------------------------- - //
	inline bool IsAwake() {
		return SleepClock > 0;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline void WakeUp() {
		SleepClock = 16;
	}	
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Features for object building //
	int AddNode();
	void DeleteNode( size_t Number );
	// Dump contents to the console //
	void Dump();
	// - -------------------------------------------------------------------------------------- - //
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Physics_DynamicNodes_H__ //
// - ------------------------------------------------------------------------------------------ - //
