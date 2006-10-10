#ifdef EDITOR
// - ------------------------------------------------------------------------------------------ - //
#include "ComponentEdit.h"

#include <Graphics/Gfx.h>
#include <Input/Input.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Global.h>
// - ------------------------------------------------------------------------------------------ - //
using namespace Input;
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::MeshAddFace()
{
	if( Button[ KEY_0_PAD ].Pressed() || Button[ KEY_A ].Pressed() /* || isPaste == true */ )
	{
		if(	!DynObj->AnimationSet->Animation[ CurMeshAnim ].Frame.empty() )
		{
			if( CurSelected.size() == 3 )
			{
				ABCSet< unsigned int > tempFace;
				
				MeshClockwise( tempFace );
	
				DynObj->AnimationSet->MeshPose[ DynObj->AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].MeshPoseIndex ].Face.push_back( tempFace );
				
				CurSelected.clear();
	
				ActiveAction();
			}
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::MeshDeleteFace()
{
	if( Button[ KEY_DELETE ].Pressed() || EditEventFlags & flDelete )
	{
		if( !CurSelected.empty() && !DynObj->AnimationSet->Animation[ CurMeshAnim ].Frame.empty() )
		{
			std::vector < ABCSet< unsigned int > > tempFace;
		
			for( size_t i = 0; i < DynObj->AnimationSet->MeshPose[ DynObj->AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].MeshPoseIndex ].Face.size(); ++i )
			{
				bool IndexA = false;
				bool IndexB = false;
				bool IndexC = false;
			
				for( size_t idx = 0; idx < CurSelected.size(); ++idx )
				{
					if( DynObj->AnimationSet->MeshPose[ DynObj->AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].MeshPoseIndex ].Face[i].a == CurSelected[idx] )
					{
						IndexA = true;
					}
					if( DynObj->AnimationSet->MeshPose[ DynObj->AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].MeshPoseIndex ].Face[i].b == CurSelected[idx] )
					{
						IndexB = true;
					}
					if( DynObj->AnimationSet->MeshPose[ DynObj->AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].MeshPoseIndex ].Face[i].c == CurSelected[idx] )
					{
						IndexC = true;
					}
				}
				
				if( IndexA && IndexB && IndexC )
				{
					
				}
				else if( EditEventFlags & flDelete )
				{
					if( IndexA || IndexB || IndexC )
					{
						
					}
					else
					{
						tempFace.push_back( DynObj->AnimationSet->MeshPose[ DynObj->AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].MeshPoseIndex ].Face[i] );
					}
				}
				else
				{
					tempFace.push_back( DynObj->AnimationSet->MeshPose[ DynObj->AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].MeshPoseIndex ].Face[i] );
				}
			}
			DynObj->AnimationSet->MeshPose[ DynObj->AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].MeshPoseIndex ].Face.clear();
			DynObj->AnimationSet->MeshPose[ DynObj->AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].MeshPoseIndex ].Face.swap( tempFace );
			
			if( !( EditEventFlags & flDelete ) )
			{
				CurSelected.clear();
				ActiveAction();
			}
			else
			{
				std::vector< ABCSet<unsigned int> > subFace;
				
				ABCSet< unsigned int > tempABC;

				tempABC.a = 0;
				tempABC.b = 0;
				tempABC.c = 0;
				
				for( size_t idx = 0; idx < DynObj->AnimationSet->MeshPose[ DynObj->AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].MeshPoseIndex ].Face.size(); ++idx )
				{
					subFace.push_back( tempABC );
				}
								
				for( size_t idx = 0; idx < DynObj->AnimationSet->MeshPose[ DynObj->AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].MeshPoseIndex ].Face.size(); ++idx )
				{
					for( size_t ii = 0; ii < CurSelected.size(); ++ii )
					{						
						if( DynObj->AnimationSet->MeshPose[ DynObj->AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].MeshPoseIndex ].Face[idx].a 
							> CurSelected[ii] )
						{
							++subFace[ idx ].a;
						}
						if( DynObj->AnimationSet->MeshPose[ DynObj->AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].MeshPoseIndex ].Face[idx].b 
							> CurSelected[ii] )
						{
							++subFace[ idx ].b;
						}
						if( DynObj->AnimationSet->MeshPose[ DynObj->AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].MeshPoseIndex ].Face[idx].c 
							> CurSelected[ii] )
						{
							++subFace[ idx ].c;
						}
					}
				}
				for( size_t idx = 0; idx < DynObj->AnimationSet->MeshPose[ DynObj->AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].MeshPoseIndex ].Face.size(); ++idx )
				{
					DynObj->AnimationSet->MeshPose[ DynObj->AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].MeshPoseIndex ].Face[idx].a -= subFace[ idx ].a;
					DynObj->AnimationSet->MeshPose[ DynObj->AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].MeshPoseIndex ].Face[idx].b -= subFace[ idx ].b;
					DynObj->AnimationSet->MeshPose[ DynObj->AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].MeshPoseIndex ].Face[idx].c -= subFace[ idx ].c;
				}			
			}
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::MeshClockwise( ABCSet< unsigned int > &tempFace )
{
	if( !DynObj->AnimationSet->Animation[ CurMeshAnim ].Frame.empty() )
	{

		Vector2D Ba = DynObj->AnimationSet->MeshPose[ DynObj->AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].MeshPoseIndex ].Node[ CurSelected[ 1 ] ].Pos -
			DynObj->AnimationSet->MeshPose[ DynObj->AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].MeshPoseIndex ].Node[ CurSelected[ 0 ] ].Pos;
		Vector2D Pcb = ( DynObj->AnimationSet->MeshPose[ DynObj->AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].MeshPoseIndex ].Node[ CurSelected[ 2 ] ].Pos -
			DynObj->AnimationSet->MeshPose[ DynObj->AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].MeshPoseIndex ].Node[ CurSelected[ 1 ] ].Pos ).Tangent();
		
		if( Ba * Pcb >= Real( 0 ) )
		{
			tempFace.a = CurSelected[0];
			tempFace.b = CurSelected[1];
			tempFace.c = CurSelected[2];
		}
		else
		{
			tempFace.a = CurSelected[0];
			tempFace.b = CurSelected[2];
			tempFace.c = CurSelected[1];
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::MeshGenerateUV()
{
	if(	!DynObj->AnimationSet->Animation[ CurMeshAnim ].Frame.empty() )
	{
		//DynObj->AnimationSet->Animation[ CurMeshAnim ].Frame.push_back( Engine2D::cComponentFrame() );
			
	//	DynObj->AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].BodyPoseIndex = CurPose;
		
		DynObj->AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].Time = 1;
		
		DynObj->AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].Mesh =
			Engine2D::cMesh2D( DynObj->AnimationSet->MeshPose[ DynObj->AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].MeshPoseIndex ], DynObj->Body );
				
	//	DynObj->AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].Mesh.Texture = TextureID[ CurTexPreview ];
		DynObj->AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].TextureIndex = TextureID[ AnimationGenerator->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].ImageIndex ];
	}
}
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
