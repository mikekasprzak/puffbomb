// - ------------------------------------------------------------------------------------------ - //
// OldTexturePool //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Rendo_OldTexturePool_H__
#define __Rendo_OldTexturePool_H__
// - ------------------------------------------------------------------------------------------ - //
/*
#include <map>
#include <vector>
#include <string>

#include <Util/Debug.h>
*/
// - ------------------------------------------------------------------------------------------ - //
class OldTexturePool {
public:
/*	typedef unsigned int Texture;
	
	
	class cTextureInfo {
	public:
		std::string FileName;
		Texture TextureId;
		size_t Width;
		size_t Height;
		
	public:
		cTextureInfo() {
		}
		
		cTextureInfo( std::string _FileName, Texture _TextureId, size_t _Width, size_t _Height ) :
			FileName( _FileName ),
			TextureId( _TextureId ),
			Width( _Width ),
			Height( _Height )
		{
		}
	};
	
	static std::vector< std::string > SearchPath;
	static std::map< std::string, cTextureInfo > Pool;
	
public:
	static Texture Load( const std::string& _FileName );
	static size_t GetWidth( const std::string& _FileName );
	static size_t GetHeight( const std::string& _FileName );
	static void Clear();

public:
	static void AddSearchPath( const std::string& _Directory ) {
		SearchPath.push_back( _Directory );
	}
	
	static void ClearSearchPath( ) {
		SearchPath.clear();
	}*/
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Rendo_OldTexturePool_H__ //
// - ------------------------------------------------------------------------------------------ - //
