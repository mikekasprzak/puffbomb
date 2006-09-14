// - ------------------------------------------------------------------------------------------ - //
#include "ComponentAnimationSet.h"

#include <Util/ScriptParser.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
void cComponentAnimationSet::LoadText( const std::string& FileName ) {
	// Load the File //
	cScriptParser Obj( FileName );
	
	// For every instruction //
	for ( size_t idx = 0; idx < Obj.Instruction.size(); idx++ ) {
		cScriptParser::cInstruction& Instr = Obj.Instruction[ idx ];
		
		if ( Instr.Command == "TotalMass" ) {
			Log( LOG_PHIZOBJECT_INFO, "- Found Total Mass" );
		}
		
	}
	
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentAnimationSet::SaveText( const std::string& FileName ) {
	cScriptParser Obj;
	
	// For all Animations //
	for ( size_t idx = 0; idx < Animation.size(); idx++ ) {
		// Write Animation Section header //
		Obj.Append( "Animation_Start", Animation[ idx ].Frame.size() );
		Obj.Append( "LoopPoint", Animation[ idx ].LoopPoint );
		
		// For every frame //
		for ( size_t idx2 = 0; idx2 < Animation[ idx ].Frame.size(); idx2++ ) {
			Obj.Append(
				"Frame",
				Animation[ idx ].Frame[ idx2 ].BodyPoseIndex,
				Animation[ idx ].Frame[ idx2 ].MeshPoseIndex,
				Animation[ idx ].Frame[ idx2 ].Time
				);
		}
		
		// Write Animation Section footer //
		Obj.Append( "Animation_End" );
	}
	
	// For all Body Poses //
	for ( size_t idx = 0; idx < BodyPose.size(); idx++ ) {
		// Write Body Pose Section header //
		Obj.Append( "BodyPose_Start" );
		Obj.Append( "TotalMass", BodyPose[ idx ].TotalMass );

		// Node SubSection //
		{
			// Write Node SubSection header //
			Obj.Append( "BodyPose_Node_Start", BodyPose[ idx ].Node.size() );

			// For Every Node //
			for ( size_t idx2 = 0; idx2 < BodyPose[ idx ].Node.size(); idx2++ ) {
				Obj.Append(
					"BodyNode",
					BodyPose[ idx ].Node[ idx2 ].Pos.x,
					BodyPose[ idx ].Node[ idx2 ].Pos.y,
					BodyPose[ idx ].Node[ idx2 ].Mass
					);
			}

			// Write Node SubSection footer //
			Obj.Append( "BodyPose_Node_End" );
		}

		// Spring SubSection //
		{
			// Write Spring SubSection header //
			Obj.Append( "BodyPose_Spring_Start", BodyPose[ idx ].Spring.size() );

			// For Every Spring //
			for ( size_t idx2 = 0; idx2 < BodyPose[ idx ].Spring.size(); idx2++ ) {
				Obj.Append(
					"BodySpring",
					BodyPose[ idx ].Spring[ idx2 ].IndexA,
					BodyPose[ idx ].Spring[ idx2 ].IndexB,
					BodyPose[ idx ].Spring[ idx2 ].Length,
					BodyPose[ idx ].Spring[ idx2 ].Strength
					);
				
				// Write extra commands for flags //
				if ( BodyPose[ idx ].Spring[ idx2 ].Flags.ManualLength() ) {
					Obj.Append( "ManualLength" );
				}

				if ( BodyPose[ idx ].Spring[ idx2 ].Flags.IgnoreMinimum() ) {
					Obj.Append( "IgnoreMinimum" );
				}

				if ( BodyPose[ idx ].Spring[ idx2 ].Flags.IgnoreMaximum() ) {
					Obj.Append( "IgnoreMaximum" );
				}
			}

			// Write Node SubSection footer //
			Obj.Append( "BodyPose_Spring_End" );
		}

		// Sphere SubSection //
		{
			// Write Sphere SubSection header //
			Obj.Append( "BodyPose_Sphere_Start", BodyPose[ idx ].Sphere.size() );

			// For Every Sphere //
			for ( size_t idx2 = 0; idx2 < BodyPose[ idx ].Sphere.size(); idx2++ ) {
				Obj.Append(
					"BodySphere",
					BodyPose[ idx ].Sphere[ idx2 ].Index,
					BodyPose[ idx ].Sphere[ idx2 ].Radius
					);
				
				// Write extra commands for flags //
				if ( BodyPose[ idx ].Sphere[ idx2 ].Flags.Sensor() ) {
					Obj.Append( "Sensor" );
				}

				if ( BodyPose[ idx ].Sphere[ idx2 ].Flags.Actuator() ) {
					Obj.Append( "Actuator" );
				}
			}

			// Write Node SubSection footer //
			Obj.Append( "BodyPose_Sphere_End" );
		}

		// Write Body Pose Section footer //
		Obj.Append( "BodyPose_End" );		
	}
	
	// For all Mesh Poses //
	for ( size_t idx = 0; idx < MeshPose.size(); idx++ ) {
		// Write Body Pose Section header //
		Obj.Append( "MeshPose_Start" );

		// Node SubSection //
		{
			// Write Node SubSection header //
			Obj.Append( "MeshPose_Node_Start", MeshPose[ idx ].Node.size() );

			// For Every Node //
			for ( size_t idx2 = 0; idx2 < MeshPose[ idx ].Node.size(); idx2++ ) {
				Obj.Append(
					"MeshNode",
					MeshPose[ idx ].Node[ idx2 ].Pos.x,
					MeshPose[ idx ].Node[ idx2 ].Pos.y,
					MeshPose[ idx ].Node[ idx2 ].PivotIndex,
					MeshPose[ idx ].Node[ idx2 ].HandleIndex
					);
			}

			// Write Node SubSection footer //
			Obj.Append( "MeshPose_Node_End" );
		}
		
		// Face SubSection //
		{
			// Write Face SubSection header //
			Obj.Append( "MeshPose_Face_Start", MeshPose[ idx ].Face.size() );

			// For Every Face //
			for ( size_t idx2 = 0; idx2 < MeshPose[ idx ].Face.size(); idx2++ ) {
				Obj.Append(
					"MeshFace",
					MeshPose[ idx ].Face[ idx2 ].a,
					MeshPose[ idx ].Face[ idx2 ].b,
					MeshPose[ idx ].Face[ idx2 ].c
					);
			}

			// Write Face SubSection footer //
			Obj.Append( "MeshPose_Face_End" );
		}

		// Write Body Pose Section footer //
		Obj.Append( "MeshPose_End" );		
	}

	// Save the File //	
	Obj.SaveFile( FileName );
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
