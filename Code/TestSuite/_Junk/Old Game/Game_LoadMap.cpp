// - ------------------------------------------------------------------------------------------ - //
#include <SDL/SDL.h>

#include <string>
#include <map>
#include <iostream>

#include <Graphics/Mesh3dPool.h>

#include <String/String.h>
#include <Util/Pool.h>
// - ------------------------------------------------------------------------------------------ - //
using namespace std;
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include "Game.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cGame::LoadMap( char* _FileName ) {
	
	
	string FileName = _FileName;

	cScriptParser MapFile( FileName );
	string MeshPrefix = String::DirectorySlash( FileName );

	cSphereObject* LastCreatedSphereObject = 0;

	class cScriptPool : public cPool< cScriptParser > {
	public:
		cScriptPool( const string& _Directory ) {
			SearchPath.Add( _Directory );
		}
	};

	cScriptPool Templates( MeshPrefix + "../2D" );

	//map< string, cScriptParser > Templates;
	Real ObjectScalar = Real::One;

	// Load Map //
	int CurrentNode = -2;
	
	bool DynamicNode = true;
//	bool DynamicPolygon = false;
	bool OldNodeSet = true;
	
	for ( size_t idx = 0; idx < MapFile.Instruction.size(); idx++ ) {
		if ( MapFile.Instruction[ idx ].Command == "Dynamic" ) {
			CurrentNode = -1;
			DynamicNode = true;
//			DynamicPolygon = false;
			OldNodeSet = true;

//			string File = MeshPrefix + MapFile.Instruction[ idx ].Arg[ 0 ];
//			if ( Templates.find( File ) == Templates.end() ) {
//				Log( LOG_HIGHEST_LEVEL, "Loading Body2D " << File );
//				Templates[ File ] = cScriptParser( File );
//				Log( LOG_HIGHEST_LEVEL, "Body2D Loaded" );
//			}
//			Log( LOG_HIGHEST_LEVEL, "Using Body2D " << File );

//					Templates[ File ],

			SphereObject.push_back(
				new cSphereObject(
					Templates.Load( MapFile.Instruction[ idx ].Arg[ 0 ] ),
					atof( MapFile.Instruction[ idx ].Arg[ 1 ].c_str() ),
					atof( MapFile.Instruction[ idx ].Arg[ 2 ].c_str() ),
					ObjectScalar
					)
				);
			ObjectScalar = Real::One;
			LastCreatedSphereObject = SphereObject.back();

			AddController(
				SphereObject.back()->Control,
				SphereObject.back(),
				MapFile.Instruction[ idx ].Arg[ 0 ]
				);
		}
//		else if ( MapFile.Instruction[ idx ].Command == "Poly" ) {
//			CurrentNode = -1;
//			DynamicNode = false;
//			DynamicPolygon = true;
//			OldNodeSet = true;
//
////			string File = MeshPrefix + MapFile.Instruction[ idx ].Arg[ 0 ];
////			if ( Templates.find( File ) == Templates.end() ) {
////				Templates[ File ] = cScriptParser( File );
////			}
////					Templates[ File ],
//
//			PolyObject.push_back(
//				new cPolyObject(
//					Templates.Load( MapFile.Instruction[ idx ].Arg[ 0 ] ),
//					atof( MapFile.Instruction[ idx ].Arg[ 1 ].c_str() ),
//					atof( MapFile.Instruction[ idx ].Arg[ 2 ].c_str() )
//					)
//				);
//		}
		else if ( MapFile.Instruction[ idx ].Command == "Zone" ) {
			Zone.push_back( 
				cZone( 
					atof( MapFile.Instruction[ idx ].Arg[ 0 ].c_str() ),
					atof( MapFile.Instruction[ idx ].Arg[ 1 ].c_str() ),
					atof( MapFile.Instruction[ idx ].Arg[ 2 ].c_str() ),
					atof( MapFile.Instruction[ idx ].Arg[ 3 ].c_str() )
					)
				);
		}
		else if ( MapFile.Instruction[ idx ].Command == "ZoneId" ) {
			Zone.back().Id = atoi( MapFile.Instruction[ idx ].Arg[ 0 ].c_str() );
		}
		else if ( MapFile.Instruction[ idx ].Command == "ZoneArg" ) {
			Zone.back().Argument = atoi( MapFile.Instruction[ idx ].Arg[ 0 ].c_str() );
		}
		else if ( MapFile.Instruction[ idx ].Command == "Element" ) {
			Element.push_back( 
				cElement( 
					atof( MapFile.Instruction[ idx ].Arg[ 0 ].c_str() ),
					atof( MapFile.Instruction[ idx ].Arg[ 1 ].c_str() )
					)
				);
		}
		else if ( MapFile.Instruction[ idx ].Command == "ElementId" ) {
			Element.back().Id = atoi( MapFile.Instruction[ idx ].Arg[ 0 ].c_str() );
		}
		else if ( MapFile.Instruction[ idx ].Command == "ElementArg" ) {
			Element.back().Argument = atoi( MapFile.Instruction[ idx ].Arg[ 0 ].c_str() );
		}
		else if ( MapFile.Instruction[ idx ].Command == "Focus1" ) {
			Focus1 = LastCreatedSphereObject;
		}
		else if ( MapFile.Instruction[ idx ].Command == "Focus2" ) {
			Focus2 = LastCreatedSphereObject;
		}
		else if ( MapFile.Instruction[ idx ].Command == "Scale" ) {
			ObjectScalar = atof( MapFile.Instruction[ idx ].Arg[ 0 ].c_str() );
		}
		else if ( MapFile.Instruction[ idx ].Command == "MapModel" ) {
			Mesh3d.push_back(
				cLevelData(
					Vector3D(
						atof( MapFile.Instruction[ idx ].Arg[ 1 ].c_str() ),
						atof( MapFile.Instruction[ idx ].Arg[ 2 ].c_str() ),
						Real( 0.0 )
					),
					//&ModelPool.Load( MapFile.Instruction[ idx ].Arg[ 0 ] ),
					&Mesh3dPool.Load( MapFile.Instruction[ idx ].Arg[ 0 ] )
				)
			);
			Log( LOG_MAP_INFO, "Map Model Loaded" );
		}
		else {
			if ( MapFile.Instruction[ idx ].Command == "NewPos" ) {
				if ( CurrentNode == -2 ) {
					// No Objects Added //
				}
				
				if ( !OldNodeSet ) {
					if ( DynamicNode /* || DynamicPolygon */ ) {
						(*SphereObject.back()).Old( CurrentNode ) = (*SphereObject.back()).Pos( CurrentNode );
					}
				}
				
				CurrentNode++;
				OldNodeSet = false;
				
//				if ( DynamicPolygon ) {
//					(*PolyObject.back()).Pos( CurrentNode ).Set( 
//						atof( MapFile.Instruction[ idx ].Arg[ 0 ].c_str() ),
//						atof( MapFile.Instruction[ idx ].Arg[ 1 ].c_str() )
//					);					
//				}
//				else
				if ( DynamicNode ) {
					(*SphereObject.back()).Pos( CurrentNode ).Set( 
						atof( MapFile.Instruction[ idx ].Arg[ 0 ].c_str() ),
						atof( MapFile.Instruction[ idx ].Arg[ 1 ].c_str() )
					);
				}
				else {
					(*StaticObject.back()).Pos( CurrentNode ).Set( 
						atof( MapFile.Instruction[ idx ].Arg[ 0 ].c_str() ),
						atof( MapFile.Instruction[ idx ].Arg[ 1 ].c_str() )
					);
				}				
			}
			else if ( MapFile.Instruction[ idx ].Command == "NewOld" ) {
				if ( CurrentNode < 0 ) {
					// No Object or New Nodes Added //
				}
				
				OldNodeSet = true;

//				if ( DynamicPolygon ) {
//					(*PolyObject.back()).Old( CurrentNode ).Set( 
//						atof( MapFile.Instruction[ idx ].Arg[ 0 ].c_str() ),
//						atof( MapFile.Instruction[ idx ].Arg[ 1 ].c_str() )
//					);
//				}
//				else
				if ( DynamicNode ) {
					(*SphereObject.back()).Old( CurrentNode ).Set( 
						atof( MapFile.Instruction[ idx ].Arg[ 0 ].c_str() ),
						atof( MapFile.Instruction[ idx ].Arg[ 1 ].c_str() )
					);
				}
				else {
					// Error!  No such thing as old in a static!! //
				}				
			}
		}
	}
	// In case no focus is set, make it the last object, to avoid bugs //
	if ( !Focus1 )
		Focus1 = SphereObject.back();

	if ( !Focus2 )
		Focus2 = SphereObject.back();
	
	// Update the Current Home Positions to the Current Position, in case it was modified //
	for ( size_t idx = 0; idx < SphereObject.size(); ++idx ) {
		SphereObject[ idx ]->SetHome();
	}	

	// Update Static Object Rectangles //
	for ( size_t idx = 0; idx < StaticObject.size(); ++idx ) {
		StaticObject[ idx ]->Refresh();
	}
	
	// Activate and Remove InitZones //
	for ( size_t idx = 0; idx < Zone.size(); ++idx ) {
		if ( Zone[ idx ].InitZone() ) {
			Zone.erase( Zone.begin() + idx );
			idx--;
		}
	}		

}
// - ------------------------------------------------------------------------------------------ - //
