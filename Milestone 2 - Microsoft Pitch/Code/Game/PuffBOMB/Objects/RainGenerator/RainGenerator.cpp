// - ------------------------------------------------------------------------------------------ - //
// RainGenerator //
// - ------------------------------------------------------------------------------------------ - //
#include <Util/Debug.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Particle2D/FXLibrary.h>
// - ------------------------------------------------------------------------------------------ - //
#include "RainGenerator.h"
#include <Engine2D.h>
// - ------------------------------------------------------------------------------------------ - //
extern int GetTime();
// - ------------------------------------------------------------------------------------------ - //
bool cRainGenerator::Work()
{
	if( LastTime < GetTime() )
	{
		FXLibrary::Rain( Pos, RainDensity );
		
		LastTime = GetTime() + RainFreq;
	}	
	
	return true;
}
// - ------------------------------------------------------------------------------------------ - //
