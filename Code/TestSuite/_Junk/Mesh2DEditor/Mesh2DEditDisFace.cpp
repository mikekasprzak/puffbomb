#ifdef EDITOR
// - ------------------------------------------------------------------------------------------ - //
#include "Mesh2DEdit.h"
#include "Input/Input.h"
#include <Geometry/Set.h>
// - ------------------------------------------------------------------------------------------ - //
#include <SDL/SDL.h>

using namespace Input;
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::DrawDisSelectFace()
{
	if( Button[ MOUSE_1 ] )
	{
		Vector2D CurMousePos = CalcMousePos();
		gfx::Rect( OldMousePos, CurMousePos, gfx::RGB( 255, 255, 255 ) );
		if( !Button[ KEY_LCTRL ] || !Button[ KEY_RCTRL ] )
		{
			for( size_t idx = 0; idx < DisplayMesh[ CurrentObject ].size(); ++idx )
			{
				if( WithinBox( DisplayMesh[ CurrentObject ].Pos( idx ), CurMousePos,
					 OldMousePos ) )
				{
					for( size_t i = 0; i < DisplayMesh[ CurrentObject ].Face.size(); ++i )
					{
						if( DisFaceInBox( i, idx ) &&
							DisplayMesh[ CurrentObject ].Face[ i ].Layer == CurLayer )
						{
							gfx::Line( 
								DisplayMesh[ CurrentObject ].Pos(
									DisplayMesh[ CurrentObject ].Face[ i ].Vertex.a ),
								DisplayMesh[ CurrentObject ].Pos(
									DisplayMesh[ CurrentObject ].Face[ i ].Vertex.b ),
								gfx::RGB( 0, 150, 50 )
							);
							gfx::Line( 
								DisplayMesh[ CurrentObject ].Pos(
									DisplayMesh[ CurrentObject ].Face[ i ].Vertex.b ),
								DisplayMesh[ CurrentObject ].Pos(
									DisplayMesh[ CurrentObject ].Face[ i ].Vertex.c ),
								gfx::RGB( 0, 150, 50 )
							);
							gfx::Line( 
								DisplayMesh[ CurrentObject ].Pos(
									DisplayMesh[ CurrentObject ].Face[ i ].Vertex.c ),
								DisplayMesh[ CurrentObject ].Pos(
									DisplayMesh[ CurrentObject ].Face[ i ].Vertex.a ),
								gfx::RGB( 0, 150, 50 )
							);
						} 
					}
				}
			}
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::DisAddFace()
{
	if( Button[ KEY_0_PAD ].Pressed() || Button[ KEY_A ].Pressed() )
	{
		if( CurSelected.size() == 3 )
		{
			cDisplayMesh::cFace tempFace;
			
			DisClockwise( tempFace );
						
			tempFace.UV.a = Vector2D( 0.0, 0.0 );
			tempFace.UV.b = Vector2D( 0.0, 1.0 );
			tempFace.UV.c = Vector2D( 1.0, 1.0 );
			
			DisplayMesh[ CurrentObject ].Face.push_back( tempFace );
			CurrentFace = DisplayMesh[ CurrentObject ].Face.size() - 1;
			
			DisplayMesh[ CurrentObject ].Face[ CurrentFace ].Layer = CurLayer;
		}
		if( CurSelected.size() == 4 )
		{
			int DeselectIdx = 0;
			int SelectIdx = 0;
			Real DeselectDistance = 0.0;
			Real TestDistance = 0.0;

			for( size_t idx = 0; idx < CurSelected.size(); ++idx )
			{
				for( size_t i = 0; i < CurSelected.size(); ++i )
				{
					TestDistance = ( DisplayMesh[ CurrentObject ].Pos( CurSelected[idx] )
						- DisplayMesh[ CurrentObject ].Pos( CurSelected[i] ) ).Magnitude();
				
					if( TestDistance > DeselectDistance )
					{
						DeselectDistance = TestDistance;
						DeselectIdx = CurSelected[idx];
						SelectIdx = CurSelected[i];
					}
				}
			}
			
			std::vector <size_t> tempVec;
			for( size_t vec = 0; vec < CurSelected.size(); ++vec )
			{
				if( int( CurSelected[vec] ) != DeselectIdx )
				{
					tempVec.push_back( CurSelected[vec] );
				}
			}
			CurSelected.swap( tempVec );
			
			cDisplayMesh::cFace tempFace;
			
			DisClockwise( tempFace );

			if( DisplayMesh[ CurrentObject ].Pos( tempFace.Vertex.a ).y < 
				DisplayMesh[ CurrentObject ].Pos( tempFace.Vertex.b ).y &&
				DisplayMesh[ CurrentObject ].Pos( tempFace.Vertex.a ).y < 
				DisplayMesh[ CurrentObject ].Pos( tempFace.Vertex.c ).y )
			{
				if( tempFace.Vertex.a == SelectIdx )
				{
					SelectIdx = tempFace.Vertex.c;
				}
			}
			else
			{
				if( tempFace.Vertex.a == SelectIdx )
				{
					SelectIdx = tempFace.Vertex.b;
				}
			}

			tempFace.UV.a = Vector2D( 0.0, 0.0 );
			tempFace.UV.b = Vector2D( 1.0, 1.0 );
			tempFace.UV.c = Vector2D( 1.0, 0.0 );
			
			DisplayMesh[ CurrentObject ].Face.push_back( tempFace );
			CurrentFace = DisplayMesh[ CurrentObject ].Face.size() - 1;
			
			DisplayMesh[ CurrentObject ].Face[ CurrentFace ].Layer = CurLayer;

			CurSelected.swap( tempVec );
			
			tempVec.clear();
			for( size_t vec = 0; vec < CurSelected.size(); ++vec )
			{
				if( int( CurSelected[vec] ) != SelectIdx )
				{
					tempVec.push_back( CurSelected[vec] );
				}
			}

			CurSelected.swap( tempVec );	
			
			DisClockwise( tempFace );
						
			tempFace.UV.a = Vector2D( 0.0, 0.0 );
			tempFace.UV.b = Vector2D( 0.0, 1.0 );
			tempFace.UV.c = Vector2D( 1.0, 1.0 );
			
			DisplayMesh[ CurrentObject ].Face.push_back( tempFace );
			CurrentFace = DisplayMesh[ CurrentObject ].Face.size() - 1;
			
			DisplayMesh[ CurrentObject ].Face[ CurrentFace ].Layer = CurLayer;
			
			CurSelected.swap( tempVec );
		}
		ActiveAction();
		LayerCheck();
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::DisDeleteFace()
{
	if( Button[ KEY_DELETE ].Pressed() || isDelete )
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
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::DisClockwise( cDisplayMesh::cFace &tempFace )
{
	Vector2D Ba = DisplayMesh[ CurrentObject ].Pos( CurSelected[1] )
		- DisplayMesh[ CurrentObject ].Pos( CurSelected[0] );
	Vector2D Pcb = ( DisplayMesh[ CurrentObject ].Pos( CurSelected[2] )
		- DisplayMesh[ CurrentObject ].Pos( CurSelected[1] ) ).Tangent();
		
	if( Ba * Pcb >= Real( 0 ) )
	{
		tempFace.Vertex.a = CurSelected[0];
		tempFace.Vertex.b = CurSelected[2];
		tempFace.Vertex.c = CurSelected[1];
	}
	else
	{
		tempFace.Vertex.a = CurSelected[0];
		tempFace.Vertex.b = CurSelected[1];
		tempFace.Vertex.c = CurSelected[2];
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::SwitchFace()
{	
	if ( Button[ KEY_UP ].Pressed() )
	{
		if( CurrentFace > 0 )
		{
			--CurrentFace;
		}
		else
		{
			CurrentFace = DisplayMesh[ CurrentObject ].Face.size() - 1;
		}
	}
	else if ( Button[ KEY_DOWN ].Pressed() )
	{
		if( CurrentFace < DisplayMesh[ CurrentObject ].Face.size() - 1 )
		{
			++CurrentFace;	
		}
		else
		{
			CurrentFace = 0;	
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::DisSelectFace()
{
	if( Button[ MOUSE_1 ].Pressed() )
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
	}
}
// - ------------------------------------------------------------------------------------------ - //
bool cMesh2DEdit::DisFaceInBox( int i, int idx )
{
	if( DisplayMesh[ CurrentObject ].Face[i].Vertex.a == int( idx ) )
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
	return false;
}
// - ------------------------------------------------------------------------------------------ - //
int cMesh2DEdit::DisSingleSelectFace( Vector2D &CurMousePos )
{
	if( DisplayMesh[ CurrentObject ].Face.size() > 0 )
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
	}
	return -1;
}
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
