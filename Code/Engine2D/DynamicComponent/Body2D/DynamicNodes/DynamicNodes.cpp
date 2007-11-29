// - ------------------------------------------------------------------------------------------ - //
// DynamicNodes //
// - ------------------------------------------------------------------------------------------ - //
#include "DynamicNodes.h"
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
int cDynamicNodes::Add() {
	NodeA.push_back( Vector2D::Zero );
	NodeB.push_back( Vector2D::Zero );
	Force.push_back( Vector2D::Zero );
		
	Friction.push_back( Real::One );
	_InvMass.push_back( Real::One );
	Mass.push_back( Real::One );
	
	return NodeA.size() - 1;
}
// - ------------------------------------------------------------------------------------------ - //
void cDynamicNodes::Resize( const size_t _Size ) {
	NodeA.resize( _Size );
	NodeB.resize( _Size );
	Force.resize( _Size );
	Friction.resize( _Size );
	_InvMass.resize( _Size );
	Mass.resize( _Size );
}	
// - ------------------------------------------------------------------------------------------ - //
void cDynamicNodes::Remove( const size_t Number ) {
	// Make this an assert //
	if ( Number >= Size() )
		return;
		
	NodeA.erase( NodeA.begin() + Number );
	NodeB.erase( NodeB.begin() + Number );
	Force.erase( Force.begin() + Number );
	Friction.erase( Friction.begin() + Number );
	_InvMass.erase( _InvMass.begin() + Number );
	Mass.erase( Mass.begin() + Number );
}
// - ------------------------------------------------------------------------------------------ - //
void cDynamicNodes::Dump() {
	for ( size_t idx = 0; idx < NodeA.size(); idx++ ) {
		Log( 10, "[ " << idx << " ]" <<
			"Pos: " << Pos( idx ).x << " " << Pos( idx ).y << 
			"  Old: " << Old( idx ).x << " " << Old( idx ).y
			);
		Log( 10, "[ " << idx << " ]" <<
			"Friction: " << Friction[ idx ] << 
			"  Force: " << Force[ idx ].x << " " << Force[ idx ].y
			);
//		Log( 10, "[ " << idx << " ]" <<
//			"HomePos: " << HomePos( idx ).x << " " << _HomePos( idx ).y << 
//			"  HomeOld: " << HomeOld( idx ).x << " " << _HomeOld( idx ).y
//			);
	}
	
	Log( 10, "PosPTR: " << Pos() << "  OldPtr: " << Old() );
}	
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
