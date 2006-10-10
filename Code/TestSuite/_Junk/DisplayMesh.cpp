// - ------------------------------------------------------------------------------------------ - //
// DisplayMesh //
// - ------------------------------------------------------------------------------------------ - //
#include "DisplayMesh.h"
#include <Util/ScriptParser.h>
// - ------------------------------------------------------------------------------------------ - //
#include <sstream>
#include <fstream>
#include <iostream>
// - ------------------------------------------------------------------------------------------ - //
using namespace std;
// - ------------------------------------------------------------------------------------------ - //
bool cDisplayMesh::Load( const std::string& FileName )
{
	char Line[1024];

	cDisplayMesh::cDisplayNode TempDisNode;
	cDisplayMesh::cFace TempFace;

	//string MeshName = DirPrefix + FileName;
	
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
			else if( Token == "X" )
			{
				Text >> Token;
				TempDisNode.Pos.x = atof( Token.c_str() );
			}
			else if( Token == "Y" )
			{
				Text >> Token;
				TempDisNode.Pos.y = atof( Token.c_str() );
			}
			else if( Token == "H" )
			{
				Text >> Token;
				TempDisNode.Handle = atoi( Token.c_str() );
			}
			else if( Token == "P" )
			{
				Text >> Token;
				TempDisNode.Pivot = atoi( Token.c_str() );
				
				DisplayNode.push_back( TempDisNode );
			}
			// Face //
			// Vertex //
			else if( Token == "Va" )
			{
				Text >> Token;
				TempFace.Vertex.a = atoi( Token.c_str() );
			}
			else if( Token == "Vb" )
			{
				Text >> Token;
				TempFace.Vertex.b = atoi( Token.c_str() );
			}
			else if( Token == "Vc" )
			{
				Text >> Token;
				TempFace.Vertex.c = atoi( Token.c_str() );
			}
			// UV //
			else if( Token == "L" )
			{
				Text >> Token;
				TempFace.Layer = atoi( Token.c_str() );
			}
			else if( Token == "UVax" )
			{
				Text >> Token;
				TempFace.UV.a.x = atof( Token.c_str() );
			}
			else if( Token == "UVay" )
			{
				Text >> Token;
				TempFace.UV.a.y = atof( Token.c_str() );
			}
			else if( Token == "UVbx" )
			{
				Text >> Token;
				TempFace.UV.b.x = atof( Token.c_str() );
			}
			else if( Token == "UVby" )
			{
				Text >> Token;
				TempFace.UV.b.y = atof( Token.c_str() );
			}
			else if( Token == "UVcx" )
			{
				Text >> Token;
				TempFace.UV.c.x = atof( Token.c_str() );
			}
			else if( Token == "UVcy" )
			{
				Text >> Token;
				TempFace.UV.c.y = atof( Token.c_str() );
				
				Face.push_back( TempFace );
			}
			else if( Token == "T" )
			{
				Text >> Token;
				TextureName = Token;
			}
		}
	}
	return true;
}
// - ------------------------------------------------------------------------------------------ - //
void cDisplayMesh::Save( const std::string& FileName, std::vector< int > &DrawLayers ) {
	cScriptParser Script;

	for( size_t idx = 0; idx < DisplayNode.size(); idx++ )
	{
		Script.Append( "X", DisplayNode[idx].Pos.x );
		Script.Append( "Y", DisplayNode[idx].Pos.y );
		Script.Append( "H", DisplayNode[idx].Handle );
		Script.Append( "P", DisplayNode[idx].Pivot );
	}
	
	for( size_t i = 0; i < DrawLayers.size(); i++ )
	{
		for( size_t idx = 0; idx < Face.size(); idx++ )
		{
			if( Face[idx].Layer == DrawLayers[i] )
			{
				Script.Append( "L", Face[idx].Layer );
		
				Script.Append( "Va", Face[idx].Vertex.a );
				Script.Append( "Vb", Face[idx].Vertex.b );
				Script.Append( "Vc", Face[idx].Vertex.c );
		
				Script.Append( "UVax", Face[idx].UV.a.x );
				Script.Append( "UVay", Face[idx].UV.a.y );
				Script.Append( "UVbx", Face[idx].UV.b.x );
				Script.Append( "UVby", Face[idx].UV.b.y );
				Script.Append( "UVcx", Face[idx].UV.c.x );
				Script.Append( "UVcy", Face[idx].UV.c.y );
			}
		}
	}
	if( TextureIdx != -1 )
	{
		Script.Append( "T", TextureName );
	}

	Script.SaveFile( FileName );	
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
