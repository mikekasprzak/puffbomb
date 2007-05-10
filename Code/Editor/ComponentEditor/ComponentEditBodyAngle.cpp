#ifdef EDITOR
// - ------------------------------------------------------------------------------------------ - //
#include "ComponentEdit.h"
#include "Input/Input.h"
// - ------------------------------------------------------------------------------------------ - //
#include <SDL/SDL.h>

using namespace Input;
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::BodyAddAngle()
{
	if( Button[ KEY_0_PAD ].Pressed() || Button[ KEY_A ].Pressed() /*|| isPaste == true*/ )
	{
		for( size_t idx = 0; idx < CurSelected.size(); ++idx )
		{
			DynObj->Body.AddSphere( CurSelected[idx] );
		}

		//if( !isPaste )
		{
			ActiveAction();
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::BodyDeleteAngle()
{
	if( Button[ KEY_DELETE ].Pressed() )
	{
		for( size_t idx = 0; idx < CurSelected.size(); ++idx )
		{
			for( size_t SphereIdx = 0; SphereIdx < DynObj->Body.SphereSize(); ++SphereIdx )
			{
				if( CurSelected[idx] == DynObj->Body.Sphere( SphereIdx ).Index )
				{
					DynObj->Body.DeleteSphere( SphereIdx );
				}
			}
		}
	}
} 
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
