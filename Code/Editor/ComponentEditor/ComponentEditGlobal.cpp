#ifdef EDITOR
// - ------------------------------------------------------------------------------------------ - //
#include "ComponentEdit.h"

#include <Graphics/Gfx.h>
#include <Input/Input.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Platform/Global.h>

#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>

// - ------------------------------------------------------------------------------------------ - //
using namespace Input;
// - ------------------------------------------------------------------------------------------ - //
Vector2D cComponentEdit::CalcMousePos()
{
	Vector2D tempMousPos;
	if( Platform::AspectRatio < Real( 0.79 ) )
	{
		tempMousPos = Vector2D(
				Real( ( int( Mouse.x * Real( cGlobal::HudW * Real( 1.33 ) ) ) )
				- ( -Camera->Pos.x / Real( Camera->Pos.z / cGlobal::HudZoom ) )
				- ( ( Real(cGlobal::HudW) * Real( 1.33 ) ) / Real(2) ) )
				* Real( Camera->Pos.z / cGlobal::HudZoom ),
				Real( ( int( -Mouse.y * Real( cGlobal::HudH * Real( 1.33 ) ) ) )
				+ ( Camera->Pos.y / Real( Camera->Pos.z / cGlobal::HudZoom ) )
				+ ( ( Real(cGlobal::HudH * Real( 0.75 ) ) * Real( 1.33 ) ) / Real(2) ) )
				* Real( Camera->Pos.z / cGlobal::HudZoom )
		);
	}
	else
	{
		tempMousPos = Vector2D(
				Real( ( int( Mouse.x * Real( cGlobal::HudW ) ) )
				- ( -Camera->Pos.x / Real( Camera->Pos.z / cGlobal::HudZoom ) )
				- ( ( Real(cGlobal::HudW) * Real( 0.75 ) ) / Real(2) ) )
				* Real( Camera->Pos.z / cGlobal::HudZoom ),
				Real( ( int( -Mouse.y * Real( cGlobal::HudH ) ) )
				+ ( Camera->Pos.y / Real( Camera->Pos.z / cGlobal::HudZoom  ) )
				+ ( cGlobal::HudH >> 1 ) )
				* Real( Camera->Pos.z / cGlobal::HudZoom )
		);
	}
	
	return tempMousPos;
}
// - ------------------------------------------------------------------------------------------ - //
Vector2D cComponentEdit::CalcUVMousePos()
{
	Vector2D tempMousPos;
	if( Platform::AspectRatio < Real( 0.79 ) )
	{
		tempMousPos = Vector2D(
			Real( ( int( Mouse.x * Real( cGlobal::HudW * Real( 0.33 ) ) ) )
			- ( -UVCamera->Pos.x / Real( UVCamera->Pos.z / UVZoomOffsetX ) )
			- ( ( Real(cGlobal::HudW) * Real( 0.33 ) ) ) )
			* Real( UVCamera->Pos.z / UVZoomOffsetX ) / UVScale + Real( 1 )
			+ ( ( UVCamera->Pos.z - Real( 122 ) ) / Real( 122 ) ),
			Real( ( int( -Mouse.y * Real( cGlobal::HudH ) * Real( 0.25 ) )
			+ ( UVCamera->Pos.y / Real( UVCamera->Pos.z / UVZoomOffsetY ) )
			+ ( ( cGlobal::HudH * Real( 0.25 ) ) ) )
			* Real( UVCamera->Pos.z / UVZoomOffsetY ) ) / UVScale - Real( 1 )
			- ( ( UVCamera->Pos.z - Real( 611 ) ) / Real( 611 ) )
		);
	}
	else
	{
		tempMousPos =  Vector2D(
			Real( ( int( Mouse.x * Real( cGlobal::HudW * UVWidth ) ) )
			- ( -UVCamera->Pos.x / Real( UVCamera->Pos.z / UVZoomOffsetX ) )
			- ( ( Real(cGlobal::HudW) * UVWidth ) ) )
			* Real( UVCamera->Pos.z / UVZoomOffsetX ) / UVScale + Real( 1 )
			+ ( ( UVCamera->Pos.z - Real( 611 ) ) / Real( 611 ) ),
			Real( ( int( -Mouse.y * Real( cGlobal::HudH ) * UVHeight )
			+ ( UVCamera->Pos.y / Real( UVCamera->Pos.z / UVZoomOffsetY ) )
			+ ( ( cGlobal::HudH * UVHeight ) ) )
			* Real( UVCamera->Pos.z / UVZoomOffsetY ) ) / UVScale - Real( 1 )
			- ( ( UVCamera->Pos.z - Real( 618 ) ) / Real( 618 ) )
		);
	}

	tempMousPos *= UVScale;

	return tempMousPos;
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::Undo()
{
	// Resets the zoom
	if ( Button[ KEY_TAB ].Pressed() )
	{
		Camera->Pos.x = 0.0;
		Camera->Pos.y = 0.0;
		Camera->Pos.z = Real( 800.0 );
		
		Camera->View.x = Camera->Pos.x;
		Camera->View.y = Camera->Pos.y;
		Camera->View.z = 0.0;

		UVCamera->Pos.x = 128.0;
		UVCamera->Pos.y = 128.0;
		UVCamera->Pos.z = 400.0;
		
		UVCamera->View.x = UVCamera->Pos.x;
		UVCamera->View.y = UVCamera->Pos.y;
		UVCamera->View.z = 0.0;

		PreviewCamera->Pos.x = 0.0;
		PreviewCamera->Pos.y = 0.0;
		if( Platform::AspectRatio < Real( 0.79 ) )
		{
			PreviewCamera->Pos.z = cGlobal::HudZoom * ( Real( 1 ) - Real( 0.75 ) );
		}
		else
		{
			PreviewCamera->Pos.z = cGlobal::HudZoom * ( Real( 1 ) - UVHeight );
		}	
		
		PreviewCamera->View.x = PreviewCamera->Pos.x;
		PreviewCamera->View.y = PreviewCamera->Pos.y;
		PreviewCamera->View.z = 0.0;
	}	
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::ActiveAction()
{
	if( CurMode == MESH_NODE_MODE || CurMode == FACE_MODE )
	{
		MeshGenerateUV();
	}
	IsSaved = false;
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::SwitchMode()
{	
	unsigned int LastMode = CurMode;
	
	if( Button[ KEY_1 ].Pressed() )
	{
		CurMode = NODE_MODE;
	}
	else if( Button[ KEY_2 ].Pressed() )
	{
		CurMode = SPHERE_MODE;
	}
	else if( Button[ KEY_3 ].Pressed() )
	{
		CurMode = SPRING_MODE;
	}
	else if( Button[ KEY_4 ].Pressed() )
	{
		CurMode = MESH_NODE_MODE;
	}
	else if( Button[ KEY_5 ].Pressed() )
	{
		CurMode = FACE_MODE;
	}
	else if( Button[ KEY_6 ].Pressed() )
	{
		CurMode = PIVOT_HANDLE_MODE;
	}
	else if( Button[ KEY_9 ].Pressed() )
	{
		CurMode = COMP_MESH_MODE;	
	} 
	else if( Button[ KEY_0 ].Pressed() )
	{
		CurMode = COMP_BODY_MODE;	
	} 
	if( LastMode != CurMode )
	{
		if( LastMode <= SPRING_MODE && CurMode <= SPRING_MODE )
		{
			
		}
		else
		{
			CurSelected.clear();
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::BodyAddPose()
{
	if( Button[ KEY_0_PAD ].Pressed() || Button[ KEY_A ].Pressed() )
	{
/*		std::vector< Engine2D::cBody2DPose > TempPose;
		for( size_t idx = 0; idx < DynObj[ CurObj ].AnimationSet->BodyPose.size(); ++idx )
		{
			TempPose.push_back( DynObj[ CurObj ].AnimationSet->BodyPose[ idx ] );
			
			if( idx == DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].BodyPoseIndex )
			{
				TempPose.push_back( DynObj[ CurObj ].AnimationSet->BodyPose[ DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].BodyPoseIndex ] );
			}
		}
		DynObj[ CurObj ].AnimationSet->BodyPose.clear();
		DynObj[ CurObj ].AnimationSet->BodyPose.swap( TempPose );
		
		//DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].BodyPoseIndex++;
		DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].BodyPoseIndex = DynObj[ CurObj ].AnimationSet->BodyPose.size() - 1;
	*/
	
		DynObj[ CurObj ].AnimationSet->BodyPose.push_back( DynObj[ CurObj ].AnimationSet->BodyPose[ DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].BodyPoseIndex ] );
			
		DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].BodyPoseIndex = DynObj[ CurObj ].AnimationSet->BodyPose.size() - 1;
		
		DynObj[ CurObj ].Body = DynObj[ CurObj ].AnimationSet->BodyPose[ DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].BodyPoseIndex ];
		Pose = &DynObj[ CurObj ].AnimationSet->BodyPose[ DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].BodyPoseIndex ];

		ActiveAction();
		CurMode = NODE_MODE;
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::BodyDeletePose()
{
	if( Button[ KEY_DELETE ].Pressed() && DynObj[ CurObj ].AnimationSet->BodyPose.size() > 1 )
	{
		std::vector< Engine2D::cBody2DPose > TempPose;
		size_t DeleteIdx = DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].BodyPoseIndex;
		for( size_t idx = 0; idx < DynObj[ CurObj ].AnimationSet->BodyPose.size(); ++idx )
		{
			if( idx != DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].BodyPoseIndex )
			{
				TempPose.push_back( DynObj[ CurObj ].AnimationSet->BodyPose[ idx ] );
			}
		}
		DynObj[ CurObj ].AnimationSet->BodyPose.clear();
		DynObj[ CurObj ].AnimationSet->BodyPose.swap( TempPose );
		
		if( DeleteIdx >= DynObj[ CurObj ].AnimationSet->MeshPose.size() )
		{
			for( size_t idx = 0; idx < DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame.size(); ++idx )
			{
				if( DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame[ idx ].BodyPoseIndex >= DeleteIdx )
				{
					--DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame[ idx ].BodyPoseIndex;
				}
			}
		}
		else
		{
			for( size_t idx = 0; idx < DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame.size(); ++idx )
			{
				if( DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame[ idx ].BodyPoseIndex > DeleteIdx )
				{
					--DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame[ idx ].BodyPoseIndex;
				}
			}				
		}
		
	
		DynObj[ CurObj ].Body = DynObj[ CurObj ].AnimationSet->BodyPose[ DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].BodyPoseIndex ];
		Pose = &DynObj[ CurObj ].AnimationSet->BodyPose[ DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].BodyPoseIndex ];
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::MeshAddPose()
{
	if( Button[ KEY_0_PAD ].Pressed() || Button[ KEY_A ].Pressed() )
	{
		DynObj[ CurObj ].AnimationSet->MeshPose.push_back( DynObj[ CurObj ].AnimationSet->MeshPose[ DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].MeshPoseIndex ] );
			
		DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].MeshPoseIndex = DynObj[ CurObj ].AnimationSet->MeshPose.size() - 1;

		CurMode = MESH_NODE_MODE;
		ActiveAction();
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::MeshDeletePose()
{
	if( Button[ KEY_DELETE ].Pressed() && DynObj[ CurObj ].AnimationSet->MeshPose.size() > 1 )
	{
		std::vector< Engine2D::cMesh2DPose > TempPose;
		size_t DeleteIdx = DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].MeshPoseIndex;
		for( size_t idx = 0; idx < DynObj[ CurObj ].AnimationSet->MeshPose.size(); ++idx )
		{
			if( idx != DeleteIdx )
			{
				TempPose.push_back( DynObj[ CurObj ].AnimationSet->MeshPose[ idx ] );
			}
		}
		DynObj[ CurObj ].AnimationSet->MeshPose.clear();
		DynObj[ CurObj ].AnimationSet->MeshPose.swap( TempPose );
		
		if( DeleteIdx >= DynObj[ CurObj ].AnimationSet->MeshPose.size() )
		{
			for( size_t idx = 0; idx < DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame.size(); ++idx )
			{
				if( DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame[ idx ].MeshPoseIndex >= DeleteIdx )
				{
					--DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame[ idx ].MeshPoseIndex;
				}
			}
		}
		else
		{
			for( size_t idx = 0; idx < DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame.size(); ++idx )
			{
				if( DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame[ idx ].MeshPoseIndex > DeleteIdx )
				{
					--DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame[ idx ].MeshPoseIndex;
				}
			}
		}

		ActiveAction();
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::BodySwitchPose( size_t MyFrame )
{
	if( Button[ KEY_N ].Pressed() || EditEventFlags & flGlobalDecrease )
	{
		if( DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame[ MyFrame ].BodyPoseIndex > 0 )
		{
			--DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame[ MyFrame ].BodyPoseIndex;
		}
		else
		{
			DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame[ MyFrame ].BodyPoseIndex = DynObj[ CurObj ].AnimationSet->BodyPose.size() - 1;
		}
		
		DynObj[ CurObj ].Body = DynObj[ CurObj ].AnimationSet->BodyPose[ DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame[ MyFrame ].BodyPoseIndex ];
		Pose = &DynObj[ CurObj ].AnimationSet->BodyPose[ DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame[ MyFrame ].BodyPoseIndex ];
		MeshGenerateUV();
		CurSelected.clear();
	}
	//else if ( Button[ KEY_RIGHT ].Pressed() )
	else if( Button[ KEY_M ].Pressed() || EditEventFlags & flGlobalIncrease )
	{
		if( DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame[ MyFrame ].BodyPoseIndex < DynObj[ CurObj ].AnimationSet->BodyPose.size() - 1 )
		{
			++DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame[ MyFrame ].BodyPoseIndex;
		}
		else
		{
			DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame[ MyFrame ].BodyPoseIndex = 0;	
		}
		
		DynObj[ CurObj ].Body = DynObj[ CurObj ].AnimationSet->BodyPose[ DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame[ MyFrame ].BodyPoseIndex ];
		Pose = &DynObj[ CurObj ].AnimationSet->BodyPose[ DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame[ MyFrame ].BodyPoseIndex ];
		MeshGenerateUV();
		CurSelected.clear();
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::MeshSwitchPose( size_t MyFrame )
{
	if ( Button[ KEY_J ].Pressed() || EditEventFlags & flGlobalDecrease )
	{
		if(	!DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame.empty() )
		{
			if( DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame[ MyFrame ].MeshPoseIndex > 0 )
			{
				--DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame[ MyFrame ].MeshPoseIndex;
			}
			else
			{
				DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame[ MyFrame ].MeshPoseIndex = DynObj[ CurObj ].AnimationSet->MeshPose.size() - 1;
			}
		
			MeshGenerateUV();
			CurSelected.clear();
		}
	}
	else if ( Button[ KEY_K ].Pressed() || EditEventFlags & flGlobalIncrease )
	{
		if(	!DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame.empty() )
		{
			if( DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame[ MyFrame ].MeshPoseIndex < DynObj[ CurObj ].AnimationSet->MeshPose.size() - 1 )
			{
				++DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame[ MyFrame ].MeshPoseIndex;
			}
			else
			{
				DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame[ MyFrame ].MeshPoseIndex = 0;	
			}
			
			MeshGenerateUV();
			CurSelected.clear();
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::MeshSwitchAnim()
{
	if( Button[ KEY_O ].Pressed() )
	{
		if( CurMeshAnim > 0 )
		{
			--CurMeshAnim;
		}
		else
		{
			CurMeshAnim = AnimationGenerator.Animation.size() - 1;
		}
		CurMeshFrame = 0;
		CurSelected.clear();
		MeshGenerateUV();
	}
	else if( Button[ KEY_P ].Pressed() )
	{
		if( CurMeshAnim < AnimationGenerator.Animation.size() - 1 )
		{
			++CurMeshAnim;
		}
		else
		{
			CurMeshAnim = 0;	
		}
		CurMeshFrame = 0;
		CurSelected.clear();
		MeshGenerateUV();
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::MeshSwitchFrame()
{
	if ( Button[ KEY_LEFT ].Pressed() ) 
	{
		if( CurMeshFrame > 0 )
		{
			--CurMeshFrame;
		}
		else
		{
			CurMeshFrame = AnimationGenerator.Animation[ CurMeshAnim ].Frame.size() - 1;
		}
		
		DynObj[ CurObj ].Body = DynObj[ CurObj ].AnimationSet->BodyPose[ DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].BodyPoseIndex ];
		Pose = &DynObj[ CurObj ].AnimationSet->BodyPose[ DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].BodyPoseIndex ];

		MeshGenerateUV();
		CurSelected.clear();
	}
	else if ( Button[ KEY_RIGHT ].Pressed() )
	{
		if( CurMeshFrame < AnimationGenerator.Animation[ CurMeshAnim ].Frame.size() - 1 )
		{
			++CurMeshFrame;
		}
		else
		{
			CurMeshFrame = 0;	
		}
		
		DynObj[ CurObj ].Body = DynObj[ CurObj ].AnimationSet->BodyPose[ DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].BodyPoseIndex ];
		Pose = &DynObj[ CurObj ].AnimationSet->BodyPose[ DynObj[ CurObj ].AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].BodyPoseIndex ];
		
		MeshGenerateUV();
		CurSelected.clear();
	}
}
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
