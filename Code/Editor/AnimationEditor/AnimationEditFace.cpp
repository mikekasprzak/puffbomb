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
	/*if( Button[ MOUSE_1 ].Pressed() )
	{
		OldMousePos = CalcMousePos();
	}
	
	if( Button[ MOUSE_1 ].Released() )
	{
		Vector2D CurMousePos = CalcMousePos();
		// Group add-select //
		if( Button[ KEY_LSHIFT ] || Button[ KEY_RSHIFT ] )
		{
			// Single add-select //
			int temp = DisSingleSelectFace( CurMousePos );
			if( temp != -1 &&
				DisplayMesh[ CurrentObject ].Face[temp].Layer == CurLayer )
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
			int temp = DisSingleSelectFace( CurMousePos );
			if( temp != -1 &&
				DisplayMesh[ CurrentObject ].Face[temp].Layer == CurLayer )
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

			for( size_t idx = 0; idx < DisplayMesh[ CurrentObject ].size(); ++idx )
			{
				if( WithinBox( DisplayMesh[ CurrentObject ].Pos( idx ), CurMousePos,
					 OldMousePos ) )
				{
					for( size_t i = 0; i < DisplayMesh[ CurrentObject ].Face.size(); ++i )
					{
						if( DisFaceInBox( i, idx ) &&
							DisplayMesh[ CurrentObject ].Face[i].Layer == CurLayer )
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
				int temp = DisSingleSelectFace( CurMousePos );
				if( temp != -1 && 
					DisplayMesh[ CurrentObject ].Face[temp].Layer == CurLayer )
				{
					CurSelected.push_back( temp );
				}
			}
		}
		
		if( !CurSelected.empty() )
		{
			CurrentNode = CurSelected[0];
		}
		CurSelUV.clear();
	}*/
}
// - ------------------------------------------------------------------------------------------ - //
bool cAnimationEdit::FaceInBox( int i, int idx )
{
	/*if( DisplayMesh[ CurrentObject ].Face[i].Vertex.a == int( idx ) )
	{
		return true;	
	}
	if( DisplayMesh[ CurrentObject ].Face[i].Vertex.b == int( idx ) )
	{
		return true;	
	}
	if( DisplayMesh[ CurrentObject ].Face[i].Vertex.c == int( idx ) )
	{
		return true;	
	}
	return false;*/
}
// - ------------------------------------------------------------------------------------------ - //
int cAnimationEdit::SingleSelectFace()
{
	/*if( DisplayMesh[ CurrentObject ].Face.size() > 0 )
	{
		for( size_t idx = 0; idx < DisplayMesh[ CurrentObject ].Face.size(); ++idx )
		{
			Vector2D Pba = 
				( DisplayMesh[ CurrentObject ].Pos(
					DisplayMesh[ CurrentObject ].Face[idx].Vertex.b ) -
				DisplayMesh[ CurrentObject ].Pos(
					DisplayMesh[ CurrentObject ].Face[idx].Vertex.a ) ).Tangent();

			Vector2D Pcb = 
				( DisplayMesh[ CurrentObject ].Pos(
					DisplayMesh[ CurrentObject ].Face[idx].Vertex.c ) -
				DisplayMesh[ CurrentObject ].Pos(
					DisplayMesh[ CurrentObject ].Face[idx].Vertex.b ) ).Tangent();
					
			Vector2D Pac = 
				( DisplayMesh[ CurrentObject ].Pos(
					DisplayMesh[ CurrentObject ].Face[idx].Vertex.a ) -
				DisplayMesh[ CurrentObject ].Pos(
					DisplayMesh[ CurrentObject ].Face[idx].Vertex.c ) ).Tangent();

			Vector2D Am	=
					DisplayMesh[ CurrentObject ].Pos(
						DisplayMesh[ CurrentObject ].Face[idx].Vertex.a ) - 
					CurMousePos;
			Vector2D Bm	=
					DisplayMesh[ CurrentObject ].Pos(
						DisplayMesh[ CurrentObject ].Face[idx].Vertex.b ) - 
					CurMousePos;
			Vector2D Cm	=
					DisplayMesh[ CurrentObject ].Pos(
						DisplayMesh[ CurrentObject ].Face[idx].Vertex.c ) - 
					CurMousePos;
			
			Real InSideA = ( Pba * Am );
			Real InSideB = ( Pcb * Bm );
			Real InSideC = ( Pac * Cm );
			
			if( InSideA < 1 && InSideB < 1 && InSideC < 1 )
			{
				CurrentFace = idx;
				return idx;
			}
		}
	}*/
	return -1;
}
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
