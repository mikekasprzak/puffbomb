// - ------------------------------------------------------------------------------------------ - //
#include "SuperFlow.h"
// - ------------------------------------------------------------------------------------------ - //
#include <Particle2D/ParticleFactory.h>
#include <Particle2D/NewParticleFactory.h>
// - ------------------------------------------------------------------------------------------ - //
#include <SplashScreen/SplashScreen.h>
// - ------------------------------------------------------------------------------------------ - //
cSuperFlow::cSuperFlow()
{
	// Populate the particle factorys with their max number of particles //
	FlatParticle.Populate( 500 );
	AdditiveParticle.Populate( 500 );

	NewParticle.Populate( 40000 );

	// Display the Sykhronics spash screen //
	{
		cSykhronicsSplash SykhronicsSplash;
	}
}
// - ------------------------------------------------------------------------------------------ - //
