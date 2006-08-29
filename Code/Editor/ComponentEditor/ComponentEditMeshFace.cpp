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
		/*CurSelected.clear();

		int PivotIdx = 0;
		int HandleIdx = 1;
		Real Pivot = 100000.0;
		Real Handle = 100000.0;
		Real TestDistance = 100000.0;
	
		for( size_t idx = 0; idx < Pose->Node.size(); ++idx )
		{
			TestDistance = ( Pose->Node[ idx ].Pos - CurMousePos ).Magnitude();
		
			if( TestDistance < Pivot )
			{
				Pivot = TestDistance;
				PivotIdx = idx;
			}
		}
		
		for( size_t idx = 0; idx < Pose->Node.size(); ++idx )
		{
			TestDistance = ( Pose->Node[ idx ].Pos - CurMousePos ).Magnitude();
			
			if( int( idx ) != PivotIdx )
			{
				if( TestDistance < Handle )
				{
					Handle = TestDistance;
					HandleIdx = idx;
				}
			}
		}

		Vector2D TempPos = CurMousePos;

		if( !Button[ KEY_LSHIFT ] )
		{
			SetGridDepth( Camera, CurrentGridDepth, 32.0 );
			SetGridArray( CurrentGridDepth, UVGridDepth );

			CalcSnapToGrid( TempPos, CurrentGridDepth, UVGridDepth );
		}
		DynObj[ CurObj ].AnimationSet->MeshPose[ CurMeshPose ].Node.push_back( Engine2D::cMeshPoseNode( TempPos, PivotIdx, HandleIdx ) );

		CurSelected.push_back( DynObj[ CurObj ].AnimationSet->MeshPose[ CurMeshPose ].Node.size() - 1 );

		ActiveAction();*/
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
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
