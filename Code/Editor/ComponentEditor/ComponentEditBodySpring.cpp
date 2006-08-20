#ifdef EDITOR
// - ------------------------------------------------------------------------------------------ - //
#include "ComponentEdit.h"
#include "Input/Input.h"
// - ------------------------------------------------------------------------------------------ - //
#include <SDL/SDL.h>

using namespace Input;
// - ------------------------------------------------------------------------------------------ - //
/*void cComponentEdit::DrawSpring( int Color, size_t Spring )
{
	gfx::Line( Object[ CurrentObject ].Pos( Object[ CurrentObject ].Spring[Spring].IndexA ),
		Object[ CurrentObject ].Pos( Object[ CurrentObject ].Spring[Spring].IndexB ),
		Color );
}*/
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::BodySelectSpring()
{
	/*if ( Button[ MOUSE_1 ].Pressed() )
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
	}*/
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::BodyAddSpring()
{
	if( Button[ KEY_0_PAD ].Pressed() || Button[ KEY_A ].Pressed() )
	{
		if( !CurSelected.empty() )
		{
			for( size_t idx = 0; idx < CurSelected.size(); ++idx )
			{
				for( size_t i = idx + 1; i < CurSelected.size(); ++i )
				{
					Body2D[ CurBody ].AddSpring( CurSelected[idx], CurSelected[i] );
					
					//CurrentSpring = 
					//	Object[ CurrentObject ].AddSpring( CurSelected[idx], CurSelected[i] );
				}
			}
			ActiveAction();
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::BodyDeleteSpring()
{
	/*if( Button[ KEY_DELETE ].Pressed() )
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
	}*/
}
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
