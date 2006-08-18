#ifdef EDITOR
// - ------------------------------------------------------------------------------------------ - //
#include "ComponentEdit.h"
#include "Input/Input.h"
// - ------------------------------------------------------------------------------------------ - //
#include <SDL/SDL.h>

using namespace Input;
// - ------------------------------------------------------------------------------------------ - //
/*void cMesh2DEdit::DrawSphere( int Color, int SphereNumber )
{
	gfx::Circle( 
		Object[ CurrentObject ].Pos( Object[ CurrentObject ].Sphere[ SphereNumber ].Index ),
		Object[ CurrentObject ].Sphere[ SphereNumber ].Radius,
		Color
	);
}*/
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::BodySetRadius( Real RadiusDiff, int Node )
{
/*	Body2D[ CurBody ].Sphere[ SphereIdx ].Index
	
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
	}*/
}
// - ------------------------------------------------------------------------------------------ - //
// Used for paste //
void cComponentEdit::BodyAddSphere()
{
	if( Button[ KEY_0_PAD ].Pressed() || Button[ KEY_A ].Pressed() /*|| isPaste == true*/ )
	{
		for( size_t idx = 0; idx < CurSelected.size(); ++idx )
		{
			Body2D[ CurBody ].AddSphere( CurSelected[idx] );
		}

		//if( !isPaste )
		{
			ActiveAction();
		}
		/*		
		if( !HasSphere[ CurrentNode ] )
		{
			Object[ CurrentObject ].AddSphere( CurrentNode );
		
			SphereCheck();
			if( !isPaste )
			{
				ActiveAction();
			}
		}*/
	}
}
// - ------------------------------------------------------------------------------------------ - //
/*void cComponentEdit::DelSphere( int Node )
{
	if( Button[ KEY_DELETE ].Pressed() )
	{
		for( size_t idx = 0; idx < Object[ CurrentObject ].Sphere.size(); idx++ ) {
			if ( Object[ CurrentObject ].Sphere[ idx ].Index == size_t(Node) ) {
				Object[ CurrentObject ].DeleteSphere( idx );
			}
		}
	}
}*/
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::BodySphereCheck()
{
	/*HasSphere.clear();
	
	int NodeSize = Object[ CurrentObject ].size() - 1;

	for( int idx = 0; idx <= NodeSize; ++idx )
	{
		HasSphere.push_back( false );
	}
	
	for( size_t idx = 0; idx < Object[ CurrentObject ].Sphere.size(); ++idx )
	{
		HasSphere[ Object[ CurrentObject ].Sphere[ idx ].Index ] = true;
	}*/
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::BodyDeleteSphere()
{
	/*if( !CurSelected.empty() )
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
	}*/
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::BodyRadius( Real RadiusDiff )
{
	if( Button[ KEY_LCTRL ] )
	{
		for( size_t idx = 0; idx < CurSelected.size(); ++idx )
		{
			for( size_t SphereIdx = 0; SphereIdx < Body2D[ CurBody ].Sphere.size(); ++SphereIdx )
			{
				if( CurSelected[idx] == Body2D[ CurBody ].Sphere[ SphereIdx ].Index )
				{
					//Body2D[ CurBody ].DrawSphere( SphereIdx, true );
					//Body2D[ CurBody ].Sphere[ CurSelected[idx] ].Radius += Real( 20 );
					
					if( Body2D[ CurBody ].Sphere[ SphereIdx ].Radius > Real( 1.0 ) )
					{
						if ( Button[ KEY_MINUS ] )
						{
							Body2D[ CurBody ].Sphere[ SphereIdx ].Radius -= RadiusDiff;
						}
						
						if( Mouse.Wheel.Diff() < 0 )
						{
							Body2D[ CurBody ].Sphere[ SphereIdx ].Radius -= RadiusDiff;
						}		
					}
					// - -------------------------------------------------------------------------- - //
					if( Button[ KEY_EQUALS ] )
					{
						Body2D[ CurBody ].Sphere[ SphereIdx ].Radius += RadiusDiff;
					}
					if( Mouse.Wheel.Diff() > 0 )
					{
						Body2D[ CurBody ].Sphere[ SphereIdx ].Radius += RadiusDiff;
					}
					
					break;
				}
			}
		}
	
	}
	
	/*
	
		for( size_t idx = 0; idx < CurSelected.size(); ++idx )
	{
		//Body2D[ CurBody ].AddSphere( CurSelected[idx] );
		Body2D[ CurBody ].Sphere[ CurSelected[idx] ].Radius = Real( 20 );
	}

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
	}*/
}
// - ------------------------------------------------------------------------------------------ - //
/*void cComponentEdit::BodyAddSphere()
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
}*/
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
