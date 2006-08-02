// - ------------------------------------------------------------------------------------------ - //
// Animation //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Rendo_Animation_H__
#define __Rendo_Animation_H__
// - ------------------------------------------------------------------------------------------ - //
#include "Frame.h"
#include <vector>
#include <string>
// - ------------------------------------------------------------------------------------------ - //
class cAnimation
{
public:
	class cFrameInfo
	{
	public:
		int Time;
		cFrame MyFrame;
		
	public:
		cFrameInfo() :
			Time( 0 )
		{
			
		}
		
		cFrameInfo( const int& _Time, const cFrame& _MyFrame ) :
			Time( _Time ),
			MyFrame( _MyFrame )
		{
				
		}
		
		inline int& GetTime()
		{
			return Time;	
		}
		inline cFrame& GetFrame()
		{
			return MyFrame;	
		}
	};
	
	int LoopPoint;
	bool Interpolate;
	std::vector< cFrameInfo > Frame;	

public:
	cAnimation() :
	LoopPoint( 0 ),
	Interpolate( false )
	{
		Frame.push_back( cFrameInfo() );
	}
	
	inline cAnimation( const std::string& FileName )
	{
		Load( FileName );	
	}
	
	bool Load( const std::string& FileName );
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Rendo_Animation_H__ //
// - ------------------------------------------------------------------------------------------ - //
