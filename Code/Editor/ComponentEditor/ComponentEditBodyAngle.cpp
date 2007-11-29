#ifdef EDITOR
// - ------------------------------------------------------------------------------------------ - //
#include "ComponentEdit.h"
#include "Input/Input.h"
// - ------------------------------------------------------------------------------------------ - //
#include <SDL/SDL.h>

using namespace Input;
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::BodyAddAngle()
{
	if( Button[ KEY_0_PAD ].Pressed() || Button[ KEY_A ].Pressed() /*|| isPaste == true*/ )
	{
		if( DynObj->Body.Nodes.Size() > 2 )
		{
			for( size_t idx = 0; idx < CurSelected.size(); ++idx )
			{
				int IndexA = 1;
				int IndexB = 2;
				Real IndexADistance = 100000.0;
				Real IndexBDistance = 100000.0;
				Real TestDistance = 100000.0;
				
				for( size_t idx2 = 0; idx2 < Pose->Node.size(); ++idx2 )
				{	
					if( idx2 != CurSelected[ idx ] )
					{	
						TestDistance = ( Pose->Node[ idx2 ].Pos - Pose->Node[ CurSelected[ idx ] ].Pos ).Magnitude();
					
						if( TestDistance < IndexADistance )
						{
							IndexADistance = TestDistance;
							IndexA = idx2;
						}
					}
				}

				for( int idx2 = 0; idx2 < (int)Pose->Node.size(); ++idx2 )
				{	
					if( (size_t)idx2 != CurSelected[ idx ] )
						if ( idx2 != IndexA ) {	
							TestDistance = ( Pose->Node[ idx2 ].Pos - Pose->Node[ CurSelected[ idx ] ].Pos ).Magnitude();
						
							if( TestDistance < IndexBDistance )
							{
								IndexBDistance = TestDistance;
								IndexB = idx2;
							}
						}
				}

				DynObj->Body.AddAngleCross( CurSelected[idx], IndexA, IndexB );
			}
		}

		{
			ActiveAction();
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::BodyDeleteAngle()
{
	if( Button[ KEY_DELETE ].Pressed() )
	{
		for( size_t idx = 0; idx < CurSelected.size(); ++idx )
		{
			for( size_t AngleIdx = 0; AngleIdx < DynObj->Body.Pose->AngleCross.size(); ++AngleIdx )
			{
				if( CurSelected[idx] == DynObj->Body.Pose->AngleCross[ AngleIdx ].IndexPivot )
				{
					DynObj->Body.DeleteAngleCross( AngleIdx );
				}
			}
		}
	}
} 
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::BodyAngleIndexes()
{
	if( Button[ KEY_Q ].Pressed() )
	{
		for( size_t idx = 0; idx < CurSelected.size(); ++idx )
		{
			Real IndexADistance = 100000.0;
			Real TestDistance = 100000.0;
			
			for( size_t idx2 = 0; idx2 < Pose->Node.size(); ++idx2 )
			{	
				TestDistance = ( Pose->Node[ idx2 ].Pos - CurMousePos ).Magnitude();
			
				if( TestDistance < IndexADistance )
				{
					IndexADistance = TestDistance;
					for( size_t AngleIdx = 0; AngleIdx < DynObj->Body.Pose->AngleCross.size(); ++AngleIdx )
					{
						if( CurSelected[ idx ] == DynObj->Body.Pose->AngleCross[ AngleIdx ].IndexPivot )
						{
							DynObj->Body.Pose->AngleCross[ AngleIdx ].IndexA = idx2;
						}
					}
				}
			}
		}


		{
			ActiveAction();
		}
	}
	if( Button[ KEY_W ].Pressed() )
	{
		for( size_t idx = 0; idx < CurSelected.size(); ++idx )
		{
			Real IndexBDistance = 100000.0;
			Real TestDistance = 100000.0;
			
			for( size_t idx2 = 0; idx2 < Pose->Node.size(); ++idx2 )
			{	
				TestDistance = ( Pose->Node[ idx2 ].Pos - CurMousePos ).Magnitude();
			
				if( TestDistance < IndexBDistance )
				{
					IndexBDistance = TestDistance;
					for( size_t AngleIdx = 0; AngleIdx < DynObj->Body.Pose->AngleCross.size(); ++AngleIdx )
					{
						if( CurSelected[ idx ] == DynObj->Body.Pose->AngleCross[ AngleIdx ].IndexPivot )
						{
							DynObj->Body.Pose->AngleCross[ AngleIdx ].IndexB = idx2;
						}
					}
				}
			}
		}


		{
			ActiveAction();
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
