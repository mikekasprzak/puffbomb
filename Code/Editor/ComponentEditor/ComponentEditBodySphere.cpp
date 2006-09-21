#ifdef EDITOR
// - ------------------------------------------------------------------------------------------ - //
#include "ComponentEdit.h"
#include "Input/Input.h"
// - ------------------------------------------------------------------------------------------ - //
#include <SDL/SDL.h>

using namespace Input;
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::BodyAddSphere()
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
void cComponentEdit::BodyDeleteSphere()
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
void cComponentEdit::BodyRadius( const Real RadiusDiff )
{
	if( Button[ KEY_LCTRL ] )
	{
		for( size_t idx = 0; idx < CurSelected.size(); ++idx )
		{
			for( size_t SphereIdx = 0; SphereIdx < DynObj->Body.SphereSize(); ++SphereIdx )
			{
				if( CurSelected[idx] == DynObj->Body.Sphere( SphereIdx ).Index )
				{
					if( DynObj->Body.Sphere( SphereIdx ).Radius > Real( 1.0 ) )
					{
						if ( Button[ KEY_MINUS ] )
						{
							DynObj->Body.Sphere( SphereIdx ).Radius -= RadiusDiff;
						}
						
						if( Mouse.Wheel.Diff() < 0 )
						{
							DynObj->Body.Sphere( SphereIdx ).Radius -= RadiusDiff;
						}		
					}
					// - ---------------------------------------------------------------------- - //
					if( Button[ KEY_EQUALS ] )
					{
						DynObj->Body.Sphere( SphereIdx ).Radius += RadiusDiff;
					}
					if( Mouse.Wheel.Diff() > 0 )
					{
						DynObj->Body.Sphere( SphereIdx ).Radius += RadiusDiff;
					}
					
					break;
				}
			}
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
