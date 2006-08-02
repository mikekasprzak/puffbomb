// - ------------------------------------------------------------------------------------------ - //
#include <Font/Font.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Util/Debug.h>
#include <Phiz/SphereObject.h>
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
void cFont::Load( string &File )
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
				TempCharacter.Texture = TexturePool.Load( Token ).ID;
				
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
void cFont::Write( const std::string &Text, Vector3D Pos, const Real Size, const int Color )
{
//	glColor4ub( Color & 0xff, (Color>>8) & 0xff, (Color>>16) & 0xff, (Color>>24) & 0xff );
	
	unsigned int IndicesSize = Text.size() * 4;
	
	ABCDSet< Vector3D > Vertex[ Text.size() ];
	ABCDSet< Vector2D > TexCoord[ Text.size() ];
	unsigned int Indices[ IndicesSize ];
	
	unsigned int TextureID; 

	for( size_t idx = 0; idx < Text.size(); ++idx )
	{
		cCharacter& TempChar = FindCharacter( Text[idx] );
		
		//glBindTexture( GL_TEXTURE_2D, TempChar.Texture );
		
		TextureID = TempChar.Texture;
		
		Pos.x -= TempChar.LeftKerning - TempChar.UVa.x;
	
		Pos.y -= ( TempChar.UVb.y - TempChar.BaseLine ) * Size;
	
		Vector2D UV = TempChar.UVb - TempChar.UVa;

		Vector3D b = Pos + Vector3D( Real( 0.0 ), UV.y * Size, Real( 0.0 ) );
		Vector3D c = Pos + Vector3D( UV.x * Size, UV.y * Size, Real( 0.0 ) );
		Vector3D d = Pos + Vector3D( UV.x * Size, Real( 0.0 ), Real( 0.0 ) );

		//gfx::Quad( b, Pos, d, c, TempChar.UVa, TempChar.UVb );
// - ------------------------------------------------------------------------------------------ - //
		Vertex[ idx ].a = b;
		Vertex[ idx ].b = Pos;
		Vertex[ idx ].c = d;
		Vertex[ idx ].d = c;
		
		Vector2D UVa = Vector2D::Zero;
		Vector2D UVb = Vector2D::Zero;
		if( TextureWidth != 0 && TextureHeight != 0 )
		{
			UVa.x = TempChar.UVa.x / Real( TextureWidth );
			UVb.x = TempChar.UVb.x / Real( TextureWidth );
			UVa.y = TempChar.UVa.y / Real( TextureHeight );
			UVb.y = TempChar.UVb.y / Real( TextureHeight );
		}
		TexCoord[ idx ].a = UVa;
		
		TexCoord[ idx ].b.x = UVa.x;
		TexCoord[ idx ].b.y = UVb.y;
		
		TexCoord[ idx ].c = UVb;
		
		TexCoord[ idx ].d.x = UVb.x;
		TexCoord[ idx ].d.y = UVa.y;
	
		Indices[ idx ] = idx;	
// - ------------------------------------------------------------------------------------------ - //
		Pos.y += ( TempChar.UVb.y - TempChar.BaseLine ) * Size;

		Pos.x += TempChar.RightKerning - TempChar.UVb.x;
	
		Pos.x += ( UV.x * Size ) + Real( 1.0 );
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
void cFont::Write( const std::string &Text, Vector2D Pos, const Real Size, const int Color )
{
	Write( Text, Vector3D( Pos.x, Pos.y, 0.0 ), Size, Color );
}
// - ------------------------------------------------------------------------------------------ - //
