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
void cCollectionEdit::HardAdd()
{
	if( Button[ KEY_0_PAD ].Pressed() || Button[ KEY_A ].Pressed() )
	{	
		for( size_t idx = 0; idx < CurSelected.size(); ++idx )
		{
			Collection.NodeAnchor.push_back( Engine2D::cNodeAnchor( CurSelComp, CurSelected[ idx ] ) );
		}
		Collection.UpdateAnchors();
		
		CurSelected.clear();
		
		ActiveAction();
	}
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
