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
int cCollectionEdit::DynSingleSelect()
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
					if( CurSelComp != idx )
					{
						CurSelected.clear();
					}
					
					CurSelComp = idx;
					LastIdx = idx2;
				}
			}
		}
	}
		
	return LastIdx;
}
// - ------------------------------------------------------------------------------------------ - //
void cCollectionEdit::DynSelect()
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
							if( CurSelected[i] == idx2 )
							{
								CurSelectedTest = true;
							}
						}
						if( !CurSelectedTest )
						{
							CurSelComp = idx;
							CurSelected.push_back( idx2 );	
						}
					}
				}
			}
			// Single add-select //
			int temp = DynSingleSelect();
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
							if( CurSelected[i] == idx2 )
							{
								std::vector <size_t> tempVec;
								for( size_t vec = 0; vec < CurSelected.size(); ++vec )
								{
									if( CurSelected[vec] != idx2 )
									{
										CurSelComp = idx;
										//CurSelected.push_back( idx2 );	
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
			int temp = DynSingleSelect();
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
			for( size_t idx = 0; idx < Collection.Component.size(); ++idx )
			{
				for( size_t idx2 = 0; idx2 < Collection.Component[ idx ].AnimationSet->BodyPose[ 0 ].Node.size(); ++idx2 )
				{
					if( WithinBox( Collection.Component[ idx ].AnimationSet->BodyPose[ 0 ].Node[ idx2 ].Pos, CurMousePos, OldMousePos ) )
					{
						bool CurSelectedTest = false;
						for( size_t i = 0; i < CurSelected.size(); ++i )
						{
							if( CurSelected[i] == idx2 )
							{
								CurSelectedTest = true;
							}					
						}
						if( !CurSelectedTest )
						{
							CurSelComp = idx;
							CurSelected.push_back( idx2 );	
						}
					}
				}
			}
			// Single select //
			if( CurSelected.empty() )
			{
				int temp = DynSingleSelect();
				if( temp != -1 )
				{
					CurSelected.push_back( temp );
				}
			}
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cCollectionEdit::DynMove()
{
	if( Button[ MOUSE_1 ].Pressed() )
	{
		if( !Button[ KEY_LCTRL ] && !Button[ KEY_RCTRL ] && !Button[ KEY_LSHIFT ]  )
		{
			int temp = DynSingleSelect();
			for( size_t idx = 0; idx < CurSelected.size(); ++idx )
			{
				if( temp == int( CurSelected[idx] ) )
				{
					isGroupMove = true;
				}
			}
		}
	}
	if( Button[ MOUSE_1 ].Released() )
	{
		isGroupMove = false;
	}
	if( isGroupMove )
	{
		//for( size_t idx = 0; idx < Collection.Component[ CurSelComp ].AnimationSet->BodyPose.size(); ++idx )
		{
			for( size_t idx2 = 0; idx2 < CurSelected.size(); ++idx2 )
			{
				//Collection.Component[ CurSelComp ].AnimationSet->BodyPose[ idx ].Node[ CurSelected[ idx2 ] ].Pos -= OldMousePos - CurMousePos;	
				Collection.Component[ CurSelComp ].Body.Nodes.Pos( CurSelected[ idx2 ] ) -= OldMousePos - CurMousePos;	
			}
		}
			
		//Collection.Component[ CurSelComp ].Body = Collection.Component[ CurSelComp ].AnimationSet->BodyPose[ 0 ];
			
		
		OldMousePos = CurMousePos;
	}
}
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
