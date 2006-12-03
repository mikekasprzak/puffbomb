#ifdef EDITOR
// - ------------------------------------------------------------------------------------------ - //
#include "CollectionEdit.h"

#include <Graphics/Gfx.h>
#include <Input/Input.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Global.h>
// - ------------------------------------------------------------------------------------------ - //
using namespace Input;
// - ------------------------------------------------------------------------------------------ - //
void cCollectionEdit::NodeAddLink()
{
	if( Button[ KEY_0_PAD ] || Button[ KEY_A ] )
	{
		if( Button[ MOUSE_1 ].Released() )
		{
			if( LastComp != CurSelComp )
			{
				if( !CurSelected.empty() )
				{
					Collection.NodeLink.push_back( Engine2D::cNodeLink( LastComp, LastNode, CurSelComp, CurSelected[ 0 ] ) );
					
					Collection.NodeLink.back().Length = 
						( Collection.Component[ LastComp ].Body.Nodes.Pos( LastNode ) -
						Collection.Component[ CurSelComp ].Body.Nodes.Pos( CurSelected[ 0 ] ) ).Magnitude();

					Collection.NodeLink.back().Flags.ResetBreakable();
				}
			}
		}
	}
	
	if( !CurSelected.empty() )
	{
		LastComp = CurSelComp;
		LastNode = CurSelected[ 0 ];
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cCollectionEdit::NodeDeleteLink()
{
	if( !CurSelected.empty() )
	{
		if( Button[ KEY_DELETE ].Pressed() )
		{
			std::vector< Engine2D::cNodeLink > tempVec;
			
			for( size_t idx = 0; idx < Collection.NodeLink.size(); ++idx )
			{
				bool isDelete = false;
				for( size_t i = 0; i < CurSelected.size(); ++i )
				{
					if( CurSelComp == Collection.NodeLink[ idx ].ObjectA )
					{
						if( CurSelected[ i ] == Collection.NodeLink[ idx ].IndexA )
						{
							isDelete = true;
						}
					}
					if( CurSelComp == Collection.NodeLink[ idx ].ObjectB )
					{
						if( CurSelected[ i ] == Collection.NodeLink[ idx ].IndexB )
						{
							isDelete = true;
						}
					}
				}
				if( !isDelete )
				{
					tempVec.push_back( Collection.NodeLink[ idx ] );
				}
			}

			Collection.NodeLink.swap( tempVec );
			
			CurSelected.clear();
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
