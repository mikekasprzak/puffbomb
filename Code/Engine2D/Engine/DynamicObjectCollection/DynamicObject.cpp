// - ------------------------------------------------------------------------------------------ - //
#include <Util/Debug.h>

#include <Physics/Physics.h>

#include "DynamicObject.h"
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
// In the case of a component without a parent, if checks should be placed to stop messanging //
cDynamicObject::cDynamicObject( ) :
	Parent( 0 )
{	
}
// - ------------------------------------------------------------------------------------------ - //
cDynamicObject::cDynamicObject( const class cDynamicObject* const _Parent ) :
	Parent( _Parent )
{
}
// - ------------------------------------------------------------------------------------------ - //
void cDynamicObject::Step() {
	// Step the nodes //
	Body.Step();

	// Physics relaxation loop //
	for ( int NodeSteps = 0; NodeSteps < cPhysics::Current->RelaxationSteps; NodeSteps++ ) {
		// Update all Springs //
		Body.StepSprings();
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cDynamicObject::Draw() {
	Mesh.Draw( Body );
}
// - ------------------------------------------------------------------------------------------ - //
void cDynamicObject::DrawBody( const bool Selected ) const {
	// Draw the debug body information //
	Body.DrawSpheres();
	Body.DrawSprings();
	Body.DrawNodes();
	
	Body.DrawBoundingRect();
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
