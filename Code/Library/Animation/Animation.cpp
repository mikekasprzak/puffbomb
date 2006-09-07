// - ------------------------------------------------------------------------------------------ - //
// Animation //
// - ------------------------------------------------------------------------------------------ - //
#include "Animation.h"
// - ------------------------------------------------------------------------------------------ - //
#include <sstream>
#include <fstream>
#include <iostream>
#include <Graphics/TexturePool.h>
// - ------------------------------------------------------------------------------------------ - //
using namespace std;
// - ------------------------------------------------------------------------------------------ - //
bool cAnimation::Load( const std::string& FileName )
{	
	Frame.clear();
	
	cFrame TempFrame;
	ABCSet< int > TempVertIdx;
	ABCSet< Vector2D > TempUV;
	
	char Line[1024];

	ifstream InFile( FileName.c_str() );
	
	if( !InFile.good() ) {
		return false;	
	}
	
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
			// Display Node //
			else if( Token == "Vertex" )
			{
				Text >> Token;
				
				Vector2D Temp2D;
				Temp2D.x = atof( Token.c_str() );
				
				Text >> Token;
				Temp2D.y = atof( Token.c_str() );
				
				TempFrame.Vertex.push_back( cFrame::cVertex( Temp2D ) );									
			}
			else if( Token == "FVa" )
			{
				Text >> Token;
				TempVertIdx.a = atoi( Token.c_str() );
			}
			else if( Token == "FVb" )
			{
				Text >> Token;
				TempVertIdx.b = atoi( Token.c_str() );
			}
			else if( Token == "FVc" )
			{
				Text >> Token;
				TempVertIdx.c = atoi( Token.c_str() );
			}

			else if( Token == "FUVa" )
			{
				Text >> Token;
				TempUV.a.x = atof( Token.c_str() );

				Text >> Token;
				TempUV.a.y = atof( Token.c_str() );
			}
			else if( Token == "FUVb" )
			{
				Text >> Token;
				TempUV.b.x = atof( Token.c_str() );

				Text >> Token;
				TempUV.b.y = atof( Token.c_str() );
			}
			else if( Token == "FUVc" )
			{
				Text >> Token;
				TempUV.c.x = atof( Token.c_str() );

				Text >> Token;
				TempUV.c.y = atof( Token.c_str() );
				
				TempFrame.Face.push_back(
					cFrame::cFace( 
						ABCSet< int >( TempVertIdx ),
						ABCSet< Vector2D >( TempUV )
					)
				);
			}
			else if( Token == "Texture" )
			{
				Text >> Token;
				TempFrame.TextureId = TexturePool.Load( Token );
			}
			else if( Token == "Time" )
			{
				Text >> Token;
									
				Frame.push_back( cFrameInfo( Real( atoi( Token.c_str() ) ), cFrame( TempFrame ) ) );
				
				TempFrame.Vertex.clear();
				TempFrame.Face.clear();
			}
			else if( Token == "LoopPoint" )
			{
				Text >> Token;
				LoopPoint = atoi( Token.c_str() );
			}
			else if( Token == "Interpolate" )
			{
				Interpolate = true;
			}
		}
	}
	return true;
}
// - ------------------------------------------------------------------------------------------ - //
