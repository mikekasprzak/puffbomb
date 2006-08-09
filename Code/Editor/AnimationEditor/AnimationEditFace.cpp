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
void cAnimationEdit::DeleteFace()
{
	/*if( Button[ KEY_DELETE ].Pressed() || isDelete )
	{
		if( !CurSelected.empty() )
		{
			std::vector < cDisplayMesh::cFace > tempFace;
		
			for( size_t i = 0; i < DisplayMesh[ CurrentObject ].Face.size(); ++i )
			{
				bool IndexA = false;
				bool IndexB = false;
				bool IndexC = false;
			
				for( size_t idx = 0; idx < CurSelected.size(); ++idx )
				{
					if( DisplayMesh[ CurrentObject ].Face[i].Vertex.a == int(CurSelected[idx]) )
					{
						IndexA = true;
					}
					if( DisplayMesh[ CurrentObject ].Face[i].Vertex.b == int(CurSelected[idx]) )
					{
						IndexB = true;
					}
					if( DisplayMesh[ CurrentObject ].Face[i].Vertex.c == int(CurSelected[idx]) )
					{
						IndexC = true;
					}
				}
				
				if( IndexA && IndexB && IndexC )
				{
					
				}
				else if( isDelete )
				{
					if( IndexA || IndexB || IndexC )
					{
						
					}
					else
					{
						tempFace.push_back( DisplayMesh[ CurrentObject ].Face[i] );
					}
				}
				else
				{
					tempFace.push_back( DisplayMesh[ CurrentObject ].Face[i] );
				}
			}
			DisplayMesh[ CurrentObject ].Face.clear();
			DisplayMesh[ CurrentObject ].Face.swap( tempFace );
			if( !isDelete )
			{
				CurSelected.clear();
				CurrentNode = DisplayMesh[ CurrentObject ].size() - 1;
				CurrentFace = DisplayMesh[ CurrentObject ].Face.size() - 1;
				ActiveAction();
			}
			else
			{
				std::vector< ABCSet<int> > subFace;
				
				ABCSet< int > tempABC;

				tempABC.a = 0;
				tempABC.b = 0;
				tempABC.c = 0;
				
				for( size_t idx = 0; idx < DisplayMesh[ CurrentObject ].Face.size(); ++idx )
				{
					subFace.push_back( tempABC );
				}
								
				for( size_t idx = 0; idx < DisplayMesh[ CurrentObject ].Face.size(); ++idx )
				{
					for( size_t ii = 0; ii < CurSelected.size(); ++ii )
					{						
						if( DisplayMesh[ CurrentObject ].Face[idx].Vertex.a 
							> int( CurSelected[ii] ) )
						{
							++subFace[ idx ].a;
						}
						if( DisplayMesh[ CurrentObject ].Face[idx].Vertex.b 
							> int( CurSelected[ii] ) )
						{
							++subFace[ idx ].b;
						}
						if( DisplayMesh[ CurrentObject ].Face[idx].Vertex.c 
							> int( CurSelected[ii] ) )
						{
							++subFace[ idx ].c;
						}
					}
				}
				for( size_t idx = 0; idx < DisplayMesh[ CurrentObject ].Face.size(); ++idx )
				{
					DisplayMesh[ CurrentObject ].Face[idx].Vertex.a -= subFace[ idx ].a;
					DisplayMesh[ CurrentObject ].Face[idx].Vertex.b -= subFace[ idx ].b;
					DisplayMesh[ CurrentObject ].Face[idx].Vertex.c -= subFace[ idx ].c;
				}			
			}
		}
	}*/
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
