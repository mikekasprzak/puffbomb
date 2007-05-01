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
	size_t idx = 0;
	while ( idx < Obj.Instruction.size() ) {
		Log( 0, "- " << Obj.Instruction[ idx ].Command );

		// ------ Animation! ------------------------- //
		// If an animation is found //
		if ( Obj.Instruction[ idx ].Command == "Animation_Start" ) {
			// Add this new animation //
			Animation.push_back( cComponentAnimation() );

			// Next Instruction //
			idx++;
			
			// Loop until END found //
			while ( (Obj.Instruction[ idx ].Command != "Animation_End") && (idx < Obj.Instruction.size()) ) {
				// Output Command Name //
				Log( 0, "- " << Obj.Instruction[ idx ].Command );

				// If a loop point, set the current animation's loop point to this //
				if ( Obj.Instruction[ idx ].Command == "LoopPoint" ) {
					Animation.back().LoopPoint = atoi( Obj.Instruction[ idx ].Arg[ 0 ].c_str() );
				}

				// If a frame, set current animation's Pose Indecies //
				if ( Obj.Instruction[ idx ].Command == "Frame" ) {
					Animation.back().Frame.push_back(
						cComponentFrame(
							atoi( Obj.Instruction[ idx ].Arg[ 0 ].c_str() ),
							atoi( Obj.Instruction[ idx ].Arg[ 1 ].c_str() )
							)
						);
				}				

				// Next Instruction //
				idx++;
			}
		}

		// ------ Body Pose! ------------------------- //
		// If a Body Pose is found //
		if ( Obj.Instruction[ idx ].Command == "BodyPose_Start" ) {
			// Add this new Pose //
			BodyPose.push_back( cBody2DPose() );

			// Next Instruction //
			idx++;
			
			// Loop until END found //
			while ( (Obj.Instruction[ idx ].Command != "BodyPose_End") && (idx < Obj.Instruction.size()) ) {
				// Output Command Name //
				Log( 0, "- " << Obj.Instruction[ idx ].Command );

				// ------ TotalMass ------------------------- //
				// If TotalMass, set the object's TotalMass //
				if ( Obj.Instruction[ idx ].Command == "TotalMass" ) {
					BodyPose.back().TotalMass = atoi( Obj.Instruction[ idx ].Arg[ 0 ].c_str() );
				}

				// ------ Node ------------------------- //
				// If a Node, add a node //
				if ( Obj.Instruction[ idx ].Command == "BodyNode" ) {
					BodyPose.back().Node.push_back(
						cBodyPoseNode(
							Vector2D(
								atof( Obj.Instruction[ idx ].Arg[ 0 ].c_str() ),
								atof( Obj.Instruction[ idx ].Arg[ 1 ].c_str() )
								),
							atof( Obj.Instruction[ idx ].Arg[ 2 ].c_str() )
							)
						);
				}

				// ------ Spring ------------------------- //
				// If a Spring, add a Spring //
				if ( Obj.Instruction[ idx ].Command == "BodySpring" ) {
					BodyPose.back().Spring.push_back(
						cSpring(
							atoi( Obj.Instruction[ idx ].Arg[ 0 ].c_str() ),
							atoi( Obj.Instruction[ idx ].Arg[ 1 ].c_str() ),
							atof( Obj.Instruction[ idx ].Arg[ 2 ].c_str() ),
							atof( Obj.Instruction[ idx ].Arg[ 3 ].c_str() )
							)
						);
				}
				
				// The "Don't calculate spring length, mine is good" flag for springs //
				if ( Obj.Instruction[ idx ].Command == "ManualLength" ) {
					BodyPose.back().Spring.back().Flags.SetManualLength();
				}

				// The "Ignoring of Maximum Length" flag for springs //
				if ( Obj.Instruction[ idx ].Command == "IgnoreMaximum" ) {
					BodyPose.back().Spring.back().Flags.SetIgnoreMaximum();
				}

				// The "Ignoring of Minimum Length" flag for springs //
				if ( Obj.Instruction[ idx ].Command == "IgnoreMinimum" ) {
					BodyPose.back().Spring.back().Flags.SetIgnoreMinimum();
				}
				
				// ------ AngleCross ------------------------- //
				// If an AngleCross constraint, add an AngleCross constraint //
				if ( Obj.Instruction[ idx ].Command == "BodyAngleCross" ) {
					BodyPose.back().AngleCross.push_back(
						cAngleCross(
							atoi( Obj.Instruction[ idx ].Arg[ 0 ].c_str() ),
							atoi( Obj.Instruction[ idx ].Arg[ 1 ].c_str() ),
							atof( Obj.Instruction[ idx ].Arg[ 2 ].c_str() )
							)
						);
				}

				
				// ------ Sphere ------------------------- //
				// If a Sphere, add a Sphere //
				if ( Obj.Instruction[ idx ].Command == "BodySphere" ) {
					BodyPose.back().Sphere.push_back(
						cSphere(
							atoi( Obj.Instruction[ idx ].Arg[ 0 ].c_str() ),
							atof( Obj.Instruction[ idx ].Arg[ 1 ].c_str() )
							)
						);
				}

				// The "I cause action messages" flag for spheres //
				if ( Obj.Instruction[ idx ].Command == "Actuator" ) {
					BodyPose.back().Sphere.back().Flags.SetActuator();
				}

				// The "I sense, but not act" flag for spheres //
				if ( Obj.Instruction[ idx ].Command == "Sensor" ) {
					BodyPose.back().Sphere.back().Flags.SetSensor();
				}

				// Next Instruction //
				idx++;
			}
		}

		// ------ Mesh Pose! ------------------------- //
		// If a Mesh Pose is found //
		if ( Obj.Instruction[ idx ].Command == "MeshPose_Start" ) {
			// Add this new Pose //
			MeshPose.push_back( cMesh2DPose() );

			// Next Instruction //
			idx++;
			
			// Loop until END found //
			while ( (Obj.Instruction[ idx ].Command != "MeshPose_End") && (idx < Obj.Instruction.size()) ) {
				// Output Command Name //
				Log( 0, "- " << Obj.Instruction[ idx ].Command );
				
				// ------ Scale ------------------------ //
				// If a Node, add a node //
				if ( Obj.Instruction[ idx ].Command == "MeshPose_Scale" ) {
					MeshPose.back().TextureScale = atof( Obj.Instruction[ idx ].Arg[ 0 ].c_str() );
				}

				// ------ Node ------------------------- //
				// If a Node, add a node //
				if ( Obj.Instruction[ idx ].Command == "MeshNode" ) {
					MeshPose.back().Node.push_back(
						cMeshPoseNode(
							Vector2D(
								atof( Obj.Instruction[ idx ].Arg[ 0 ].c_str() ),
								atof( Obj.Instruction[ idx ].Arg[ 1 ].c_str() )
								),
							atoi( Obj.Instruction[ idx ].Arg[ 2 ].c_str() ),
							atoi( Obj.Instruction[ idx ].Arg[ 3 ].c_str() )
							)
						);
				}

				// ------ Face ------------------------- //
				// If a Face, add a Face //
				if ( Obj.Instruction[ idx ].Command == "MeshFace" ) {
					MeshPose.back().Face.push_back(
						ABCSet< size_t >(
							atoi( Obj.Instruction[ idx ].Arg[ 0 ].c_str() ),
							atoi( Obj.Instruction[ idx ].Arg[ 1 ].c_str() ),
							atoi( Obj.Instruction[ idx ].Arg[ 2 ].c_str() )
							)
						);
				}
	
				// Next Instruction //
				idx++;
			}
		}
		
		// Next Instruction //
		idx++;
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
				Animation[ idx ].Frame[ idx2 ].MeshPoseIndex
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

		// AngleCross SubSection //
		{
			// Write AngleCross SubSection header //
			Obj.Append( "BodyPose_AngleCross_Start", BodyPose[ idx ].AngleCross.size() );

			// For Every AngleCross constraint //
			for ( size_t idx2 = 0; idx2 < BodyPose[ idx ].AngleCross.size(); idx2++ ) {
				Obj.Append(
					"BodyAngleCross",
					BodyPose[ idx ].Spring[ idx2 ].IndexP,
					BodyPose[ idx ].Spring[ idx2 ].IndexA,
					BodyPose[ idx ].Spring[ idx2 ].IndexB
					);
				
				// Write extra commands for flags //
//				if ( BodyPose[ idx ].Spring[ idx2 ].Flags.ManualLength() ) {
//					Obj.Append( "ManualLength" );
//				}
			}

			// Write Node SubSection footer //
			Obj.Append( "BodyPose_AngleCross_End" );
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
			
			Obj.Append( "MeshPose_Scale", MeshPose[ idx ].TextureScale );

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
