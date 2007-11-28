// - ------------------------------------------------------------------------------------------ - //
#include <Util/Debug.h>

#include <Physics/Physics.h>

#include <DynamicCollection/DynamicCollection.h>
#include "DynamicComponent.h"

#include "ComponentAnimationSet/ComponentAnimationSetPool.h"
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
// In the case of a component without a parent, if checks should be placed to stop messanging //
cDynamicComponent::cDynamicComponent( ) :
	Parent( 0 )
{
}
// - ------------------------------------------------------------------------------------------ - //
cDynamicComponent::cDynamicComponent( cDynamicCollection* const _Parent, const std::string& ComponentFile, const Vector2D& Offset ) :
	Parent( _Parent ),
	Animator( ComponentAnimationSetPool.Load( ComponentFile ) ),
	Body( *Animator.GetPose(), Offset )
{
}
// - ------------------------------------------------------------------------------------------ - //
void cDynamicComponent::Step() {
	// Step the nodes //
	Body.Step();

	// Physics relaxation loop //
	for ( int NodeSteps = 0; NodeSteps < cPhysics::Current->RelaxationSteps; NodeSteps++ ) {
		// Update all Springs //
		Body.StepInternalConstraints();
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cDynamicComponent::StepAnimation() {
	Animator.Step();
}
// - ------------------------------------------------------------------------------------------ - //
void cDynamicComponent::SetAnimation( const int AnimationNumber, const Real& _PlayBackRate ) {
	Animator.SetAnimation( AnimationNumber, _PlayBackRate );
	// Set the Pose //
	Body.Pose = Animator.GetPose();
}
// - ------------------------------------------------------------------------------------------ - //
void cDynamicComponent::SetArcingAnimation( const int AnimationNumber ) {
	Animator.SetArcingAnimation( AnimationNumber );
	// Set the Pose //
	Body.Pose = Animator.GetPose();
}
// - ------------------------------------------------------------------------------------------ - //
void cDynamicComponent::SetArc( const Real& Arc ) {
	Animator.SetArc( Arc );
	// Set the Pose //
	Body.Pose = Animator.GetPose();
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cDynamicComponent::Draw( const int RenderPass ) {
	Animator.Draw( Body, RenderPass );
}
// - ------------------------------------------------------------------------------------------ - //
void cDynamicComponent::DrawBody( const bool /*Selected*/ ) const {
	// Draw the debug body information //
	Body.DrawSpheres();
	Body.DrawSprings();
	Body.DrawAngleCrosses();
	Body.DrawNodes();
	
	Body.DrawBoundingRect();
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
