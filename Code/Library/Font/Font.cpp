// - ------------------------------------------------------------------------------------------ - //
#include <Font/Font.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Util/Debug.h>
#include <Graphics/Gfx.h>
// - ------------------------------------------------------------------------------------------ - //
#include <sys/types.h>
#include <SDL/SDL.h>
#include <dirent.h>
// - ------------------------------------------------------------------------------------------ - //
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <Graphics/TexturePool.h>

#include <Util/ClassDesigner.h>
// - ------------------------------------------------------------------------------------------ - //
using namespace std;
// - ------------------------------------------------------------------------------------------ - //
void cFont::Load( const string &File )
{
	char Line[1024];
	
	cBlock TempBlock;
	cCharacter TempCharacter;
		
	ifstream InFile( File.c_str() );
	
	while( !InFile.eof() )
	{
		// Read a line from the file //
		InFile.getline( Line, sizeof( Line ) );
	
		// Populate and use a string stream to tokenize the data //
		stringstream Text;
		Text << Line;
						
		// Read all the tokens from that string //
		string Token;
		while( !Text.eof() )
		{
			// Read next token //
			Text >> Token;
			
			// Test to make sure this line/token isn't stupid and blank //
			if ( Token == "" ) {
				break;
			}
			// Test if a comment //
			else if ( Token[ 0 ] == '/' ) {
				break;
			}
			else if ( Token[ 0 ] == '#' ) {
				break;
			}

			else if( Token == "T" )
			{
				Text >> Token;
				TempCharacter.Texture = TexturePool.Load( Token ).Id;
				
				TextureWidth = TexturePool.GetWidth( Token );
				TextureHeight = TexturePool.GetHeight( Token );
			}
			else if( Token == "UVa" )
			{
				Text >> Token;
				Real TempUVa = atof( Token.c_str() );
				Text >> Token;								
				TempCharacter.UVa = Vector2D( TempUVa, atof( Token.c_str() ) );
			}
			else if( Token == "UVb" )
			{
				Text >> Token;
				Real TempUVb = atof( Token.c_str() );
				Text >> Token;								
				TempCharacter.UVb = Vector2D( TempUVb, atof( Token.c_str() ) );
			}
			else if( Token == "BL" )
			{
				Text >> Token;
				TempCharacter.BaseLine = atof( Token.c_str() );
			}
			else if( Token == "LK" )
			{
				Text >> Token;
				TempCharacter.LeftKerning = atof( Token.c_str() );
			}
			else if( Token == "RK" )
			{
				Text >> Token;
				TempCharacter.RightKerning = atof( Token.c_str() );
				
				TempBlock.Character.push_back( TempCharacter );
			}
			else if( Token == "Start" )
			{
				Text >> Token;
				TempBlock.Start = atoi( Token.c_str() );
			}
			else if( Token == "End" )
			{
				Block.push_back( TempBlock );
				TempBlock.Character.clear();
			}
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
cCharacter& cFont::FindCharacter( int CharacterIdx )
{
	for( size_t idx = 0; idx < Block.size(); ++idx )
	{
		if( CharacterIdx >= Block[idx].GetStart() && CharacterIdx < Block[idx].GetEnd() )
		{
			CharacterIdx -= Block[idx].GetStart();
			
			return Block[idx].Character[CharacterIdx];
		} 
	}
	return cCharacter::Dummy;
}
// - ------------------------------------------------------------------------------------------ - //
void cFont::Write( const std::string &Text, Vector3D Pos, const Real Size, const int Color, const int Alignment )
{
	unsigned int IndicesSize = Text.size() * 4;
	
	Vector3D Vertex[ IndicesSize ];
	Vector2D TexCoord[ IndicesSize ];

	unsigned int Indices[ IndicesSize ];
	
	unsigned int TextureID; 
	
	unsigned int VertIdx = 0;
	if( Alignment == LEFT_ALIGN )
	{
		
	}
	else
	{
		Real Offset = Real::Zero;
		
		for( size_t idx = 0; idx < Text.size(); ++idx )
		{
			cCharacter& TempChar = FindCharacter( Text[idx] );
			
			Offset -= TempChar.LeftKerning - TempChar.UVa.x;
			
			Vector2D UV = TempChar.UVb - TempChar.UVa;
			
			Offset += TempChar.RightKerning - TempChar.UVb.x;
	
			Offset += ( UV.x * Size ) + Real( 1.0 );
		}
		
		if( Alignment == CENTER_ALIGN )
		{
			Offset /= Real( 2 );
		}
		
		Pos.x -= Offset;
	}
	
	for( size_t idx = 0; idx < Text.size(); ++idx )
	{
		cCharacter& TempChar = FindCharacter( Text[idx] );
		
		TextureID = TempChar.Texture;
		
		Pos.x -= TempChar.LeftKerning - TempChar.UVa.x;
	
		Pos.y -= ( TempChar.UVb.y - TempChar.BaseLine ) * Size;
	
		Vector2D UV = TempChar.UVb - TempChar.UVa;

		Vector3D b = Pos + Vector3D( Real( 0.0 ), UV.y * Size, Real( 0.0 ) );
		Vector3D c = Pos + Vector3D( UV.x * Size, UV.y * Size, Real( 0.0 ) );
		Vector3D d = Pos + Vector3D( UV.x * Size, Real( 0.0 ), Real( 0.0 ) );

// - ------------------------------------------------------------------------------------------ - //
		Vertex[ VertIdx ] = b;
		Vertex[ VertIdx + 1 ] = Pos;
		Vertex[ VertIdx + 2 ] = d;
		Vertex[ VertIdx + 3 ] = c;
		
		Vector2D UVa = Vector2D::Zero;
		Vector2D UVb = Vector2D::Zero;
		if( TextureWidth != 0 && TextureHeight != 0 )
		{
			if( TextureWidth != 512 )  // because the font code is not based on UV coords (should be fixed later) //
			{
				Real TempWidthScale = Real( 512 ) / Real( TextureWidth );
				TextureWidth = Real( TextureWidth ) * TempWidthScale;
			}
			
			if( TextureHeight != 512 )  // because the font code is not based on UV coords (should be fixed later) //
			{
				Real TempHeightScale = Real( 512 ) / Real( TextureHeight );
				TextureHeight = Real( TextureHeight ) * TempHeightScale;
			}
			
			UVa.x = TempChar.UVa.x / Real( TextureWidth );
			UVb.x = TempChar.UVb.x / Real( TextureWidth );
			UVa.y = TempChar.UVa.y / Real( TextureHeight );
			UVb.y = TempChar.UVb.y / Real( TextureHeight );
		}
		TexCoord[ VertIdx ] = UVa;
		
		TexCoord[ VertIdx + 1 ].x = UVa.x;
		TexCoord[ VertIdx + 1 ].y = UVb.y;
		
		TexCoord[ VertIdx + 2 ] = UVb;
		
		TexCoord[ VertIdx + 3 ].x = UVb.x;
		TexCoord[ VertIdx + 3 ].y = UVa.y;
	
		Indices[ idx ] = idx;	
// - ------------------------------------------------------------------------------------------ - //
		Pos.y += ( TempChar.UVb.y - TempChar.BaseLine ) * Size;

		Pos.x += TempChar.RightKerning - TempChar.UVb.x;
	
		Pos.x += ( UV.x * Size ) + Real( 1.0 );
		
		VertIdx += 4;
// - ------------------------------------------------------------------------------------------ - //
	}

	for( size_t idx = Text.size(); idx < IndicesSize; ++idx )
	{
		Indices[ idx ] = idx;
	}
	
	if( Text.size() > 0 )
	{
			
		Gfx::DrawQuads(
			Vertex,
			TexCoord,
			Indices,
			IndicesSize,
			TextureID,
			Color
		);
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cFont::Write( const std::string &Text, const Vector2D Pos, const Real Size, const int Color, const int Alignment )
{
	Write( Text, Vector3D( Pos.x, Pos.y, 0.0 ), Size, Color, Alignment );
}
// - ------------------------------------------------------------------------------------------ - //
