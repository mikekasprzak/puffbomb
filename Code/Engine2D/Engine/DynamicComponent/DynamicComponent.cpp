// - ------------------------------------------------------------------------------------------ - //
#include <Util/Debug.h>

#include <Physics/Physics.h>

#include <Engine/DynamicCollection.h>
#include "../DynamicComponent.h"
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
// In the case of a component without a parent, if checks should be placed to stop messanging //
cDynamicComponent::cDynamicComponent( ) :
	Parent( 0 )
{	
}
// - ------------------------------------------------------------------------------------------ - //
cDynamicComponent::cDynamicComponent( const cDynamicCollection* const _Parent ) :
	Parent( _Parent )
{
}
// - ------------------------------------------------------------------------------------------ - //
void cDynamicComponent::Step() {
	// Step the nodes //
	Body.Step();

	// Physics relaxation loop //
	for ( int NodeSteps = 0; NodeSteps < cPhysics::Current->RelaxationSteps; NodeSteps++ ) {
		// Update all Springs //
		Body.StepSprings();
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cDynamicComponent::Draw() {
	// Should be animator //
	//Mesh.Draw( Body );
}
// - ------------------------------------------------------------------------------------------ - //
void cDynamicComponent::DrawBody( const bool Selected ) const {
	// Draw the debug body information //
	Body.DrawSpheres();
	Body.DrawSprings();
	Body.DrawNodes();
	
	Body.DrawBoundingRect();
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
