// - ------------------------------------------------------------------------------------------ - //
// DenseParticleSystem //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Phiz_DenseParticleSystem_H__
#define __Phiz_DenseParticleSystem_H__
// - ------------------------------------------------------------------------------------------ - //

#include <vector>
#include <list>

#include <Graphics/TexturePool.h>

#include "DenseParticle.h"
#include "DenseLink.h"

#include <Graphics/LinearImage.h>
// - ------------------------------------------------------------------------------------------ - //
class cDenseParticleSystem {
public:
	static float ParticleSize;
	static Real ParticleRadius;
	//static Real ParticleDrawSize;
	
	cLinearImage GroundImage;
	GLuint GroundTexID;

	int CurPixel;

	class cTile {
	public:
		typedef std::list< cDenseParticle* > ParticleType;
		
		ParticleType Particle;
	};
	
	class cGrid {
	public:
		// Dimensions of the grid and tiles //
		int w, h;
		Real TileW, TileH;
				
		std::vector< cTile > Tile;
		//cTile Outside;

	public:
		void CreateGrid( const int _w, const int _h, const Real& _TileW, const Real& _TileH ) {			
			// Copy our stats //
			w = _w;//+1;
			h = _h;//+1;
			TileW = _TileW;
			TileH = _TileH;
			
			// Create our grid of the correct size //
			Tile.clear();
			Tile.resize( w * h );
		}
		
	public:
		// Using Pos, add's itself to the grid //
		inline void Add( cDenseParticle* a ) {
			int TileX = a->Pos.x / TileW;
			int TileY = a->Pos.y / TileH;
			
			int Pos = (TileY * w) + TileX;
			
			//Log( 10, " w:" << w << " h:" << h << " t:" << (w*h) );
			
//			Log( 10, "TileX:" << TileX << " TileY:" << TileY );
//			
//			Log( 10, "Numbah: " << Pos );
			
			
			Tile[Pos].Particle.push_back( a );
			a->TileNumber = Pos;
			a->MyTile = --Tile[Pos].Particle.end();
		}

		inline void Remove( cDenseParticle* a ) {
			// Can only remove if you have an iterator that defines you //
			Tile[a->TileNumber].Particle.erase( a->MyTile );
		}

		
		// Using Old //
		inline void RemoveOld( cDenseParticle* a ) {
			int TileX = a->Old.x / TileW;
			int TileY = a->Old.y / TileH;

			int Pos = (TileY * w) + TileX;
			
			// Can only remove if you have an iterator that defines you //
			Tile[Pos].Particle.erase( a->MyTile );
		}

		// Using Pos //
		inline void RemovePos( cDenseParticle* a ) {
			int TileX = a->Pos.x / TileW;
			int TileY = a->Pos.y / TileH;

			int Pos = (TileY * w) + TileX; 
			
			// Can only remove if you have an iterator that defines you //
			Tile[Pos].Particle.erase( a->MyTile );
		}
		
	};
public:
	// All Particles and Links //
	std::vector< cDenseParticle* > Particle;
	std::list< cDenseLink* > Link;


	unsigned int CircleTexture;
	
	// Our partitioning grid //
	cGrid Grid;	
public:
	cDenseParticleSystem( );
	// {
				
		//LoadSystem();
		// Need image dimensions //
		//Grid.CreateGrid( ... );
	//}
	
	~cDenseParticleSystem() {
		// Remove Particles //
		for( size_t idx = 0; idx < Particle.size(); idx++ ) {
			delete Particle[idx];
		}
		
		// Remove Links //
		for( std::list< cDenseLink* >::iterator idx = Link.begin(); idx != Link.end(); idx++ ) {
			delete *idx;
		}
		
		glDeleteTextures( 1, &GroundTexID );
	//	SDL_FreeSurface( GroundImage );
	}
	
	// Given our Map file, load the needed information //
	void LoadSystem();
	
public:
	void Reset() {
		// Restore all particles //
		for( size_t idx = 0; idx < Particle.size(); idx++ ) {
			Particle[ idx ]->Reset();
		}		
	}
	
	void Step();
	
	void Draw();
	
	void Update( int X, int Width );
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Phiz_DenseParticleSystem_H__ //
// - ------------------------------------------------------------------------------------------ - //
