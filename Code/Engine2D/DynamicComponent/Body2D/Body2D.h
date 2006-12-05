// - ------------------------------------------------------------------------------------------ - //
// Body2D //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Physics_Body2D_H__
#define __Engine2D_Physics_Body2D_H__
// - ------------------------------------------------------------------------------------------ - //
#include <vector>
// - ------------------------------------------------------------------------------------------ - //
#include <Physics/Physics.h>

#include "DynamicNodes/DynamicNodes.h"
#include "Pose/Body2DPose.h"
#include "CollisionFlags.h"

#include "Constraints/Spring.h"
#include "Constraints/Sphere.h"
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cBody2D {
public:
	// Nodes //
	cDynamicNodes Nodes;
	
	// Pose //
	cBody2DPose* Pose;
	
	// Constraints //
	inline cSpring& Spring( const size_t _Index ) const {
		return Pose->Spring[ _Index ];
	}
	inline const size_t SpringSize( ) const {
		return Pose->Spring.size();
	}

	inline cSphere& Sphere( const size_t _Index ) const {
		return Pose->Sphere[ _Index ];
	}
	inline const size_t SphereSize( ) const {
		return Pose->Sphere.size();
	}
	
//	std::vector< cSpring > Spring;
//	std::vector< cSphere > Sphere;
	
//	std::vector< cCylinder > Cylinder;	// A ?
//	std::vector< cCapsule > Capsule;	// or B ?

//	std::vector< cTriangle > Triangle;	// A ?
//	std::vector< cQuad > Quad;			// or B ?
//	std::vector< cPolygon > Polygon;	// or C ?
	
	
	// Collision monitoring flags //
	cCollisionFlags CollisionFlags;
	std::vector< cCollisionFlags > SphereFlags;	

public:
	cBody2D() {
		//Log( 10, "Haaagendaz" );
//		Pose = new cBody2DPose();
	}
	
	cBody2D( cBody2DPose& _Pose, const Vector2D& Offset = Vector2D::Zero ) :
		Pose( &_Pose )
	{
		Nodes.Resize( Pose->Node.size() );
		for ( size_t idx = 0; idx < Pose->Node.size(); idx++ ) {
			Nodes.Pos( idx ) = Pose->Node[ idx ].Pos + Offset;
			Nodes.Old( idx ) = Pose->Node[ idx ].Pos + Offset;
			Nodes.Force[ idx ] = Vector2D::Zero;
			Nodes.Friction[ idx ] = Real::Zero;
			Nodes.InvMass( idx ) = Pose->Node[ idx ].Mass;
			// Not needed when not in editor mode //
			Nodes.Mass[ idx ] = Pose->Node[ idx ].Mass;
		}
		SphereFlags.resize( Pose->Sphere.size() );

		Nodes.TotalMass = Pose->TotalMass;
	}
	
//	cBody2D( const cBody2D& Copy ) :
//		Nodes( Copy.Nodes ),
//		CollisionFlags( Copy.CollisionFlags ),
//		SphereFlags( Copy.SphereFlags ),
//		BoundingRect( Copy.BoundingRect )
//	{
//		//Log( 10, "Haaagendaz Go Go Duplicatotron!" );
//		Pose = new cBody2DPose( *Copy.Pose );
//	}

	~cBody2D() {
		//Log( 10, "Haaagendaz 4 evah!" );
//		delete Pose;
	}


public:	
	// - -------------------------------------------------------------------------------------- - //
	// Bounding rectangle, for early out test, and partitioning //
	cPhysics::BoundingRectType BoundingRect;
	// Calculate the rectangle for the object //
	void CalcBoundingRect();
	// Given a Sphere that caused a change, grow the bounding rectangle //
	void GrowBoundingRectBySphere( const size_t _Index );

public:
	// - -------------------------------------------------------------------------------------- - //
	// Step the nodes in the body. //
	// Unlike cDynamicComponent/Collection, this is not a self sufficent physics system. //
	void Step();
	// Step the springs in the body. //
	void StepSprings();
	
	// Calculate the length of all springs (given their current positions) //
	void CalculateSpringLength();

public:	
	// - -------------------------------------------------------------------------------------- - //
	// Solve Collisions/Actions //
	bool Solve( cBody2D& _Vs );
	void Solve( class cStaticBody2D& _Vs, const Vector2D& _Offset = Vector2D::Zero );
	void Solve( class cImpulse& _Vs );

public:
	// - -------------------------------------------------------------------------------------- - //
	// Debug Drawing Functions //
	void DrawNode( const size_t Index, const bool Selected = false ) const;
	void DrawSpring( const size_t Index, const bool Selected = false ) const;
	void DrawSphere( const size_t Index, const bool Selected = false ) const;

	void DrawNodes( const std::vector< size_t >& SelectionVector = std::vector< size_t >() ) const;
	void DrawSprings( const std::vector< size_t >& SelectionVector = std::vector< size_t >() ) const;
	void DrawSpheres( const std::vector< size_t >& SelectionVector = std::vector< size_t >() ) const;
	
	void DrawBoundingRect( const bool Selected = false ) const;
	// - -------------------------------------------------------------------------------------- - //
#ifdef EDITOR
public:
	// Editor Function //
	int AddNode();
	void DeleteNode( size_t Number );

	int AddSpring( size_t _IndexA, size_t _IndexB );
	void DeleteSpring( size_t Number );
	
	int AddSphere( size_t _Index );
	void DeleteSphere( size_t Number );
	
	void SetPos( const size_t Index, const Vector2D& _Pos ) {
		Pose->Node[ Index ].Pos = _Pos;
		Nodes.Pos( Index ) = _Pos;
		Nodes.Old( Index ) = _Pos;
	}

	void SetMass( const size_t Index, const Real& _Mass ) {
		Pose->Node[ Index ].Mass = _Mass;
		Nodes.Mass[ Index ] = _Mass;
	}

	void SetTotalMass( const Real& _Mass ) {
		Pose->TotalMass = _Mass;
		Nodes.TotalMass = _Mass;
	}
#endif // EDITOR //
	// - -------------------------------------------------------------------------------------- - //
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Physics_Body2D_H__ //
// - ------------------------------------------------------------------------------------------ - //
