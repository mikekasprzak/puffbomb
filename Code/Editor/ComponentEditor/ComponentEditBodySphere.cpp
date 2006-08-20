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
			Body2D[ CurBody ].AddSphere( CurSelected[idx] );
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
			for( size_t SphereIdx = 0; SphereIdx < Body2D[ CurBody ].Sphere.size(); ++SphereIdx )
			{
				if( CurSelected[idx] == Body2D[ CurBody ].Sphere[ SphereIdx ].Index )
				{
					Body2D[ CurBody ].DeleteSphere( SphereIdx );
				}
			}
		}
		
		
		/*for( size_t idx = 0; idx < Object[ CurrentObject ].Sphere.size(); idx++ ) {
			if ( Object[ CurrentObject ].Sphere[ idx ].Index == size_t(Node) ) {
				Object[ CurrentObject ].DeleteSphere( idx );
			}
		}*/
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::BodyRadius( Real RadiusDiff )
{
	if( Button[ KEY_LCTRL ] )
	{
		for( size_t idx = 0; idx < CurSelected.size(); ++idx )
		{
			for( size_t SphereIdx = 0; SphereIdx < Body2D[ CurBody ].Sphere.size(); ++SphereIdx )
			{
				if( CurSelected[idx] == Body2D[ CurBody ].Sphere[ SphereIdx ].Index )
				{
					if( Body2D[ CurBody ].Sphere[ SphereIdx ].Radius > Real( 1.0 ) )
					{
						if ( Button[ KEY_MINUS ] )
						{
							Body2D[ CurBody ].Sphere[ SphereIdx ].Radius -= RadiusDiff;
						}
						
						if( Mouse.Wheel.Diff() < 0 )
						{
							Body2D[ CurBody ].Sphere[ SphereIdx ].Radius -= RadiusDiff;
						}		
					}
					// - -------------------------------------------------------------------------- - //
					if( Button[ KEY_EQUALS ] )
					{
						Body2D[ CurBody ].Sphere[ SphereIdx ].Radius += RadiusDiff;
					}
					if( Mouse.Wheel.Diff() > 0 )
					{
						Body2D[ CurBody ].Sphere[ SphereIdx ].Radius += RadiusDiff;
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
