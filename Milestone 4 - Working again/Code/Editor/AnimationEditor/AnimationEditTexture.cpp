#ifdef EDITOR
// - ------------------------------------------------------------------------------------------ - //
#include "AnimationEdit.h"

#include <Graphics/Gfx.h>
#include <Input/Input.h>

// - ------------------------------------------------------------------------------------------ - //
#include <Global.h>
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
void cAnimationEdit::DrawUV()
{
	Gfx::SetLineWidth( 1.0 );

	ABSet< Vector3D > LineVertex[ CurSelected.size() * 3 ];
	unsigned int LineIndicesSize = CurSelected.size() * 6;
	unsigned int LineIndices[ LineIndicesSize ];

	for( size_t idx = 0; idx < CurSelected.size(); ++idx )
	{
		Vector2D UVa = Vector2D( CurFrame->Face[ CurSelected[ idx ] ].UV.a.x * UVScale,
				UVScale - ( CurFrame->Face[ CurSelected[ idx ] ].UV.a.y * UVScale ) );
		Vector2D UVb = Vector2D( CurFrame->Face[ CurSelected[ idx ] ].UV.b.x * UVScale,
				UVScale - ( CurFrame->Face[ CurSelected[ idx ] ].UV.b.y * UVScale ) );
		Vector2D UVc = Vector2D( CurFrame->Face[ CurSelected[ idx ] ].UV.c.x * UVScale,
				UVScale - ( CurFrame->Face[ CurSelected[ idx ] ].UV.c.y * UVScale ) );
		
		// Draw circles representing selected faces UV coord's //
		Gfx::Circle( UVa, NodeRadius, Gfx::RGBA( 200, 0, 0, 255 ) );
		Gfx::Circle( UVb, NodeRadius, Gfx::RGBA( 0, 200, 0, 255 ) );
		Gfx::Circle( UVc, NodeRadius, Gfx::RGBA( 0, 0, 200, 255 ) );
		
		LineVertex[ idx ].a = UVa.ToVector3D();
		LineVertex[ idx ].b = UVb.ToVector3D();

		LineVertex[ idx + CurSelected.size() ].a = LineVertex[ idx ].b;
		LineVertex[ idx + CurSelected.size() ].b = UVc.ToVector3D();

		LineVertex[ idx + ( CurSelected.size() * 2 ) ].a = LineVertex[ idx ].a;
		LineVertex[ idx + ( CurSelected.size() * 2 ) ].b = LineVertex[ idx + CurSelected.size() ].b;

		LineIndices[ idx ] = idx;
	}

	for( size_t idx = CurSelected.size(); idx < LineIndicesSize; ++idx )
	{
		LineIndices[ idx ] = idx;
	}
	
	// Draw Lines representing selected faces UV coord's//
	Gfx::DrawLines( LineVertex, LineIndices, LineIndicesSize, Gfx::RGBA( 0, 200, 0, 255 ) );	
}
// - ------------------------------------------------------------------------------------------ - //
void cAnimationEdit::DrawSelectedUV()
{
	Gfx::SetLineWidth( 4.0 );
	
	// Draws the currently selected UV //
	for( size_t idx = 0; idx < CurSelUV.size(); ++idx )
	{
		int VertexNum = CurSelUV[idx] % 3;
		int i = ( CurSelUV[idx] / 3 );
				
		if( VertexNum == 0 )
		{
			Vector2D UVa = Vector2D( CurFrame->Face[ i ].UV.a.x * UVScale,
				UVScale - ( CurFrame->Face[ i ].UV.a.y * UVScale ) );

			Gfx::Circle( UVa, NodeRadius, Gfx::RGBA( 0, 255, 100, 255 ) );
			
		}
		else if( VertexNum == 1 )
		{
			Vector2D UVb = Vector2D( CurFrame->Face[ i ].UV.b.x * UVScale,
				UVScale - ( CurFrame->Face[ i ].UV.b.y * UVScale ) );

			Gfx::Circle( UVb, NodeRadius, Gfx::RGBA( 0, 255, 100, 255 ) );
		}
		else if( VertexNum == 2 )
		{
			Vector2D UVc = Vector2D( CurFrame->Face[ i ].UV.c.x * UVScale,
				UVScale - ( CurFrame->Face[ i ].UV.c.y * UVScale ) );

			Gfx::Circle( UVc, NodeRadius, Gfx::RGBA( 0, 255, 100, 255 ) );
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cAnimationEdit::SelectUV()
{
	if( Button[ MOUSE_1 ].Pressed() )
	{
		OldMousePos = CurMousePos;
	}
	
	if( Button[ MOUSE_1 ].Released() && !CurSelected.empty() )
	{
		Vector2D OldPos = OldMousePos;
		
		OldPos /= UVScale;
		
		OldPos.y = ( OldPos.y - Real(1.0) ) * Real(-1.0);
		
		Vector2D CurPos = CurMousePos;
		
		CurPos /= UVScale;
		
		CurPos.y = ( CurPos.y - Real(1.0) ) * Real(-1.0);

		// Group de-select //
		if( Button[ KEY_LCTRL ] || Button[ KEY_RCTRL ] )
		{
			for( size_t idx = 0; idx < CurSelected.size(); ++idx )
			{
				if( WithinBox( CurFrame->Face[ CurSelected[idx] ].UV.a, CurPos, OldPos ) )
				{	
					bool IsNewUV = true;
					for( size_t i = 0; i < CurSelUV.size(); ++i )
					{
						if( CurSelUV[i] == ( CurSelected[ idx ] * 3 ) )
						{
							IsNewUV = false;
						}
					}
					if( !IsNewUV )
					{
						std::vector <size_t> tempVec;
						
						for( size_t vec = 0; vec < CurSelUV.size(); ++vec )
						{
							if( CurSelUV[vec] != CurSelected[ idx ] * 3 )
							{
								tempVec.push_back( CurSelUV[vec] );
							}
						}
						CurSelUV.swap( tempVec );
					}	
				}
				if( WithinBox( CurFrame->Face[ CurSelected[idx] ].UV.b, CurPos, OldPos ) )
				{
					bool IsNewUV = true;
					for( size_t i = 0; i < CurSelUV.size(); ++i )
					{
						if( CurSelUV[i] == ( CurSelected[ idx ] * 3 ) + 1 )
						{
							IsNewUV = false;
						}
					}
					if( !IsNewUV )
					{
						std::vector <size_t> tempVec;
						
						for( size_t vec = 0; vec < CurSelUV.size(); ++vec )
						{
							if( CurSelUV[vec] != ( CurSelected[ idx ] * 3 ) + 1 )
							{
								tempVec.push_back( CurSelUV[vec] );
							}
						}
						CurSelUV.swap( tempVec );
					}	
				}
				if( WithinBox( CurFrame->Face[ CurSelected[idx] ].UV.c, CurPos, OldPos ) )
				{
					bool IsNewUV = true;
					for( size_t i = 0; i < CurSelUV.size(); ++i )
					{
						if( CurSelUV[i] == ( CurSelected[ idx ] * 3 ) + 2 )
						{
							IsNewUV = false;
						}
					}
					if( !IsNewUV )
					{
						std::vector <size_t> tempVec;
						
						for( size_t vec = 0; vec < CurSelUV.size(); ++vec )
						{
							if( CurSelUV[vec] != ( CurSelected[ idx ] * 3 ) + 2 )
							{
								tempVec.push_back( CurSelUV[vec] );
							}
						}
						CurSelUV.swap( tempVec );
					}	
				}
			}
			int TestUV = -1;
			TestUV = SingleSelectUV( CurPos );
			if( TestUV != -1 )
			{
				bool IsNewUV = true;
				for( size_t idx = 0; idx < CurSelUV.size(); ++idx )
				{
					if( int( CurSelUV[idx] ) == TestUV )
					{
						IsNewUV = false;
					}
				}
				if( !IsNewUV )
				{
					std::vector <size_t> tempVec;
					
					for( size_t vec = 0; vec < CurSelUV.size(); ++vec )
					{
						if( int(CurSelUV[vec]) != TestUV )
						{
							tempVec.push_back( CurSelUV[vec] );
						}
					}
					CurSelUV.swap( tempVec );
				}	
			}
		}
		else
		{	
			// Group add-select //	
			if( Button[ KEY_LSHIFT ] || Button[ KEY_RSHIFT ] )
			{
					
			}
			// Standard group select //
			else
			{
				CurSelUV.clear();
			}
			for( size_t idx = 0; idx < CurSelected.size(); ++idx )
			{
				if( WithinBox( CurFrame->Face[ CurSelected[idx] ].UV.a, CurPos, OldPos ) )
				{	
					bool IsNewUV = true;
					for( size_t i = 0; i < CurSelUV.size(); ++i )
					{
						if( CurSelUV[i] == ( CurSelected[ idx ] * 3 ) )
						{
							IsNewUV = false;
						}
					}
					if( IsNewUV )
					{
						CurSelUV.push_back( ( CurSelected[ idx ] * 3 ) );
					}
				}
				if( WithinBox( CurFrame->Face[ CurSelected[idx] ].UV.b, CurPos, OldPos ) )
				{
					bool IsNewUV = true;
					for( size_t i = 0; i < CurSelUV.size(); ++i )
					{
						if( CurSelUV[i] == ( CurSelected[ idx ] * 3 ) + 1 )
						{
							IsNewUV = false;
						}
					}
					if( IsNewUV )
					{
						CurSelUV.push_back( ( CurSelected[ idx ] * 3 ) + 1 );
					}
				}
				if( WithinBox( CurFrame->Face[ CurSelected[idx] ].UV.c, CurPos, OldPos ) )
				{
					bool IsNewUV = true;
					for( size_t i = 0; i < CurSelUV.size(); ++i )
					{
						if( CurSelUV[i] == ( CurSelected[ idx ] * 3 ) + 2 )
						{
							IsNewUV = false;
						}
					}
					if( IsNewUV )
					{
						CurSelUV.push_back( ( CurSelected[ idx ] * 3 ) + 2 );
					}	
				}
			}
			int TestUV = -1;
			
			TestUV = SingleSelectUV( CurPos );
			
			if( TestUV != -1 )
			{
				bool IsNewUV = true;
				for( size_t idx = 0; idx < CurSelUV.size(); ++idx )
				{
					if( int( CurSelUV[idx] ) == TestUV )
					{
						IsNewUV = false;
					}
				}
				if( IsNewUV )
				{
					CurSelUV.push_back( TestUV );
				}	
			}
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
int cAnimationEdit::SingleSelectUV( const Vector2D& CurPos )
{
	Real UVRadius = NodeRadius / ( UVScale );
	UVRadius *= UVRadius;
	for( size_t idx = 0; idx < CurSelected.size(); ++idx )
	{
		if( ( CurFrame->Face[ CurSelected[idx] ].UV.a - CurPos ).MagnitudeSquared() < UVRadius )
		{
			return CurSelected[ idx ] * 3;
		}
		if( ( CurFrame->Face[ CurSelected[idx] ].UV.b - CurPos ).MagnitudeSquared() < UVRadius )
		{
			return CurSelected[ idx ] * 3 + 1;
		}
		if( ( CurFrame->Face[ CurSelected[idx] ].UV.c - CurPos ).MagnitudeSquared() < UVRadius )
		{
			return CurSelected[ idx ] * 3 + 2;
		}
	}
	return -1;
}
// - ------------------------------------------------------------------------------------------ - //
void cAnimationEdit::MoveUV()
{
	if( Button[ MOUSE_1 ].Pressed() )
	{
		if( !Button[ KEY_LCTRL ] )
		{
			Vector2D CurPos = CurMousePos;
			CurPos /= UVScale;
			CurPos.y = ( CurPos.y - Real(1.0) ) * Real(-1.0);

			int temp = SingleSelectUV( CurPos );
//			CurPos *= UVScale;
			for( size_t idx = 0; idx < CurSelUV.size(); ++idx )
			{
				if( temp == int(CurSelUV[idx]) )
				{
					isGroupMove = true;
				}
			}
		}
		// Snaps to grid
		if( !Button[ KEY_LSHIFT ] && isGroupMove )
		{
			SnapToGrid = true;
		}
		else
		{
			SnapToGrid = false;
		}
	}
	if( Button[ MOUSE_1 ].Released() )
	{
		isGroupMove = false;
		
		if( SnapToGrid )
		{
			for( size_t idx = 0; idx < CurSelUV.size(); ++idx )
			{
				int VertexNum = CurSelUV[idx] % 3;
				int i = ( CurSelUV[idx] / 3 );
				
				if( VertexNum == 0 )
				{
					CurFrame->Face[ i ].UV.a.x *= UVScale;
					CurFrame->Face[ i ].UV.a.y *= UVScale;
					
					CalcSnapToGrid( CurFrame->Face[ i ].UV.a, CurrentGridDepth, GridDepth );
					
					//CalcSnapToGrid( CurFrame->Face[ i ].UV.a, CurUVGridDepth, UVGridDepth );
					
					CurFrame->Face[ i ].UV.a.x /= UVScale;
					CurFrame->Face[ i ].UV.a.y /= UVScale;
				}
				else if( VertexNum == 1 )
				{
					CurFrame->Face[ i ].UV.b.x *= UVScale;
					CurFrame->Face[ i ].UV.b.y *= UVScale;
					
					CalcSnapToGrid( CurFrame->Face[ i ].UV.b, CurrentGridDepth, GridDepth );
					//CalcSnapToGrid( CurFrame->Face[ i ].UV.b, CurUVGridDepth, UVGridDepth );
					
					CurFrame->Face[ i ].UV.b.x /= UVScale;
					CurFrame->Face[ i ].UV.b.y /= UVScale;
				}
				else if( VertexNum == 2 )
				{
					CurFrame->Face[ i ].UV.c.x *= UVScale;
					CurFrame->Face[ i ].UV.c.y *= UVScale;
					
					CalcSnapToGrid( CurFrame->Face[ i ].UV.c, CurrentGridDepth, GridDepth );
					
					//CalcSnapToGrid( CurFrame->Face[ i ].UV.c, CurUVGridDepth, UVGridDepth );
					
					CurFrame->Face[ i ].UV.c.x /= UVScale;
					CurFrame->Face[ i ].UV.c.y /= UVScale;
				}
			}
			SnapToGrid = false;
			ActiveAction();
		}
		else
		{
			//ActiveAction();
		}
	}
	if( isGroupMove )
	{
		for( size_t idx = 0; idx < CurSelUV.size(); ++idx )
		{
			int VertexNum = CurSelUV[idx] % 3;
			int i = ( CurSelUV[idx] / 3 );
				
			if( VertexNum == 0 )
			{
				CurFrame->Face[ i ].UV.a.x -=
				( Mouse.Diff().x * ( Real( Global::HudW ) * ( UVWidth ) ) ) *
				Real( UVCamera->Pos.z / UVZoomOffsetX ) / ( UVScale );
				
				CurFrame->Face[ i ].UV.a.y +=
				( -Mouse.Diff().y * Real( Global::HudH ) * ( UVHeight ) ) *
				Real( -UVCamera->Pos.z / UVZoomOffsetY ) / ( UVScale ) * Real(-1.0);
			}
			else if( VertexNum == 1 )
			{
				CurFrame->Face[ i ].UV.b.x -=
				( Mouse.Diff().x * ( Real( Global::HudW ) * ( UVWidth ) ) ) *
				Real( UVCamera->Pos.z / UVZoomOffsetX ) / ( UVScale );
				
				CurFrame->Face[ i ].UV.b.y +=
				( -Mouse.Diff().y * Real( Global::HudH ) * ( UVHeight ) ) *
				Real( -UVCamera->Pos.z / UVZoomOffsetY ) / ( UVScale ) * Real(-1.0);

			}
			else if( VertexNum == 2 )
			{
				CurFrame->Face[ i ].UV.c.x -=
				( Mouse.Diff().x * ( Real( Global::HudW ) * ( UVWidth ) ) ) *
				Real( UVCamera->Pos.z / UVZoomOffsetX ) / ( UVScale );
				
				CurFrame->Face[ i ].UV.c.y +=
				( -Mouse.Diff().y * Real( Global::HudH ) * ( UVHeight ) ) *
				Real( -UVCamera->Pos.z / UVZoomOffsetY ) / ( UVScale ) * Real(-1.0);
			}
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cAnimationEdit::RotateUV()
{
	if( Button[ KEY_T ].Pressed() )
	{
		for( size_t idx = 0; idx < CurSelected.size(); ++idx )
		{
			CurFrame->Face[CurSelected[idx]].UV.a.x =
			( CurFrame->Face[CurSelected[idx]].UV.a.x - Real(1.0) )
			* Real(-1.0);
			CurFrame->Face[CurSelected[idx]].UV.a.y = 
			( CurFrame->Face[CurSelected[idx]].UV.a.y - Real(1.0) )
			* Real(-1.0);
			
			CurFrame->Face[CurSelected[idx]].UV.b.x =
			( CurFrame->Face[CurSelected[idx]].UV.b.x - Real(1.0) )
			* Real(-1.0);
			CurFrame->Face[CurSelected[idx]].UV.b.y = 
			( CurFrame->Face[CurSelected[idx]].UV.b.y - Real(1.0) )
			* Real(-1.0);

			CurFrame->Face[CurSelected[idx]].UV.c.x =
			( CurFrame->Face[CurSelected[idx]].UV.c.x - Real(1.0) )
			* Real(-1.0);
			CurFrame->Face[CurSelected[idx]].UV.c.y = 
			( CurFrame->Face[CurSelected[idx]].UV.c.y - Real(1.0) )
			* Real(-1.0);

		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cAnimationEdit::RotateUVRGB()
{
	if( Button[ KEY_R ].Pressed() )
	{
		for( size_t idx = 0; idx < CurSelected.size(); ++idx )
		{
			Vector2D temp = CurFrame->Face[CurSelected[idx]].UV.a;

			CurFrame->Face[CurSelected[idx]].UV.a = 
			CurFrame->Face[CurSelected[idx]].UV.c;

			CurFrame->Face[CurSelected[idx]].UV.c = 
			CurFrame->Face[CurSelected[idx]].UV.b;

			CurFrame->Face[CurSelected[idx]].UV.b = temp;
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cAnimationEdit::InvertUV()
{
	if( Button[ KEY_I ].Pressed() )
	{
		for( size_t idx = 0; idx < CurSelected.size(); ++idx )
		{
			Vector2D temp = CurFrame->Face[CurSelected[idx]].UV.a;

			CurFrame->Face[CurSelected[idx]].UV.a = 
			CurFrame->Face[CurSelected[idx]].UV.b;

			CurFrame->Face[CurSelected[idx]].UV.b = temp;
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cAnimationEdit::SwitchTexture()
{
	if( Button[ KEY_N ].Pressed() )
	{
		int temp = FindTexture( CurFrame->TextureId );
		temp--;
		if( temp >= 0 )
		{
			CurFrame->TextureId = TextureID[ temp ];
			CurTexIdx = temp;
		}
		else
		{
			CurFrame->TextureId = TextureID[ TextureID.size() - 1 ];
			CurTexIdx = TextureID.size() - 1;
		}
	}
	else if( Button[ KEY_M ].Pressed() )
	{
		int temp = FindTexture( CurFrame->TextureId );
		temp++;
		if( temp < int( TextureID.size() ) )
		{
			CurFrame->TextureId = TextureID[ temp ];
			CurTexIdx = temp;
		}
		else
		{
			CurFrame->TextureId = TextureID[ 0 ];
			CurTexIdx = 0;
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
