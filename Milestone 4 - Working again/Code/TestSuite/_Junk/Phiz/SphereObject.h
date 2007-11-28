// - ------------------------------------------------------------------------------------------ - //
// SphereObject //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Phiz_SphereObject_H__
#define __Phiz_SphereObject_H__
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include <vector>
// - ------------------------------------------------------------------------------------------ - //
#include <Util/Debug.h>
#include <Graphics/Gfx.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Geometry/Rect.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Global.h>

#include "DynamicNodes.h"

#include "Constraints/Sphere.h"
#include "Constraints/Spring.h"
#include "Constraints/Hard.h"
// - ------------------------------------------------------------------------------------------ - //
#include <FileIO/ScriptParser.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
class cSphereObject: public cDynamicNodes {
public:
	std::vector< cSphere > Sphere;
	std::vector< cSpring > Spring;

	std::vector< cSphere > SensorSphere;
	std::vector< cSpring > SensorSpring;
	
	// Hard constraints that lock to a point //	
	std::vector< cHard >  Hard;

public:	
	// Bounding Rectangle of all colliding objects //
	typedef RadiusRect2D RectType;
	RectType BoundingRect;
	
public:	
	// Information Flags About the SphereObject (Set by various parts of the engine) //
//	enum {
//		flSleeping = bit30,
//		flActive = bit31,
//	};
	
	// Associated Controller //
	int Control;
	
public:
	// - -------------------------------------------------------------------------------------- - //
	cSphereObject( ) :
		cDynamicNodes( 0 )
	{
	}
	// - -------------------------------------------------------------------------------------- - //	
	cSphereObject( const cScriptParser& Obj, const Real _x, const Real _y, const Real Scalar );
	// - -------------------------------------------------------------------------------------- - //


	// - -------------------------------------------------------------------------------------- - //
	void Step();
	// - -------------------------------------------------------------------------------------- - //
	void Solve( cSphereObject& Vs );
	void Solve( class cPolyObject& Vs );
	void Solve( class cStaticObject& Vs );
	void Solve( class cImpulse& Vs );
	void Solve( class cZone& Vs );
	// - -------------------------------------------------------------------------------------- - //
	void DebugDraw( /*const Vector2D& Offset*/ );
	void DebugDraw( int SpringColour, int SphereColour, Vector2D MapPos );
	// - -------------------------------------------------------------------------------------- - //	
	void Reset();
	// - -------------------------------------------------------------------------------------- - //	
	void SetHome();
	// - -------------------------------------------------------------------------------------- - //
	int AddHard( size_t _Index ) {
		Hard.push_back( cHard( _Index ) );
		Hard.back().Lock();
		return Hard.size() - 1;
	}
	// - -------------------------------------------------------------------------------------- - //
	void DeleteHard( size_t Number ) {
		// Make this an assert //
		if ( Number >= Hard.size() )
			return;
		// Test for less than zero too //
		
		Hard.erase( Hard.begin() + Number );
	}
	// - -------------------------------------------------------------------------------------- - //
	int AddSpring( size_t _IndexA, size_t _IndexB ) {
		// Make this an assert //
		if ( _IndexA >= size() )
			return -1;
		if ( _IndexB >= size() )
			return -1;
		// Test for less than zero too //
		
		Spring.push_back( cSpring( _IndexA, _IndexB ) );
		
		return Spring.size() - 1;
	}
	// - -------------------------------------------------------------------------------------- - //
	void DeleteSpring( size_t Number ) {
		// Make this an assert //
		if ( Number >= Spring.size() )
			return;
		// Test for less than zero too //
		
		Spring.erase( Spring.begin() + Number );
	}
	// - -------------------------------------------------------------------------------------- - //
	int AddSphere( size_t _Index ) {
		// Make this an assert //
		if ( _Index >= size() )
			return -1;
		// Test for less than zero too //
		
		Sphere.push_back( cSphere( _Index ) );

		return Sphere.size() - 1;
	}
	// - -------------------------------------------------------------------------------------- - //
	void DeleteSphere( size_t Number ) {
		// Make this an assert //
		if ( Number >= Sphere.size() )
			return;
		// Test for less than zero too //
		
//		std::vector< cSphere >::iterator Iterator = Sphere.begin();
//		for( size_t idx = 0; idx < Number; idx++ ) {
//			Iterator++;
//		}
		
		Sphere.erase( Sphere.begin() + Number );
	}
	// - -------------------------------------------------------------------------------------- - //
	void DeleteNode( size_t Number ) {
		// Remove Spheres //
		for( size_t idx = 0; idx < Sphere.size(); idx++ ) {
			if ( Sphere[ idx ].Index == Number ) {
				DeleteSphere( idx );
			}
		}
		// Update offsets //
		for( size_t idx = 0; idx < Sphere.size(); idx++ ) {
			if ( Sphere[ idx ].Index > Number ) {
				Sphere[ idx ].Index--;
			}
		}
		
		// Remove Springs, and offset greater ones //
		for( size_t idx = 0; idx < Spring.size(); idx++ ) {
			if ( Spring[ idx ].IndexA == Number ) {
				DeleteSpring( idx );
			}
			if ( Spring[ idx ].IndexB == Number ) {
				DeleteSpring( idx );
			}
		}
		for( size_t idx = 0; idx < Spring.size(); idx++ ) {			
			if ( Spring[ idx ].IndexA > Number ) {
				Spring[ idx ].IndexA--;
			}
			if ( Spring[ idx ].IndexB > Number ) {
				Spring[ idx ].IndexB--;
			}
		}
		
		// Lazy, toast all hard's //
		Hard.clear();
		
		// Remove the Node //
		cDynamicNodes::DeleteNode( Number );
	}
	// - -------------------------------------------------------------------------------------- - //
	void SaveFile( const char* File );
	// - -------------------------------------------------------------------------------------- - //
	void CalcBoundingRect();
	void CalculateSpringLength();
	// - -------------------------------------------------------------------------------------- - //
	inline void ClearFlags() {
		Flags.Clear();
		for ( size_t idx = 0; idx < Sphere.size(); idx ++ ) {
			Sphere[ idx ].Flags.Clear();
		}
	}
	// - -------------------------------------------------------------------------------------- - //
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Phiz_SphereObject_H__ //
// - ------------------------------------------------------------------------------------------ - //
