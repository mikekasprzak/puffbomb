#ifdef EDITOR
// - ------------------------------------------------------------------------------------------ - //
#include "AnimationEdit.h"

#include <Graphics/Gfx.h>
#include <Input/Input.h>

// - ------------------------------------------------------------------------------------------ - //
#include <Platform/Global.h>
// - ------------------------------------------------------------------------------------------ - //
using namespace Input;
// - ------------------------------------------------------------------------------------------ - //
void cAnimationEdit::AddFace()
{
	if( Button[ KEY_0_PAD ].Pressed() || Button[ KEY_A ].Pressed() )
	{
		if( CurSelected.size() == 3 )
		{
			cFrame::cFace tempFace;
			
			Clockwise( tempFace );
						
			tempFace.UV.a = Vector2D( 0.0, 0.0 );
			tempFace.UV.b = Vector2D( 0.0, 1.0 );
			tempFace.UV.c = Vector2D( 1.0, 1.0 );
			
			/*tempFace.UV.a = Vector2D( 0.0, 0.0 );
			tempFace.UV.b = Vector2D( 0.0, 1.0 );  // NEED SOMTHING BETTER THEN THIS SHIT
			tempFace.UV.c = Vector2D( 1.0, 1.0 );
			*/
			CurFrame->Face.push_back( tempFace );
			
			CurSelected.clear();
			//CurrentFace = DisplayMesh[ CurrentObject ].Face.size() - 1;
			
			//DisplayMesh[ CurrentObject ].Face[ CurrentFace ].Layer = CurLayer;
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cAnimationEdit::DeleteFaceFromNodes()
{
	if( Button[ KEY_DELETE ].Pressed() )
	{
		if( !CurSelected.empty() )
		{
			std::vector < cFrame::cFace > tempFace;
		
			for( size_t i = 0; i < CurFrame->Face.size(); ++i )
			{
				bool IndexA = false;
				bool IndexB = false;
				bool IndexC = false;
			
				for( size_t idx = 0; idx < CurSelected.size(); ++idx )
				{
					if( CurFrame->Face[i].VertexIdx.a == int(CurSelected[idx]) )
					{
						IndexA = true;
					}
					if( CurFrame->Face[i].VertexIdx.b == int(CurSelected[idx]) )
					{
						IndexB = true;
					}
					if( CurFrame->Face[i].VertexIdx.c == int(CurSelected[idx]) )
					{
						IndexC = true;
					}
				}
				
				if( IndexA && IndexB && IndexC )
				{
					
				}
				else
				{
					tempFace.push_back( CurFrame->Face[i] );
				}
			}
			CurFrame->Face.clear();
			CurFrame->Face.swap( tempFace );
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cAnimationEdit::Clockwise( cFrame::cFace &tempFace )
{
	Vector2D Ba = CurFrame->Vertex[ CurSelected[1] ].Pos
		- CurFrame->Vertex[ CurSelected[0] ].Pos;
	Vector2D Pcb = ( CurFrame->Vertex[ CurSelected[2] ].Pos
		- CurFrame->Vertex[ CurSelected[1] ].Pos ).Tangent();
		
	if( Ba * Pcb >= Real( 0 ) )
	{
		tempFace.VertexIdx.a = CurSelected[0];
		tempFace.VertexIdx.b = CurSelected[1];
		tempFace.VertexIdx.c = CurSelected[2];
	}
	else
	{

		tempFace.VertexIdx.a = CurSelected[0];
		tempFace.VertexIdx.b = CurSelected[2];
		tempFace.VertexIdx.c = CurSelected[1];
	}
}
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
