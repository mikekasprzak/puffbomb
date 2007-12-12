
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
// TODO: If you make function like these for a vector implementation, do 2 types.  //
//   Ones that wrap (Index % Size), and ones that clamp (Index >= Size ? Size-1 : Index). //
//   I'm unsure if a combination is useful (wraps, clamping to the value on the other extreme) //

inline const size_t PrevIndex( const size_t Max, int Index ) {
	Index--;
	
	if ( Index < 0 )
		return Max-1;
		
	return Index;
}

inline const size_t ThisIndex( const size_t, const size_t Index ) {
	return Index;
}

inline const size_t NextIndex( const size_t Max, size_t Index ) {
	Index++;
	
	if ( Index >= Max )
		return 0;
		
	return Index;
}
// - ------------------------------------------------------------------------------------------ - //
// Edges are the line segments, A to B (i.e. B-A order). //
inline Vector2D PrevEdge( const vector< Vector2D >& Verts, const size_t Index ) {
	return Verts[ThisIndex( Verts.size(), Index )] - Verts[PrevIndex( Verts.size(), Index )];
}

inline Vector2D ThisEdge( const vector< Vector2D >& Verts, const size_t Index ) {
	return Verts[NextIndex( Verts.size(), Index )] - Verts[ThisIndex( Verts.size(), Index )];
}

inline Vector2D NextEdge( const vector< Vector2D >& Verts, const size_t Index ) {
	return Verts[NextIndex( Verts.size(), NextIndex( Verts.size(), Index ) )] - Verts[NextIndex( Verts.size(), Index )];
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
bool VertexInsideTriangle( Vector2D* Vert, const size_t _P, const size_t _A, const size_t _B, const size_t _C ) {
	Vector2D& P = Vert[ _P ];
	Vector2D& A = Vert[ _A ];
	Vector2D& B = Vert[ _B ];
	Vector2D& C = Vert[ _C ];
	
	Vector2D EdgeA = B - A;
	Vector2D EdgeB = C - B;
	Vector2D EdgeC = A - C;
	
	if ( (P - A) * (-EdgeA.Tangent()) > 0 )
		return false;
	if ( (P - B) * (-EdgeB.Tangent()) > 0 )
		return false;
	if ( (P - C) * (-EdgeC.Tangent()) > 0 )
		return false;
	return true;
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
class cTriangle {
public:
	Vector2D a, b, c;
	int Color;
	
	cTriangle( ) {
	}
	
	cTriangle( const Vector2D& _a, const Vector2D& _b, const Vector2D& _c, const int _Color ) :
		a(_a),
		b(_b),
		c(_c),
		Color(_Color)
	{
	}
};
// - ------------------------------------------------------------------------------------------ - //
vector< cTriangle > Triangulate( vector< Vector2D > Vert ) {
	vector< cTriangle > Triangle;
	vector< Vector2D > OriginalVert = Vert;
	
	if ( Vert.size() > 2 ) {
		int ColorOffset = makecol( 0, 0, 128 );
		
		cout << "Searching for triangles (" << Vert.size() << " vertices)..." << endl;
		
		while ( Vert.size() > 2 ) {
			bool Found = false;
			vector< bool > Concave;
			
			// Build Concavity list //
			for ( size_t idx = 0; idx < Vert.size(); idx++ ) {
				Concave.push_back( PrevEdge( Vert, idx ).IsAcuteAngle( ThisEdge( Vert, idx ) ) );
			}

			// Test if verts are ears //
			for ( size_t idx = 0; idx < Vert.size(); idx++ ) {
//				cout << "+A: " << ThisEdge( Vert, idx ).x << ", " << ThisEdge( Vert, idx ).y <<
//					"  vs B: " << NextEdge( Vert, idx ).x << ", " << NextEdge( Vert, idx ).y <<
//					endl;

				cout << "-A: " << PrevIndex( Vert.size(), idx ) << " =A: " << ThisIndex( Vert.size(), idx ) << " +A: " << NextIndex( Vert.size(), idx ) << endl;

				
//				if ( ThisEdge( Vert, idx ).IsAcuteAngle( NextEdge( Vert, idx ) ) )
//					if ( PrevEdge( Vert, idx ).IsAcuteAngle( ThisEdge( Vert, idx ) ) )
//						if ( NextEdge( Vert, idx ).IsAcuteAngle( NextEdge( Vert, NextIndex( Vert.size(), idx ) ) ) )

				// Make sure we're not a concave vertex //
				if ( !Concave[ ThisIndex( Vert.size(), idx ) ] ) {
					// Make sure we don't contain a convex vertex //
					bool EarFailure = false;
					for( size_t idx2 = 0; idx2 < Vert.size(); idx2++ ) {
						// Skip myself //
						if ( idx2 == PrevIndex( Vert.size(), idx ) )
							continue;
						if ( idx2 == ThisIndex( Vert.size(), idx ) )
							continue;
						if ( idx2 == NextIndex( Vert.size(), idx ) )
							continue;
						
						// If the vertex is concave, we have a problem //
						if ( Concave[ idx2 ] ) {
							// If it's inside us, we're not an ear //
							if (
								VertexInsideTriangle( 
									&Vert[0],
									idx2, 
									PrevIndex( Vert.size(), idx ),
									ThisIndex( Vert.size(), idx ),
									NextIndex( Vert.size(), idx )
									)
								)
							{
								EarFailure = true;
								break;
							}
						}
					}
					
					if ( EarFailure )
						continue;
					
					cout << "Found ear " << idx << endl;
					Triangle.push_back(
						cTriangle(
							Vert[PrevIndex( Vert.size(), idx )],
							Vert[ThisIndex( Vert.size(), idx )],
							Vert[NextIndex( Vert.size(), idx )],
							ColorOffset
							)
						);
					Vert.erase( Vert.begin() + ThisIndex( Vert.size(), idx ) );
					ColorOffset += 32<<8;
					Found = true;
					break;
				}
			}
			
			if ( Found )
				continue;
				
			cout << "Error!!  Ear not found!" << endl;
			return Triangle;
			//return vector<cTriangle>();
		}
	}
		
	return Triangle;
}
// - ------------------------------------------------------------------------------------------ - //



// - ------------------------------------------------------------------------------------------ - //
void DrawPolygonOutlineArrows( BITMAP* Buffer, Vector2D* Vert, size_t Count, int Color = makecol( 0, 0, 0 ), int Length = 10 ) {
	// Need 2 points, as draw line code needs point and point+1 //
	if ( Count > 1 ) {
		// Draw lines //
		for ( size_t idx = 0; idx < Count - 1; idx++ ) {
			line(
				Buffer,
				(int)Vert[idx+0].x, (int)Vert[idx+0].y,
				(int)Vert[idx+1].x, (int)Vert[idx+1].y,
				Color
				);
				
			Vector2D HeadA = (Vert[idx+1] - Vert[idx+0]).Normal();
			Vector2D HeadB = HeadA.RotateNegative45() * Real( Length );
			HeadA = HeadA.Rotate45() * Real( Length );
			
			line(
				Buffer,
				(int)Vert[idx+1].x, (int)Vert[idx+1].y,
				(int)(Vert[idx+1].x - HeadA.x), (int)(Vert[idx+1].y - HeadA.y),
				Color
				);
			
			line(
				Buffer,
				(int)Vert[idx+1].x, (int)Vert[idx+1].y,
				(int)(Vert[idx+1].x - HeadB.x), (int)(Vert[idx+1].y - HeadB.y),
				Color
				);
		}
		
		// Closing line //
		line(
			Buffer,
			(int)Vert[Count-1].x, (int)Vert[Count-1].y,
			(int)Vert[0].x, (int)Vert[0].y,
			Color
			);
			
				
		Vector2D HeadA = (Vert[0] - Vert[Count-1]).Normal();
		Vector2D HeadB = HeadA.RotateNegative45() * Real( Length );
		HeadA = HeadA.Rotate45() * Real( Length );
		
		line(
			Buffer,
			(int)Vert[0].x, (int)Vert[0].y,
			(int)(Vert[0].x - HeadA.x), (int)(Vert[0].y - HeadA.y),
			Color
			);
		
		line(
			Buffer,
			(int)Vert[0].x, (int)Vert[0].y,
			(int)(Vert[0].x - HeadB.x), (int)(Vert[0].y - HeadB.y),
			Color
			);
	}
}
// - ------------------------------------------------------------------------------------------ - //
void DrawPolygonOutline( BITMAP* Buffer, Vector2D* Vert, size_t Count, int Color = makecol( 0, 0, 0 ) ) {
	// Need 2 points, as draw line code needs point and point+1 //
	if ( Count > 1 ) {
		// Draw lines //
		for ( size_t idx = 0; idx < Count - 1; idx++ ) {
			line(
				Buffer,
				(int)Vert[idx+0].x, (int)Vert[idx+0].y,
				(int)Vert[idx+1].x, (int)Vert[idx+1].y,
				Color
				);
		}
		
		// Closing line //
		line(
			Buffer,
			(int)Vert[Count-1].x, (int)Vert[Count-1].y,
			(int)Vert[0].x, (int)Vert[0].y,
			Color
			);
	}
}
// - ------------------------------------------------------------------------------------------ - //
void DrawTriangles( BITMAP* Buffer, cTriangle* Tri, size_t Count ) {
	// Need 2 points, as draw line code needs point and point+1 //
	if ( Count > 0 ) {
		// Draw lines //
		for ( size_t idx = 0; idx < Count; idx++ ) {
			triangle(
				Buffer,
				(int)Tri[idx].a.x, (int)Tri[idx].a.y,
				(int)Tri[idx].b.x, (int)Tri[idx].b.y,
				(int)Tri[idx].c.x, (int)Tri[idx].c.y,
				Tri[idx].Color
				);
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void DrawVerts( BITMAP* Buffer, Vector2D* Vert, size_t Count, int Color = makecol( 200, 0, 0 ) ) {
	// Draw vertices //
	for ( size_t idx = 0; idx < Count; idx++ ) {
		circle(
			Buffer,
			(int)Vert[idx+0].x, (int)Vert[idx+0].y,
			5,
			Color
			);
	}
}
// - ------------------------------------------------------------------------------------------ - //
int main( int argc, char* argv ) {
	cout << "Captain!  We're under attack! " << TemplateSine<360,45>::sin() << endl;
	
	// Initialize Allegro //
	allegro_init();
	install_keyboard();
	install_mouse();
	//install_joystick();
	
	// Create our window and back buffer //
	set_color_depth( 16 );
	set_gfx_mode( GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0 );
	
	BITMAP* Buffer = create_bitmap( 800, 600 );
	
	// Killed by pressing ESC //
	while( !key[ KEY_ESC ] ) {
		// Initialize things for our experiment //
		vector< Vector2D > Polygon;
		vector< cTriangle > Triangle;
		

		int MouseStatus = mouse_b;
		int MouseButton = mouse_b;
		// The Loop - killed by ESC, reset by TAB //
		while( !key[ KEY_ESC ] && !key[ KEY_TAB ] ) {
			clear_to_color( Buffer, makecol(230, 230, 200) );
			MouseStatus = MouseButton;
			MouseButton = mouse_b;
			
			// Work ----------------------------------------------------- //
			// If mouse button status changed //
			if ( MouseStatus != MouseButton ) {
				// Button 1 pressed //
				if ( ((MouseButton ^ MouseStatus) & MouseButton) == 1 ) {
					// Add point //
					Polygon.push_back( Vector2D( mouse_x, mouse_y ) );
					
					Triangle = Triangulate( Polygon );
				}			
			};
			
			// Draw ----------------------------------------------------- //
			// Basic polygon information //
			DrawTriangles( Buffer, &Triangle[0], Triangle.size() );
			DrawPolygonOutlineArrows( Buffer, &Polygon[0], Polygon.size() );
			DrawVerts( Buffer, &Polygon[0], Polygon.size() );
			textprintf_ex(
				Buffer, font, 0, 0, makecol( 0, 0, 0 ), -1,
				"Verts: %i (Edges: %i)",
				Polygon.size(), Polygon.size() >= 2 ? Polygon.size() - 1 : 0 );
			
			
			// Mouse Cursor //
			circle( Buffer, mouse_x, mouse_y, 3, makecol( 55, 55, 0 ) );

			
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
