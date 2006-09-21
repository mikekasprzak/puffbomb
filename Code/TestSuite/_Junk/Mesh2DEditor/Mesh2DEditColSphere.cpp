#ifdef EDITOR
// - ------------------------------------------------------------------------------------------ - //
#include "Mesh2DEdit.h"
#include "Input/Input.h"
// - ------------------------------------------------------------------------------------------ - //
#include <SDL/SDL.h>

using namespace Input;
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::DrawSphere( int Color, int SphereNumber )
{
	gfx::Circle( 
		Object[ CurrentObject ].Pos( Object[ CurrentObject ].Sphere[ SphereNumber ].Index ),
		Object[ CurrentObject ].Sphere[ SphereNumber ].Radius,
		Color
	);
}
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::SetRadius( Real RadiusDiff, int Node )
{
	for( size_t idx = 0; idx < Object[ CurrentObject ].Sphere.size(); idx++ )
	{
		if ( Object[ CurrentObject ].Sphere[ idx ].Index == size_t(Node) )
		{
					
			if( Object[ CurrentObject ].Sphere[ idx ].Radius > Real( 1.0 ) )
			{
				if ( Button[ KEY_MINUS ] )
				{
					Object[ CurrentObject ].Sphere[ idx ].Radius -= RadiusDiff;
				}
				
				if( Mouse.Wheel.Diff() < 0 )
				{
					Object[ CurrentObject ].Sphere[ idx ].Radius -= RadiusDiff;
				}		
			}
			// - -------------------------------------------------------------------------- - //
			if( Button[ KEY_EQUALS ] )
			{
				Object[ CurrentObject ].Sphere[ idx ].Radius += RadiusDiff;
			}
			if( Mouse.Wheel.Diff() > 0 )
			{
				Object[ CurrentObject ].Sphere[ idx ].Radius += RadiusDiff;
			}
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
// Used for paste //
void cMesh2DEdit::AddSphere()
{
	if( Button[ KEY_0_PAD ].Pressed() || Button[ KEY_A ].Pressed() || isPaste == true )
	{
		if( !HasSphere[ CurrentNode ] )
		{
			Object[ CurrentObject ].AddSphere( CurrentNode );
		
			SphereCheck();
			if( !isPaste )
			{
				ActiveAction();
			}
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::DelSphere( int Node )
{
	if( Button[ KEY_DELETE ].Pressed() )
	{
		for( size_t idx = 0; idx < Object[ CurrentObject ].Sphere.size(); idx++ ) {
			if ( Object[ CurrentObject ].Sphere[ idx ].Index == size_t(Node) ) {
				Object[ CurrentObject ].DeleteSphere( idx );
			}
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::SphereCheck()
{
	HasSphere.clear();
	
	int NodeSize = Object[ CurrentObject ].size() - 1;

	for( int idx = 0; idx <= NodeSize; ++idx )
	{
		HasSphere.push_back( false );
	}
	
	for( size_t idx = 0; idx < Object[ CurrentObject ].Sphere.size(); ++idx )
	{
		HasSphere[ Object[ CurrentObject ].Sphere[ idx ].Index ] = true;
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::ColDeleteSphere()
{
	if( !CurSelected.empty() )
	{
		if( Button[ KEY_DELETE ].Pressed() )
		{
			for( size_t idx = 0; idx < CurSelected.size(); ++idx )
			{
				DelSphere( CurSelected[idx] );
			}
			CurSelected.clear();
			SphereCheck();
		
			ActiveAction();
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::ColRadius( Real RadiusDiff )
{
	if( Button[ KEY_LCTRL ] )
	{
		if( !CurSelected.empty() )
		{
			for( size_t i = 0; i < CurSelected.size(); ++i )
			{
				if( HasSphere[ CurSelected[i] ] )
				{
					for( size_t idx = 0; idx < Object[ CurrentObject ].Sphere.size(); idx++ )
					{
						if ( Object[ CurrentObject ].Sphere[ idx ].Index == CurSelected[i] )
						{
							SetRadius( RadiusDiff, Object[ CurrentObject ].Sphere[ idx ].Index );
						}
					}
				}
			}	
		}
	}
	else if( Button[ KEY_LCTRL ].Released() )
	{
		if( !Mesh2DInfo[ CurrentObject ].UndoObject.empty() )
		{
			if( Object[ CurrentObject ].Sphere[ CurrentNode ].Radius !=
				Mesh2DInfo[ CurrentObject ].UndoObject.back().SphereObject.Sphere[ CurrentNode ].Radius )
			{				
				ActiveAction();
				SphereCheck();
			}
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cMesh2DEdit::ColAddSphere()
{
	if( Button[ KEY_0_PAD ].Pressed() || Button[ KEY_A ].Pressed() )
	{
		if( !CurSelected.empty() )
		{
			for( size_t i = 0; i < CurSelected.size(); ++i )
			{
				if( !HasSphere[ CurSelected[i] ] )
				{
					Object[ CurrentObject ].AddSphere( CurSelected[i] );
				}
			}
			ActiveAction();
			SphereCheck();
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
