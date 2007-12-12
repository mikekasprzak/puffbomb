// - ------------------------------------------------------------------------------------------ - //
// Body2DPose //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Physics_Body2D_Body2DPose_H__
#define __Engine2D_Physics_Body2D_Body2DPose_H__
// - ------------------------------------------------------------------------------------------ - //
#include <vector>
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Real.h>
#include <Math/Vector.h>
// - ------------------------------------------------------------------------------------------ - //
#include "BodyPoseNode.h"
#include <DynamicComponent/Body2D/Constraints/Spring.h>
#include <DynamicComponent/Body2D/Constraints/Sphere.h>
#include <DynamicComponent/Body2D/Constraints/AngleCross.h>
#include <DynamicComponent/Body2D/Constraints/RopeConstraint.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cBody2DPose {
public:
	std::vector< cBodyPoseNode > Node;
	std::vector< cSpring > Spring;
	std::vector< cSphere > Sphere;
	std::vector< cAngleCross > AngleCross;
	std::vector< cRopeConstraint > RopeConstraint;
		
	Real TotalMass;
	
	cBody2DPose() :
		TotalMass( Real::One )
	{
	}
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Physics_Body2D_Body2DPose_H__ //
// - ------------------------------------------------------------------------------------------ - //
