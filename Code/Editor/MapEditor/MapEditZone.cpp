#ifdef EDITOR
// - ------------------------------------------------------------------------------------------ - //
#include "MapEdit.h"
#include <Graphics/Gfx.h>
#include <Input/Input.h>

// !!!! OPENGL !!!! //
#include <gl/gl.h>
#include <gl/glu.h>
// !!!! OPENGL !!!! //

// - ------------------------------------------------------------------------------------------ - //
using namespace Input;
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::DrawZones()
{
	glEnable(GL_BLEND);
	
	// Draws all non selected zones //
/*	for( size_t idx = 0; idx < Game->Zone.size(); ++idx )
	{
		if( idx != CurZone )
		{
			if( Game->Zone[ idx ].Id != Game->Zone[ CurZone ].Id )
			{
				gfx::Rect(
						Game->Zone[ idx ].BoundingRect.P1(),
						Game->Zone[ idx ].BoundingRect.P2(),
						gfx::RGBA( 255, 255, 255, 128 )
				);

				gfx::Rect(
						Game->Zone[ idx ].BoundingRect.P1() + Vector2D( CornerSize, CornerSize ),
						Game->Zone[ idx ].BoundingRect.P2() - Vector2D( CornerSize, CornerSize ),
						gfx::RGBA( 255, 255, 255, 96 )
				);
			}
			else
			{
				gfx::Rect(
						Game->Zone[ idx ].BoundingRect.P1(),
						Game->Zone[ idx ].BoundingRect.P2(),
						gfx::RGBA( 0, 128, 255, 128 )
				);
				gfx::Rect(
						Game->Zone[ idx ].BoundingRect.P1() + Vector2D( CornerSize, CornerSize ),
						Game->Zone[ idx ].BoundingRect.P2() - Vector2D( CornerSize, CornerSize ),
						gfx::RGBA( 0, 128, 255, 96 )
				);
			}
		}
	}
	
	// Draws the select zone //
	DrawSelZone();
	
	glDisable(GL_BLEND); */ // Removed because of game dependency //
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::DrawSelZone()
{
/*	gfx::FilledRect(
		Game->Zone[ CurZone ].BoundingRect.P1(),
		Game->Zone[ CurZone ].BoundingRect.P2(),
		gfx::RGBA( 0, 0, 255, 32 )
	);
	
	gfx::Rect(
		Game->Zone[ CurZone ].BoundingRect.P1(),
		Game->Zone[ CurZone ].BoundingRect.P2(),
		gfx::RGBA( 0, 0, 255, 128 )
	);
	
	gfx::Rect(
		Game->Zone[ CurZone ].BoundingRect.P1() + Vector2D( CornerSize, CornerSize ),
		Game->Zone[ CurZone ].BoundingRect.P2() - Vector2D( CornerSize, CornerSize ),
		gfx::RGBA( 0, 0, 255, 96 )
	);

	// Corners //
	int CornerColor = gfx::RGBA( 0, 0, 0, 128 );
	
	Vector2D Pos1 = Game->Zone[ CurZone ].BoundingRect.P1();
	Vector2D Pos2 = Game->Zone[ CurZone ].BoundingRect.P2();
	
	gfx::FilledRect(
		Pos1,
		Pos1 + Vector2D( CornerSize, CornerSize ),
		CornerColor
	);

	gfx::FilledRect(
		Pos2 - Vector2D( CornerSize, CornerSize ),
		Pos2,
		CornerColor
	);

	gfx::FilledRect(
		Vector2D(
			Pos1.x,
			Pos2.y
		) - Vector2D( 0, CornerSize ),
		Vector2D(
			Pos1.x,
			Pos2.y
		) + Vector2D( CornerSize, 0 ),
		CornerColor
	);

	gfx::FilledRect(
		Vector2D(
			Pos2.x,
			Pos1.y
		) - Vector2D( CornerSize, 0 ),
		Vector2D(
			Pos2.x,
			Pos1.y
		) + Vector2D( 0, CornerSize ),
		CornerColor
	);

	// Center //
	gfx::FilledRect(
		Vector2D(
			Pos1 -
			( Pos1 - Pos2 ) / 2
		) - Vector2D( CornerSize, CornerSize ),
		Vector2D(
			Pos1 -
			( Pos1 - Pos2 ) / 2
		) + Vector2D( CornerSize, CornerSize ),
		CornerColor
	);
*/ // Removed because of game dependency //
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::SwitchZone()
{
/*	if ( Button[ KEY_LEFT ].Pressed() )
	{
		if( CurZone > 0 )
		{
			--CurZone;
		}
		else
		{
			CurZone = Game->Zone.size() - 1;
		}
	}
	else if ( Button[ KEY_RIGHT ].Pressed() )
	{
		if( CurZone < Game->Zone.size() - 1 )
		{
			++CurZone;
		}
		else
		{
			CurZone = 0;
		}
	}	*/ // Removed because of game dependency //
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::SelectZone()
{
/*	if( Button[ MOUSE_1 ].Pressed() )
	{
		OldMousePos = CalcMousePos();
		
		for( size_t idx = 0; idx < Game->Zone.size(); ++idx )
		{
			RadiusRect2D TempRect =
				RadiusRect2D::Pair(
					Game->Zone[ idx ].BoundingRect.P1() + CornerSize,
					Game->Zone[ idx ].BoundingRect.P2() - CornerSize
				);
			
			if( Game->Zone[ idx ].BoundingRect == OldMousePos &&
				TempRect != OldMousePos )
			{
				CurZone	= idx;
			}
		}
	} */ // Removed because of game dependency //
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::MoveZone()
{
/*	if( Button[ MOUSE_1 ] )
	{		
		RadiusRect2D TempRect =
			RadiusRect2D::Pair(
				Game->Zone[ CurZone ].BoundingRect.P1() + CornerSize,
				Game->Zone[ CurZone ].BoundingRect.P2() - CornerSize
			);

		if( Game->Zone[ CurZone ].BoundingRect == OldMousePos &&
			TempRect != OldMousePos  )
		{
			isGroupMove = true;
		}
		
		TempRect = RadiusRect2D::Pair(
			Vector2D(
				Game->Zone[ CurZone ].BoundingRect.P1() -
				( Game->Zone[ CurZone ].BoundingRect.P1() - 
					Game->Zone[ CurZone ].BoundingRect.P2() ) / 2
			) - Vector2D( CornerSize, CornerSize ),
			Vector2D(
				Game->Zone[ CurZone ].BoundingRect.P1() -
				( Game->Zone[ CurZone ].BoundingRect.P1() - 
					Game->Zone[ CurZone ].BoundingRect.P2() ) / 2
			) + Vector2D( CornerSize, CornerSize )
		);
		if( TempRect == OldMousePos )
		{
			isGroupMove = true;
		}
	
		if( isGroupMove )
		{
			Game->Zone[ CurZone ].BoundingRect =
				RadiusRect2D::Pair(
					Vector2D(
						Game->Zone[ CurZone ].BoundingRect.P1().x - 
							( ( Mouse.Diff().x * Real( Global::HudW ) ) *
							Real( Camera->Pos.z / Global::HudZoom ) ),
						Game->Zone[ CurZone ].BoundingRect.P1().y +	
							( ( Mouse.Diff().y * Real( Global::HudH ) ) *
							Real( Camera->Pos.z / Global::HudZoom ) )
					),
					Vector2D(
						Game->Zone[ CurZone ].BoundingRect.P2().x - 
							( ( Mouse.Diff().x * Real( Global::HudW ) ) *
							Real( Camera->Pos.z / Global::HudZoom ) ),
						Game->Zone[ CurZone ].BoundingRect.P2().y +	
							( ( Mouse.Diff().y * Real( Global::HudH ) ) *
							Real( Camera->Pos.z / Global::HudZoom ) )
					)
				);
		}
	}
	if( Button[ MOUSE_1 ].Released() )
	{
		isGroupMove = false;
		isSaved = false;
	} */ // Removed because of game dependency //
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::ResizeZone()
{
/*	if( Button[ MOUSE_1 ].Pressed() )
	{
		OldMousePos = CalcMousePos();
	}
	if( Button[ MOUSE_1 ] )
	{
		RadiusRect2D TempRect = RadiusRect2D::Pair(
			Game->Zone[ CurZone ].BoundingRect.P1(),
			Game->Zone[ CurZone ].BoundingRect.P1() + Vector2D( CornerSize, CornerSize )
		);
		
		if( TempRect == OldMousePos )
		{
			ResizeCorner = 1;
		}

		TempRect = RadiusRect2D::Pair(
			Game->Zone[ CurZone ].BoundingRect.P2() - Vector2D( CornerSize, CornerSize ),
			Game->Zone[ CurZone ].BoundingRect.P2()
		);
		
		if( TempRect == OldMousePos )
		{
			ResizeCorner = 2;
		}

		TempRect = RadiusRect2D::Pair(
			Vector2D(
				Game->Zone[ CurZone ].BoundingRect.P1().x,
				Game->Zone[ CurZone ].BoundingRect.P2().y
			) - Vector2D( 0, CornerSize ),
			Vector2D(
				Game->Zone[ CurZone ].BoundingRect.P1().x,
				Game->Zone[ CurZone ].BoundingRect.P2().y
			) + Vector2D( CornerSize, 0 )
		);
		
		if( TempRect == OldMousePos )
		{
			ResizeCorner = 3;
		}
		
		TempRect = RadiusRect2D::Pair(
			Vector2D(
				Game->Zone[ CurZone ].BoundingRect.P2().x,
				Game->Zone[ CurZone ].BoundingRect.P1().y
			) - Vector2D( CornerSize, 0 ),
			Vector2D(
				Game->Zone[ CurZone ].BoundingRect.P2().x,
				Game->Zone[ CurZone ].BoundingRect.P1().y
			) + Vector2D( 0, CornerSize )
		);
		
		if( TempRect == OldMousePos )
		{
			ResizeCorner = 4;
		}
	// - -------------------------------------------------------------------------------------- - //
		if( ResizeCorner != 0 )
		{
			if( ResizeCorner == 1 )
			{
				Game->Zone[ CurZone ].BoundingRect = RadiusRect2D::Pair(
					Vector2D(
						Game->Zone[ CurZone ].BoundingRect.P1().x - 
							( ( Mouse.Diff().x * Real( Global::HudW ) ) *
							Real( Camera->Pos.z / Global::HudZoom ) ),
						Game->Zone[ CurZone ].BoundingRect.P1().y +	
							( ( Mouse.Diff().y * Real( Global::HudH ) ) *
							Real( Camera->Pos.z / Global::HudZoom ) )
					),
					Game->Zone[ CurZone ].BoundingRect.P2()
				);
			}
			if( ResizeCorner == 2 )
			{
				Game->Zone[ CurZone ].BoundingRect = RadiusRect2D::Pair(
					Game->Zone[ CurZone ].BoundingRect.P1(),
					Vector2D(
						Game->Zone[ CurZone ].BoundingRect.P2().x - 
							( ( Mouse.Diff().x * Real( Global::HudW ) ) *
							Real( Camera->Pos.z / Global::HudZoom ) ),
						Game->Zone[ CurZone ].BoundingRect.P2().y +	
							( ( Mouse.Diff().y * Real( Global::HudH ) ) *
							Real( Camera->Pos.z / Global::HudZoom ) )
					)
				);
			}
			if( ResizeCorner == 3 )
			{
				Game->Zone[ CurZone ].BoundingRect = RadiusRect2D::Pair(
					Vector2D(
						Game->Zone[ CurZone ].BoundingRect.P1().x - 
							( ( Mouse.Diff().x * Real( Global::HudW ) ) *
							Real( Camera->Pos.z / Global::HudZoom ) ),
						Game->Zone[ CurZone ].BoundingRect.P1().y
					),
					Vector2D(
						Game->Zone[ CurZone ].BoundingRect.P2().x,
						Game->Zone[ CurZone ].BoundingRect.P2().y +	
							( ( Mouse.Diff().y * Real( Global::HudH ) ) *
							Real( Camera->Pos.z / Global::HudZoom ) )
					)
				);
			}
			if( ResizeCorner == 4 )
			{
				Game->Zone[ CurZone ].BoundingRect = RadiusRect2D::Pair(
					Vector2D(
						Game->Zone[ CurZone ].BoundingRect.P1().x,
						Game->Zone[ CurZone ].BoundingRect.P1().y +
							( ( Mouse.Diff().y * Real( Global::HudH ) ) *
							Real( Camera->Pos.z / Global::HudZoom ) )
					),
					Vector2D(
						Game->Zone[ CurZone ].BoundingRect.P2().x - 
							( ( Mouse.Diff().x * Real( Global::HudW ) ) *
							Real( Camera->Pos.z / Global::HudZoom ) ),
						Game->Zone[ CurZone ].BoundingRect.P2().y
					)
				);
			}
			isSaved = false;
		}
	}
	else
	{
		ResizeCorner = 0;
	}
	*/ // Removed because of game dependency //
	
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::AddZone()
{
/*	if( Button[ KEY_0_PAD ].Pressed() || Button[ KEY_A ].Pressed() )
	{
		Real CreationSize = CornerSize * Real( 2 );
		Vector2D CurMousePos = CalcMousePos();
		Game->Zone.push_back( 
			cZone( 
				CurMousePos - Vector2D( CreationSize, CreationSize ),
				CurMousePos + Vector2D( CreationSize, CreationSize )
				)
			);
			
		CurZone = Game->Zone.size() - 1;
		
		isSaved = false;
	}*/ // Removed because of game dependency //
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::DeleteZone()
{
/*	if( !Game->Zone.empty() )
	{
		if( Button[ KEY_DELETE ].Pressed() )
		{
			std::vector< cZone > tempVec;
				
			for( size_t idx = 0; idx < Game->Zone.size(); ++idx )
			{
				if( CurZone != idx )
				{
					tempVec.push_back( Game->Zone[ idx ] );
				}
			}
			Game->Zone.swap( tempVec );
			
			CurZone = Game->Zone.size() - 1;
			
			isSaved = false;
		}
	} */ // Removed because of game dependency //
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::ChangeID()
{
/*	if( Button[ KEY_Q ].Pressed() )
	{
		if( Game->Zone[ CurZone ].Id > 0 )
		{
			Game->Zone[ CurZone ].Id--;
			
			isSaved = false;
		}
	}
	if( Button[ KEY_W ].Pressed() )
	{
		if( Game->Zone[ CurZone ].Id < 63 )
		{
			Game->Zone[ CurZone ].Id++;
			
			isSaved = false;
		}
	}
	*/ // Removed because of game dependency //
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::ChangeArg()
{
/*	if( Button[ KEY_Z ].Pressed() )
	{
		if( Game->Zone[ CurZone ].Argument > 0 )
		{
			Game->Zone[ CurZone ].Argument--;
			
			isSaved = false;
		}
	}
	if( Button[ KEY_X ].Pressed() )
	{
		Game->Zone[ CurZone ].Argument++;
		
		isSaved = false;
	} */ // Removed because of game dependency //
}
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
