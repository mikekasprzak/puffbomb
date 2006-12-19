// - ------------------------------------------------------------------------------------------ - //
// FXLibrary //
// - ------------------------------------------------------------------------------------------ - //
#include "FXLibrary.h"
#include <Animation/AnimationPool.h>
#include <Animation/Animation.h>
#include <Particle2D/AnimParticleFactory.h>
#include <Particle2D/SolidParticleFactory.h>
#include <Particle2D/DenseParticleFactory.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
/*void FXLibrary::Explosion1( const Vector2D& Pos )
{
//	int AdditiveParticles = NewParticle.Allocate( 480, true );
	int AdditiveParticles = NewParticle.Allocate( 320, true );
	
	if( AdditiveParticles == -1 )
	{
		return;	
	}
	
	cAnimation& Explosion1 = AnimationPool.Load( "Explosion1.anim" );
	cAnimation& Explosion2 = AnimationPool.Load( "Explosion2.anim" );
	cAnimation& Explosion3 = AnimationPool.Load( "Explosion3.anim" );
	cAnimation& Smoke2 = AnimationPool.Load( "Smoke2.anim" );
		
	int MaxSteps = 80;
	for( int idx = 0; idx < MaxSteps; idx++ )
	{
		Real StepAsRadian = (Real( idx ) / Real( MaxSteps )) * (Real( 2 ) * Real::Pi);

		Vector2D Point( sin( StepAsRadian ), cos( StepAsRadian ) );
		// Bad circle explosion //
		
		Vector2D Velocity = Point * Real::Random();

		NewParticle.Add(
			Pos, 		// Pos //
			Velocity,	// Velocity //
			Vector2D::Zero,  			// Acceleration //
			Vector2D::Zero,		// Drift //
			int( Real::Random() * Real(30) + Real(30) ), 	// Life //
			Explosion1,		// Animation //
			255,						// Alpha //
			30,							// Fade // What time to start fading //
			AdditiveParticles
		);
		
		Velocity = Point * Real::Random() * 1.5;
		
		NewParticle.Add(
			Pos, 		// Pos //
			Velocity,	// Velocity //
			Vector2D::Zero,  			// Acceleration //
			Vector2D::Zero,		// Drift //
			int( Real::Random() * Real(30) + Real(50) ), 	// Life //
			Explosion2,		// Animation //
			255,						// Alpha //
			50,							// Fade // What time to start fading //
			AdditiveParticles
		);
		
		Velocity = Point * Real::Random() * 3;
		
		NewParticle.Add(
			Pos, 		// Pos //
			Velocity,	// Velocity //
			Vector2D::Zero,  			// Acceleration //
			Vector2D( 0.0, -0.001 * Real::Random() ),		// Drift //
			int( Real::Random() * Real(30) + Real(70) ), 	// Life //
			Explosion3,		// Animation //
			127,						// Alpha //
			70,							// Fade // What time to start fading //
			AdditiveParticles
		);

		Velocity = Point * Real::Random() * 2;
		
		NewParticle.Add(
			Pos, 		// Pos //
			Velocity * Real::Random() * 0.6,	// Velocity //
			Vector2D::Zero,  			// Acceleration //
			Vector2D( 0.0, 0.0008 * Real::Random() ),		// Drift //
			int( Real::Random() * Real(30) + Real(90) ), 	// Life //
			Smoke2,		// Animation //
			127,						// Alpha //
			90,							// Fade // What time to start fading //
			AdditiveParticles
		);
		
	}	
}
// - ------------------------------------------------------------------------------------------ - //
void FXLibrary::Explosion2( const Vector2D& Pos )
{
	cAnimation& TestAnimation2 = AnimationPool.Load( "TestAnimation2.anim" );
	cAnimation& TestAnimation3 = AnimationPool.Load( "TestAnimation3.anim" );

	int MaxSteps = 350;
	for( int idx = 0; idx < MaxSteps; idx++ )
	{
		Real StepAsRadian = (Real( idx ) / Real( MaxSteps )) * (Real( 2 ) * Real::Pi);

		Vector2D Point( sin( StepAsRadian ), cos( StepAsRadian ) );
		// Bad circle explosion //
		for( Real i = 1.0; i < 1.35; i += 0.05 )
		{
			Point *= i;
			
			if( i < 1.1 )
			{
				Vector2D Velocity = Point * Real::Random() * 1.8;

				AdditiveParticle.Add(
					Pos, 		// Pos //
					Velocity,	// Velocity //
					Vector2D::Zero,  			// Acceleration //
					Vector2D( 0.0, 0.001 * Real::Random() ),		// Drift //
					int( Real::Random() * Real(50) + Real(80) ), 	// Life //
					TestAnimation2,		// Animation //
					255,						// Alpha //
					80							// Fade // What time to start fading //
				);
			}
			else
			{
			
				Vector2D Velocity = Point * Real::Random() * 3.0;

				AdditiveParticle.Add(
					Pos, 		// Pos //
					Velocity,	// Velocity //
					Vector2D::Zero,  			// Acceleration //
					Vector2D::Zero,		// Drift //
					int( Real::Random() * Real(50) + Real(60) ), 	// Life //
					TestAnimation3,		// Animation //
					160,						// Alpha //
					60							// Fade // What time to start fading //
				);
			}
		}
	}	
}
// - ------------------------------------------------------------------------------------------ - //
void FXLibrary::Shot1( const Vector2D& Pos )
{
	cAnimation& ToonTankAni = AnimationPool.Load( "ToonTankAni.anim" );
	AdditiveParticle.Add(
		Pos, 		// Pos //
		Vector2D::Zero,	// Velocity //
		Vector2D::Zero,  			// Acceleration //
		Vector2D::Zero,		// Drift //
		10, 	// Life //
		ToonTankAni,		// Animation //
		255,						// Alpha //
		10							// Fade // What time to start fading //
	);
}
// - ------------------------------------------------------------------------------------------ - //
void FXLibrary::MuzzleFlash( const Vector2D& Pos, const Vector2D& Direction )
{
	Smoke1( Pos );
	
	cAnimation& Smoke1 = AnimationPool.Load( "Smoke1.anim" );
	cAnimation& Smoke2 = AnimationPool.Load( "Smoke2.anim" );
	cAnimation& Explosion2 = AnimationPool.Load( "Explosion2.anim" );
	cAnimation& Explosion3 = AnimationPool.Load( "Explosion3.anim" );
	
	int MaxSteps = 15;
	for( int idx = 0; idx < MaxSteps; idx++ )
	{
		AdditiveParticle.Add(
			Pos, 		// Pos //
			( ( Direction * Real::Random() * 0.3 ).Tangent() + Direction ) * Real::Random() * 2,	// Velocity //
			Vector2D::Zero,
			Vector2D( 0.0, 0.001 * Real::Random() ),		// Drift //
			int( Real::Random() * Real(20) + Real(40) ), 	// Life //
			Smoke1,		// Animation //
			255,						// Alpha //
			60							// Fade // What time to start fading //
		);

		AdditiveParticle.Add(
			Pos, 		// Pos //
			( ( -Direction * Real::Random() * 0.3 ).Tangent() + Direction ) * Real::Random() * 2,	// Velocity //
			Vector2D::Zero,
			Vector2D( 0.0, 0.001 * Real::Random() ),		// Drift //
			int( Real::Random() * Real(20) + Real(40) ), 	// Life //
			Smoke1,		// Animation //
			255,						// Alpha //
			60							// Fade // What time to start fading //
		);
	
		AdditiveParticle.Add(
			Pos, 		// Pos //
			( ( Direction * Real::Random() * 0.3 ).Tangent() + Direction ) * Real::Random() * 4,	// Velocity //
			Vector2D::Zero,
			Vector2D( 0.0, 0.001 * Real::Random() ),		// Drift //
			int( Real::Random() * Real(20) + Real(40) ), 	// Life //
			Smoke2,		// Animation //
			255,						// Alpha //
			60							// Fade // What time to start fading //
		);

		AdditiveParticle.Add(
			Pos, 		// Pos //
			( ( -Direction * Real::Random() * 0.3 ).Tangent() + Direction ) * Real::Random() * 4,	// Velocity //
			Vector2D::Zero,
			Vector2D( 0.0, 0.001 * Real::Random() ),		// Drift //
			int( Real::Random() * Real(20) + Real(40) ), 	// Life //
			Smoke2,		// Animation //
			255,						// Alpha //
			60							// Fade // What time to start fading //
		);
	}	
	MaxSteps = 40;
	for( int idx = 0; idx < MaxSteps; idx++ )
	{
		Vector2D Velocity = Vector2D(
			( ( Direction * Real::Random() * 0.35 ).Tangent() + Direction ) * Real::Random() * 8
		);
		
		AdditiveParticle.Add(
			Pos, 		// Pos //
			Velocity,	// Velocity //
			-Velocity * 0.02,
			Vector2D( 0.0, -0.0015 * Real::Random() ),		// Drift //
			int( Real::Random() * Real(20) + Real(20) ), 	// Life //
			Explosion3,		// Animation //
			255,						// Alpha //
			40							// Fade // What time to start fading //
		);
		
		Velocity = Vector2D(
			( ( -Direction * Real::Random() * 0.35 ).Tangent() + Direction ) * Real::Random() * 8
		);
	
		AdditiveParticle.Add(
			Pos, 		// Pos //
			Velocity,	// Velocity //
			-Velocity * 0.02,
			Vector2D( 0.0, -0.0015 * Real::Random() ),		// Drift //
			int( Real::Random() * Real(20) + Real(20) ), 	// Life //
			Explosion3,		// Animation //
			255,						// Alpha //
			40							// Fade // What time to start fading //
		);
	}
	MaxSteps = 20;
	for( int idx = 0; idx < MaxSteps; idx++ )
	{
		
		AdditiveParticle.Add(
			Pos, 		// Pos //
			( ( Direction * Real::Random() * 0.3 ).Tangent() + Direction ) * Real::Random() * 4,	// Velocity //
			Vector2D::Zero,
			Vector2D::Zero,		// Drift //
			int( Real::Random() * Real(20) + Real(10) ), 	// Life //
			Explosion2,		// Animation //
			255,						// Alpha //
			30							// Fade // What time to start fading //
		);

		AdditiveParticle.Add(
			Pos, 		// Pos //
			( ( -Direction * Real::Random() * 0.3 ).Tangent() + Direction ) * Real::Random() * 4,	// Velocity //
			Vector2D::Zero,
			Vector2D::Zero,		// Drift //
			int( Real::Random() * Real(20) + Real(10) ), 	// Life //
			Explosion2,		// Animation //
			255,						// Alpha //
			30							// Fade // What time to start fading //
		);
	}
}
// - ------------------------------------------------------------------------------------------ - //
void FXLibrary::Smoke1( const Vector2D& Pos )
{
	cAnimation& Smoke2 = AnimationPool.Load( "Smoke2.anim" );

	int MaxSteps = 15;
	for( int idx = 0; idx < MaxSteps; idx++ )
	{
		AdditiveParticle.Add(
			Pos + Vector2D( Real::Random() * Real( 6 ), 0.0 ), 		// Pos //
			Vector2D( 0.0, 0.4 * Real::Random() ),	// Velocity //
			Vector2D::Zero,  			// Acceleration //
			Vector2D::Zero,		// Drift //
			int( Real::Random() * Real(40) + Real(80) ), 	// Life //
			Smoke2,		// Animation //
			255,						// Alpha //
			80							// Fade // What time to start fading //
		);
		AdditiveParticle.Add(
			Pos + Vector2D( Real::Random() * -Real( 6 ), 0.0 ), 		// Pos //
			Vector2D( 0.0, 0.4 * Real::Random() ),	// Velocity //
			Vector2D::Zero,  			// Acceleration //
			Vector2D::Zero,		// Drift //
			int( Real::Random() * Real(40) + Real(80) ), 	// Life //
			Smoke2,		// Animation //
			255,						// Alpha //
			80							// Fade // What time to start fading //
		);
	}
}
// - ------------------------------------------------------------------------------------------ - //
void FXLibrary::Steam( const Vector2D& Pos, const Vector2D& Direction )
{
	cAnimation& Smoke1 = AnimationPool.Load( "Smoke1.anim" );

	AdditiveParticle.Add(
		Pos, 		// Pos //
		(Direction * ((Real::Random() * Real(0.4)) + Real(1.0) )) + (Direction.Tangent() * (Real::Random() * Real(0.2))), // Velocity
		Vector2D( 0, 0.02 ), // Acceleration //
		Vector2D::Zero,		// Drift //
		int( Real::Random() * Real(20) + Real(40) ), 	// Life //
		Smoke1,		// Animation //
		255,						// Alpha //
		60							// Fade // What time to start fading //
	);
}*/
// - ------------------------------------------------------------------------------------------ - //
void FXLibrary::Bomb( const Vector2D& Pos )
{
	int AdditiveParticles = DenseParticle.Allocate( 600, true );
	
	if( AdditiveParticles == -1 )
	{
		return;
	}

	cAnimation& ParticleTest = AnimationPool.Load( "ParticleTest.anim" );

	int MaxSteps = 200;
	for( int idx = 0; idx < MaxSteps; idx++ )
	{
		Real StepAsRadian = (Real( idx ) / Real( MaxSteps )) * (Real( 2 ) * Real::Pi);

		Vector2D Point( sin( StepAsRadian ), cos( StepAsRadian ) );
		// Bad circle explosion //
		
		//Vector2D Velocity = Point * Real::Random() * Real(1.5);
		Vector2D Velocity = Point * Real(6.70) * Real::Random();
		
		//Real LifeTime = Real::Random() * Real(30) + Real(30);
		Real LifeTime = Real(30) + ( Real( 5 ) * Real::Random() );

			// Additive //
		DenseParticle.Add(
			Pos, 		// Pos //
			Velocity,	// Velocity //
			Vector2D::Zero,  			// Acceleration //
			Vector2D::Zero,		// Drift //
			int( LifeTime ), 	// Life //
			ParticleTest,		// Animation //
			255,						// Alpha //
			20,							// Fade // What time to start fading //
			AdditiveParticles
		);

		LifeTime = Real(25) + ( Real( 5 ) * Real::Random() );
		
		Velocity = Point * Real(7.85) * Real::Random();
		
		// Additive //
		DenseParticle.Add(
			Pos, 		// Pos //
			Velocity,	// Velocity //
			Vector2D::Zero,  			// Acceleration //
			Vector2D::Zero,		// Drift //
			int( LifeTime ), 	// Life //
			ParticleTest,		// Animation //
			255,						// Alpha //
			20,							// Fade // What time to start fading //
			AdditiveParticles
		);
		
		Velocity = Point * Real(7) + ( Real::Random() - Real( 0.5 ) );
		
		LifeTime = Real(35) + ( Real( 5 ) * Real::Random() );

		// Additive //
		DenseParticle.Add(
			Pos, 		// Pos //
			Velocity,	// Velocity //
			Vector2D::Zero,  			// Acceleration //
			Vector2D::Zero,		// Drift //
			int( LifeTime ), 	// Life //
			ParticleTest,		// Animation //
			255,						// Alpha //
			20,							// Fade // What time to start fading //
			AdditiveParticles
		);		


	}
}
// - ------------------------------------------------------------------------------------------ - //
void FXLibrary::CrazyTest( const Vector2D& Pos )
{
	int AdditiveParticles = DenseParticle.Allocate( 120, true );
	
	if( AdditiveParticles == -1 )
	{
		return;
	}

	cAnimation& ParticleTest = AnimationPool.Load( "ParticleTest.anim" );

	int MaxSteps = 120;
	for( int idx = 0; idx < MaxSteps; idx++ )
	{
		Real StepAsRadian = (Real( idx ) / Real( MaxSteps )) * (Real( 2 ) * Real::Pi);

		Vector2D Point( sin( StepAsRadian ), cos( StepAsRadian ) );
		// Bad circle explosion //
		
		Vector2D Velocity = Point * Real::Random() * Real(1.5);
		
		Real LifeTime = Real::Random() * Real(30) + Real(30);

		// Additive //
		DenseParticle.Add(
			Pos, 		// Pos //
			Velocity,	// Velocity //
			Vector2D::Zero,  			// Acceleration //
			Vector2D::Zero,		// Drift //
			int( LifeTime ), 	// Life //
			ParticleTest,		// Animation //
			255,						// Alpha //
			20,							// Fade // What time to start fading //
			AdditiveParticles
		);
	}
}
// - ------------------------------------------------------------------------------------------ - //
void FXLibrary::CrazyPuffTest( const Vector2D& Pos )
{
	int AdditiveParticles = DenseParticle.Allocate( 20, true );
	
	if( AdditiveParticles == -1 )
	{
		return;
	}

	cAnimation& ParticleTest = AnimationPool.Load( "OldPuff.anim" );
//	cAnimation& ParticleTest = AnimationPool.Load( "RainParticle.anim" );

	int MaxSteps = 20;
	for( int idx = 0; idx < MaxSteps; idx++ )
	{
		Real StepAsRadian = (Real( idx ) / Real( MaxSteps )) * (Real( 2 ) * Real::Pi);

		Vector2D Point( sin( StepAsRadian ), cos( StepAsRadian ) );
		
		// Bad circle explosion //
		
		//Vector2D Velocity = Point * Real::Random() * Real(2.5);
		Vector2D Velocity = Point * Real(1.5);
		
		Real LifeTime = Real::Random() * Real(30) + Real(500);

		// Additive //
		DenseParticle.Add(
			Pos, 		// Pos //
			Velocity,	// Velocity //
			Vector2D::Zero,  			// Acceleration //
			Vector2D::Zero,		// Drift //
			int( LifeTime ), 	// Life //
			ParticleTest,		// Animation //
			255,						// Alpha //
			20,							// Fade // What time to start fading //
			AdditiveParticles
		);
	}
}
// - ------------------------------------------------------------------------------------------ - //
void FXLibrary::Rain( const Vector2D& Pos, const int Density )
{
	int MyDensity = Density + (rand() & 7) - 4;
	Real CircleOffset = Real::Random();
	
	int AdditiveParticles = SolidParticle.Allocate( MyDensity, true );
	
	if( AdditiveParticles == -1 )
	{
		return;
	}

	cAnimation& ParticleTest = AnimationPool.Load( "RainParticle.anim" );
//	cAnimation& ParticleTest = AnimationPool.Load( "ParticleTest.anim" );
	
	for( int idx = 0; idx < MyDensity; idx++ )
	{
		Real StepAsRadian = (Real( idx ) / Real( MyDensity )) * (Real( 2 ) * Real::Pi);

		Vector2D Point( sin( StepAsRadian + CircleOffset ), cos( StepAsRadian + CircleOffset ) );

		Vector2D Velocity = Point * Real::Random() * 3;
		
		// Bad circle explosion //
		
		//Vector2D Velocity = Point * Real::Random() * Real(2.5);
//		Vector2D Velocity = Point * Real(2.5);
		
		Real LifeTime = Real::Random() * Real(30) + Real(400);

		// Additive //
		SolidParticle.Add(
			Pos, 		// Pos //
			Velocity,	// Velocity //
			Vector2D( 0, -0.15 - (0.05 * Real::Random()) ),  			// Acceleration //
			Vector2D::Zero,		// Drift //
			int( LifeTime ), 	// Life //
			ParticleTest,		// Animation //
			255,						// Alpha //
			20,							// Fade // What time to start fading //
			AdditiveParticles
		);
	
	}
}
// - ------------------------------------------------------------------------------------------ - //
void FXLibrary::Drip( const Vector2D& Pos, const int Density )
{
	int AdditiveParticles = SolidParticle.Allocate( Density, true );
	
	if( AdditiveParticles == -1 )
	{
		return;
	}

	cAnimation& ParticleTest = AnimationPool.Load( "RainParticle.anim" );
	
	for( int idx = 0; idx < Density; idx++ )
	{
		//Real StepAsRadian = (Real( idx ) / Real( Density )) * (Real( 2 ) * Real::Pi);

		//Vector2D Point( sin( StepAsRadian + CircleOffset ), cos( StepAsRadian + CircleOffset ) );

		//Vector2D Velocity = Point * Real::Random() * 3;
		Vector2D Velocity = Vector2D( 0, -0.15 - (0.015 * Real::Random()) );
		
		Real LifeTime = Real::Random() * Real(30) + Real(200);

		// Additive //
		SolidParticle.Add(
			Pos, 		// Pos //
			Velocity,	// Velocity //
			Vector2D( -0.005 + ( 0.01 * Real::Random() ), -0.15 - (0.015 * Real::Random()) ),  			// Acceleration //
			Vector2D::Zero,		// Drift //
			int( LifeTime ), 	// Life //
			ParticleTest,		// Animation //
			255,						// Alpha //
			20,							// Fade // What time to start fading //
			AdditiveParticles
		);
	
	}
}
// - ------------------------------------------------------------------------------------------ - //
void FXLibrary::OutlineTest( const Vector2D& Pos )
{
	int FlatParticles = DenseParticle.Allocate( 240, false );

	if( FlatParticles == -1 )
	{
		return;
	}
	
	int TempStart = DenseParticle.Segment[ FlatParticles ]->Start;
	
	int AdditiveParticles = DenseParticle.Allocate( 240, true );
	
	for( size_t idx = 0; idx < DenseParticle.Segment.size(); idx++ )
	{
		if( DenseParticle.Segment[ idx ]->Start == TempStart )
		{
			FlatParticles = idx;
			break;
		}
	}
	
	if( AdditiveParticles == -1 )
	{
		DenseParticle.Release( FlatParticles );
		return;
	}

	cAnimation& ParticleTest = AnimationPool.Load( "ParticleTest.anim" );
	cAnimation& OutlineTest = AnimationPool.Load( "OutlineTest.anim" );

	int MaxSteps = 80;
	for( int idx = 0; idx < MaxSteps; idx++ )
	{
		Real StepAsRadian = (Real( idx ) / Real( MaxSteps )) * (Real( 2 ) * Real::Pi);

		Vector2D Point( sin( StepAsRadian ), cos( StepAsRadian ) );
		// Bad circle explosion //
		
		Vector2D Velocity = Point * Real::Random();
		
		Real LifeTime = Real::Random() * Real(30) + Real(30);

		// Additive //
		DenseParticle.Add(
			Pos, 		// Pos //
			Velocity,	// Velocity //
			Vector2D::Zero,  			// Acceleration //
			Vector2D::Zero,		// Drift //
			int( LifeTime ), 	// Life //
			ParticleTest,		// Animation //
			127,						// Alpha //
			10,							// Fade // What time to start fading //
			AdditiveParticles
		);
		
		// Flat //
		DenseParticle.Add(
			Pos, 		// Pos //
			Velocity,	// Velocity //
			Vector2D::Zero,  			// Acceleration //
			Vector2D::Zero,		// Drift //
			int( LifeTime ), 	// Life //
			OutlineTest,		// Animation //
			255,						// Alpha //
			10,							// Fade // What time to start fading //
			FlatParticles
		);

		
		Velocity = Point * Real::Random() * 1.5;
		
		LifeTime = Real::Random() * Real(30) + Real(50);
		
		// Additive //
		DenseParticle.Add(
			Pos, 		// Pos //
			Velocity,	// Velocity //
			Vector2D::Zero,  			// Acceleration //
			Vector2D::Zero,		// Drift //
			int( LifeTime ), 	// Life //
			ParticleTest,		// Animation //
			127,						// Alpha //
			10,							// Fade // What time to start fading //
			AdditiveParticles
		);
		
		// Flat //
		DenseParticle.Add(
			Pos, 		// Pos //
			Velocity,	// Velocity //
			Vector2D::Zero,  			// Acceleration //
			Vector2D::Zero,		// Drift //
			int( LifeTime ), 	// Life //
			OutlineTest,		// Animation //
			255,						// Alpha //
			10,							// Fade // What time to start fading //
			FlatParticles
		);
		
		Velocity = Point * Real::Random() * 3;
		
		LifeTime = Real::Random() * Real(30) + Real(70);
		
		Vector2D MyDrift = Vector2D( 0.0, -0.001 * Real::Random() );
		
		// Additive //
		DenseParticle.Add(
			Pos, 		// Pos //
			Velocity,	// Velocity //
			Vector2D::Zero,  			// Acceleration //
			MyDrift,		// Drift //
			int( LifeTime ), 	// Life //
			ParticleTest,		// Animation //
			127,						// Alpha //
			10,							// Fade // What time to start fading //
			AdditiveParticles
		);
		
		// Flat //
		DenseParticle.Add(
			Pos, 		// Pos //
			Velocity,	// Velocity //
			Vector2D::Zero,  			// Acceleration //
			MyDrift,		// Drift //
			int( LifeTime ), 	// Life //
			OutlineTest,		// Animation //
			255,						// Alpha //
			10,							// Fade // What time to start fading //
			FlatParticles
		);
	}
}
// - ------------------------------------------------------------------------------------------ - //

		/*
void FXLibrary::Bomb( const Vector2D& Pos )
{
	int AdditiveParticles = DenseParticle.Allocate( 300, true );
	
	if( AdditiveParticles == -1 )
	{
		return;
	}

	cAnimation& ParticleTest = AnimationPool.Load( "ParticleTest.anim" );

	int MaxSteps = 100;
	for( int idx = 0; idx < MaxSteps; idx++ )
	{
		Real StepAsRadian = (Real( idx ) / Real( MaxSteps )) * (Real( 2 ) * Real::Pi);

		Vector2D Point( sin( StepAsRadian ), cos( StepAsRadian ) );
		// Bad circle explosion //
		
		//Vector2D Velocity = Point * Real::Random() * Real(1.5);
		Vector2D Velocity = Point * Real(3.70);
		
		//Real LifeTime = Real::Random() * Real(30) + Real(30);
		Real LifeTime = Real(45);

			// Additive //
		DenseParticle.Add(
			Pos, 		// Pos //
			Velocity,	// Velocity //
			Vector2D::Zero,  			// Acceleration //
			Vector2D::Zero,		// Drift //
			int( LifeTime ), 	// Life //
			ParticleTest,		// Animation //
			255,						// Alpha //
			20,							// Fade // What time to start fading //
			AdditiveParticles
		);
	
		
		Velocity = Point * Real(3.85);
		
		// Additive //
		DenseParticle.Add(
			Pos, 		// Pos //
			Velocity,	// Velocity //
			Vector2D::Zero,  			// Acceleration //
			Vector2D::Zero,		// Drift //
			int( LifeTime ), 	// Life //
			ParticleTest,		// Animation //
			255,						// Alpha //
			20,							// Fade // What time to start fading //
			AdditiveParticles
		);
		
		Velocity = Point * Real(4);
		
		// Additive //
		DenseParticle.Add(
			Pos, 		// Pos //
			Velocity,	// Velocity //
			Vector2D::Zero,  			// Acceleration //
			Vector2D::Zero,		// Drift //
			int( LifeTime ), 	// Life //
			ParticleTest,		// Animation //
			255,						// Alpha //
			20,							// Fade // What time to start fading //
			AdditiveParticles
		);		


	}
}
		
		
// Bad Laser shot //

	int MaxSteps = 200;
	for( int idx = 0; idx < MaxSteps; idx++ )
	{
		
		ParticleFactory::Add(
			Pos, 		// Pos //
			Direction * idx,	// Velocity //
			Vector2D::Zero,  			// Acceleration //
			Vector2D::Zero,		// Drift //
			int( Real::Random() * Real(30) + Real(30) ), 	// Life //
			cAnimations::Explosion3,		// Animation //
			255,						// Alpha //
			30							// Fade // What time to start fading //
		);
	}
		
		
// Bad Mussle Flash explosion //

		int MaxSteps = 500;
		for( int idx = 0; idx < MaxSteps; idx++ )
		{
			Real StepAsRadian = (Real( idx ) / Real( MaxSteps )) * (Real( 2 ) * Real::Pi);

			Vector2D Point( sin( StepAsRadian ), cos( StepAsRadian ) );
			// Do Stuff Here //


			for( Real i = 1.0; i < 1.35; i += 0.05 )
			{
				Point *= i;
				{
					Point += 2;
					
					Vector2D Velocity = Point * Real::Random();

					ParticleFactory::Add(
						Vector2D( -500, 0 ), 		// Pos //
						Velocity,	// Velocity //
						Vector2D::Zero,  			// Acceleration //
						Vector2D::Zero,		// Drift //
						int( Real::Random() * Real(50) + Real(80) ), 	// Life //
						cAnimations::TestAni3,		// Animation //
						160,						// Alpha //
						80							// Fade // What time to start fading //
					);
				}
			}
		}		
		*/

/*

			// Bad Fire //
			for( Real i = 1.0; i < 1.1; i += 0.05 )
			{
				Point *= i;
				
				Vector2D Velocity = Point * Real::Random();
				
				ParticleFactory::Add(
					Vector2D( -500, 0 ), 		// Pos //
					Velocity,	// Velocity //
			//		Vector2D::Zero,  			// Acceleration //
					Vector2D( 0.0, 0.05 ),		// Acceleration //
					Vector2D( 0.0, -0.001 * Real::Random() ),		// Drift //
					int( Real::Random() * Real(50) + Real(50) ), 	// Life //
					cAnimations::TestAni3,		// Animation //
					140,						// Alpha //
					50							// Fade // What time to start fading //
				);
			}
*/			
/*			// Large Explosion //
			for( Real i = 1.1; i < 1.5; i += 0.05 )
			{
				Point *= i;
				
				ParticleFactory::Add(
					Vector2D( -500, 0 ), 		// Pos //
					Point * Real::Random() * 2,	// Velocity //
					Vector2D::Zero,  			// Acceleration //
					Vector2D::Zero, 			// Drift //
					int( Real::Random() * Real(50) + Real(50) ), 	// Life //
					cAnimations::TestAni2,		// Animation //
					140,						// Alpha //
					50							// Fade // What time to start fading //
				);
			}
*/
	
/*		ParticleFactory::Add(
			Vector2D( -500, 0 ), 		// Pos //
			Vector2D( 5, 0 ),			// Velocity //
			Vector2D::Zero, 			// Acceleration //
			Vector2D::Zero, 			// Drift //
			90,	 						// Life //
			cAnimations::TestAni		// Animation //
		);
*/
/*		ParticleFactory::Add(
			Vector2D( -500, 0 ), 		// Pos //
			Vector2D( 0, 5 ),			// Velocity //
			Vector2D::Zero, 			// Acceleration //
			Vector2D::Zero, 			// Drift //
			100, 						// Life //
			cAnimations::TestAni2		// Animation //
		);*/
	
	// !!!!!!!!!!!!!!!! //
