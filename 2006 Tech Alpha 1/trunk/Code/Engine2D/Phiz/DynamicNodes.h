// - ------------------------------------------------------------------------------------------ - //
// DynamicNodes //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Phiz_DynamicNodes_H__
#define __Phiz_DynamicNodes_H__
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include <vector>
// - ------------------------------------------------------------------------------------------ - //
#include <Geometry/Vector.h>
#include <Physics/BodyFlags.h>

#include "Physics.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
class cDynamicNodes {
	// - -------------------------------------------------------------------------------------- - //	
	std::vector< Vector2D > NodeA;
	std::vector< Vector2D > NodeB;
	
	std::vector< Vector2D > _Force;
	std::vector< Real > _Friction;
	std::vector< Real > _InvMass;
	// - -------------------------------------------------------------------------------------- - //	
	std::vector< Vector2D > _HomePos;
	std::vector< Vector2D > _HomeOld;
	// - -------------------------------------------------------------------------------------- - //	
public:
	std::vector< Real > Mass;
	Real TotalMass;

	cBodyFlags Flags;

	int SleepClock;

public:
	// Constructor //
	cDynamicNodes( size_t _Count ) :
		NodeA( _Count ),
		NodeB( _Count ),
		_Force( _Count ),
		_Friction( _Count ),
		_InvMass( _Count ),
		_HomePos( _Count ),
		_HomeOld( _Count ),
		Mass( _Count )
	{
		Flags.Init();
		
		WakeUp();
		
		// Not really a nice spot to print this here, so remove this //
		Log( LOG_PHIZOBJECT_INFO, "Node set created (" << _Count << ")" );
	}
	
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
	inline Vector2D& HomePos( const size_t& _Index ) {
		return _HomePos[ _Index ];
	}
	// - -------------------------------------------------------------------------------------- - //
	// Get the Old Home Position as an index, and return a reference so it may be changed //
	inline Vector2D& HomeOld( const size_t& _Index ) {
		return _HomeOld[ _Index ];
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	inline void Set( const size_t& _Index, Vector2D _Value ) {
		_HomePos[ _Index ] = _Value;
		_HomeOld[ _Index ] = _Value;
		Pos( _Index ) = _Value;
		Old( _Index ) = _Value;
	}
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
		if ( _Value < _Friction[ _Index ] )
			_Friction[ _Index ] = _Value;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Reset the value of friction. //
	inline void ResetFriction( const size_t& _Index ) {
		_Friction[ _Index ] = Real::One;
	}
	// - -------------------------------------------------------------------------------------- - //


	// - -------------------------------------------------------------------------------------- - //
	// 
	inline void AddForce( const size_t& _Index, const Vector2D& _Value ) {
		_Force[ _Index ] += _Value;
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
				Velocity = ((Pos( idx ) - Old( idx ) ) * _Friction[ idx ]) + _Force[ idx ];
				TotalMotion += Velocity;
				Old( idx ) = Pos( idx ) + Velocity;
				
				// With added forces on the inside //
				//Old( idx ) = Pos( idx ) + ((Pos( idx ) - Old( idx ) + _Force[ idx ] ) * _Friction[ idx ]);
				
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
		_Friction[ Index ] = cPhysics::Friction;
		_Force[ Index ] = cPhysics::Force;
	}
	// - -------------------------------------------------------------------------------------- - //
public:
	// - -------------------------------------------------------------------------------------- - //
	inline size_t size() {
		return NodeA.size();
	}
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
	int AddNode();
	void DeleteNode( size_t Number );
	// - -------------------------------------------------------------------------------------- - //
public:
	// - -------------------------------------------------------------------------------------- - //
	void Dump() {
		for ( size_t idx = 0; idx < NodeA.size(); idx++ ) {
			Log( 10, "[ " << idx << " ]" <<
				"Pos: " << Pos( idx ).x << " " << Pos( idx ).y << 
				"  Old: " << Old( idx ).x << " " << Old( idx ).y
				);
			Log( 10, "[ " << idx << " ]" <<
				"Friction: " << _Friction[ idx ] << 
				"  Force: " << _Force[ idx ].x << " " << _Force[ idx ].y
				);
			Log( 10, "[ " << idx << " ]" <<
				"HomePos: " << _HomePos[ idx ].x << " " << _HomePos[ idx ].y << 
				"  HomeOld: " << _HomeOld[ idx ].x << " " << _HomeOld[ idx ].y
				);
		}
		
		Log( 10, "PosPTR: " << Pos() << "  OldPtr: " << Old() );
	}	
	// - -------------------------------------------------------------------------------------- - //
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Phiz_DynamicNodes_H__ //
// - ------------------------------------------------------------------------------------------ - //
