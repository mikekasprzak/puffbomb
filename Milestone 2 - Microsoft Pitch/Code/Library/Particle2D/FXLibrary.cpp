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
#include <string>
#include <sstream>
// - ------------------------------------------------------------------------------------------ - //
cAnimation* FXLibrary::Number[ 10 ];
// - ------------------------------------------------------------------------------------------ - //
void FXLibrary::InitAnims()
{
	Number[ 0 ] = &AnimationPool.Load( "Number0.anim" );
	Number[ 1 ] = &AnimationPool.Load( "Number1.anim" );
	Number[ 2 ] = &AnimationPool.Load( "Number2.anim" );
	Number[ 3 ] = &AnimationPool.Load( "Number3.anim" );
	Number[ 4 ] = &AnimationPool.Load( "Number4.anim" );
	Number[ 5 ] = &AnimationPool.Load( "Number5.anim" );
	Number[ 6 ] = &AnimationPool.Load( "Number6.anim" );
	Number[ 7 ] = &AnimationPool.Load( "Number7.anim" );
	Number[ 8 ] = &AnimationPool.Load( "Number8.anim" );
	Number[ 9 ] = &AnimationPool.Load( "Number9.anim" );
}
// - ------------------------------------------------------------------------------------------ - //
void FXLibrary::Bomb( const Vector2D& Pos )
{
//	OutlineTest( Pos );
//	return;

	int AdditiveParticles = DenseParticle.Allocate( 900, true, true );
	
	if( AdditiveParticles == -1 )
	{
		return;
	}
	
	cAnimation& SmallFireParticle = AnimationPool.Load( "SmallFireParticle.anim" );

	int MaxSteps = 300;
	for( int idx = 0; idx < MaxSteps; idx++ )
	{
		Real StepAsRadian = (Real( idx ) / Real( MaxSteps )) * (Real( 2 ) * Real::Pi);

		Vector2D Point( sin( StepAsRadian ), cos( StepAsRadian ) );
		
		Vector2D Velocity = Point * Real(8) * Real::Random();
		Vector2D Drift = Vector2D::Zero;
		Vector2D Acceleration = Vector2D::Zero;
		
		Real LifeTime = Real(30) + ( Real( 5 ) * Real::Random() );

		DenseParticle.Add(
			Pos, 		// Pos //
			Velocity,	// Velocity //
			Vector2D::Zero,  			// Acceleration //
			Vector2D::Zero,		// Drift //
			int( LifeTime ), 	// Life //
			SmallFireParticle,		// Animation //
			255,						// Alpha //
			20,							// Fade // What time to start fading //
			AdditiveParticles
		);

		LifeTime = Real(25) + ( Real( 5 ) * Real::Random() );
		
		Velocity = Point * Real(8) * Real::Random();
		
		DenseParticle.Add(
			Pos, 		// Pos //
			Velocity,	// Velocity //
			Vector2D::Zero,  			// Acceleration //
			Vector2D::Zero,		// Drift //
			int( LifeTime ), 	// Life //
			SmallFireParticle,		// Animation //
			255,						// Alpha //
			20,							// Fade // What time to start fading //
			AdditiveParticles
		);
		
		Velocity = Point * Real(12) + ( Real::Random() - Real( 0.5 ) );
		
		Acceleration = Point * Real(0.25);
		
		LifeTime = Real(35) + ( Real( 5 ) * Real::Random() );

		DenseParticle.Add(
			Pos, 		// Pos //
			Velocity,	// Velocity //
			-Acceleration,  			// Acceleration //
			Vector2D::Zero,		// Drift //
			int( LifeTime ), 	// Life //
			SmallFireParticle,		// Animation //
			255,						// Alpha //
			20,							// Fade // What time to start fading //
			AdditiveParticles
		);		
	}
	
	int DenseParticleLocation = DenseParticle.Allocate( 100, true, true );
	
	if( DenseParticleLocation == -1 )
	{
		return;
	}
	
	MaxSteps = 100;
	for( int idx = 0; idx < MaxSteps; idx++ )
	{
		Real StepAsRadian = (Real( idx ) / Real( MaxSteps )) * (Real( 2 ) * Real::Pi);

		Vector2D Point( sin( StepAsRadian ), cos( StepAsRadian ) );

		Vector2D Velocity = Point * ( Real( 22 ) * Real( ( Real::Random() - Real( 0.5 ) ) ) );
		Vector2D Drift = Vector2D::Zero;
		Drift.y = -Real( 0.0005 );
		
		Real LifeTime = Real(40) + ( Real( 40 ) * Real::Random() );

		DenseParticle.Add(
			Pos, 		// Pos //
			Velocity,	// Velocity //
			Vector2D::Zero,  			// Acceleration //
			Drift,		// Drift //
			int( LifeTime ), 	// Life //
			SmallFireParticle,		// Animation //
			255,						// Alpha //
			20,							// Fade // What time to start fading //
			DenseParticleLocation
		);
	}
	
	cAnimation& FireParticle = AnimationPool.Load( "FireParticle.anim" );

	DenseParticleLocation = DenseParticle.Allocate( 60, true, true );
	
	if( DenseParticleLocation == -1 )
	{
		return;
	}
	
	MaxSteps = 60;
	for( int idx = 0; idx < MaxSteps; idx++ )
	{
		Real StepAsRadian = (Real( idx ) / Real( MaxSteps )) * (Real( 2 ) * Real::Pi);

		Vector2D Point( sin( StepAsRadian ), cos( StepAsRadian ) );

		Vector2D Velocity = Point * ( Real( 4 ) * Real( Real::Random() ) );
		Vector2D Drift = Vector2D::Zero;
		Drift.y = -Real( 0.0005 );
		
		Real LifeTime = Real(40) + ( Real( 60 ) * Real::Random() );

		DenseParticle.Add(
			Pos, 		// Pos //
			Velocity,	// Velocity //
			Vector2D::Zero,  			// Acceleration //
			Drift,		// Drift //
			int( LifeTime ), 	// Life //
			FireParticle,		// Animation //
			255,						// Alpha //
			20,							// Fade // What time to start fading //
			DenseParticleLocation
		);
	}
	
	// Smoke //			
	cAnimation& SmokeParticle = AnimationPool.Load( "SmokeParticle.anim" );
	
	DenseParticleLocation = DenseParticle.Allocate( 200, true, true );
	
	if( DenseParticleLocation == -1 )
	{
		return;
	}
	
	MaxSteps = 50;
	for( int idx = 0; idx < MaxSteps; idx++ )
	{
		Real StepAsRadian = (Real( idx ) / Real( MaxSteps )) * (Real( 2 ) * Real::Pi);

		Vector2D Point( sin( StepAsRadian ), cos( StepAsRadian ) );

		Vector2D Velocity = Point * ( Real( 0.7 ) * Real( ( Real::Random() ) ) );
		Vector2D Drift = Vector2D::Zero;
		Drift.y = Real( 0.0001 );

		Real LifeTime = Real(70) + ( Real( 40 ) * Real::Random() );

		DenseParticle.Add(
			Pos + Vector2D( -5, -5 ), 		// Pos //
			Velocity,	// Velocity //
			Vector2D::Zero,  			// Acceleration //
			Drift,		// Drift //
			int( LifeTime ), 	// Life //
			SmokeParticle,		// Animation //
			255,						// Alpha //
			40,							// Fade // What time to start fading //
			DenseParticleLocation
		);
		
		Velocity = Point * ( Real( 0.7 ) * Real( ( Real::Random() ) ) );
		LifeTime = Real(70) + ( Real( 40 ) * Real::Random() );

		DenseParticle.Add(
			Pos + Vector2D( -5, 5 ), 		// Pos //
			Velocity,	// Velocity //
			Vector2D::Zero,  			// Acceleration //
			Drift,		// Drift //
			int( LifeTime ), 	// Life //
			SmokeParticle,		// Animation //
			255,						// Alpha //
			40,							// Fade // What time to start fading //
			DenseParticleLocation
		);
	
		Velocity = Point * ( Real( 0.7 ) * Real( ( Real::Random() ) ) );
		LifeTime = Real(70) + ( Real( 40 ) * Real::Random() );

		DenseParticle.Add(
			Pos + Vector2D( 5, 5 ), 		// Pos //
			Velocity,	// Velocity //
			Vector2D::Zero,  			// Acceleration //
			Drift,		// Drift //
			int( LifeTime ), 	// Life //
			SmokeParticle,		// Animation //
			255,						// Alpha //
			40,							// Fade // What time to start fading //
			DenseParticleLocation
		);
	
	
		Velocity = Point * ( Real( 0.7 ) * Real( ( Real::Random() ) ) );
		LifeTime = Real(70) + ( Real( 40 ) * Real::Random() );

		DenseParticle.Add(
			Pos + Vector2D( 5, -5 ), 		// Pos //
			Velocity,	// Velocity //
			Vector2D::Zero,  			// Acceleration //
			Drift,		// Drift //
			int( LifeTime ), 	// Life //
			SmokeParticle,		// Animation //
			255,						// Alpha //
			40,							// Fade // What time to start fading //
			DenseParticleLocation
		);
	}

	
}
// - ------------------------------------------------------------------------------------------ - //
void FXLibrary::Pickup( const Vector2D& Pos, const int Points )
{
	int MaxSteps = 16;

	int AdditiveParticles = DenseParticle.Allocate( MaxSteps, true );
	
	if( AdditiveParticles == -1 )
	{
		return;
	}
	cAnimation& StarParticle = AnimationPool.Load( "StarParticle.anim" );
	
	for( int idx = 0; idx < MaxSteps; idx++ )
	{
		Real StepAsRadian = (Real( idx ) / Real( MaxSteps )) * (Real( 2 ) * Real::Pi);

		Vector2D Point( sin( StepAsRadian ), cos( StepAsRadian ) );
		
		Vector2D Velocity = Point * Real( 5 );
		
		Real LifeTime = Real(50);

		DenseParticle.Add(
			Pos, 		// Pos //
			Velocity,	// Velocity //
			Vector2D::Zero,  			// Acceleration //
			Vector2D::Zero,		// Drift //
			int( LifeTime ), 	// Life //
			StarParticle,		// Animation //
			255,						// Alpha //
			40,							// Fade // What time to start fading //
			AdditiveParticles
		);
	}
	
	std::stringstream Temp;
	Temp << Points;
	std::string TempString = Temp.str();
	
	int NumberParticles = DenseParticle.Allocate( TempString.size(), false );
	
	if( NumberParticles == -1 )
	{
		return;
	}
	
	Vector2D Acceleration = Vector2D::Zero;
	Acceleration.y = Real( 0.05 );
	
	for( int idx = 0; idx < TempString.size(); idx++ )
	{
		DenseParticle.Add(
			Vector2D( Pos.x + Real( 38 * idx ) - ( ( Real( 38 * ( TempString.size() - 1 ) ) ) / Real( 2 ) ), Pos.y ), 		// Pos //
			Vector2D::Zero,	// Velocity //
			Acceleration,  			// Acceleration //
			Vector2D::Zero,		// Drift //
			90, 	// Life //
			*Number[ TempString[ idx ] - '0' ],		// Animation //
			255,						// Alpha //
			40,							// Fade // What time to start fading //
			NumberParticles
		);
	}

}
// - ------------------------------------------------------------------------------------------ - //
void FXLibrary::CrazyTest( const Vector2D& Pos )
{
	int AdditiveParticles = DenseParticle.Allocate( 32, true );
	
	if( AdditiveParticles == -1 )
	{
		return;
	}

	cAnimation& FireParticle = AnimationPool.Load( "StarParticle.anim" );

	int MaxSteps = 32;
	for( int idx = 0; idx < MaxSteps; idx++ )
	{
		Real StepAsRadian = (Real( idx ) / Real( MaxSteps )) * (Real( 2 ) * Real::Pi);

		Vector2D Point( sin( StepAsRadian ), cos( StepAsRadian ) );
		// Bad circle explosion //
		
		Vector2D Velocity = Point * Real::Random() * Real(1.5);
		
		Real LifeTime = Real::Random() * Real(10) + Real(50);

		// Additive //
		DenseParticle.Add(
			Pos, 		// Pos //
			Velocity,	// Velocity //
			Vector2D::Zero,  			// Acceleration //
			Vector2D::Zero,		// Drift //
			int( LifeTime ), 	// Life //
			FireParticle,		// Animation //
			255,						// Alpha //
			50,							// Fade // What time to start fading //
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

	cAnimation& FireParticle = AnimationPool.Load( "OldPuff.anim" );
//	cAnimation& FireParticle = AnimationPool.Load( "RainParticle.anim" );

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
			FireParticle,		// Animation //
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

	cAnimation& FireParticle = AnimationPool.Load( "RainParticle.anim" );
//	cAnimation& FireParticle = AnimationPool.Load( "FireParticle.anim" );
	
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
			FireParticle,		// Animation //
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

	cAnimation& FireParticle = AnimationPool.Load( "RainParticle.anim" );
	
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
			FireParticle,		// Animation //
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

	cAnimation& FireParticle = AnimationPool.Load( "FireParticle.anim" );
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
			FireParticle,		// Animation //
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
			FireParticle,		// Animation //
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
			FireParticle,		// Animation //
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
			
		);
		
		

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
		
		
		
		
		
		void FXLibrary::Bomb( const Vector2D& Pos )
{
	//OutlineTest( Pos );
//	return;
	
	int AdditiveParticles = DenseParticle.Allocate( 900, true );
	
	if( AdditiveParticles == -1 )
	{
		return;
	}

	cAnimation& SmallFireParticle = AnimationPool.Load( "SmallFireParticle.anim" );

	int MaxSteps = 300;
	for( int idx = 0; idx < MaxSteps; idx++ )
	{
		Real StepAsRadian = (Real( idx ) / Real( MaxSteps )) * (Real( 2 ) * Real::Pi);

		Vector2D Point( sin( StepAsRadian ), cos( StepAsRadian ) );
		
		Vector2D Velocity = Point * Real(8) * Real::Random();
		Vector2D Drift = Vector2D::Zero;
		Vector2D Acceleration = Vector2D::Zero;
		
		Real LifeTime = Real(30) + ( Real( 5 ) * Real::Random() );

		DenseParticle.Add(
			Pos, 		// Pos //
			Velocity,	// Velocity //
			Vector2D::Zero,  			// Acceleration //
			Vector2D::Zero,		// Drift //
			int( LifeTime ), 	// Life //
			SmallFireParticle,		// Animation //
			255,						// Alpha //
			20,							// Fade // What time to start fading //
			AdditiveParticles
		);

		LifeTime = Real(25) + ( Real( 5 ) * Real::Random() );
		
		Velocity = Point * Real(8) * Real::Random();
		
		DenseParticle.Add(
			Pos, 		// Pos //
			Velocity,	// Velocity //
			Vector2D::Zero,  			// Acceleration //
			Vector2D::Zero,		// Drift //
			int( LifeTime ), 	// Life //
			SmallFireParticle,		// Animation //
			255,						// Alpha //
			20,							// Fade // What time to start fading //
			AdditiveParticles
		);
		
		Velocity = Point * Real(12) + ( Real::Random() - Real( 0.5 ) );
		
		Acceleration = Point * Real(0.25);
		
		LifeTime = Real(35) + ( Real( 5 ) * Real::Random() );

		DenseParticle.Add(
			Pos, 		// Pos //
			Velocity,	// Velocity //
			-Acceleration,  			// Acceleration //
			Vector2D::Zero,		// Drift //
			int( LifeTime ), 	// Life //
			SmallFireParticle,		// Animation //
			255,						// Alpha //
			20,							// Fade // What time to start fading //
			AdditiveParticles
		);		
	}
	
	int DenseParticleLocation = DenseParticle.Allocate( 100, true );
	
	if( DenseParticleLocation == -1 )
	{
		return;
	}
	
	MaxSteps = 100;
	for( int idx = 0; idx < MaxSteps; idx++ )
	{
		Real StepAsRadian = (Real( idx ) / Real( MaxSteps )) * (Real( 2 ) * Real::Pi);

		Vector2D Point( sin( StepAsRadian ), cos( StepAsRadian ) );

		Vector2D Velocity = Point * ( Real( 22 ) * Real( ( Real::Random() - Real( 0.5 ) ) ) );
		Vector2D Drift = Vector2D::Zero;
		Drift.y = -Real( 0.0005 );
		
		Real LifeTime = Real(40) + ( Real( 40 ) * Real::Random() );

		DenseParticle.Add(
			Pos, 		// Pos //
			Velocity,	// Velocity //
			Vector2D::Zero,  			// Acceleration //
			Drift,		// Drift //
			int( LifeTime ), 	// Life //
			SmallFireParticle,		// Animation //
			255,						// Alpha //
			20,							// Fade // What time to start fading //
			DenseParticleLocation
		);
	}
	
	cAnimation& FireParticle = AnimationPool.Load( "FireParticle.anim" );

	DenseParticleLocation = DenseParticle.Allocate( 60, true );
	
	if( DenseParticleLocation == -1 )
	{
		return;
	}
	
	MaxSteps = 60;
	for( int idx = 0; idx < MaxSteps; idx++ )
	{
		Real StepAsRadian = (Real( idx ) / Real( MaxSteps )) * (Real( 2 ) * Real::Pi);

		Vector2D Point( sin( StepAsRadian ), cos( StepAsRadian ) );

		Vector2D Velocity = Point * ( Real( 4 ) * Real( Real::Random() ) );
		Vector2D Drift = Vector2D::Zero;
		Drift.y = -Real( 0.0005 );
		
		Real LifeTime = Real(40) + ( Real( 60 ) * Real::Random() );

		DenseParticle.Add(
			Pos, 		// Pos //
			Velocity,	// Velocity //
			Vector2D::Zero,  			// Acceleration //
			Drift,		// Drift //
			int( LifeTime ), 	// Life //
			FireParticle,		// Animation //
			255,						// Alpha //
			20,							// Fade // What time to start fading //
			DenseParticleLocation
		);
	}
	
	// Smoke //			
	cAnimation& SmokeParticle = AnimationPool.Load( "SmokeParticle.anim" );
	
	DenseParticleLocation = DenseParticle.Allocate( 200, true );
	
	if( DenseParticleLocation == -1 )
	{
		return;
	}
	
	MaxSteps = 50;
	for( int idx = 0; idx < MaxSteps; idx++ )
	{
		Real StepAsRadian = (Real( idx ) / Real( MaxSteps )) * (Real( 2 ) * Real::Pi);

		Vector2D Point( sin( StepAsRadian ), cos( StepAsRadian ) );

		Vector2D Velocity = Point * ( Real( 0.7 ) * Real( ( Real::Random() ) ) );
		Vector2D Drift = Vector2D::Zero;
		Drift.y = Real( 0.0001 );

		Real LifeTime = Real(70) + ( Real( 40 ) * Real::Random() );

		DenseParticle.Add(
			Pos + Vector2D( -5, -5 ), 		// Pos //
			Velocity,	// Velocity //
			Vector2D::Zero,  			// Acceleration //
			Drift,		// Drift //
			int( LifeTime ), 	// Life //
			SmokeParticle,		// Animation //
			255,						// Alpha //
			40,							// Fade // What time to start fading //
			DenseParticleLocation
		);
		
		Velocity = Point * ( Real( 0.7 ) * Real( ( Real::Random() ) ) );
		LifeTime = Real(70) + ( Real( 40 ) * Real::Random() );

		DenseParticle.Add(
			Pos + Vector2D( -5, 5 ), 		// Pos //
			Velocity,	// Velocity //
			Vector2D::Zero,  			// Acceleration //
			Drift,		// Drift //
			int( LifeTime ), 	// Life //
			SmokeParticle,		// Animation //
			255,						// Alpha //
			40,							// Fade // What time to start fading //
			DenseParticleLocation
		);
	
		Velocity = Point * ( Real( 0.7 ) * Real( ( Real::Random() ) ) );
		LifeTime = Real(70) + ( Real( 40 ) * Real::Random() );

		DenseParticle.Add(
			Pos + Vector2D( 5, 5 ), 		// Pos //
			Velocity,	// Velocity //
			Vector2D::Zero,  			// Acceleration //
			Drift,		// Drift //
			int( LifeTime ), 	// Life //
			SmokeParticle,		// Animation //
			255,						// Alpha //
			40,							// Fade // What time to start fading //
			DenseParticleLocation
		);
	
	
		Velocity = Point * ( Real( 0.7 ) * Real( ( Real::Random() ) ) );
		LifeTime = Real(70) + ( Real( 40 ) * Real::Random() );

		DenseParticle.Add(
			Pos + Vector2D( 5, -5 ), 		// Pos //
			Velocity,	// Velocity //
			Vector2D::Zero,  			// Acceleration //
			Drift,		// Drift //
			int( LifeTime ), 	// Life //
			SmokeParticle,		// Animation //
			255,						// Alpha //
			40,							// Fade // What time to start fading //
			DenseParticleLocation
		);
	}

	
}
		*/
	
	// !!!!!!!!!!!!!!!! //
