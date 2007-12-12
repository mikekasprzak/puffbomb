// - ------------------------------------------------------------------------------------------ - //
// Segment //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Particle2D_Segment_H__
#define __Library_Particle2D_Segment_H__
// - ------------------------------------------------------------------------------------------ - //
#include <algorithm>
#include <functional>
// - ------------------------------------------------------------------------------------------ - //
#include <ClassDesigner/Set.h>
// - ------------------------------------------------------------------------------------------ - //
class cSegment
{
public:
	int Start;
	int SegIdx;
	int Size;
	
	unsigned int IndicesIdx;
	unsigned int IndicesSize;
	unsigned int TextureID;
	
//	ABCDSet< Vector2D > UVPos;
//	ABCDSet< Vector2D > UV;
	
	//ABCSet< Vector2D > UVPos;
	//ABCSet< Vector2D >* UVTest;
	
	bool IsAdditive;
	bool DrawOnBlack;
	
	cSegment(
		const int _Start,
		const int _Size,
		const bool _IsAdditive,
		const bool _DrawOnBlack ) :
			Start( _Start ),
			SegIdx( _Start ),
			Size( _Start + _Size ),
			IndicesIdx( ( Start << 2 ) ),
			IndicesSize( ( Size << 2 ) ),
			IsAdditive( _IsAdditive ),
			DrawOnBlack( _DrawOnBlack )
	{
		
	}

	// - -------------------------------------------------------------------------------------- - //
	static bool compare_segment(const cSegment &a, const cSegment &b) 
	{
	    return a.Start < b.Start;
	}
	// - -------------------------------------------------------------------------------------- - //
	static bool less_segment(const cSegment *a, const cSegment *b) 
	{
	    return a->Start < b->Start;
	}
};

// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Particle2D_Segment_H__ //
// - ------------------------------------------------------------------------------------------ - //
