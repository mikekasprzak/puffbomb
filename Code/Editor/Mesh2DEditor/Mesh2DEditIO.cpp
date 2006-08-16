#ifdef EDITOR
// - ------------------------------------------------------------------------------------------ - //
#include "Mesh2DEdit.h"
#include "Mesh2DInfo.h"
#include <Engine2D/DisplayMesh.h>
// - ------------------------------------------------------------------------------------------ - //
#include "Input/Input.h"
#include "Phiz/SphereObject.h"
#include <Util/String.h>
#include <Util/DirectoryCache.h>
#include <Graphics/TexturePool.h>
// - ------------------------------------------------------------------------------------------ - //
#include <sys/types.h>
#include <SDL/SDL.h>
// - ------------------------------------------------------------------------------------------ - //
#include <string>
// - ------------------------------------------------------------------------------------------ - //
using namespace std;
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::OpenCMesh( const std::string &Dir )
{
	Log( LOG_HIGHEST_LEVEL, "OpenCMesh " );
	cDirectoryCache cDirCache( Dir );
	
	for( size_t idx = 0; idx < cDirCache.File.size(); ++idx )
	{
		int MeshCheck = cDirCache.File[idx].size();
		
		if( MeshCheck > 5 )
		{
			if( String::LastExtension( cDirCache.File[idx] ) == ".body2d" )
			{
				string MeshName = Dir + cDirCache.File[idx];
				cScriptParser tempPhiz( MeshName.c_str() );
				
				Object.push_back(
					cSphereObject(
						tempPhiz,
						Real::Zero,
						Real::Zero,
						Real( 1.0 )
					)
				);
				Log( LOG_HIGHEST_LEVEL, "Mesh FileName (Editor) = " << cDirCache.File[idx] );
				cMesh2DInfo TempInfo;
				TempInfo.MeshName = Dir + cDirCache.File[idx];
				Mesh2DInfo.push_back( TempInfo );

			}
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::OpenDMesh( string &Dir )
{
	Log( LOG_HIGHEST_LEVEL, "OpenDMesh " );

	cDisplayMesh TempTObj;
	
	cDirectoryCache cDirCache( Dir );
	
	for( size_t diridx = 0; diridx < cDirCache.File.size(); ++diridx )
	{
		int MeshCheck = cDirCache.File[diridx].size();
		
		if( MeshCheck > 6 )
		{
			if( String::LastExtension( cDirCache.File[diridx] ) == ".mesh2d" )
			{
				Log( LOG_HIGHEST_LEVEL, ".mesh2d FileName (Editor) = " << cDirCache.File[diridx] );

				
				TempTObj.clear();
				string MeshName = Dir + cDirCache.File[diridx];
				
				if( TempTObj.Load( MeshName ) )
				{
					Log( LOG_HIGHEST_LEVEL, "Mesh2d Loaded = " << MeshName );
				}
				else
				{
					Log( LOG_HIGHEST_LEVEL, "Mesh2d Failed to load = " << MeshName );
				}

				string CompareName = String::BaseName( cDirCache.File[diridx] );
				
				Log( LOG_HIGHEST_LEVEL, "CompareName = " << CompareName );
				for( size_t idx = 0; idx < Mesh2DInfo.size(); ++idx )
				{
					string TempMeshName = String::BaseName( Mesh2DInfo[idx].MeshName );

					if( TempMeshName == CompareName )
					{
						Log( LOG_HIGHEST_LEVEL, "	TempMeshName = " << TempMeshName );

						DisplayMesh[idx] = TempTObj;
						
						for( size_t i = 0; i < TextureName.size(); ++i )
						{
							if( DisplayMesh[idx].TextureName == TextureName[i] )
							{
								DisplayMesh[idx].TextureIdx = i;
							}
						}
					}		
				}
			}
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::SaveCurrentMesh()
{
	if( Input::Button[ KEY_LCTRL ] )
	{
		if( Input::Button[ KEY_S ].Pressed() && Mesh2DInfo[ CurrentObject ].isSaved == false )
		{

			std::string Temp = Mesh2DInfo[ CurrentObject ].MeshName;
			Log( LOG_HIGHEST_LEVEL, "Save body2d FileName (Editor) = " << Temp );
			
			Object[ CurrentObject ].SaveFile( Temp.c_str() );
			
			std::string RemoveExt = String::Directory( Temp ) + "/" + String::BaseName( Temp ) + String::NoLastExtension( Temp );
			
			RemoveExt += ".mesh2d";
			Log( LOG_HIGHEST_LEVEL, "Save mesh2d FileName (Editor) = " << RemoveExt );

			SaveDMesh( RemoveExt.c_str() );

			Mesh2DInfo[ CurrentObject ].isSaved = true;
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::SaveDMesh( const char* File )
{
	if( !DisplayMesh[ CurrentObject ].DisplayNode.empty() )
	{
		if( DisplayMesh[CurrentObject].TextureIdx != -1 )
		{
			DisplayMesh[CurrentObject].TextureName = TextureName[ DisplayMesh[CurrentObject].TextureIdx ];
		}
		
		DisplayMesh[CurrentObject].Save( File, DrawLayers );
	}
}
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
