// - ------------------------------------------------------------------------------------------ - //
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include "../../Library/Util/String.h"

#include "Model.h"
// - ------------------------------------------------------------------------------------------ - //
using namespace std;
// - ------------------------------------------------------------------------------------------ - //
cModel::~cModel() {
//	Log( LOG_HIGHEST_LEVEL, endl << "[ Model Destructor ] " );
//	Log( LOG_HIGHEST_LEVEL, "Objects: " << Object.size() );
//	Log( LOG_HIGHEST_LEVEL, "TextureCoords: " << TextureCoord.size() );
//	Log( LOG_HIGHEST_LEVEL, "VertexNormals: " << VertexNormal.size() );
}
// - ------------------------------------------------------------------------------------------ - //
cModel::cObject::~cObject() {
//	Log( LOG_HIGHEST_LEVEL, endl << "[ Model/Object Destructor ] ***************" );
//	Log( LOG_HIGHEST_LEVEL, "Vertices: " << Vertex.size() );
//	Log( LOG_HIGHEST_LEVEL, "Groups: " << Group.size() );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cModel::clear()
{
	for( size_t idx = 0; idx < Object.size(); ++idx ) {
		Object[idx].clear();
	}		
	Object.clear();

	TextureCoord.clear();
	VertexNormal.clear();

}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
/*void cModel::Draw( const cLevelData* MyModel )
{
	// Draws 3d model //
	for( size_t ObjectIndex = 0; ObjectIndex < Object.size(); ++ObjectIndex )
	{
		for( size_t GroupIndex = 0; GroupIndex < Object[ObjectIndex].Group.size(); ++GroupIndex )
		{
			// Binds the texture to the next set of polygons that are to be drawn //
			if( Object[ ObjectIndex ].Group[ GroupIndex ].TextureID != 0 )
			{
				glBindTexture( GL_TEXTURE_2D, Object[ObjectIndex].Group[ GroupIndex ].TextureID );
			}
//			glBegin(GL_POLYGON);
			
			// Draw each face //
			for( 
				size_t FaceIndex = 0;
				FaceIndex < Object[ObjectIndex].Group[ GroupIndex ].Face.size();
				++FaceIndex
				)
			{										
			//	gfx::Draw3DModel( ObjectIndex, GroupIndex, FaceIndex, MyModel );
			}			
//			glEnd();	
		}
	}
}*/
// - ------------------------------------------------------------------------------------------ - //
void cModel::Load( const std::string& FileName )
{
	char Line[1024];
	
	PathName = FileName;
	
	int Stage = 1;
	
	float Scale = 41.0;

	cModel::cObject myObject;
	cModel::cObject::cGroup myGroup;
		
	ifstream InFile( FileName.c_str() );
	
	//Vector3D TempVec3D;
	vector<float> TempValues;
	vector<int> TempIntValues;
//	Log( LOG_HIGHEST_LEVEL, "Finished Creating Temp 3D Objects..." ); 

	while( !InFile.eof() ) {
		// Read a line from the file //
		InFile.getline( Line, sizeof( Line ) );
	
		// Populate and use a string stream to tokenize the data //
		stringstream Text;
		Text << Line;
		
		
		// Read all the tokens from that string //
		string Token;
		
		while( !Text.eof() ) {
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

			// Tests to see if what the numbers should be stored in //
			if ( Token == "Vertices" )
			{
				if( Stage == 5 )
				{
					if( myGroup.size() > 0 )
					{
						myObject.Group.push_back( myGroup );
						myGroup.clear();
					}
					Object.push_back( myObject );
					
					myObject.clear();
				}
				
				Stage = 1;
			}
			else if ( Token == "TextureCoord" ) {
				Stage = 2;
			}
			else if ( Token == "VertexNormal" ) {
				Stage = 3;
			}
			else if ( Token == "TextureName" ) {
				Stage = 4;
				Text.clear();
				
				// Read a line from the file //
				InFile.getline( Line, sizeof( Line ) );

				Token = Line;
				
				if( Token == "Material" )
				{
					break;
				}
				else if( Token == "FUN" )
				{
					break;
				}
				else if ( Token[ 0 ] == '/' )
				{
					break;
				}
				else if ( Token[ 0 ] == '#' )
				{
					break;
				}
				if( myGroup.size() > 0 )
				{
					myObject.Group.push_back( myGroup );
					myGroup.clear();
				}

				//myGroup.TextureID = TexturePool.Load( Token );
				myGroup.TextureName = Token;

				break;
			} 
			else if( Token == "FUN" ) {
				Stage = 5;
			}
			else if ( Token == "NoCollision" ) {
//				Log( LOG_HIGHEST_LEVEL, 
//					"Disabled Collision Generation for this Shape (" << 
//					myGroup.NoCollision << ")" ); 
				myGroup.NoCollision = true;
			}

//			// ?? //
			if( Stage != 4 ) {
				TempValues.push_back( atof( Token.c_str() ) );
				TempIntValues.push_back( atoi( Token.c_str() ) );
			}
		}
		
		if( TempValues.size() >= 3 ) {
			switch( Stage ) {
				// - -------------------------------------------------------------------------- - //
				case 1:  // Vertices
					myObject.Vertex.push_back(
						ABCSet< float >(
							TempValues[0] * Scale,
							TempValues[2] * Scale,
							TempValues[1] * Scale
							)
						);
/*
					myObject.Vertex.push_back(
						TempVec3D.Set(
							TempValues[0] * Scale,
							TempValues[2] * Scale,
							TempValues[1] * Scale
							)
						);*/
				break;	
				// - -------------------------------------------------------------------------- - //
				case 2:  // TextureCoord
				{
					float Invert;
					
					Invert = ( TempValues[1] - float(1.0) ) * float(-1.0);
					
					if( Invert < 0.0 ) {
						Invert *= float( -1.0 );
					}
			
					TextureCoord.push_back(
						ABCSet< float >(
							TempValues[0],
							Invert,
							TempValues[2]
							)
						);

/*

					TextureCoord.push_back(
						TempVec3D.Set(
							TempValues[0],
							Invert,
							TempValues[2]
							)
						);
*/
					break;
				}
				// - -------------------------------------------------------------------------- - //
				case 3:  // VertexNormal
				{
					VertexNormal.push_back(
						ABCSet< float >(
							TempValues[0],
							TempValues[2],
							TempValues[1]
							) 
						);

/*
					VertexNormal.push_back(
						TempVec3D.Set(
							TempValues[0],
							TempValues[2],
							TempValues[1]
							) 
						);
*/
					break;
				}
				// - -------------------------------------------------------------------------- - //
				case 4:  // TextureName

				break;	
				// - -------------------------------------------------------------------------- - //
				case 5:  // FUN
				{
					// - ---------------------------------------------------------------------- - //
					myGroup.Face.push_back( cObject::cGroup::cFace() );
					
					myGroup.Face.back().Vertex = ABCSet<int>(
						(int)TempIntValues[0],
						(int)TempIntValues[4],
						(int)TempIntValues[8]
						);

					myGroup.Face.back().UV = ABCSet<int>(
						(int)TempIntValues[1],
						(int)TempIntValues[5],
						(int)TempIntValues[9]
						);

					myGroup.Face.back().Normal = ABCSet<int>(
						(int)TempIntValues[2],
						(int)TempIntValues[6],
						(int)TempIntValues[10]
						);

					myGroup.Face.back().VertColor = ABCSet<unsigned int>(
						(unsigned int)TempIntValues[3],
						(unsigned int)TempIntValues[7],
						(unsigned int)TempIntValues[11]
						);

/*
					myGroup.Face.back().Vertex = ABCSet<int>(
						(int)TempValues[0],
						(int)TempValues[3],
						(int)TempValues[6]
						);

					myGroup.Face.back().UV = ABCSet<int>(
						(int)TempValues[1],
						(int)TempValues[4],
						(int)TempValues[7]
						);

					myGroup.Face.back().Normal = ABCSet<int>(
						(int)TempValues[2],
						(int)TempValues[5],
						(int)TempValues[8]
						);
*/

					// - ---------------------------------------------------------------------- - //
				}
				break;	
				// - -------------------------------------------------------------------------- - //
			}
		}

		TempValues.clear();
		TempIntValues.clear();
	}

	if( myGroup.size() > 0 )
	{
		myObject.Group.push_back( myGroup );
		myGroup.clear();
	}
	
	Object.push_back( myObject );
	myObject.clear();

//	Log( LOG_HIGHEST_LEVEL, "Finished Loading Model File" );
}
// - ------------------------------------------------------------------------------------------ - //
#include <algorithm>
#include <functional>
// - ------------------------------------------------------------------------------------------ - //
bool compare_vert(const cModel::cObject &a, const cModel::cObject &b) 
{
    return a.Vertex[ 0 ].c < b.Vertex[ 0 ].c;
}
// - ------------------------------------------------------------------------------------------ - //
void cModel::SaveBin( char* NewName )
{
	std::sort( Object.begin(), Object.end(), compare_vert );
		

/*	
	std::string NewName = String::DirectorySlash( PathName )
						+ String::BaseName( PathName )
						+ ".bin"
						+ String::LastExtension( PathName );
	
	std::ofstream outfile ( NewName.c_str(), ofstream::binary );
	*/
	std::ofstream outfile ( NewName, ofstream::binary );

	cToMesh3d TempMesh3d;
	
	unsigned int IndiciesIdx;
	
	unsigned int ObjNum = 0;
	for( size_t obj = 0; obj < Object.size(); ++obj )
	{
		ObjNum += Object[obj].Group.size();
	}
	
	outfile.write( (char*)&ObjNum, sizeof( unsigned int ) );

	if( Object.size() > 0 )
	{
		if( Object[0].Group.size() > 0 )
		{
			// Arguments NoCollision, etc //  // This will only support 1 argument per file, else were fucked for doing inverted normals //
			unsigned int Arguments = Object[0].Group[ 0 ].NoCollision;
			outfile.write( (char*)&Arguments, sizeof( unsigned int ) );
		}
	}

	for( size_t obj = 0; obj < Object.size(); ++obj )
	{
//		unsigned int LookupSize = Object[obj].Group.size();
//		outfile.write( (char*)&LookupSize, sizeof( unsigned int ) );
	
		for( size_t lookup = 0; lookup < Object[obj].Group.size(); ++lookup )
		{
			IndiciesIdx = 0;
			//TempMesh3d.TextureID = Object[obj].Group[ lookup ].TextureID;
			
			for( 
				size_t idx = 0;
				idx < Object[obj].Group[ lookup ].Face.size();
				++idx
				)
			{
				bool IsDupe = false;
/*				ABCSet< float > TempVertex = ABCSet< float >(
						Object[obj].Vertex[Object[obj].Group[lookup].Face[idx].Vertex.a].x,
						Object[obj].Vertex[Object[obj].Group[lookup].Face[idx].Vertex.a].y,
						-Object[obj].Vertex[Object[obj].Group[lookup].Face[idx].Vertex.a].z
					);
				ABCSet< float > TempVertexNormal = ABCSet< float >(
						VertexNormal[Object[obj].Group[lookup].Face[idx].Normal.a].x,
						VertexNormal[Object[obj].Group[lookup].Face[idx].Normal.a].y,
						VertexNormal[Object[obj].Group[lookup].Face[idx].Normal.a].z
					);
				unsigned int TempVertexColor = Object[obj].Group[lookup].Face[idx].VertColor.a;
				ABSet< float > TempTextureCoord = ABSet< float >(
						TextureCoord[Object[obj].Group[lookup].Face[idx].UV.a].x,
						TextureCoord[Object[obj].Group[lookup].Face[idx].UV.a].y
					);
					*/
					
				ABCSet< float > TempVertex = ABCSet< float >(
						Object[obj].Vertex[Object[obj].Group[lookup].Face[idx].Vertex.a].a,
						Object[obj].Vertex[Object[obj].Group[lookup].Face[idx].Vertex.a].b,
						-Object[obj].Vertex[Object[obj].Group[lookup].Face[idx].Vertex.a].c
					);
				ABCSet< float > TempVertexNormal = ABCSet< float >(
						VertexNormal[Object[obj].Group[lookup].Face[idx].Normal.a].a,
						VertexNormal[Object[obj].Group[lookup].Face[idx].Normal.a].b,
						VertexNormal[Object[obj].Group[lookup].Face[idx].Normal.a].c
					);
				unsigned int TempVertexColor = Object[obj].Group[lookup].Face[idx].VertColor.a;
				ABSet< float > TempTextureCoord = ABSet< float >(
						TextureCoord[Object[obj].Group[lookup].Face[idx].UV.a].a,
						TextureCoord[Object[obj].Group[lookup].Face[idx].UV.a].b
					);
				for( size_t DupeIdx = 0; DupeIdx < TempMesh3d.Indicies.size(); ++DupeIdx )
				{
					if( TempMesh3d.Vertex[ TempMesh3d.Indicies[ DupeIdx ] ] == TempVertex )
					{
						if( TempMesh3d.VertexNormal[ TempMesh3d.Indicies[ DupeIdx ] ] == TempVertexNormal )
						{
							if( TempMesh3d.VertexColor[ TempMesh3d.Indicies[ DupeIdx ] ] == TempVertexColor )
							{
								if( TempMesh3d.TextureCoord[ TempMesh3d.Indicies[ DupeIdx ] ] == TempTextureCoord )
								{
									IsDupe = true;
									TempMesh3d.Indicies.push_back( TempMesh3d.Indicies[ DupeIdx ] );
									break;
								}
							}
						}
					}
				}
				if( !IsDupe )
				{
					TempMesh3d.Vertex.push_back( TempVertex	);
					TempMesh3d.VertexNormal.push_back( TempVertexNormal	);
					TempMesh3d.VertexColor.push_back( TempVertexColor );
					TempMesh3d.TextureCoord.push_back( TempTextureCoord );
					
					TempMesh3d.Indicies.push_back( IndiciesIdx );
					IndiciesIdx++;
				}
				
				IsDupe = false;
				TempVertex = ABCSet< float >(
						Object[obj].Vertex[Object[obj].Group[lookup].Face[idx].Vertex.b].a,
						Object[obj].Vertex[Object[obj].Group[lookup].Face[idx].Vertex.b].b,
						-Object[obj].Vertex[Object[obj].Group[lookup].Face[idx].Vertex.b].c
					);
				TempVertexNormal = ABCSet< float >(
						VertexNormal[Object[obj].Group[lookup].Face[idx].Normal.b].a,
						VertexNormal[Object[obj].Group[lookup].Face[idx].Normal.b].b,
						VertexNormal[Object[obj].Group[lookup].Face[idx].Normal.b].c
					);
				TempVertexColor = Object[obj].Group[lookup].Face[idx].VertColor.b;
				TempTextureCoord = ABSet< float >(
						TextureCoord[Object[obj].Group[lookup].Face[idx].UV.b].a,
						TextureCoord[Object[obj].Group[lookup].Face[idx].UV.b].b
					);
				for( size_t DupeIdx = 0; DupeIdx < TempMesh3d.Indicies.size(); ++DupeIdx )
				{
					if( TempMesh3d.Vertex[ TempMesh3d.Indicies[ DupeIdx ] ] == TempVertex )
					{
						if( TempMesh3d.VertexNormal[ TempMesh3d.Indicies[ DupeIdx ] ] == TempVertexNormal )
						{
							if( TempMesh3d.VertexColor[ TempMesh3d.Indicies[ DupeIdx ] ] == TempVertexColor )
							{
								if( TempMesh3d.TextureCoord[ TempMesh3d.Indicies[ DupeIdx ] ] == TempTextureCoord )
								{
									IsDupe = true;
									TempMesh3d.Indicies.push_back( TempMesh3d.Indicies[ DupeIdx ] );
									break;
								}
							}
						}
					}
				}
				if( !IsDupe )
				{
					TempMesh3d.Vertex.push_back( TempVertex	);
					TempMesh3d.VertexNormal.push_back( TempVertexNormal	);
					TempMesh3d.VertexColor.push_back( TempVertexColor );
					TempMesh3d.TextureCoord.push_back( TempTextureCoord );
					
					TempMesh3d.Indicies.push_back( IndiciesIdx );
					IndiciesIdx++;
				}
				
				IsDupe = false;
				TempVertex = ABCSet< float >(
						Object[obj].Vertex[Object[obj].Group[lookup].Face[idx].Vertex.c].a,
						Object[obj].Vertex[Object[obj].Group[lookup].Face[idx].Vertex.c].b,
						-Object[obj].Vertex[Object[obj].Group[lookup].Face[idx].Vertex.c].c
					);
				TempVertexNormal = ABCSet< float >(
						VertexNormal[Object[obj].Group[lookup].Face[idx].Normal.c].a,
						VertexNormal[Object[obj].Group[lookup].Face[idx].Normal.c].b,
						VertexNormal[Object[obj].Group[lookup].Face[idx].Normal.c].c
					);
				TempVertexColor = Object[obj].Group[lookup].Face[idx].VertColor.c;
				TempTextureCoord = ABSet< float >(
						TextureCoord[Object[obj].Group[lookup].Face[idx].UV.c].a,
						TextureCoord[Object[obj].Group[lookup].Face[idx].UV.c].b
					);

				for( size_t DupeIdx = 0; DupeIdx < TempMesh3d.Indicies.size(); ++DupeIdx )
				{
					if( TempMesh3d.Vertex[ TempMesh3d.Indicies[ DupeIdx ] ] == TempVertex )
					{
						if( TempMesh3d.VertexNormal[ TempMesh3d.Indicies[ DupeIdx ] ] == TempVertexNormal )
						{
							if( TempMesh3d.VertexColor[ TempMesh3d.Indicies[ DupeIdx ] ] == TempVertexColor )
							{
								if( TempMesh3d.TextureCoord[ TempMesh3d.Indicies[ DupeIdx ] ] == TempTextureCoord )
								{
									IsDupe = true;
									TempMesh3d.Indicies.push_back( TempMesh3d.Indicies[ DupeIdx ] );
									break;
								}
							}
						}
					}
				}
				if( !IsDupe )
				{
					TempMesh3d.Vertex.push_back( TempVertex	);
					TempMesh3d.VertexNormal.push_back( TempVertexNormal	);
					TempMesh3d.VertexColor.push_back( TempVertexColor );
					TempMesh3d.TextureCoord.push_back( TempTextureCoord );
					
					TempMesh3d.Indicies.push_back( IndiciesIdx );
					IndiciesIdx++;
				}
			}
			
			// Vertex's //
			unsigned int VertSize = TempMesh3d.Vertex.size();
			outfile.write( (char*)&VertSize, sizeof( unsigned int ) );
			
			outfile.write( (char*)&TempMesh3d.Vertex[0], sizeof( ABCSet< float > ) * TempMesh3d.Vertex.size() );
			// Vertex Normals //
			unsigned int VertNormSize = TempMesh3d.VertexNormal.size();
			outfile.write( (char*)&VertNormSize, sizeof( unsigned int ) );
	
			outfile.write( (char*)&TempMesh3d.VertexNormal[0], sizeof( ABCSet< float > ) * TempMesh3d.VertexNormal.size() );
			// Vertex Color //
			unsigned int VertColSize = TempMesh3d.VertexColor.size();
			outfile.write( (char*)&VertColSize, sizeof( unsigned int ) );
	
			outfile.write( (char*)&TempMesh3d.VertexColor[0], sizeof( unsigned int ) * TempMesh3d.VertexColor.size() );
			// Texture Coords //
			unsigned int TextCoordSize = TempMesh3d.TextureCoord.size();
			outfile.write( (char*)&TextCoordSize, sizeof( unsigned int ) );
	
			outfile.write( (char*)&TempMesh3d.TextureCoord[0], sizeof( ABSet< float > ) * TempMesh3d.TextureCoord.size() );
			// Indicies //
			unsigned int IndiciesSize = TempMesh3d.Indicies.size();
			outfile.write( (char*)&IndiciesSize, sizeof( unsigned int ) );
	
			outfile.write( (char*)&TempMesh3d.Indicies[0], sizeof( unsigned int ) * TempMesh3d.Indicies.size() );
	
			
			std::string TextureNameTX = String::DirectorySlash( Object[obj].Group[ lookup ].TextureName )
									  + String::BaseName( Object[obj].Group[ lookup ].TextureName )
									  + ".tx";

			// Texture Name //
//			unsigned int TextureNameSize = Object[obj].Group[ lookup ].TextureName.size() + 1;
			unsigned int TextureNameSize = TextureNameTX.size() + 1;
			outfile.write( (char*)&TextureNameSize, sizeof( unsigned int ) );
						
			int PadNum = TextureNameSize % 4;
			if( PadNum != 0 )
			{
				PadNum = 4 - PadNum;
			}
			outfile.write( TextureNameTX.c_str(), TextureNameSize );
			for( int PadIdx = 0; PadIdx < PadNum; ++PadIdx )
			{
				outfile.write( " ", sizeof( unsigned char ) );
			}
//			outfile.write( Object[obj].Group[ lookup ].TextureName.c_str(),
//				Object[obj].Group[ lookup ].TextureName.size() + 1 );
			
			TempMesh3d.clear();
		}
	}

	
	outfile.close();
	
	// - -------------------------------------------------------------------------------------- - //
}
// - ------------------------------------------------------------------------------------------ - //
