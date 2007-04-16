#ifdef EDITOR
// - ------------------------------------------------------------------------------------------ - //
#include "MapEdit.h"
#include <Graphics/Gfx.h>
#include <Input/Input.h>
// - ------------------------------------------------------------------------------------------ - //
using namespace Input;
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::DrawZones()
{
	// Draws all non selected zones //
	for( size_t idx = 0; idx < Zone.size(); ++idx )
	{
		if( idx != CurZone )
		{
			if( Zone[ idx ].Id != Zone[ CurZone ].Id )
			{
				Gfx::Rect(
						Zone[ idx ].BoundingRect.P1(),
						Zone[ idx ].BoundingRect.P2(),
						Gfx::RGBA( 255, 255, 255, 128 )
				);

				Gfx::Rect(
						Zone[ idx ].BoundingRect.P1() + Vector2D( CornerSize, CornerSize ),
						Zone[ idx ].BoundingRect.P2() - Vector2D( CornerSize, CornerSize ),
						Gfx::RGBA( 255, 255, 255, 96 )
				);
			}
			else
			{
				Gfx::Rect(
						Zone[ idx ].BoundingRect.P1(),
						Zone[ idx ].BoundingRect.P2(),
						Gfx::RGBA( 0, 128, 255, 128 )
				);
				Gfx::Rect(
						Zone[ idx ].BoundingRect.P1() + Vector2D( CornerSize, CornerSize ),
						Zone[ idx ].BoundingRect.P2() - Vector2D( CornerSize, CornerSize ),
						Gfx::RGBA( 0, 128, 255, 96 )
				);
			}
		}
	}
	
	if( !Zone.empty() )
	{
		// Draws the select zone //
		DrawSelZone();
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::DrawSelZone()
{
	Gfx::FilledRect(
		Zone[ CurZone ].BoundingRect.P1(),
		Zone[ CurZone ].BoundingRect.P2(),
		Gfx::RGBA( 0, 0, 255, 32 )
	);
	
	Gfx::Rect(
		Zone[ CurZone ].BoundingRect.P1(),
		Zone[ CurZone ].BoundingRect.P2(),
		Gfx::RGBA( 0, 0, 255, 128 )
	);
	
	Gfx::Rect(
		Zone[ CurZone ].BoundingRect.P1() + Vector2D( CornerSize, CornerSize ),
		Zone[ CurZone ].BoundingRect.P2() - Vector2D( CornerSize, CornerSize ),
		Gfx::RGBA( 0, 0, 255, 96 )
	);

	// Corners //
	int CornerColor = Gfx::RGBA( 0, 0, 0, 128 );
	
	Vector2D Pos1 = Zone[ CurZone ].BoundingRect.P1();
	Vector2D Pos2 = Zone[ CurZone ].BoundingRect.P2();
	
	Gfx::FilledRect(
		Pos1,
		Pos1 + Vector2D( CornerSize, CornerSize ),
		CornerColor
	);

	Gfx::FilledRect(
		Pos2 - Vector2D( CornerSize, CornerSize ),
		Pos2,
		CornerColor
	);

	Gfx::FilledRect(
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

	Gfx::FilledRect(
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
	Gfx::FilledRect(
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
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::SwitchZone()
{
	if ( Button[ KEY_LEFT ].Pressed() )
	{
		if( CurZone > 0 )
		{
			--CurZone;
		}
		else
		{
			CurZone = Zone.size() - 1;
		}
	}
	else if ( Button[ KEY_RIGHT ].Pressed() )
	{
		if( CurZone < Zone.size() - 1 )
		{
			++CurZone;
		}
		else
		{
			CurZone = 0;
		}
	}	
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::SelectZone()
{
	if( Button[ MOUSE_1 ].Pressed() )
	{
		OldMousePos = CalcMousePos();
		
		for( size_t idx = 0; idx < Zone.size(); ++idx )
		{
			RadiusRect2D TempRect =
				RadiusRect2D::Pair(
					Zone[ idx ].BoundingRect.P1() + CornerSize,
					Zone[ idx ].BoundingRect.P2() - CornerSize
				);
			
			if( Zone[ idx ].BoundingRect == OldMousePos &&
				TempRect != OldMousePos )
			{
				CurZone	= idx;
			}
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::MoveZone()
{
	if( Button[ MOUSE_1 ] )
	{		
		RadiusRect2D TempRect =
			RadiusRect2D::Pair(
				Zone[ CurZone ].BoundingRect.P1() + CornerSize,
				Zone[ CurZone ].BoundingRect.P2() - CornerSize
			);

		if( Zone[ CurZone ].BoundingRect == OldMousePos &&
			TempRect != OldMousePos  )
		{
			isGroupMove = true;
		}
		
		TempRect = RadiusRect2D::Pair(
			Vector2D(
				Zone[ CurZone ].BoundingRect.P1() -
				( Zone[ CurZone ].BoundingRect.P1() - 
					Zone[ CurZone ].BoundingRect.P2() ) / 2
			) - Vector2D( CornerSize, CornerSize ),
			Vector2D(
				Zone[ CurZone ].BoundingRect.P1() -
				( Zone[ CurZone ].BoundingRect.P1() - 
					Zone[ CurZone ].BoundingRect.P2() ) / 2
			) + Vector2D( CornerSize, CornerSize )
		);
		if( TempRect == OldMousePos )
		{
			isGroupMove = true;
		}
	
		if( isGroupMove )
		{
			Zone[ CurZone ].BoundingRect =
				RadiusRect2D::Pair(
					Vector2D(
						Zone[ CurZone ].BoundingRect.P1().x - 
							( ( Mouse.Diff().x * Real( Global::HudW ) ) *
							Real( Camera->Pos.z / Global::HudZoom ) ),
						Zone[ CurZone ].BoundingRect.P1().y +	
							( ( Mouse.Diff().y * Real( Global::HudH ) ) *
							Real( Camera->Pos.z / Global::HudZoom ) )
					),
					Vector2D(
						Zone[ CurZone ].BoundingRect.P2().x - 
							( ( Mouse.Diff().x * Real( Global::HudW ) ) *
							Real( Camera->Pos.z / Global::HudZoom ) ),
						Zone[ CurZone ].BoundingRect.P2().y +	
							( ( Mouse.Diff().y * Real( Global::HudH ) ) *
							Real( Camera->Pos.z / Global::HudZoom ) )
					)
				);
		}
	}
	if( Button[ MOUSE_1 ].Released() )
	{
		isGroupMove = false;
		IsSaved = false;
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::ResizeZone()
{
	if( Button[ MOUSE_1 ].Pressed() )
	{
		OldMousePos = CalcMousePos();
	}
	if( Button[ MOUSE_1 ] )
	{
		RadiusRect2D TempRect = RadiusRect2D::Pair(
			Zone[ CurZone ].BoundingRect.P1(),
			Zone[ CurZone ].BoundingRect.P1() + Vector2D( CornerSize, CornerSize )
		);
		
		if( TempRect == OldMousePos )
		{
			ResizeCorner = 1;
		}

		TempRect = RadiusRect2D::Pair(
			Zone[ CurZone ].BoundingRect.P2() - Vector2D( CornerSize, CornerSize ),
			Zone[ CurZone ].BoundingRect.P2()
		);
		
		if( TempRect == OldMousePos )
		{
			ResizeCorner = 2;
		}

		TempRect = RadiusRect2D::Pair(
			Vector2D(
				Zone[ CurZone ].BoundingRect.P1().x,
				Zone[ CurZone ].BoundingRect.P2().y
			) - Vector2D( 0, CornerSize ),
			Vector2D(
				Zone[ CurZone ].BoundingRect.P1().x,
				Zone[ CurZone ].BoundingRect.P2().y
			) + Vector2D( CornerSize, 0 )
		);
		
		if( TempRect == OldMousePos )
		{
			ResizeCorner = 3;
		}
		
		TempRect = RadiusRect2D::Pair(
			Vector2D(
				Zone[ CurZone ].BoundingRect.P2().x,
				Zone[ CurZone ].BoundingRect.P1().y
			) - Vector2D( CornerSize, 0 ),
			Vector2D(
				Zone[ CurZone ].BoundingRect.P2().x,
				Zone[ CurZone ].BoundingRect.P1().y
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
				Zone[ CurZone ].BoundingRect = RadiusRect2D::Pair(
					Vector2D(
						Zone[ CurZone ].BoundingRect.P1().x - 
							( ( Mouse.Diff().x * Real( Global::HudW ) ) *
							Real( Camera->Pos.z / Global::HudZoom ) ),
						Zone[ CurZone ].BoundingRect.P1().y +	
							( ( Mouse.Diff().y * Real( Global::HudH ) ) *
							Real( Camera->Pos.z / Global::HudZoom ) )
					),
					Zone[ CurZone ].BoundingRect.P2()
				);
			}
			if( ResizeCorner == 2 )
			{
				Zone[ CurZone ].BoundingRect = RadiusRect2D::Pair(
					Zone[ CurZone ].BoundingRect.P1(),
					Vector2D(
						Zone[ CurZone ].BoundingRect.P2().x - 
							( ( Mouse.Diff().x * Real( Global::HudW ) ) *
							Real( Camera->Pos.z / Global::HudZoom ) ),
						Zone[ CurZone ].BoundingRect.P2().y +	
							( ( Mouse.Diff().y * Real( Global::HudH ) ) *
							Real( Camera->Pos.z / Global::HudZoom ) )
					)
				);
			}
			if( ResizeCorner == 3 )
			{
				Zone[ CurZone ].BoundingRect = RadiusRect2D::Pair(
					Vector2D(
						Zone[ CurZone ].BoundingRect.P1().x - 
							( ( Mouse.Diff().x * Real( Global::HudW ) ) *
							Real( Camera->Pos.z / Global::HudZoom ) ),
						Zone[ CurZone ].BoundingRect.P1().y
					),
					Vector2D(
						Zone[ CurZone ].BoundingRect.P2().x,
						Zone[ CurZone ].BoundingRect.P2().y +	
							( ( Mouse.Diff().y * Real( Global::HudH ) ) *
							Real( Camera->Pos.z / Global::HudZoom ) )
					)
				);
			}
			if( ResizeCorner == 4 )
			{
				Zone[ CurZone ].BoundingRect = RadiusRect2D::Pair(
					Vector2D(
						Zone[ CurZone ].BoundingRect.P1().x,
						Zone[ CurZone ].BoundingRect.P1().y +
							( ( Mouse.Diff().y * Real( Global::HudH ) ) *
							Real( Camera->Pos.z / Global::HudZoom ) )
					),
					Vector2D(
						Zone[ CurZone ].BoundingRect.P2().x - 
							( ( Mouse.Diff().x * Real( Global::HudW ) ) *
							Real( Camera->Pos.z / Global::HudZoom ) ),
						Zone[ CurZone ].BoundingRect.P2().y
					)
				);
			}
			IsSaved = false;
		}
	}
	else
	{
		ResizeCorner = 0;
	}	
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::AddZone()
{
	if( Button[ KEY_0_PAD ].Pressed() || Button[ KEY_A ].Pressed() )
	{
		Real CreationSize = CornerSize * Real( 2 );
		Vector2D CurMousePos = CalcMousePos();
		Zone.push_back( 
			Engine2D::cZone( 
				CurMousePos - Vector2D( CreationSize, CreationSize ),
				CurMousePos + Vector2D( CreationSize, CreationSize )
				)
			);
			
		CurZone = Zone.size() - 1;
		
		IsSaved = false;
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::DeleteZone()
{
	if( !Zone.empty() )
	{
		if( Button[ KEY_DELETE ].Pressed() )
		{
			std::vector< Engine2D::cZone > tempVec;
				
			for( size_t idx = 0; idx < Zone.size(); ++idx )
			{
				if( CurZone != idx )
				{
					tempVec.push_back( Zone[ idx ] );
				}
			}
			Zone.swap( tempVec );
			
			CurZone = Zone.size() - 1;
			
			IsSaved = false;
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::ChangeID()
{
	if( Button[ KEY_Q ].Pressed() )
	{
		if( Zone[ CurZone ].Id > 0 )
		{
			Zone[ CurZone ].Id--;
			
			IsSaved = false;
		}
	}
	if( Button[ KEY_W ].Pressed() )
	{
		if( Zone[ CurZone ].Id < 63 )
		{
			Zone[ CurZone ].Id++;
			
			IsSaved = false;
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::ChangeArg()
{
	if( Button[ KEY_Z ].Pressed() )
	{
		if( Zone[ CurZone ].Argument > 0 )
		{
			Zone[ CurZone ].Argument--;
			
			IsSaved = false;
		}
	}
	if( Button[ KEY_X ].Pressed() )
	{
		Zone[ CurZone ].Argument++;
		
		IsSaved = false;
	}
}
// - ------------------------------------------------------------------------------------------ - //
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::LoadZoneDesc()
{
char Line[1024];
	
	std::ifstream InFile( "../../../../Content/ZoneDescriptions.txt" );

	ZoneDesc.push_back( "Undefined" );

	while( !InFile.eof() )
	{
		// Read a line from the file //
		InFile.getline( Line, sizeof( Line ) );
	
		// Populate and use a string stream to tokenize the data //
		std::stringstream Text;
		Text << Line;
		
		ZoneDesc.push_back( Text.str() );
	}
}
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
