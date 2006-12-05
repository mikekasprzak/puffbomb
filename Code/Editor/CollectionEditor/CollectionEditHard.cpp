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
void cCollectionEdit::HardDelete()
{
	if( !CurSelected.empty() )
	{
		if( Button[ KEY_DELETE ].Pressed() )
		{
			std::vector< Engine2D::cNodeAnchor > tempVec;
	
			for( size_t idx = 0; idx < Collection.NodeAnchor.size(); ++idx )
			{
				if( Collection.NodeAnchor[ idx ].Object == CurSelComp )
				{
					bool isDelete = false;
					for( size_t i = 0; i < CurSelected.size(); ++i )
					{
						if( CurSelected[i] == Collection.NodeAnchor[ idx ].Index )
						{
							isDelete = true;
						}
					}
					if( !isDelete )
					{
						tempVec.push_back( Collection.NodeAnchor[ idx ] );
					}
				}
				else
				{
					tempVec.push_back( Collection.NodeAnchor[ idx ] );
				}
			}
			Collection.NodeAnchor.swap( tempVec );

			CurSelected.clear();
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cCollectionEdit::HardStrength( const Real Strength )
{
	if( Button[ KEY_LCTRL ] )
	{
		for( size_t idx = 0; idx < Collection.NodeAnchor.size(); ++idx )
		{
			if( Collection.NodeAnchor[ idx ].Object == CurSelComp )
			{
				for( size_t i = 0; i < CurSelected.size(); ++i )
				{
					if( CurSelected[i] == Collection.NodeAnchor[ idx ].Index )
					{
						if( Collection.NodeAnchor[ idx ].Strength > Real( 1.0 ) )
						{
							if( ( Button[ KEY_MINUS ] ) || ( Mouse.Wheel.Diff() < 0 ) )
							{
								Collection.NodeAnchor[ idx ].Strength -= Strength;
							}
						}
						if( ( Button[ KEY_EQUALS ] ) || ( Mouse.Wheel.Diff() > 0 ) )
						{
								Collection.NodeAnchor[ idx ].Strength += Strength;
						}
					}
				}
			}
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
