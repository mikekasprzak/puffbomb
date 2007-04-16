#ifdef EDITOR
// - ------------------------------------------------------------------------------------------ - //
#include "Mesh2DEdit.h"
#include "Input/Input.h"
// - ------------------------------------------------------------------------------------------ - //
#include <SDL/SDL.h>

using namespace Input;
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::DrawSpring( int Color, size_t Spring )
{
	gfx::Line( Object[ CurrentObject ].Pos( Object[ CurrentObject ].Spring[Spring].IndexA ),
		Object[ CurrentObject ].Pos( Object[ CurrentObject ].Spring[Spring].IndexB ),
		Color );
}
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::SelectSpring()
{
	if ( Button[ MOUSE_1 ].Pressed() )
	{
		Vector2D MousePos = CalcMousePos();
		
		for( size_t idx = 0; idx < Object[ CurrentObject ].Spring.size(); ++idx )
		{
			Vector2D ClosestPoint =
			ClosestPointOnLine(
				Object[ CurrentObject ].Pos( Object[ CurrentObject ].Spring[idx].IndexA ),
				Object[ CurrentObject ].Pos( Object[ CurrentObject ].Spring[idx].IndexB ),
				MousePos
			);
			
			if( ( ClosestPoint - MousePos ).Magnitude() < Real( 3.0 ) )
			{
				 CurrentSpring = idx;
				 return;
			}
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::DrawSpringPlacement()
{
	if( SpringPlacement )
	{
		Vector2D MousePos = CalcMousePos();
		
		gfx::Line( Object[ CurrentObject ].Pos( CurrentNode ),
		CalcMousePos(),
		gfx::RGB( 0, 255, 0 ) );
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::ColAddSpring()
{
	if( Button[ KEY_0_PAD ].Pressed() || Button[ KEY_A ].Pressed() )
	{
		if( !CurSelected.empty() )
		{
			for( size_t idx = 0; idx < CurSelected.size(); ++idx )
			{
				for( size_t i = idx + 1; i < CurSelected.size(); ++i )
				{
					CurrentSpring = 
						Object[ CurrentObject ].AddSpring( CurSelected[idx], CurSelected[i] );
				}
			}
			ActiveAction();
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::ColDeleteSpring()
{
	if( Button[ KEY_DELETE ].Pressed() )
	{
		if( !CurSelected.empty() )
		{
			for( int spring = Object[ CurrentObject ].Spring.size() - 1; spring >= 0; --spring )
			{
				bool IndexA = false;
				bool IndexB = false;
				
				for( size_t idx = 0; idx < CurSelected.size(); ++idx )
				{
					if( Object[ CurrentObject ].Spring[spring].IndexA == CurSelected[idx] )
					{
						IndexA = true;
					}
					if( Object[ CurrentObject ].Spring[spring].IndexB == CurSelected[idx] )
					{
						IndexB = true;
					}
				}
				
				if( IndexA && IndexB )
				{
					 Object[ CurrentObject ].DeleteSpring( spring );
				}
			}
			ActiveAction();
		}
		if( CurrentSpring > Object[ CurrentObject ].Spring.size() - 1 )
		{
			CurrentSpring = Object[ CurrentObject ].Spring.size() - 1;
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::SwitchSpring()
{	
	if( Button[ KEY_UP ].Pressed() )
	{
	
		if( CurrentSpring > 0 )
		{
			--CurrentSpring;
		}
		else
		{
			CurrentSpring = Object[ CurrentObject ].Spring.size() - 1;
		}
	}
	else if( Button[ KEY_DOWN ].Pressed() )
	{

		if( CurrentSpring < Object[ CurrentObject ].Spring.size() - 1 )
		{
			++CurrentSpring;	
		}
		else
		{
			CurrentSpring = 0;	
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
