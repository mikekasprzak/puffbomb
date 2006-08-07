#ifdef EDITOR
// - ------------------------------------------------------------------------------------------ - //
#include "MapEdit.h"
#include "Input/Input.h"
#include "Phiz/SphereObject.h"
#include <Graphics/Mesh3dPool.h>
#include <Util/String.h>
#include <Game/Global.h>
#include <Util/DirectoryCache.h>
// - ------------------------------------------------------------------------------------------ - //
#include <sys/types.h>
#include <SDL/SDL.h>
#include <dirent.h>
// - ------------------------------------------------------------------------------------------ - //
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
// - ------------------------------------------------------------------------------------------ - //
using namespace std;
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::LoadMap( string &Dir )
{
	cSearchPath SearchPath;
	SearchPath.Add( "../../../../Content/PuffBOMB" );
//	SearchPath.Add( "Maps" );
	Log( LOG_EDITOR_CREATE, "LoadMap (Editor) " );
	
	char Line[1024];
	
	cMapObject tempMapObject;

	ifstream InFile( Dir.c_str() );
	
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

			else if( Token == "Dynamic" )
			{
				Text >> Token;
				
				std::string FullPathName = SearchPath.Find( Token );

				
				/*string tempName;
					
				if( Token.size() > 12 )
				{
					tempName = Token.substr( 3, Token.size() - 1 );
				}*/
				Log( LOG_EDITOR_INFO, "Dynamic Token (Editor)= " << Token );
				Log( LOG_EDITOR_INFO, "Dynamic (Editor)= " << FullPathName );
				
				tempMapObject.MeshIdx = -1;
				
				for( size_t idx = 0; idx < Mesh2DEdit->Mesh2DInfo.size(); ++idx )
				{
					if( FullPathName == Mesh2DEdit->Mesh2DInfo[idx].MeshName )
					{
						Log( LOG_EDITOR_INFO, "Success " << Mesh2DEdit->Mesh2DInfo[idx].MeshName );
						tempMapObject.MeshIdx = idx;
					}					
				}
				if( tempMapObject.MeshIdx == -1 )
				{
					tempMapObject.MeshIdx = 0;
				}				
				
				Text >> Token;
				tempMapObject.Pos.x = atof( Token.c_str() );
				
				Text >> Token;
				tempMapObject.Pos.y = atof( Token.c_str() );
				
				MapObject.push_back( tempMapObject );
			}
			else if( Token == "Focus1" )
			{
				Focus1 = MapObject.size() - 1;
			}
			else if( Token == "Focus2" )
			{
				Focus2 = MapObject.size() - 1;
			}
			else if( Token == "MapModel" )
			{
				Text >> Token;
				
				std::string MapModel = Token;
				
				ModelName.push_back( MapModel );
				
				Vector3D Pos;
				
				Text >> Token;
				
				Pos.x = atof( Token.c_str() );

				Text >> Token;

				Pos.y = atof( Token.c_str() );
				
				Pos.z = 0.0;
				
				Model.push_back(
					cLevelData(
						Pos,
						&Mesh3dPool.Load( MapModel )
					)
				);
				
				MapModel = String::PriorBaseName( MapModel );
				
				if( MapModel.size() > 2 )
				{
					if( MapModel == "Scene" )
					{
						SceneryIdx = ModelName.size() - 1;
					}	
				}
				
				Log( LOG_EDITOR_INFO, "SceneryIdx = " << SceneryIdx << " " << MapModel );
				
				CurModel = 0;
				
				/*for ( size_t idx = 0; idx < ModelNameList.size(); ++idx )
				{
					if( MapModel == ModelNameList[ idx ] )
					{
						CurModel = idx;
						break;
					}
				}*/
			}
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::SaveMap( const char* File )
{
	if( Input::Button[ KEY_LCTRL ] )
	{
		if( Input::Button[ KEY_S ].Pressed() && isSaved == false )
		{
			std::string SavePath = CurrentDir + File;
			Log( LOG_EDITOR_CREATE, "Map Saved = " << SavePath );
		
			cScriptParser Script;
			
			for( size_t idx = 0; idx < ModelName.size(); ++idx )
			{
				Script.Append( "MapModel " + ModelName[idx], Model[idx].Offset.x, Model[idx].Offset.y );
			}
						
			for( size_t idx = 0; idx < MapObject.size(); ++idx )
			{
//				std::string tempstr =
//					"Dynamic Meshes/" + Mesh2DEdit->Mesh2DInfo[MapObject[idx].MeshIdx].MeshName;
				std::string tempstr = "Dynamic " + String::FileName( Mesh2DEdit->Mesh2DInfo[MapObject[idx].MeshIdx].MeshName );
				Script.Append( tempstr, MapObject[idx].Pos.x, MapObject[idx].Pos.y );

				if( Focus1 == int(idx) )
				{
					Script.Append( "Focus1" );
				}
				if( Focus2 == int(idx) )
				{
					Script.Append( "Focus2" );
				}
			}
			for( size_t idx = 0; idx < Game->Zone.size(); ++idx )
			{
				Script.Append( "Zone",
					Game->Zone[ idx ].BoundingRect.P1().x,
					Game->Zone[ idx ].BoundingRect.P1().y,
					Game->Zone[ idx ].BoundingRect.P2().x,
					Game->Zone[ idx ].BoundingRect.P2().y
				);
				Script.Append( "ZoneId",
					Game->Zone[ idx ].Id
				);
				Script.Append( "ZoneArg",
					Game->Zone[ idx ].Argument
				);
			}
			isSaved = true;
			
			Script.SaveFile( SavePath.c_str() );
		
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::ListModels()
{
	string DirPrefix = "3D/";
	Log( LOG_EDITOR_INFO, "ListModels " );
	
	cDirectoryCache cDirCache( DirPrefix );
	
	for( size_t idx = 0; idx < cDirCache.File.size(); ++idx )
	{
		if( String::LastExtension( cDirCache.File[idx] ) == ".mesh3d" )
		{
			if( String::HasExtension( cDirCache.File[idx], ".bin" ) )
			{
				std::string TempFileName = String::FileName( cDirCache.File[idx] );
				
				TempFileName = String::BaseName( TempFileName ) + String::LastExtension( TempFileName );
				
				Log( LOG_EDITOR_INFO, "Model names in folder = " << TempFileName );
				
				ModelNameList.push_back( TempFileName );
				
				ModelList.push_back(
					cLevelData(
						Vector3D( cGlobal::Left, cGlobal::Bottom, 0.0 ),
						&Mesh3dPool.Load( TempFileName )
					)
				);
			}
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::LoadZoneDesc()
{
	char Line[1024];
	
	ifstream InFile( "../../../../Content/ZoneDescriptions.txt" );

	ZoneDesc.push_back( "Undefined" );

	while( !InFile.eof() )
	{
		// Read a line from the file //
		InFile.getline( Line, sizeof( Line ) );
	
		// Populate and use a string stream to tokenize the data //
		stringstream Text;
		Text << Line;
		
		ZoneDesc.push_back( Text.str() );
	}
}
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
