// - ------------------------------------------------------------------------------------------ - //
// LinearImage //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Util_LinearImage_H__
#define __Util_LinearImage_H__
// - ------------------------------------------------------------------------------------------ - //
#include <vector>
#include <Graphics/Gfx.h>
// - ------------------------------------------------------------------------------------------ - //
class cLinearImage
{
public:
	std::vector< unsigned int > Pixels;
	unsigned int Width;
	unsigned int Height;

	cLinearImage()
	{
		
	}

	void Init( const unsigned int _Width, const unsigned int _Height )
	{
		Pixels.resize( _Width * _Height );
		
		Width = _Width;
		Height = _Height;
		
		for( size_t idx = 0; idx < Pixels.size(); ++idx )
		{
			Pixels[ idx ] = gfx::RGBA( 0,0,0,255 );
		}
	}
	
	void Clear()
	{
		for( size_t idx = 0; idx < Pixels.size(); ++idx )
		{
			Pixels[ idx ] = gfx::RGBA( 0,0,0,255 );
		}
	}
	
	void Clear( size_t X, size_t Y, size_t _Width, size_t _Height )
	{
		for( size_t idx = X * Height; idx < ( _Width + X ) * Height; idx += Height )
		{
			for( size_t i = Y + idx; i < _Height + idx + Y; ++i )
			{
				Pixels[ i ] = gfx::RGBA( 0,0,0,255 );
			}
		}
	}
};

// - ------------------------------------------------------------------------------------------ - //
#endif // __Util_LinearImage_H__ //
// - ------------------------------------------------------------------------------------------ - //
