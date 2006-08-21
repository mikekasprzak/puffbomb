#ifdef EDITOR
// - ------------------------------------------------------------------------------------------ - //
#include "ComponentEdit.h"
#include "Input/Input.h"
// - ------------------------------------------------------------------------------------------ - //
#include <SDL/SDL.h>

using namespace Input;
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
					DynObj[ CurObj ].Body.AddSpring( CurSelected[idx], CurSelected[i] );
				}
			}
			ActiveAction();
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::BodyDeleteSpring()
{
	if( Button[ KEY_DELETE ].Pressed() )
	{
		if( !CurSelected.empty() )
		{
			for( int spring = DynObj[ CurObj ].Body.SpringSize() - 1; spring >= 0; --spring )
			{
				bool IndexA = false;
				bool IndexB = false;
				
				for( size_t idx = 0; idx < CurSelected.size(); ++idx )
				{
					if( DynObj[ CurObj ].Body.Spring(spring).IndexA == CurSelected[idx] )
					{
						IndexA = true;
					}
					if( DynObj[ CurObj ].Body.Spring(spring).IndexB == CurSelected[idx] )
					{
						IndexB = true;
					}
				}
				
				if( IndexA && IndexB )
				{
					 DynObj[ CurObj ].Body.DeleteSpring( spring );
				}
			}
			ActiveAction();
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
