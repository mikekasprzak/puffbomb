// - ------------------------------------------------------------------------------------------ - //
// DripGenerator //
// - ------------------------------------------------------------------------------------------ - //
#include <Util/Debug.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Particle2D/FXLibrary.h>
// - ------------------------------------------------------------------------------------------ - //
#include "DripGenerator.h"
#include <Engine2D.h>
// - ------------------------------------------------------------------------------------------ - //
extern int GetTime();
// - ------------------------------------------------------------------------------------------ - //
bool cDripGenerator::Work()
{
	if( LastTime < GetTime() )
	{
		FXLibrary::Drip( Pos, DripDensity );
		
		LastTime = GetTime() + DripFreq;
	}	
	
	return true;
}
// - ------------------------------------------------------------------------------------------ - //
