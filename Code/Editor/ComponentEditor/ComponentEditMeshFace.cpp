#ifdef EDITOR
// - ------------------------------------------------------------------------------------------ - //
#include "ComponentEdit.h"

#include <Graphics/Gfx.h>
#include <Input/Input.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Platform/Global.h>
// - ------------------------------------------------------------------------------------------ - //
using namespace Input;
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::MeshAddFace()
{
	if( Button[ KEY_0_PAD ].Pressed() || Button[ KEY_A ].Pressed() /* || isPaste == true */ )
	{
		if( CurSelected.size() == 3 )
		{
			ABCSet< unsigned int > tempFace;
			
			MeshClockwise( tempFace );

			DynObj[ CurObj ].AnimationSet->MeshPose[ CurMeshPose ].Face.push_back( tempFace );
			
			CurSelected.clear();

			ActiveAction();
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::MeshDeleteFace()
{
	if( !CurSelected.empty() )
	{
		if( Button[ KEY_DELETE ].Pressed() )
		{
			/*std::vector< Engine2D::cMeshPoseNode > tempVec;
			for( size_t idx = 0; idx < DynObj[ CurObj ].AnimationSet->MeshPose[ CurMeshPose ].Node.size(); ++idx )
			{
				bool isDelete = false;
				for( size_t i = 0; i < CurSelected.size(); ++i )
				{
					if( CurSelected[i] == idx )
					{
						isDelete = true;
					}
				}
				if( !isDelete )
				{
					tempVec.push_back( DynObj[ CurObj ].AnimationSet->MeshPose[ CurMeshPose ].Node[ idx ] );
				}

			}
			DynObj[ CurObj ].AnimationSet->MeshPose[ CurMeshPose ].Node.swap( tempVec );

			CurSelected.clear();*/
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::MeshClockwise( ABCSet< unsigned int > &tempFace )
{
	Vector2D Ba = DynObj[ CurObj ].AnimationSet->MeshPose[ CurMeshPose ].Node[ CurSelected[ 1 ] ].Pos -
		DynObj[ CurObj ].AnimationSet->MeshPose[ CurMeshPose ].Node[ CurSelected[ 0 ] ].Pos;
	Vector2D Pcb = ( DynObj[ CurObj ].AnimationSet->MeshPose[ CurMeshPose ].Node[ CurSelected[ 2 ] ].Pos -
		DynObj[ CurObj ].AnimationSet->MeshPose[ CurMeshPose ].Node[ CurSelected[ 1 ] ].Pos ).Tangent();
	
	if( Ba * Pcb >= Real( 0 ) )
	{
		tempFace.a = CurSelected[0];
		tempFace.b = CurSelected[2];
		tempFace.c = CurSelected[1];
	}
	else
	{
		tempFace.a = CurSelected[0];
		tempFace.b = CurSelected[1];
		tempFace.c = CurSelected[2];
	}
}
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
