// - ------------------------------------------------------------------------------------------ - //
// DynamicNodes //
// - ------------------------------------------------------------------------------------------ - //
#include "DynamicNodes.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
int cDynamicNodes::AddNode() {
	NodeA.push_back( Vector2D::Zero );
	NodeB.push_back( Vector2D::Zero );
	_Force.push_back( Vector2D::Zero );
		
	_Friction.push_back( Real::One );
	_InvMass.push_back( Real::One );
	Mass.push_back( Real::One );
	
	_HomePos.push_back( Vector2D::Zero );
	_HomeOld.push_back( Vector2D::Zero );
		
	return NodeA.size() - 1;
}	
// - ------------------------------------------------------------------------------------------ - //
void cDynamicNodes::DeleteNode( size_t Number ) {
	// Make this an assert //
	if ( Number >= size() )
		return;
	// Test for less than zero too //
		
	NodeA.erase( NodeA.begin() + Number );
	NodeB.erase( NodeB.begin() + Number );
	_Force.erase( _Force.begin() + Number );
	_Friction.erase( _Friction.begin() + Number );
	_InvMass.erase( _InvMass.begin() + Number );
	Mass.erase( Mass.begin() + Number );
	
	_HomePos.erase( _HomePos.begin() + Number );
	_HomeOld.erase( _HomeOld.begin() + Number );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
