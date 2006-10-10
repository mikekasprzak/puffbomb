// - ------------------------------------------------------------------------------------------ - //
#include <SDL/SDL_image.h>
#include <SDL/SDL.h>

#include "TankController.h"

#include <Input/Input.h>

// #include <Game.h> // Removed because of game dependency //

#include <Graphics/TexturePool.h>
#include <Particle2D/FXLibrary.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
cTankController::cTankController( 
	cSphereObject* _Object,
	cSphereObject* _Shot1,
	const std::string& File
	) :
	cDisplayObjectController( _Object, File )
{
//	Shot[0] = _Shot1;
//	Shot[1] = _Shot2;
//	CurrentShot = 0;

	Angle = Real::Zero;
	Power = Real( 8 );
	AngleVector = Vector2D( 0, 1 );

	
	Shot = _Shot1;
	
	//TextureId = TexturePool.Load( "SpiderTexture.tx" );
	
	MyPad = 0;
}
// - ------------------------------------------------------------------------------------------ - //	
void cTankController::Step() {
	if ( Input::Button[ KEY_1 ] ) {
		MyPad = 0;
	}
	if ( Input::Button[ KEY_2 ] ) {
		MyPad = 1;
	}
	if ( Input::Button[ KEY_3 ] ) {
		MyPad = 2;
	}
	if ( Input::Button[ KEY_4 ] ) {
		MyPad = 3;
	}

	// Adjust Camera Zoom based on my size //
	//Global::Zoom = Real( -800.0 ) - (Scale * Real(100) );
	//Global::Zoom = Real( -800.0 ) - (Real::One * Real(100) );

	// When you've shot your show, test to see if it's collided with anything //
	if ( Shot->Flags.IsActive() ) {
		FXLibrary::Shot1( Shot->Pos( 0 ) );
		
		// If you hit something //
		if ( Shot->Sphere[ 0 ].Flags.Collision() ) {
			// Explode Here //
	/*		cGame::Current->Impulse.push_back( 
				cImpulse(
					Shot->Pos( 0 ),
					Real( 0 ), Real( 32 ),
					Real( 300 ), Real( 0 )
					)
				);*/
				
			// Place Explosion and Use: Shot->Pos( 0 )
			FXLibrary::Explosion1( Shot->Pos( 0 ) );
//			FXLibrary::MuzzleFlash( 
//				Shot->Pos( 0 ),
//				-Shot->Velocity( 0 ).Normal()
//				);

			
//			cGame::Current->Camera->RemoveTarget( Shot, 80 );
			
			Shot->Flags.SetInactive();
		}
	}
	
	// Joypad //
	{
		// Pressing of the fire button //
		if ( Input::Pad[MyPad].Button[ PAD_FACE_A ].Pressed() ) {
			Vector2D Line = SphereObject->Pos( 4 ) - SphereObject->Pos( 3 );
			Line.Normalize();
			//Line = Line.Tangent();

			Matrix2x2 HomeMatrix;
			HomeMatrix[ 0 ] = Line.x;
			HomeMatrix[ 1 ] = Line.y;
			HomeMatrix[ 2 ] = -Line.Tangent().x;
			HomeMatrix[ 3 ] = -Line.Tangent().y;
			
			Vector2D Direction = AngleVector.ToMatrix2x1() * HomeMatrix;//Input::Pad[MyPad].Stick1.Normal();

			if ( Direction.MagnitudeSquared() != Real::Zero ) {
				Vector2D Position = SphereObject->Pos( 0 ) + Vector2D( 0, 16 );

				// Muzzle Flash //
				FXLibrary::MuzzleFlash( 
					Position + (Real( 48 ) * Direction),
					Direction
					);
				
				// Push Tank (Firing thrust) //
				for ( size_t idx = 0; idx < SphereObject->size(); idx++ ) {	
					SphereObject->AddForce( idx, -Direction * Real( 1 ) );
				}

				// Set out shot's direction and Velocity //
				Shot->Pos( 0 ) = Position + (Real( 32 ) * Direction);
				Shot->Old( 0 ) = Shot->Pos( 0 ) - (Power * Direction);
				
				Shot->ResetFriction( 0 );
				Shot->Flags.SetActive();
				
				Shot->CalcBoundingRect();
				
//				cGame::Current->Camera->NewTarget( Shot );
			}
		}

		// Turret Rotation //
//		if ( Angle 
//		Angle = Real::Zero;
//		AngleVector = Vector2D( 1, 0 );
	
	
		if ( Input::Pad[MyPad].Button[ PAD_L ] ) {
			Vector2D Line = SphereObject->Pos( 4 ) - SphereObject->Pos( 3 );
			Line.Normalize();

			SphereObject->AddForce( 3, Line.Tangent() * Real( 0.08 ) );
			FXLibrary::Steam( 
				SphereObject->Pos( 3 ),
				-Line.Tangent()
				);
		}
		
		if ( Input::Pad[MyPad].Button[ PAD_R ] ) {
			Vector2D Line = SphereObject->Pos( 4 ) - SphereObject->Pos( 3 );
			Line.Normalize();

			SphereObject->AddForce( 4, Line.Tangent() * Real( 0.08 ) );
			FXLibrary::Steam( 
				SphereObject->Pos( 4 ),
				-Line.Tangent()
				);
		}
		
		
	}


	Angle += Input::Pad[MyPad].Stick1.x.Normal() * Real( -0.01 );
	Angle = Angle.Max( Real::Zero );
	Angle = Angle.Min( Real::Half );
	
//	if ( Angle.Abs() > Real::Half ) {
//		Angle = Angle.Normal() * Real::Half;
//	}
	
	AngleVector = Vector2D( Angle.Cos(), Angle.Sin() );


//	// Torque Rotational Motion //
//	for ( int idx = 0; idx < 16; idx++ ) {	
//		SphereObject->AddForce(
//			1 + idx, 
//			(Input::Pad[MyPad].Stick1.x * Real( 0.2 )) * 
//				(SphereObject->Pos( 1 + idx ) - SphereObject->Pos( 0 )).Tangent().Normal()
//			);
//	}
}	
// - ------------------------------------------------------------------------------------------ - //	
void cTankController::Draw() {
/*	// Draw Turret //
	Vector2D Line = SphereObject->Pos( 4 ) - SphereObject->Pos( 3 );
	Line.Normalize();
	Line = Line.Tangent();

	Vector2D Position = SphereObject->Pos( 0 ) + (-Line * Real( 16 ));
	
	Matrix2x2 HomeMatrix;
	HomeMatrix[ 0 ] = Line.x;
	HomeMatrix[ 1 ] = Line.y;
	HomeMatrix[ 2 ] = -Line.Tangent().x;
	HomeMatrix[ 3 ] = -Line.Tangent().y;
	//HomeMatrix = HomeMatrix.Inverse();
	
		
	Matrix2x2 AngleMatrix;
	AngleMatrix[ 0 ] = AngleVector.x;
	AngleMatrix[ 1 ] = AngleVector.y;
	AngleMatrix[ 2 ] = -AngleVector.Tangent().x;
	AngleMatrix[ 3 ] = -AngleVector.Tangent().y;
	//AngleMatrix = AngleMatrix.Inverse();
	

	Real YOffset( 16 );

	// Vertices //
	Vector2D VertA( -4, 16 + YOffset );
	Vector2D VertB( 0, 16 + YOffset );
	Vector2D VertC( -4, 0 + YOffset );
	Vector2D VertD( 0, 0 + YOffset );

	Vector2D VertE( -8, 0 + YOffset );
	
	// UV's //
	Vector2D UVA( 28.0 / 32.0, 2.0 / 32.0 );
	Vector2D UVB( 29.0 / 32.0, 2.0 / 32.0 );
	Vector2D UVC( 28.0 / 32.0, 10.0 / 32.0 );
	Vector2D UVD( 29.0 / 32.0, 10.0 / 32.0 );

	Vector2D UVE( 27.0 / 32.0, 10.0 / 32.0 );
	
	// Draw Turret //
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);	

	glBindTexture( GL_TEXTURE_2D, TextureId );

	// Left //
	// Shaft Body //
	gfx::Face(
		(VertC.ToMatrix2x1() * AngleMatrix * HomeMatrix) + Position,
		(VertA.ToMatrix2x1() * AngleMatrix * HomeMatrix) + Position,
		(VertB.ToMatrix2x1() * AngleMatrix * HomeMatrix) + Position,
		UVC,
		UVB,
		UVA
		);

	gfx::Face(
		(VertB.ToMatrix2x1() * AngleMatrix * HomeMatrix) + Position,
		(VertD.ToMatrix2x1() * AngleMatrix * HomeMatrix) + Position,
		(VertC.ToMatrix2x1() * AngleMatrix * HomeMatrix) + Position,
		UVB,
		UVC,
		UVD
		);

	// Shaft Side //
	gfx::Face(
		(VertA.ToMatrix2x1() * AngleMatrix * HomeMatrix) + Position,
		(VertC.ToMatrix2x1() * AngleMatrix * HomeMatrix) + Position,
		(VertE.ToMatrix2x1() * AngleMatrix * HomeMatrix) + Position,
		UVA,
		UVE,
		UVC
		);


	// Right //
	// Shaft Body //
	gfx::Face(
		(VertC.FlipX().ToMatrix2x1() * AngleMatrix * HomeMatrix) + Position,
		(VertB.FlipX().ToMatrix2x1() * AngleMatrix * HomeMatrix) + Position,
		(VertA.FlipX().ToMatrix2x1() * AngleMatrix * HomeMatrix) + Position,
		UVC,
		UVA,
		UVB
		);

	gfx::Face(
		(VertB.FlipX().ToMatrix2x1() * AngleMatrix * HomeMatrix) + Position,
		(VertC.FlipX().ToMatrix2x1() * AngleMatrix * HomeMatrix) + Position,
		(VertD.FlipX().ToMatrix2x1() * AngleMatrix * HomeMatrix) + Position,
		UVB,
		UVD,
		UVC
		);

	// Shaft Side //
	gfx::Face(
		(VertA.FlipX().ToMatrix2x1() * AngleMatrix * HomeMatrix) + Position,
		(VertE.FlipX().ToMatrix2x1() * AngleMatrix * HomeMatrix) + Position,
		(VertC.FlipX().ToMatrix2x1() * AngleMatrix * HomeMatrix) + Position,
		UVA,
		UVC,
		UVE
		);


	glDisable(GL_BLEND);	
	glDisable(GL_TEXTURE_2D);		
	
	
	cDisplayObjectController::Draw();
	// Draw Cursor //
	//gfx::Circle( SphereObject->Pos( 0 ) + (Input::Pad[MyPad].Stick1.Normal() * Real(64) ), Real( 10 ), gfx::RGB( 255, 255, 255 ) );
	*/ // Removed because of game dependency //
}
// - ------------------------------------------------------------------------------------------ - //
