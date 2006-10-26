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
void cCollectionEdit::StaticAddComp()
{
	if( Button[ KEY_0_PAD ].Pressed() || Button[ KEY_A ].Pressed() )
	{	
		CurSelected.clear();
		
		Collection.Component.push_back( Engine2D::cDynamicComponent() );
		
		int CSize = Collection.Component.size() - 1;
				
		Collection.Component[ CSize ].AnimationSet = new Engine2D::cComponentAnimationSet();
		Collection.Component[ CSize ].AnimationSet->LoadBinary( CompBaseDirName + ComponentPath[ CurComp ] );
		
		Vector2D AddPos = CurMousePos;
		
		if( !Button[ KEY_LSHIFT ] )
		{
			SetGridDepth( Camera, CurrentGridDepth, 40.0 );
			SetGridArray( CurrentGridDepth, GridDepth );

			CalcSnapToGrid( AddPos, CurrentGridDepth, GridDepth );
		}
		
		for( size_t idx = 0; idx < Collection.Component[ CSize ].AnimationSet->BodyPose.size(); ++idx )
		{
			for( size_t idx2 = 0; idx2 < Collection.Component[ CSize ].AnimationSet->BodyPose[ idx ].Node.size(); ++idx2 )
			{
				Collection.Component[ CSize ].AnimationSet->BodyPose[ idx ].Node[ idx2 ].Pos += AddPos;
			}
		}
		
		Collection.Component[ CSize ].Body = Collection.Component[ CSize ].AnimationSet->BodyPose[ 0 ];
		
		//Collection.Component[ CSize ].Body.CalcBoundingRect();
		
		CurSelected.push_back( CSize );
	}
}
// - ------------------------------------------------------------------------------------------ - //
int cCollectionEdit::StaticSingleSelect()
{
	int LastIdx = -1;
	Real LastDistance = Real( 100 );
	Real TestDistance = Real( 100 );

	// LastIdx is idx because we want the component not the particular node in this mode //		
	for( size_t idx = 0; idx < Collection.Component.size(); ++idx )
	{
		for( size_t idx2 = 0; idx2 < Collection.Component[ idx ].AnimationSet->BodyPose[ 0 ].Node.size(); ++idx2 )
		{
			TestDistance = ( Collection.Component[ idx ].AnimationSet->BodyPose[ 0 ].Node[ idx2 ].Pos - CurMousePos ).Magnitude();
			
			if( TestDistance < Real( 100 ) )
			{
				if( TestDistance < LastDistance )
				{
					LastDistance = TestDistance;
					LastIdx = idx;
				}
			}
			
		}
	}
		
	return LastIdx;
}
// - ------------------------------------------------------------------------------------------ - //
void cCollectionEdit::StaticSelect()
{
	if( Button[ MOUSE_1 ].Released() )
	{	
		// Group add-select //
		if( Button[ KEY_LSHIFT ] || Button[ KEY_RSHIFT ] )
		{
			for( size_t idx = 0; idx < Collection.Component.size(); ++idx )
			{
				for( size_t idx2 = 0; idx2 < Collection.Component[ idx ].AnimationSet->BodyPose[ 0 ].Node.size(); ++idx2 )
				{
					if( WithinBox( Collection.Component[ idx ].AnimationSet->BodyPose[ 0 ].Node[ idx2 ].Pos, CurMousePos, OldMousePos ) )
					{
						bool CurSelectedTest = false;
						for( size_t i = 0; i < CurSelected.size(); ++i )
						{
							if( CurSelected[i] == idx )
							{
								CurSelectedTest = true;
							}
						}
						if( !CurSelectedTest )
						{
							CurSelected.push_back( idx );	
						}
					}
				}
			}
			// Single add-select //
			int temp = StaticSingleSelect();
			if( temp != -1 )
			{
				bool CurSelectedTest = false;
				for( size_t i = 0; i < CurSelected.size(); ++i )
				{
					if( int( CurSelected[i] ) == temp )
					{
						CurSelectedTest = true;
					}					
				}
				if( !CurSelectedTest )
				{
					CurSelected.push_back( temp );	
				}
			}
		}
		// Group de-select //
		else if( Button[ KEY_LCTRL ] || Button[ KEY_RCTRL ] )
		{
			for( size_t idx = 0; idx < Collection.Component.size(); ++idx )
			{
				for( size_t idx2 = 0; idx2 < Collection.Component[ idx ].AnimationSet->BodyPose[ 0 ].Node.size(); ++idx2 )
				{
					if( WithinBox( Collection.Component[ idx ].AnimationSet->BodyPose[ 0 ].Node[ idx2 ].Pos, CurMousePos, OldMousePos ) )
					{
						for( size_t i = 0; i < CurSelected.size(); ++i )
						{
							if( CurSelected[i] == idx )
							{
								std::vector <size_t> tempVec;
								for( size_t vec = 0; vec < CurSelected.size(); ++vec )
								{
									if( CurSelected[vec] != idx )
									{
										tempVec.push_back( CurSelected[vec] );
									}
								}
								CurSelected.swap( tempVec );
							}
						}
					}
				}
			}
			// Single de-select //
			int temp = StaticSingleSelect();
			if( temp != -1 )
			{
				for( size_t i = 0; i < CurSelected.size(); ++i )
				{
					if( int(CurSelected[i]) == temp )
					{			
						std::vector <size_t> tempVec;
						for( size_t vec = 0; vec < CurSelected.size(); ++vec )
						{
							if( int(CurSelected[vec]) != temp )
							{
								tempVec.push_back( CurSelected[vec] );
							}
						}
						CurSelected.swap( tempVec );
					}
				}
			}
		}
		// Standard group select //
		else
		{
			CurSelected.clear();
			// push back idx because we want the component not the particular node in this mode //
			for( size_t idx = 0; idx < Collection.Component.size(); ++idx )
			{
				for( size_t idx2 = 0; idx2 < Collection.Component[ idx ].AnimationSet->BodyPose[ 0 ].Node.size(); ++idx2 )
				{
					if( WithinBox( Collection.Component[ idx ].AnimationSet->BodyPose[ 0 ].Node[ idx2 ].Pos, CurMousePos, OldMousePos ) )
					{
						bool CurSelectedTest = false;
						for( size_t i = 0; i < CurSelected.size(); ++i )
						{
							if( CurSelected[i] == idx )
							{
								CurSelectedTest = true;
							}					
						}
						if( !CurSelectedTest )
						{
							CurSelected.push_back( idx );	
						}
					}
				}
			}
			// Single select //
			if( CurSelected.empty() )
			{
				int temp = StaticSingleSelect();
				if( temp != -1 )
				{
					CurSelected.push_back( temp );
				}
			}
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cCollectionEdit::StaticMove()
{
	if( Button[ MOUSE_1 ].Pressed() )
	{
		if( !Button[ KEY_LCTRL ] || !Button[ KEY_RCTRL ] )
		{
			int temp = StaticSingleSelect();
			for( size_t idx = 0; idx < CurSelected.size(); ++idx )
			{
				if( temp == int( CurSelected[idx] ) )
				{
					isGroupMove = true;
				}
			}
		}
/*		// Snaps to grid
		if( !Button[ KEY_LSHIFT ] && isGroupMove )
		{
			SnapToGrid = true;
		}
		else
		{
			SnapToGrid = false;
		}*/
	}
	if( Button[ MOUSE_1 ].Released() )
	{
		isGroupMove = false;
/*		
		if( SnapToGrid )
		{
			SetGridDepth( Camera, CurrentGridDepth, 40.0 );
			SetGridArray( CurrentGridDepth, GridDepth );
			
			Vector2D TempPos = CurMousePos;
			CalcSnapToGrid( TempPos, CurrentGridDepth, GridDepth );

			for( size_t idx = 0; idx < CurSelected.size(); ++idx )
			{
				for( size_t idx2 = 0; idx2 < Collection.Component[ CurSelected[idx] ].AnimationSet->BodyPose.size(); ++idx2 )
				{
					for( size_t idx3 = 0; idx3 < Collection.Component[ CurSelected[idx] ].AnimationSet->BodyPose[ idx2 ].Node.size(); ++idx3 )
					{
						Collection.Component[ CurSelected[idx] ].AnimationSet->BodyPose[ idx2 ].Node[ idx3 ].Pos -= CurMousePos - TempPos;
					}
				}
				Collection.Component[ CurSelected[idx] ].Body = Collection.Component[ CurSelected[idx] ].AnimationSet->BodyPose[ 0 ];
			}
			SnapToGrid = false;
		//	ActiveAction();
		}
		else
		{
		//	ActiveAction();
		}*/
	}
	if( isGroupMove )
	{
		for( size_t idx = 0; idx < CurSelected.size(); ++idx )
		{
			for( size_t idx2 = 0; idx2 < Collection.Component[ CurSelected[idx] ].AnimationSet->BodyPose.size(); ++idx2 )
			{
				for( size_t idx3 = 0; idx3 < Collection.Component[ CurSelected[idx] ].AnimationSet->BodyPose[ idx2 ].Node.size(); ++idx3 )
				{
					Collection.Component[ CurSelected[idx] ].AnimationSet->BodyPose[ idx2 ].Node[ idx3 ].Pos -= OldMousePos - CurMousePos;
				}	
			}
			Collection.Component[ CurSelected[idx] ].Body = Collection.Component[ CurSelected[idx] ].AnimationSet->BodyPose[ 0 ];
		}
		OldMousePos = CurMousePos;
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cCollectionEdit::StaticDelete()
{
	if( !CurSelected.empty() )
	{
		if( Button[ KEY_DELETE ].Pressed() )
		{
			std::vector< Engine2D::cDynamicComponent > tempVec;
			for( size_t idx = 0; idx < Collection.Component.size(); ++idx )
			{
				bool isDelete = false;
				for( size_t i = 0; i < CurSelected.size(); ++i )
				{
					if( CurSelected[i] == idx )
					{
						isDelete = true;
					}
				}
				if( !isDelete )
				{
					tempVec.push_back( Collection.Component[ idx ] );
				}
				else
				{
					delete Collection.Component[ idx ].AnimationSet;	
				}
			}
			Collection.Component.swap( tempVec );

			CurSelected.clear();
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
