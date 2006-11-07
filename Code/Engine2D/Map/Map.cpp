// - ------------------------------------------------------------------------------------------ - //
// Zone //
// - ------------------------------------------------------------------------------------------ - //
#include <Util/Debug.h>
#include <Util/InputOutput.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Engine2D.h>
// - ------------------------------------------------------------------------------------------ - //
#include "Map.h"
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
void cMap::LoadBinary( const std::string FileName )
{
	// Read Data //
	cEndianReader In( FileName );
	
	if( In.Empty() )
	{
		return;
	}
	
		
}
// - ------------------------------------------------------------------------------------------ - //
void cMap::SaveBinary( const std::string FileName )
{
	// Write Data (Comp File) //
	{
		cEndianWriter Out( FileName, true );
		
		/*std::vector< cStaticObjectInstanceInfo > StaticObjectInstanceInfo;
		std::vector< cDynamicObjectInstanceInfo > DynamicObjectInstanceInfo;
		std::vector< cPassiveObjectInstanceInfo > PassiveObjectInstanceInfo;
		std::vector< cZoneInstanceInfo > ZoneInstanceInfo;
	*/
		// Static Object part //
		{
			Out.Write( StaticObjectInstanceInfo.size() );
			
			for ( size_t idx = 0; idx < StaticObjectInstanceInfo.size(); idx++ )
			{
				Out.Write( StaticObjectInstanceInfo[ idx ].FileName.size() );
				Out.Write( StaticObjectInstanceInfo[ idx ].FileName.c_str(), StaticObjectInstanceInfo[ idx ].FileName.size() );
				
				Out.Write( StaticObjectInstanceInfo[ idx ].Pos.x );
				Out.Write( StaticObjectInstanceInfo[ idx ].Pos.y );

				Out.Write( StaticObjectInstanceInfo[ idx ].Arg );
			}
		}
		
		// Dynamic Object part //
		{
			Out.Write( DynamicObjectInstanceInfo.size() );
			
			for ( size_t idx = 0; idx < DynamicObjectInstanceInfo.size(); idx++ )
			{
				Out.Write( DynamicObjectInstanceInfo[ idx ].Id );
								
				Out.Write( DynamicObjectInstanceInfo[ idx ].Pos.x );
				Out.Write( DynamicObjectInstanceInfo[ idx ].Pos.y );

				Out.Write( DynamicObjectInstanceInfo[ idx ].Arg );
				
				Out.Write( DynamicObjectInstanceInfo[ idx ].Component.size() );
				
				for ( size_t idx2 = 0; idx2 < DynamicObjectInstanceInfo[ idx ].Component.size(); idx2++ )
				{
					Out.Write( DynamicObjectInstanceInfo[ idx ].Component[ idx2 ].NodePos.size() );
					
					for ( size_t idx3 = 0; idx3 < DynamicObjectInstanceInfo[ idx ].Component[ idx2 ].NodePos.size(); idx3++ )
					{
						Out.Write( DynamicObjectInstanceInfo[ idx ].Component[ idx2 ].NodePos[ idx3 ].x );
						Out.Write( DynamicObjectInstanceInfo[ idx ].Component[ idx2 ].NodePos[ idx3 ].y );
					}
				}
			}
			
		}
		
		// Passive Object part //
		{
			Out.Write( PassiveObjectInstanceInfo.size() );
			
		}
		
		// Zones part //
		{
			Out.Write( ZoneInstanceInfo.size() );
			
		}
		
		// 	
		/*// Component part //
		{
			// Number of Components //
			Out.Write( Component.size() );
			
			// For every component //
			for ( size_t idx = 0; idx < Component.size(); idx++ )
			{
				Out.Write( ComponentName[ idx ].size() );
				Out.Write( ComponentName[ idx ].c_str(), ComponentName[ idx ].size() );
				
				Out.Write( Component[ idx ].Body.Nodes.Size() );
				
				for( size_t idx2 = 0; idx2 < Component[ idx ].Body.Nodes.Size(); ++idx2 )
				{
					Out.Write( Component[ idx ].Body.Nodes.Pos( idx2 ).x );
					Out.Write( Component[ idx ].Body.Nodes.Pos( idx2 ).y );
				}			
			}
		}*/
	}
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
