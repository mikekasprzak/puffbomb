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

}
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
