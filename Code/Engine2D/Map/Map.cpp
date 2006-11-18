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
	StaticObjectInstanceInfo.clear();
	DynamicObjectInstanceInfo.clear();
	PassiveObjectInstanceInfo.clear();
	ZoneInstanceInfo.clear();

	// Read Data //
	cEndianReader In( FileName );

	if( In.Empty() )
	{
		return;
	}
	
	// Static Object part //
	{
		size_t StaticObjectSize = In.Read();
		StaticObjectInstanceInfo.resize( StaticObjectSize );
		
		//Log( LOG_HIGHEST_LEVEL, "StaticObjectSize : " << StaticObjectSize );

		for ( size_t idx = 0; idx < StaticObjectSize; idx++ )
		{
			int StrLen = In.Read();
			char MyString[ StrLen + 1 ];
			
			In.Read( &MyString[0], StrLen );
			
			MyString[ StrLen ] = 0;
			
			StaticObjectInstanceInfo[ idx ].FileName = MyString;
			
			//Log( LOG_HIGHEST_LEVEL, "StaticObjectInstanceInfo[ idx ].FileName " << StaticObjectInstanceInfo[ idx ].FileName );
			
			In.Read( StaticObjectInstanceInfo[ idx ].Pos.x );
			In.Read( StaticObjectInstanceInfo[ idx ].Pos.y );

			In.Read( StaticObjectInstanceInfo[ idx ].Arg );

		}
	}

	// Dynamic Object part //
	{
		size_t DynamicObjectSize = In.Read();
		DynamicObjectInstanceInfo.resize( DynamicObjectSize );
		
		//Log( LOG_HIGHEST_LEVEL, "DynamicObjectSize : " << DynamicObjectSize );

		for ( size_t idx = 0; idx < DynamicObjectSize; idx++ )
		{
			In.Read( DynamicObjectInstanceInfo[ idx ].Id );
			
			In.Read( DynamicObjectInstanceInfo[ idx ].Pos.x );
			In.Read( DynamicObjectInstanceInfo[ idx ].Pos.y );

			In.Read( DynamicObjectInstanceInfo[ idx ].Arg );
			
			size_t CompSize = In.Read();
			
			DynamicObjectInstanceInfo[ idx ].Component.resize( CompSize );			

			for ( size_t idx2 = 0; idx2 < CompSize; idx2++ )
			{
				size_t NodeSize = In.Read();

				DynamicObjectInstanceInfo[ idx ].Component[ idx2 ].NodePos.resize( NodeSize );
				
				for ( size_t idx3 = 0; idx3 < NodeSize; idx3++ )
				{
					In.Read( DynamicObjectInstanceInfo[ idx ].Component[ idx2 ].NodePos[ idx3 ].x );
					In.Read( DynamicObjectInstanceInfo[ idx ].Component[ idx2 ].NodePos[ idx3 ].y );
				}
			}
		}
	}
	
	// Passive Object part //
	{
		size_t PassiveObjectSize = In.Read();
		PassiveObjectInstanceInfo.resize( PassiveObjectSize );

	}

	// Zones part //
	{
		size_t ZoneSize = In.Read();
		ZoneInstanceInfo.resize( ZoneSize );

	}
	
}
// - ------------------------------------------------------------------------------------------ - //
void cMap::SaveBinary( const std::string FileName )
{
	// Write Data (Map File) //
	{
		cEndianWriter Out( FileName, true );

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
	}
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
