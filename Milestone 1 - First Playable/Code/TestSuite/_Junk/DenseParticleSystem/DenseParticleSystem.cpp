// - ------------------------------------------------------------------------------------------ - //
// DenseParticleSystem //
// - ------------------------------------------------------------------------------------------ - //
#include "DenseParticleSystem.h"
// - ------------------------------------------------------------------------------------------ - //
#include <string>
// - ------------------------------------------------------------------------------------------ - //
#include <SDL/SDL_image.h>
#include <SDL/SDL.h>
#include <GL/glext.h>
// - ------------------------------------------------------------------------------------------ - //
float cDenseParticleSystem::ParticleSize = 1;
Real cDenseParticleSystem::ParticleRadius( 0.5 );
//Real cDenseParticleSystem::ParticleDrawSize = Real( 1 );
// - ------------------------------------------------------------------------------------------ - //
cDenseParticleSystem::cDenseParticleSystem() :
	CurPixel( 0 )
{
}
// - ------------------------------------------------------------------------------------------ - //
void cDenseParticleSystem::LoadSystem() {
	CircleTexture = TexturePool.Load( "Circle.tx" ).Id;

	std::string CollisionLocation = "src/Content/Level01/MapInfo/Level_Collision.tx";
	std::string ImageLocation = "src/Content/Level01/MapInfo/Level_Image.tx";
		
	SDL_Surface* Collision = IMG_Load( CollisionLocation.c_str() );
	SDL_Surface* Image = IMG_Load( ImageLocation.c_str() );
	
	int Collision_Size = Collision->w * Collision->h;
	int Image_Size = Image->w * Image->h;
	
	std::vector< cDenseParticle* > ParticleMap( Image_Size );
	
	int Color = 0;
	int* CollisionPixels = (int*)Collision->pixels;
	int* Pixels = (int*)Image->pixels;
	// Create Particles //
	for( int idx = 0; idx < Collision_Size; ++idx )
	{
		if( (CollisionPixels[idx] & 0xffffff) != 0 )
		{
			int MyColor = ( ( Pixels[idx] & 0xff ) << 16 ) 
				| ( Pixels[idx] & 0xff00 ) 
				| ( ( Pixels[idx] &  0xff0000 ) >> 16 ) 
				| ( Pixels[idx] & 0xff000000 );
			
			Particle.push_back( ParticleMap[ idx ] = new
				cDenseParticle(
					Vector2D(
						Real( ( idx % Collision->w ) * ParticleSize ),
						Real( Collision->h - (( idx / Collision->w ) * ParticleSize) )
						),
					// May need this //
//					Vector2D(
//						Real( ( idx % Collision->w ) * ParticleSize ),
//						Real( Collision->h - 1 - (( idx / Collision->w ) * ParticleSize) )
//						),
					MyColor
					)
			);
			
			if ( ((CollisionPixels[idx]) & 0xff) < 0xE0 ) {
////				if ( ((CollisionPixels[idx]>>8) & 0xff) < 0x40 ) {
					Particle.back()->Flags = 0;
////				}
			}
		}
		else
		{
			ParticleMap[ idx ] = 0;
		}
	}
	
	Real StrongLink( 4 );
	Real WeakLink( 2 );
	
	// Create Linkage //
	for( int y = 0; y < Image->h; ++y )
	{
		for( int x = 0; x < Image->w; ++x )
		{
			int Me = (y*Image->w)+x;
			// Bail if I'm not worthy //
			if( !ParticleMap[Me] )
				continue;
			
			// Downs (Do only if not against bottom) //
			if ( y < Image->h - 1 ) {
				// Down Left (do only if not againt left edge) //
				if ( x > 0 ) {
					int You = ((y+1)*Image->w)+x-1;
	
					// If you're not black (not to be racist) //
					if ( ParticleMap[You] ) {
						// If Same Color, Stronger Link //
						if ( CollisionPixels[Me] == CollisionPixels[You] ) {
							Link.push_back( new
								cDenseLink(
									ParticleMap[Me],
									ParticleMap[You],
									StrongLink
									)
								);
						}
						// If Different Color, Weaker Link //
						else {
							Link.push_back( new
								cDenseLink(
									ParticleMap[Me],
									ParticleMap[You],
									WeakLink
									)
								);							
						}
					}
				}
				
				// Down //
				{
					int You = ((y+1)*Image->w)+x;
	
					// If you're not black (not to be racist) //
					if ( ParticleMap[You] ) {
						// If Same Color, Stronger Link //
						if ( CollisionPixels[Me] == CollisionPixels[You] ) {
							Link.push_back( new
								cDenseLink(
									ParticleMap[Me],
									ParticleMap[You],
									StrongLink
									)
								);
						}
						// If Different Color, Weaker Link //
						else {
							Link.push_back( new
								cDenseLink(
									ParticleMap[Me],
									ParticleMap[You],
									WeakLink
									)
								);							
						}
					}
				}				
			
				// Down Right (do only if not against right edge) //
				if ( x < Image->w - 1 ) {
					int You = ((y+1)*Image->w)+x+1;
	
					// If you're not black (not to be racist) //
					if ( ParticleMap[You] ) {
						// If Same Color, Stronger Link //
						if ( CollisionPixels[Me] == CollisionPixels[You] ) {
							Link.push_back( new
								cDenseLink(
									ParticleMap[Me],
									ParticleMap[You],
									StrongLink
									)
								);
						}
						// If Different Color, Weaker Link //
						else {
							Link.push_back( new
								cDenseLink(
									ParticleMap[Me],
									ParticleMap[You],
									WeakLink
									)
								);							
						}
					}
				}				

			}
			
			// Right (do only if not against right edge) //
			if ( x < Image->w - 1 ) {
				int You = (y*Image->w)+x+1;

				// If you're not black (not to be racist) //
				if ( ParticleMap[You] ) {
					// If Same Color, Stronger Link //
					if ( CollisionPixels[Me] == CollisionPixels[You] ) {
						Link.push_back( new
							cDenseLink(
								ParticleMap[Me],
								ParticleMap[You],
								StrongLink
								)
							);
					}
					// If Different Color, Weaker Link //
					else {
						Link.push_back( new
							cDenseLink(
								ParticleMap[Me],
								ParticleMap[You],
								WeakLink
								)
							);							
					}
				}
			}
		}		
	}	

	GroundImage.Init( Image->w, Image->h );

	for( size_t idx = 0; idx < Particle.size(); ++idx )
	{
		unsigned int PixelIdx = ( ( int( Particle[idx]->Pos.y ) ) )
			+ ( ( int( Particle[idx]->Pos.x ) ) * GroundImage.Height );
		
		if( PixelIdx < GroundImage.Pixels.size() )
		{
			GroundImage.Pixels[ PixelIdx ] = Particle[ idx ]->Color;
		}
	}
	
	glGenTextures( 1, &GroundTexID );
	glBindTexture( GL_TEXTURE_2D, GroundTexID );

    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA8, GroundImage.Height,
	  GroundImage.Width, 0, GL_BGRA,
	  GL_UNSIGNED_BYTE, ( void* )(&GroundImage.Pixels[0]) );

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	

	SDL_FreeSurface( Collision );
	SDL_FreeSurface( Image );	
	
	
	// Populate Grid //
	Grid.CreateGrid( Image->w / 4, Image->h / 4, 4, 4 );
	
	for ( size_t idx = 0; idx < Particle.size(); idx++ ) {
		Grid.Add( Particle[idx] );
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cDenseParticleSystem::Step()
{
	// Move all particles //
	for( size_t idx = 0; idx < Particle.size(); idx++ ) {
		Particle[ idx ]->Step();
	}

	for ( int idx2 = 0; idx2 < 4; idx2++ ) {
		// Update all the particles via their links //
		for( std::list< cDenseLink* >::iterator idx = Link.begin(); idx != Link.end(); idx++ ) {
			if ( (*idx)->Step() ) {
				// Remove the link from the system //
				std::list< cDenseLink* >::iterator Tmp = idx;
				Tmp++;
				delete *idx;
				Link.erase( idx );
				Tmp--;
				idx = Tmp;
			}
		}
	
		// Test for collisions between particles //
		for ( size_t idx = 0; idx < Grid.Tile.size(); idx++ ) {
			for ( cTile::ParticleType::iterator Itr = Grid.Tile[idx].Particle.begin(); Itr != Grid.Tile[idx].Particle.end(); Itr++ ) {
				if ( (*Itr)->Flags & cDenseParticle::flLockedHome )
					continue;
				
				// My Position //
				{
					cTile::ParticleType::iterator VsItr = Itr;
					VsItr++;
					
					while( VsItr != Grid.Tile[idx].Particle.end() ) {
						Vector2D Line = (*VsItr)->Pos - (*Itr)->Pos;
						
						Real MagSquared = Line.MagnitudeSquared();
						Real RadiusSum = (ParticleRadius + ParticleRadius);
						Real RadiusSquared = (RadiusSum * RadiusSum);
						
						if ( MagSquared < RadiusSquared ) {
							Vector2D Diff = (RadiusSum - MagSquared.Sqrt()) * Line;
							
							(*Itr)->Pos -= Diff * Real::Half;
							(*VsItr)->Pos += Diff * Real::Half;
						}
						VsItr++;
					};
				}
	
				// Downs // 
				if ( (idx / Grid.w) + 1 != Grid.h ) {
					// DownLeft //
					if ( idx % Grid.w != 0 ) {
						cTile::ParticleType::iterator VsItr = Grid.Tile[idx-1+Grid.w].Particle.begin();
						
						while( VsItr != Grid.Tile[idx-1+Grid.w].Particle.end() ) {
							Vector2D Line = (*VsItr)->Pos - (*Itr)->Pos;
							
							Real MagSquared = Line.MagnitudeSquared();
							Real RadiusSum = (ParticleRadius + ParticleRadius);
							Real RadiusSquared = (RadiusSum * RadiusSum);
							
							if ( MagSquared < RadiusSquared ) {
								Vector2D Diff = (RadiusSum - MagSquared.Sqrt()) * Line;
								
								(*Itr)->Pos -= Diff * Real::Half;
								(*VsItr)->Pos += Diff * Real::Half;
							}
							VsItr++;
						};
					}
		
					// Down //
					{
						cTile::ParticleType::iterator VsItr = Grid.Tile[idx+Grid.w].Particle.begin();
						
						while( VsItr != Grid.Tile[idx+Grid.w].Particle.end() ) {
							Vector2D Line = (*VsItr)->Pos - (*Itr)->Pos;
							
							Real MagSquared = Line.MagnitudeSquared();
							Real RadiusSum = (ParticleRadius + ParticleRadius);
							Real RadiusSquared = (RadiusSum * RadiusSum);
							
							if ( MagSquared < RadiusSquared ) {
								Vector2D Diff = (RadiusSum - MagSquared.Sqrt()) * Line;
								
								(*Itr)->Pos -= Diff * Real::Half;
								(*VsItr)->Pos += Diff * Real::Half;
							}
							VsItr++;
						};
					}
		
					// DownRight //
					if ( (idx % Grid.w) + 1 != Grid.w )	{
						cTile::ParticleType::iterator VsItr = Grid.Tile[idx+1+Grid.w].Particle.begin();
						
						while( VsItr != Grid.Tile[idx+1+Grid.w].Particle.end() ) {
							Vector2D Line = (*VsItr)->Pos - (*Itr)->Pos;
							
							Real MagSquared = Line.MagnitudeSquared();
							Real RadiusSum = (ParticleRadius + ParticleRadius);
							Real RadiusSquared = (RadiusSum * RadiusSum);
							
							if ( MagSquared < RadiusSquared ) {
								Vector2D Diff = (RadiusSum - MagSquared.Sqrt()) * Line;
								
								(*Itr)->Pos -= Diff * Real::Half;
								(*VsItr)->Pos += Diff * Real::Half;
							}
							VsItr++;
						};
					}
				}
				
				// Right //
				if ( (idx % Grid.w) + 1 != Grid.w )	{
					cTile::ParticleType::iterator VsItr = Grid.Tile[idx+1].Particle.begin();
					
					while( VsItr != Grid.Tile[idx+1].Particle.end() ) {
						Vector2D Line = (*VsItr)->Pos - (*Itr)->Pos;
						
						Real MagSquared = Line.MagnitudeSquared();
						Real RadiusSum = (ParticleRadius + ParticleRadius);
						Real RadiusSquared = (RadiusSum * RadiusSum);
						
						if ( MagSquared < RadiusSquared ) {
							Vector2D Diff = (RadiusSum - MagSquared.Sqrt()) * Line;
							
							(*Itr)->Pos -= Diff * Real::Half;
							(*VsItr)->Pos += Diff * Real::Half;
						}
						VsItr++;
					};
				}			
			}
		}
	}

	for( size_t idx = 0; idx < Particle.size(); idx++ ) {
		Grid.Remove( Particle[idx] );
		Grid.Add( Particle[idx] );
	}

	// Clear the Image Buffer //
	GroundImage.Clear();
//	GroundImage.Clear( 64, 64, 256, 64 );

	// Update pixels in the buffer //
	for( size_t idx = 0; idx < Particle.size(); idx++ ) {
		unsigned int PixelIdx = ( ( int( Particle[idx]->Pos.y ) ) )
			+ ( ( int( Particle[idx]->Pos.x ) ) * GroundImage.Height );
		
		if( PixelIdx < GroundImage.Pixels.size() )
		{
			GroundImage.Pixels[ PixelIdx ] = Particle[ idx ]->Color;
		}
	}

}
// - ------------------------------------------------------------------------------------------ - //
void cDenseParticleSystem::Draw()
{
	//Vector2D Radius( ParticleDrawSize, ParticleDrawSize );
	
	glEnable( GL_DEPTH_TEST );
	glEnable( GL_TEXTURE_2D );
	glEnable( GL_BLEND );
//	glBindTexture( GL_TEXTURE_2D, CircleTexture );
	
/*	glBegin( GL_QUADS );
	glNormal3f( 0.0f, 0.0f, 1.0f );
	
	for( size_t idx = 0; idx < Particle.size(); idx++ ) {
		//gfx::Circle( Particle[ idx ]->Pos, Real( HalfParticleSize ), Particle[ idx ]->Color );
		gfx::FilledRect( Particle[ idx ]->Pos - Radius, Particle[ idx ]->Pos + Radius, Particle[ idx ]->Color );
	}
	
	glEnd();*/
	
	glBindTexture( GL_TEXTURE_2D, GroundTexID );

	gfx::FlipFilledRect(
		Vector2D( 0.0, 0.0 ),
		Vector2D( GroundImage.Width << 1, GroundImage.Height << 1 ),
		gfx::RGB(255,255,255)
	);

	glDisable( GL_BLEND );
	glDisable( GL_TEXTURE_2D );
	glDisable( GL_DEPTH_TEST );

	Update( 0, GroundImage.Width );

}
// - ------------------------------------------------------------------------------------------ - //
void cDenseParticleSystem::Update( int X, int Width )
{
/*	GroundImage.Pixels[CurPixel] = gfx::RGB( 0,255,255 );
	if( CurPixel < 130000 )
	{
		CurPixel++;
	}
*/
	int XOffset = GroundImage.Height * X;

	glTexSubImage2D(	
		GL_TEXTURE_2D,
		0,
		0,
		X,
		GroundImage.Height,
		Width,
		GL_BGRA,
		GL_UNSIGNED_BYTE,
		( void* )(&GroundImage.Pixels[XOffset]) );
}
// - ------------------------------------------------------------------------------------------ - //
