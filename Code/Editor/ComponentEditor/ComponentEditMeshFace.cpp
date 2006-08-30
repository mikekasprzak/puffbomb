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
	if( Button[ KEY_DELETE ].Pressed() || EditEventFlags & flDelete )
	{
		if( !CurSelected.empty() )
		{
			std::vector < ABCSet< unsigned int > > tempFace;
		
			for( size_t i = 0; i < DynObj[ CurObj ].AnimationSet->MeshPose[ CurMeshPose ].Face.size(); ++i )
			{
				bool IndexA = false;
				bool IndexB = false;
				bool IndexC = false;
			
				for( size_t idx = 0; idx < CurSelected.size(); ++idx )
				{
					if( DynObj[ CurObj ].AnimationSet->MeshPose[ CurMeshPose ].Face[i].a == CurSelected[idx] )
					{
						IndexA = true;
					}
					if( DynObj[ CurObj ].AnimationSet->MeshPose[ CurMeshPose ].Face[i].b == CurSelected[idx] )
					{
						IndexB = true;
					}
					if( DynObj[ CurObj ].AnimationSet->MeshPose[ CurMeshPose ].Face[i].c == CurSelected[idx] )
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
						tempFace.push_back( DynObj[ CurObj ].AnimationSet->MeshPose[ CurMeshPose ].Face[i] );
					}
				}
				else
				{
					tempFace.push_back( DynObj[ CurObj ].AnimationSet->MeshPose[ CurMeshPose ].Face[i] );
				}
			}
			DynObj[ CurObj ].AnimationSet->MeshPose[ CurMeshPose ].Face.clear();
			DynObj[ CurObj ].AnimationSet->MeshPose[ CurMeshPose ].Face.swap( tempFace );
			
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
				
				for( size_t idx = 0; idx < DynObj[ CurObj ].AnimationSet->MeshPose[ CurMeshPose ].Face.size(); ++idx )
				{
					subFace.push_back( tempABC );
				}
								
				for( size_t idx = 0; idx < DynObj[ CurObj ].AnimationSet->MeshPose[ CurMeshPose ].Face.size(); ++idx )
				{
					for( size_t ii = 0; ii < CurSelected.size(); ++ii )
					{						
						if( DynObj[ CurObj ].AnimationSet->MeshPose[ CurMeshPose ].Face[idx].a 
							> CurSelected[ii] )
						{
							++subFace[ idx ].a;
						}
						if( DynObj[ CurObj ].AnimationSet->MeshPose[ CurMeshPose ].Face[idx].b 
							> CurSelected[ii] )
						{
							++subFace[ idx ].b;
						}
						if( DynObj[ CurObj ].AnimationSet->MeshPose[ CurMeshPose ].Face[idx].c 
							> CurSelected[ii] )
						{
							++subFace[ idx ].c;
						}
					}
				}
				for( size_t idx = 0; idx < DynObj[ CurObj ].AnimationSet->MeshPose[ CurMeshPose ].Face.size(); ++idx )
				{
					DynObj[ CurObj ].AnimationSet->MeshPose[ CurMeshPose ].Face[idx].a -= subFace[ idx ].a;
					DynObj[ CurObj ].AnimationSet->MeshPose[ CurMeshPose ].Face[idx].b -= subFace[ idx ].b;
					DynObj[ CurObj ].AnimationSet->MeshPose[ CurMeshPose ].Face[idx].c -= subFace[ idx ].c;
				}			
			}
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