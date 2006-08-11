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
void cAnimationEdit::SelectFace()
{
	if( Button[ MOUSE_1 ].Pressed() )
	{
		OldMousePos = CurMousePos;
	}
	
	if( Button[ MOUSE_1 ].Released() )
	{
		// Group add-select //
		if( Button[ KEY_LSHIFT ] || Button[ KEY_RSHIFT ] )
		{
			// Single add-select //
			int temp = SingleSelectFace();
			if( temp != -1 /* && CurFrame->Face[temp].Layer == CurLayer */ )
			{
				bool CurSelectedTest = false;
				for( size_t i = 0; i < CurSelected.size(); ++i )
				{
					if( int( CurSelected[i] ) == temp )
					{
						CurSelectedTest = true;
					}					
				}
				if( !CurSelectedTest )
				{
					CurSelected.push_back( temp );	
				}
			}
		}
		// Group de-select //
		else if( Button[ KEY_LCTRL ] || Button[ KEY_RCTRL ] )
		{
			// Single de-select //
			int temp = SingleSelectFace();
			if( temp != -1 /* && CurFrame->Face[temp].Layer == CurLayer */ )
			{
				for( size_t i = 0; i < CurSelected.size(); ++i )
				{
					if( int(CurSelected[i]) == temp )
					{			
						std::vector <size_t> tempVec;
						for( size_t vec = 0; vec < CurSelected.size(); ++vec )
						{
							if( int(CurSelected[vec]) != temp )
							{
								tempVec.push_back( CurSelected[vec] );
							}
						}
						CurSelected.swap( tempVec );
					}
				}
			}
		}
		// Standard group select //
		else
		{
			CurSelected.clear();

			for( size_t idx = 0; idx < CurFrame->Vertex.size(); ++idx )
			{
				if( WithinBox( CurFrame->Vertex[ idx ].Pos, CurMousePos, OldMousePos ) )
				{
					for( size_t i = 0; i < CurFrame->Face.size(); ++i )
					{
						if( FaceInBox( i, idx ) /* && CurFrame->Face[i].Layer == CurLayer */ )
						{
							bool isNew = true;
							for( size_t vec = 0; vec < CurSelected.size(); ++vec )
							{
								if( CurSelected[vec] == i )
								{
									isNew = false;
								}
							}
							if( isNew )
							{
								CurSelected.push_back( i );
							}
						} 
					}
				}
			}
			// Single select //
			if( CurSelected.empty() )
			{
				int temp = SingleSelectFace();
				if( temp != -1 /* && DisplayMesh[ CurrentObject ].Face[temp].Layer == CurLayer */ )
				{
					CurSelected.push_back( temp );
				}
			}
		}
		
		/*if( !CurSelected.empty() )
		{
			CurrentNode = CurSelected[0];
		}
		CurSelUV.clear();*/
	}
}
// - ------------------------------------------------------------------------------------------ - //
bool cAnimationEdit::FaceInBox( int i, int idx )
{
	if( CurFrame->Face[ i ].VertexIdx.a == int( idx ) )
	{
		return true;	
	}
	if( CurFrame->Face[ i ].VertexIdx.b == int( idx ) )
	{
		return true;	
	}
	if( CurFrame->Face[ i ].VertexIdx.c == int( idx ) )
	{
		return true;	
	}

	return false;
}
// - ------------------------------------------------------------------------------------------ - //
int cAnimationEdit::SingleSelectFace()
{
	for( size_t idx = 0; idx < CurFrame->Face.size(); ++idx )
	{
		Vector2D Pba = ( CurFrame->Vertex[ CurFrame->Face[ idx ].VertexIdx.b ].Pos -
						 CurFrame->Vertex[ CurFrame->Face[ idx ].VertexIdx.a ].Pos ).Tangent();

		Vector2D Pcb = ( CurFrame->Vertex[ CurFrame->Face[ idx ].VertexIdx.c ].Pos -
						 CurFrame->Vertex[ CurFrame->Face[ idx ].VertexIdx.b ].Pos ).Tangent();

		Vector2D Pac = ( CurFrame->Vertex[ CurFrame->Face[ idx ].VertexIdx.a ].Pos -
						 CurFrame->Vertex[ CurFrame->Face[ idx ].VertexIdx.c ].Pos ).Tangent();

		Vector2D Am	= CurFrame->Vertex[ CurFrame->Face[ idx ].VertexIdx.a ].Pos - CurMousePos;
		Vector2D Bm	= CurFrame->Vertex[ CurFrame->Face[ idx ].VertexIdx.b ].Pos - CurMousePos;
		Vector2D Cm	= CurFrame->Vertex[ CurFrame->Face[ idx ].VertexIdx.c ].Pos - CurMousePos;

		Real InSideA = ( Pba * Am );
		Real InSideB = ( Pcb * Bm );
		Real InSideC = ( Pac * Cm );
		
		// seem to need both of these //
		if( InSideA > 1 && InSideB > 1 && InSideC > 1 )
		{
			return idx;
		}
		if( InSideA < 1 && InSideB < 1 && InSideC < 1 )
		{
			return idx;
		}

	}
	return -1;
}
// - ------------------------------------------------------------------------------------------ - //
void cAnimationEdit::DeleteFaceFromFace()
{
	if( Button[ KEY_DELETE ].Pressed() )
	{
		if( !CurSelected.empty() )
		{
			std::vector < cFrame::cFace > tempFace;
		
			for( size_t i = 0; i < CurFrame->Face.size(); ++i )
			{
				bool IsSelected = false;
								
				for( size_t idx = 0; idx < CurSelected.size(); ++idx )
				{
					if( i == CurSelected[idx] )
					{
						IsSelected = true;
						break;
					}
				}
				
				if( !IsSelected )
				{
					tempFace.push_back( CurFrame->Face[i] );
				}
			}
			CurFrame->Face.clear();
			CurFrame->Face.swap( tempFace );
			
			CurSelected.clear();
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
