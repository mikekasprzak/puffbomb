// - ------------------------------------------------------------------------------------------ - //
// SolidParticleFactory //
// - ------------------------------------------------------------------------------------------ - //
#include <Animation/AnimationPool.h>
#include "SolidParticleFactory.h"

// If particle creation performance has a slight chunkyness it because the segment reserve is too low
// make it 2048 or more if needed.
#include <algorithm>
#include <functional>
// - ------------------------------------------------------------------------------------------ - //
#include <Engine2D.h>
// - ------------------------------------------------------------------------------------------ - //
SolidParticleFactory SolidParticle;
// - ------------------------------------------------------------------------------------------ - //
void SolidParticleFactory::Populate( int Num )
{

	Vertex.resize( Num << 2 );
	TexCoord.resize( Num << 2 );
	VertColor.resize( Num << 2 );
	Indices.resize( Num << 2 );

	cAnimation& DummyAni = AnimationPool.Load( "Dummy" );

	for( int idx = 0; idx < Num; idx++ )
	{
		Particles.push_back( cParticle() );
		
		Particles[ idx ].SetParticle(
			Vector2D( 0, 0 ),
			Vector2D( 0, 0 ),
			Vector2D( 0, 0 ),
			Vector2D( 0, 0 ),
			0,
			DummyAni,
			0,
			100
		);
	}

	Particles.resize( Num );
	
	Segment.reserve( 1024 );
}
// - ------------------------------------------------------------------------------------------ - //
int SolidParticleFactory::Allocate( const int SegmentSize, const bool _IsAdditive, const bool _DrawOnBlack )
{
	int ParticleIdx = 0;
	
	// Sort Segment //
	std::sort( Segment.begin(), Segment.end(), cSegment::less_segment );
	
	for( size_t idx = 0; idx < Segment.size(); idx++ )
	{
//		Log( LOG_HIGHEST_LEVEL, "Segment[ idx ] = " << Segment[ idx ].Start << " - " << Segment[ idx ].Size << " Segment.size() = " << Segment.size() );
		
		if( ( ParticleIdx == Segment[ idx ]->Start ) )
		{

		}
		else
		{
			if( size_t( ParticleIdx + SegmentSize ) < Particles.size() )
			{
				if( ( ParticleIdx + SegmentSize ) < Segment[ idx ]->Start )
				{

					//Log( LOG_HIGHEST_LEVEL, "( ParticleIdx + SegmentSize ) = " << ( ParticleIdx + SegmentSize ) );
					//Log( LOG_HIGHEST_LEVEL, "Segment[ idx + 1 ].Start = " << Segment[ idx + 1 ].Start );

					Segment.push_back( new cSegment( ParticleIdx, SegmentSize, _IsAdditive, _DrawOnBlack ) );					
					
					return Segment.size() - 1;
				}

			}
		}
		ParticleIdx = ( Segment[ idx ]->Size );
	}
	
	if( size_t( ParticleIdx + SegmentSize ) < Particles.size() )
	{
		Segment.push_back( new cSegment( ParticleIdx, SegmentSize, _IsAdditive, _DrawOnBlack ) );
		
		return Segment.size() - 1;
	}

	return -1;
}
// - ------------------------------------------------------------------------------------------ - //
void SolidParticleFactory::Release( const int SegIdx )
{
	Segment[ SegIdx ]->Start = Particles.size();
	
	std::sort( Segment.begin(), Segment.end(), cSegment::less_segment );
	
	delete Segment.back();
	
	Segment.pop_back();
}
// - ------------------------------------------------------------------------------------------ - //
void SolidParticleFactory::Clear()
{
	Segment.clear();
}
// - ------------------------------------------------------------------------------------------ - //
void SolidParticleFactory::Add(
	const Vector2D &_Pos,
	const Vector2D &_Velocity,
	const Vector2D &_Acceleration,
	const Vector2D &_Drift,
	const int _Life,
	cAnimation &_Animation,
	const int _Alpha,
	const int _Fade,
	const int SegIdx )
{
	if( Segment[ SegIdx ]->SegIdx < Segment[ SegIdx ]->Size )
	{
		Particles[ Segment[ SegIdx ]->SegIdx ].SetParticle( 
			_Pos,
			_Velocity,
			_Acceleration, 
			_Drift, 
			_Life,
			_Animation,
			_Alpha,
			_Fade
		);
	
		Segment[ SegIdx ]->SegIdx++;
		
		if( Segment[ SegIdx ]->SegIdx == Segment[ SegIdx ]->Size )
		{
			SetParticleData( SegIdx );
		}
	}
	else // Perhaps delete this later when all the particle effects are done //
	{
		Log( LOG_HIGHEST_LEVEL, "Error, did not allocate enough particles for the particle effect" );
	}
}
// - ------------------------------------------------------------------------------------------ - //
void SolidParticleFactory::SetParticleData( const int SegIdx )
{
	OffsetIdx = Segment[ SegIdx ]->IndicesIdx;

	for( int idx = Segment[ SegIdx ]->Start; idx < Segment[ SegIdx ]->Size; idx++ )
	{
		Indices[ OffsetIdx ] = OffsetIdx;
		Vertex[ OffsetIdx ] = (Particles[ idx ].Animator.CurDrawFrame->Vertex[ Particles[ idx ].Animator.CurDrawFrame->Face[ 0 ].VertexIdx.a ].Pos + Particles[ idx ].Pos).ToVector3D();
		TexCoord[ OffsetIdx ] = Particles[ idx ].Animator.CurDrawFrame->Face[ 0 ].UV.a;
		VertColor[ OffsetIdx ] = Gfx::RGBA( 255, 255, 255, Particles[ idx ].Alpha );
	
		++OffsetIdx;
		Indices[ OffsetIdx ] = OffsetIdx;
		Vertex[ OffsetIdx ] = (Particles[ idx ].Animator.CurDrawFrame->Vertex[ Particles[ idx ].Animator.CurDrawFrame->Face[ 0 ].VertexIdx.b ].Pos + Particles[ idx ].Pos).ToVector3D();
		TexCoord[ OffsetIdx ] = Particles[ idx ].Animator.CurDrawFrame->Face[ 0 ].UV.b;
		VertColor[ OffsetIdx ] = VertColor[ OffsetIdx - 1 ];
	
		++OffsetIdx;
		Indices[ OffsetIdx ] = OffsetIdx;
		Vertex[ OffsetIdx ] = (Particles[ idx ].Animator.CurDrawFrame->Vertex[ Particles[ idx ].Animator.CurDrawFrame->Face[ 0 ].VertexIdx.c ].Pos + Particles[ idx ].Pos).ToVector3D();
		TexCoord[ OffsetIdx ] = Particles[ idx ].Animator.CurDrawFrame->Face[ 0 ].UV.c;
		VertColor[ OffsetIdx ] = VertColor[ OffsetIdx - 1 ];
	
		++OffsetIdx;
		Indices[ OffsetIdx ] = OffsetIdx;
		Vertex[ OffsetIdx ] = (Particles[ idx ].Animator.CurDrawFrame->Vertex[ Particles[ idx ].Animator.CurDrawFrame->Face[ 1 ].VertexIdx.c ].Pos + Particles[ idx ].Pos).ToVector3D();
		TexCoord[ OffsetIdx ] = Particles[ idx ].Animator.CurDrawFrame->Face[ 1 ].UV.c;
		VertColor[ OffsetIdx ] = VertColor[ OffsetIdx - 1 ];
	
		++OffsetIdx;
	}
	Segment[ SegIdx ]->TextureID = Particles[ Segment[ SegIdx ]->Start ].Animator.CurDrawFrame->TextureId;
}
// - ------------------------------------------------------------------------------------------ - //
void SolidParticleFactory::Step()
{
	// For every segment //
	for( size_t SegIdx = 0; SegIdx < Segment.size(); SegIdx++ )
	{
		// Calculate first polygon co-ordinate offset //
		OffsetIdx = Segment[ SegIdx ]->IndicesIdx;
		// For every part of a segment //
		for( int idx = Segment[ SegIdx ]->Start; idx < Segment[ SegIdx ]->SegIdx; idx++ )
		{
			// Step the physics of the particle (move it based on all it's factors) //
			Particles[ idx ].Step();
			
			// Do collision //
			SolveVsImpulses( Particles[ idx ] );
			SolveVsObjects( Particles[ idx ] );
			SolveVsStatics( Particles[ idx ] );
			
			// If the particle dies, remove it's particle //
			if( Particles[ idx ].Life <= 0 )
			{
				while( Particles[ idx ].Life <= 0 && Segment[ SegIdx ]->Start < Segment[ SegIdx ]->SegIdx )
				{
					Segment[ SegIdx ]->IndicesSize -= 4;
					Segment[ SegIdx ]->SegIdx--;
	
					Particles[ idx ] = Particles[ Segment[ SegIdx ]->SegIdx ];
					
					Particles[ idx ].Step();
				}
			}
/*	
			Vertex[ OffsetIdx ].x += Particles[ idx ].Velocity.x;  // this made the particles twitch once and a while
			Vertex[ OffsetIdx ].y += Particles[ idx ].Velocity.y;
*/
			
			// Generate co-ordinates for the polygons in a particle //			
			Vertex[ OffsetIdx ] = (Particles[ idx ].Animator.CurDrawFrame->Vertex[ Particles[ idx ].Animator.CurDrawFrame->Face[ 0 ].VertexIdx.a ].Pos + Particles[ idx ].Pos).ToVector3D();
			VertColor[ OffsetIdx ] = Gfx::RGBA( 255, 255, 255, Particles[ idx ].Alpha );
		
			++OffsetIdx;
			Vertex[ OffsetIdx ] = (Particles[ idx ].Animator.CurDrawFrame->Vertex[ Particles[ idx ].Animator.CurDrawFrame->Face[ 0 ].VertexIdx.b ].Pos + Particles[ idx ].Pos).ToVector3D();
			VertColor[ OffsetIdx ] = VertColor[ OffsetIdx - 1 ];
		
			++OffsetIdx;
			Vertex[ OffsetIdx ] = (Particles[ idx ].Animator.CurDrawFrame->Vertex[ Particles[ idx ].Animator.CurDrawFrame->Face[ 0 ].VertexIdx.c ].Pos + Particles[ idx ].Pos).ToVector3D();
			VertColor[ OffsetIdx ] = VertColor[ OffsetIdx - 1 ];
		
			++OffsetIdx;
			Vertex[ OffsetIdx ] = (Particles[ idx ].Animator.CurDrawFrame->Vertex[ Particles[ idx ].Animator.CurDrawFrame->Face[ 1 ].VertexIdx.c ].Pos + Particles[ idx ].Pos).ToVector3D();
			VertColor[ OffsetIdx ] = VertColor[ OffsetIdx - 1 ];
		
			++OffsetIdx;
		}
		
		// If the segment dies, remove the segment //
		if( Segment[ SegIdx ]->SegIdx == Segment[ SegIdx ]->Start )
		{
			Release( SegIdx );
			
			SegIdx--;
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void SolidParticleFactory::Draw()
{
	int AdditiveArray[ Segment.size() ];
	size_t AdditiveSize = 0;
	
	for( size_t SegIdx = 0; SegIdx < Segment.size(); SegIdx++ )
	{
		if( Segment[ SegIdx ]->IsAdditive )
		{
			AdditiveArray[ AdditiveSize ] = SegIdx;
			
			AdditiveSize++;
		}
		else
		{
			Gfx::DrawQuads(
				&Vertex[ 0 ],
				&TexCoord[ 0 ],
				&VertColor[ 0 ],
				&Indices[ Segment[ SegIdx ]->IndicesIdx ],
				Segment[ SegIdx ]->IndicesSize - Segment[ SegIdx ]->IndicesIdx,
				Segment[ SegIdx ]->TextureID
			);
		}
	}
	// Cheezy additive sort hack //
	for( size_t SegIdx = 0; SegIdx < AdditiveSize; SegIdx++ )
	{
		// Enables additive blending //
		Gfx::AddBlend();

		Gfx::DrawQuads(
			&Vertex[ 0 ],
			&TexCoord[ 0 ],
			&VertColor[ 0 ],
			&Indices[ Segment[ AdditiveArray[ SegIdx ] ]->IndicesIdx ],
			Segment[ AdditiveArray[ SegIdx ] ]->IndicesSize - Segment[ AdditiveArray[ SegIdx ] ]->IndicesIdx,
			Segment[ AdditiveArray[ SegIdx ] ]->TextureID
		);
		
		// Disables additive blending //
		Gfx::StandardBlend();
	}
}
// - ------------------------------------------------------------------------------------------ - //
void SolidParticleFactory::SolveVsObjects( cParticle& Particle ) {
	if( Engine2D::cEngine2D::Current ) {
		// Calculate bounding rectangle of particle  //
		
		
		// For every dynamic component //
		for ( size_t idx = 0; idx < Engine2D::cEngine2D::Current->DynamicComponent.size(); idx++ ) {
			const Engine2D::cDynamicComponent& MyComponent = *(Engine2D::cEngine2D::Current->DynamicComponent[ idx ]);
			
			// Early out Active //
			if ( !MyComponent.IsActive() ) 
				continue;
			
			// Early out Rectangle //
			
			// Test all speheres against point //
			for ( size_t idx2 = 0; idx2 < MyComponent.Body.SphereSize(); idx2++ ) {
				const Engine2D::cSphere& MySphere = MyComponent.Body.Sphere( idx2 );
				const int& Index = MySphere.Index;
	
				// Sum of Radius //				
				Real RadiusSum = MySphere.Radius + Real( 0 );
				Real RadiusSumSquared = RadiusSum * RadiusSum;
	
				// Optimized Verlet with Square Root Approximation //
				Vector2D Ray = Particle.Pos - MyComponent.Body.Nodes.Pos( Index );
				
				// Bail if not touching //
				if ( RadiusSumSquared < Ray.MagnitudeSquared() ) {
					continue;
				}
	
				// Bail if he's a sensor //
				if ( MySphere.Flags.Sensor() ) {
					continue;
				}
				
				// Solve (Massless with square root approximation) //
				Real Divisor = ( (Ray * Ray) + (RadiusSumSquared) ) - Real( 0.5 );
				if ( Divisor.IsZero() )
					continue;
	
				Ray *= (RadiusSumSquared) / Divisor;
	
				Particle.Pos += Ray;
			}
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void SolidParticleFactory::SolveVsStatics( cParticle& Particle ) {
	if( Engine2D::cEngine2D::Current ) {
		// Calculate bounding rectangle of particle  //
		

		// For every static Object //
		for ( size_t idx = 0; idx < Engine2D::cEngine2D::Current->StaticObjectInstance.size(); idx++ ) {
			const Engine2D::cStaticBody2D& MyStatic = Engine2D::cEngine2D::Current->StaticObjectInstance[ idx ].Object->Body;
			const Vector2D _Offset = Engine2D::cEngine2D::Current->StaticObjectInstance[ idx ].Pos;

			bool Inside = false;
			
			// See if sphere is inside any polygon //
			for ( size_t idx2 = 0; idx2 < MyStatic.Polygon.size(); idx2++ ) {
				// Rectangles throw away test //
				//if ( (MyStatic.Polygon[ idx2 ].BoundingRect + _Offset) == SphereRect[idx] )
				{
					// The number of sides found, so far //
					size_t SideCount = 0;

					// An optimization.  As long as it's only 1 more, we can re use if to the end //
					Vector2D ToCorner;
					
					// Check if we're inside all sides except the last //
					for ( size_t idx3 = 0; idx3 < MyStatic.Polygon[ idx2 ].Index.size() - 1; idx3++ ) {
						Vector2D Segment =
							MyStatic.Nodes.Pos( MyStatic.Polygon[ idx2 ].Index[idx3 + 1] ) -
							MyStatic.Nodes.Pos( MyStatic.Polygon[ idx2 ].Index[idx3] );
						
						ToCorner = MyStatic.Nodes.Pos( MyStatic.Polygon[ idx2 ].Index[idx3 + 1] ) + _Offset - Particle.Pos;
						
						// If Inside this side //
						if ( (-Segment.Tangent()) * ToCorner > Real::Zero )
							SideCount++;
						else
							break;
					}

					// If we bailed early, we're not inside //
					if ( SideCount != MyStatic.Polygon[ idx2 ].Index.size() - 1 )
						continue;
						
					// Test last side //
					Vector2D Segment =
						MyStatic.Nodes.Pos( MyStatic.Polygon[ idx2 ].Index[0] ) -
						MyStatic.Nodes.Pos( MyStatic.Polygon[ idx2 ].Index[SideCount] );
					
					// If you are inside, great!  That's all we care about. //
					if ( (-Segment.Tangent()) * ToCorner > Real::Zero ) {
						Inside = true;
						break;
					}
				}
			}
			
			// If you are (confirmed), find the closest point on the nearest edge //
			if ( Inside ) {
				bool FoundPoint = false;
				Vector2D Push;
				Real Mag;

				// If none found, search all edges for nearest //
				if ( !FoundPoint ) {
					for ( size_t idx2 = 0; idx2 < MyStatic.Edge.size(); idx2++ ) {
						// Motion Vector half space throw away test (Bad, as it allows perfect squishes to go through) //
						//if ( Nodes.Velocity( Sphere[ SphereIndex[idx] ].Index ) * _Vs.Edge[idx2].Normal <= Real::Zero )
						{
							Vector2D PointOnEdge = MyStatic.Edge[idx2].ClosestPoint( MyStatic.Nodes, Particle.Pos - _Offset ) + _Offset;
							
							if ( !FoundPoint ) {
								Push = PointOnEdge - Particle.Pos;
								Mag = Push.MagnitudeSquared();
								FoundPoint = true;
							}
							else {
								Vector2D ToEdge = PointOnEdge - Particle.Pos;
								Real NewMag = ToEdge.MagnitudeSquared();
								
								if ( NewMag < Mag ) {
									Push = ToEdge;
									Mag = NewMag;
								}
							}
						}
					}
					
				}
				
				// Solve for the found edge //
				if ( FoundPoint ) {
					// Solve //
					//Push += (Push.Normal() * Sphere[ SphereIndex[idx] ].Radius);
					Particle.Pos += Push;// - (((Particle.Pos - Particle.Old) * Push.Normal()));//*Push.Normal());
				}
				else {
					Log( 10, "ERROR!!!! NO EXIT POINT FOUND!!!!! *********" );
				}
			}
		}
	}	
}
// - ------------------------------------------------------------------------------------------ - //
void SolidParticleFactory::SolveVsImpulses( cParticle& Particle ) {
	if( Engine2D::cEngine2D::Current ) {
		// Calculate bounding rectangle of particle  //
		

		// For every impulse //
		for ( size_t idx = 0; idx < Engine2D::cEngine2D::Current->Impulse.size(); idx++ ) {
			const Engine2D::cImpulse& MyImpulse = Engine2D::cEngine2D::Current->Impulse[ idx ];

			// Calculate the force applied by the impulse //
			Vector2D Force = MyImpulse.GetForce( Particle.Pos );// * Nodes.InvMass( Sphere[ idx ].Index );
			// If the force is worth caring about //
			if ( !Force.IsZero() ) {
				Particle.Pos += Force;
			}
		}	
	}
}
// - ------------------------------------------------------------------------------------------ - //
