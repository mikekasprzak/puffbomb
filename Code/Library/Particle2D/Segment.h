// - ------------------------------------------------------------------------------------------ - //
// Segment //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Particle2D_Segment_H__
#define __Library_Particle2D_Segment_H__
// - ------------------------------------------------------------------------------------------ - //
class cSegment
{
public:
	int Start;
	int SegIdx;
	int Size;
	bool IsAdditive;
	
	unsigned int IndicesIdx;
	unsigned int IndicesSize;
	unsigned int TextureID;
	
	cSegment(
		const int _Start,
		const int _Size,
		const bool _IsAdditive ) :
			Start( _Start ),
			SegIdx( _Start ),
			Size( _Start + _Size ),
			IsAdditive( _IsAdditive ),
			IndicesIdx( ( Start << 2 ) ),
			IndicesSize( ( Size << 2 ) )
	{
		
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Particle2D_Segment_H__ //
// - ------------------------------------------------------------------------------------------ - //
