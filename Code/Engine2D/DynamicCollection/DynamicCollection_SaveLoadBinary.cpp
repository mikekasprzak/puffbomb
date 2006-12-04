// - ------------------------------------------------------------------------------------------ - //
#include <Util/Debug.h>
#include <DynamicCollection/DynamicCollection.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Util/InputOutput.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
void cDynamicCollection::LoadBinary( const std::string& FileName, const Vector2D& Offset )
{
	// Read Data //
	cEndianReader In( FileName );
	
	if( In.Empty() )
	{
		return;
	}
	
	// Component part //
	{
		size_t CompSize = In.Read();
		Component.resize( CompSize );
		Log( 1, "Component Count: " << Component.size() );
			
		// For every component //
		for ( size_t idx = 0; idx < CompSize; idx++ )
		{
			int StrLen = In.Read();
			char MyString[ StrLen + 1 ];
			
			In.Read( &MyString[0], StrLen );
			
			MyString[ StrLen ] = 0;
			
			std::string TmpString1 = "2D/";
			std::string TmpString2 = MyString;
			
			Log( 1, "ComponentName " << TmpString1 << TmpString2 );

			Component[ idx ] = Engine2D::cDynamicComponent( this, TmpString1 + TmpString2, Offset );
			//Component[ idx ].AnimationSet->LoadBinary( TmpString1 + TmpString2 );

			#ifdef EDITOR
			ComponentName.push_back( TmpString2 );
			#endif // Editor //
			
			//Component[ idx ].Body = Component[ idx ].AnimationSet->BodyPose[ 0 ];
			
			size_t NodeSize = In.Read();
			for( size_t idx2 = 0; idx2 < NodeSize; ++idx2 )
			{
				In.Read( Component[ idx ].Body.Nodes.Pos( idx2 ).x );
				In.Read( Component[ idx ].Body.Nodes.Pos( idx2 ).y );

				Component[ idx ].Body.Nodes.Pos( idx2 ) += Offset;
				
				Component[ idx ].Body.Nodes.Old( idx2 ) = Component[ idx ].Body.Nodes.Pos( idx2 );
			}
		}
	}
	
	// NodeLink part //
	{
		size_t LinkSize = In.Read();
		
		for( size_t idx = 0; idx < LinkSize; ++idx )
		{
			Real Length = Real::Zero;
			Real Strength = Real::Zero;
			Real BreakPoint = Real( 3 );
			size_t ObjectA = 0;
			size_t IndexA = 0;
			size_t ObjectB = 0;
			size_t IndexB = 0;
			
			In.Read( Length );
			In.Read( Strength );
			In.Read( BreakPoint );
			In.Read( ObjectA );
			In.Read( IndexA );
			In.Read( ObjectB );
			In.Read( IndexB );
									
			NodeLink.push_back( Engine2D::cNodeLink( ObjectA, IndexA, ObjectB, IndexB, BreakPoint, Strength ) );
					
			NodeLink.back().Length = Length;
			
			// disables breakable node links... (HACK) remove when breakable node links become useful (or work better) //
			NodeLink.back().Flags.ResetBreakable();
		}
	}
	
	// NodeAnchor part //
	{
		size_t AnchorSize = In.Read();
		
		for( size_t idx = 0; idx < AnchorSize; ++idx )
		{
			Real Strength = Real::Zero;
			Real BreakPoint = Real( 3 );
			size_t Object = 0;
			size_t Index = 0;
				
			In.Read( Strength );
			In.Read( BreakPoint );
			In.Read( Object );
			In.Read( Index );
			
			NodeAnchor.push_back( Engine2D::cNodeAnchor( Object, Index, BreakPoint, Strength ) );		
		}		
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cDynamicCollection::SaveBinary( const std::string& FileName, bool LittleEndian )
{
	// Write Data (Comp File) //
	{
		cEndianWriter Out( FileName, LittleEndian );
				
		// Component part //
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
		}
		// NodeLink part //
		{
			// Number of NodeLinks //
			Out.Write( NodeLink.size() );
			
			// For every nodelink //
			for ( size_t idx = 0; idx < NodeLink.size(); idx++ )
			{
				Out.Write( NodeLink[ idx ].Length );				
				Out.Write( NodeLink[ idx ].Strength );				
				Out.Write( NodeLink[ idx ].BreakPoint );				
				Out.Write( NodeLink[ idx ].ObjectA );				
				Out.Write( NodeLink[ idx ].IndexA );				
				Out.Write( NodeLink[ idx ].ObjectB );				
				Out.Write( NodeLink[ idx ].IndexB );					
			}
		}
	
		// NodeAnchor part //
		{
			// Number of NodeAnchors //
			Out.Write( NodeAnchor.size() );
			
			// For every NodeAnchor //
			for ( size_t idx = 0; idx < NodeAnchor.size(); idx++ )
			{
				Out.Write( NodeAnchor[ idx ].Strength );				
				Out.Write( NodeAnchor[ idx ].BreakPoint );				
				Out.Write( NodeAnchor[ idx ].Object );				
				Out.Write( NodeAnchor[ idx ].Index );				
			}
		}
		
	}
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
