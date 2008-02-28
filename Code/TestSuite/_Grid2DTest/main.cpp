// - ------------------------------------------------------------------------------------------ - //
// Pillar (Ludum Dare Prototype) - (c) Michael Kasprzak 2007 (mike@sykhronics.com)
//
//   This code is made available freely for non commercial use.
//   All code and content is the property of Michael Kasprzak,
//   unless otherwise noted (or pretty freaking obvious).
// - ------------------------------------------------------------------------------------------ - //
#include <allegro.h>
// - ------------------------------------------------------------------------------------------ - //
#include <vector>
#include <deque>
#include <iostream>
using namespace std;
// - ------------------------------------------------------------------------------------------ - //
// Select part from Geometry Library //
#include <Math/Real.h>
#include <Math/Vector.h>
#include <Math/Matrix.h>
#include <Geometry/Rect.h>
// - ------------------------------------------------------------------------------------------ - //
#include "MatrixDraw.h"
// - ------------------------------------------------------------------------------------------ - //
#include "Block.h"
#include "PillarBlock.h"
//#include "PickUp.h"
#include "Game.h"
// - ------------------------------------------------------------------------------------------ - //
Matrix3x3 ViewMatrix;
Matrix3x3 Orientation;
Vector2D CameraDown;
// - ------------------------------------------------------------------------------------------ - //
int main( int argc, char* argv ) {
	cout << "Danger!  Application started!" << endl;
	
	// Grid2D Test App //
	{
		Grid2D<int> Grid(2,3,0);
		Grid(0,1) = 1;
		
		Grid = Grid.RotateCW();
		Grid = Grid2D<int>::RotateCW( Grid );
			
		Grid = Grid.FlipX();
		
//		Grid.ResizeAlign( 10, 10, 0, 0, 3 );
//		Grid.ResizeAlign( 8, 8, -1, +1, 2 );
		
		
//		Grid.Resize( 4, 4, 3 );
//		
//		Grid.Resize( 2, 6, 5 );
//		
//		Grid.SetWidthRight( 6, 2 );
//		
//		Grid.SetHeightTop( 8, 9 );
		
		cout << "Grid: " << endl;
		for ( int y = 0; y < Grid.Height(); y++ ) {
			for ( int x = 0; x < Grid.Width(); x++ ) {
				cout << Grid(x,y) << " ";
			}
			cout << endl;
		}
		
		Grid2D<int> Grad(2,2,2);
		Grad.Wrap(0,12) = 0;
		
		cout << "Grad: " << endl;
		for ( int y = 0; y < Grad.Height(); y++ ) {
			for ( int x = 0; x < Grad.Width(); x++ ) {
				cout << Grad(x,y) << " ";
			}
			cout << endl;
		}		
		
		Grid2D<int> Merged = Grid2D<int>::MergeBlendMask( Grid, Grad, 2, 0, 4, 5, 0, 2, 9 );
		
		cout << "Merged: " << endl;
		for ( int y = 0; y < Merged.Height(); y++ ) {
			for ( int x = 0; x < Merged.Width(); x++ ) {
				cout << Merged(x,y) << " ";
			}
			cout << endl;
		}
	}

	// Initialize Allegro //
	allegro_init();
	install_keyboard();
	install_mouse();
	//install_joystick();
	
	// Create our window and back buffer //
	set_color_depth( 16 );
	set_gfx_mode( GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0 );
	
	BITMAP* Buffer = create_bitmap( 800, 600 );
	
	const Matrix3x3 HomeMatrix(
		Real::One, Real::Zero, Real::Zero,
		Real::Zero, -Real::One, Real::Zero,
		Real(400), Real(300), Real::One
		);
	
	Orientation = Matrix3x3();

	CameraDown = Vector2D( 0, -1 );
	
	// Killed by pressing ESC //
	while( !key[ KEY_ESC ] ) {
		// Initialize things for our experiment //
		cGame Game;
//		Contact.clear();
		
		// The Loop - killed by ESC, reset by TAB //
		while( !key[ KEY_ESC ] && !key[ KEY_TAB ] ) {
			clear_to_color( Buffer, makecol(30, 0, 0) );

			Orientation = Matrix3x3();
			Game.Step();
			ViewMatrix = Orientation;
			ViewMatrix *= HomeMatrix;
			Game.Draw( Buffer );
			
			// Sync and copy buffer to screen //
			vsync();
			blit( Buffer, screen, 0, 0, 0, 0, 800, 600 );
			rest( 0 );
			
			// Pause by pressing the Spacebar //
			while( key[ KEY_SPACE ] ) {
				// Step by pressing enter //
				if ( key[ KEY_ENTER ] ) {
					while( key[ KEY_ENTER ] ) {	
					}
					break;
				}
			}
		};
	};
	
	destroy_bitmap( Buffer );
		
	// Kill Allegro (big sharp knife) //
	allegro_exit();
	
	return 0;
}
END_OF_MAIN();
// - ------------------------------------------------------------------------------------------ - //
