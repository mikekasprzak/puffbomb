#ifdef EDITOR
// - ------------------------------------------------------------------------------------------ - //
#include "ComponentEdit.h"

#include <Graphics/Gfx.h>
#include <Font/Fonts.h>
#include <Util/String.h>
#include <Global.h>
// - ------------------------------------------------------------------------------------------ - //
#include <sstream>
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::DisplayText()
{
	if( CurMode == NODE_MODE )
	{
		DisplayNodeInfo();
	}
	else if( CurMode == SPHERE_MODE )
	{	
		DisplaySphereInfo();
	}
	else if( CurMode == SPRING_MODE )
	{	
		DisplaySpringInfo();
	}
	else if( CurMode == MESH_NODE_MODE || CurMode == PIVOT_HANDLE_MODE )
	{	
		DisplayMeshNodeInfo();
	}
	
	DisplayMode();
	
	DisplayComponentInfo();
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::DisplayNodeInfo()
{
	if( CurSelected.size() > 0 )
	{
		Real FontSize = 0.5;
		Real XShift = 120;
		Real YShift = 40;
		Real XPos = 0;
		Real YPos = 0;
		
		if( Global::AspectRatio < Real( 0.79 ) )
		{
			YPos = Global::HudH * 0.25;
		}
		int Color = Gfx::RGBA( 255, 255, 255, 255 );
		std::stringstream Temp;
		
		// Displays the current node number //
		// - ---------------------------------------------------------------------------------- - //
		cFonts::FlangeLight.Write(
			"Node #",
			Vector3D( Global::Left + XPos, Global::Bottom + YPos + YShift, 0.0 ),
			FontSize,
			Color
		);
		
		Temp << CurSelected[0];
	
		cFonts::FlangeLight.Write(
			Temp.str(),
			Vector3D( Global::Left + XPos, Global::Bottom + YPos + Real( 6 ), 0.0 ),
			FontSize,
			Color
		);
		XPos += XShift;
		Temp.str(std::string());
		// Displays the X location of the node //
		// - ---------------------------------------------------------------------------------- - //
		cFonts::FlangeLight.Write(
			"Node X",
			Vector3D( Global::Left + XPos, Global::Bottom + YPos + YShift, 0.0 ),
			FontSize,
			Color
		);
		
		Temp << Pose->Node[ CurSelected[0] ].Pos.x;
	
		cFonts::FlangeLight.Write(
			Temp.str(),
			Vector3D( Global::Left + XPos, Global::Bottom + YPos + Real( 6 ), 0.0 ),
			FontSize,
			Color
		);
		XPos += XShift;
		Temp.str(std::string());
		// Displays the Y location of the node //
		// - ---------------------------------------------------------------------------------- - //
		cFonts::FlangeLight.Write(
			"Node Y",
			Vector3D( Global::Left + XPos, Global::Bottom + YPos + YShift, 0.0 ),
			FontSize,
			Color
		);
		
		Temp << Pose->Node[ CurSelected[0] ].Pos.y;
	
		cFonts::FlangeLight.Write(
			Temp.str(),
			Vector3D( Global::Left + XPos, Global::Bottom + YPos + Real( 6 ), 0.0 ),
			FontSize,
			Color
		);
		XPos += XShift;
		Temp.str(std::string());
		// Displays the current mass //
		// - ---------------------------------------------------------------------------------- - //
		cFonts::FlangeLight.Write(
			"Mass",
			Vector3D( Global::Left + XPos, Global::Bottom + YPos + YShift, 0.0 ),
			FontSize,
			Color
		);
		
		Temp << Pose->Node[ CurSelected[0] ].Mass;
	
		cFonts::FlangeLight.Write(
			Temp.str(),
			Vector3D( Global::Left + XPos, Global::Bottom + YPos + Real( 6 ), 0.0 ),
			FontSize,
			Color
		);
		XPos += XShift;
		Temp.str(std::string());
		// Displays the total mass //
		// - ---------------------------------------------------------------------------------- - //
		cFonts::FlangeLight.Write(
			"Total Mass",
			Vector3D( Global::Left + XPos, Global::Bottom + YPos + YShift, 0.0 ),
			FontSize,
			Color
		);
		
		//Temp << Body2D[ CurBody ].Nodes.TotalMass;
		Temp << DynObj->Body.Nodes.TotalMass;
	
		cFonts::FlangeLight.Write(
			Temp.str(),
			Vector3D( Global::Left + XPos, Global::Bottom + YPos + Real( 6 ), 0.0 ),
			FontSize,
			Color
		);

		
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::DisplaySphereInfo()
{
	if( CurSelected.size() > 0 && DynObj->Body.SphereSize() > 0 )
	{
		Real FontSize = 0.5;
		Real XShift = 120;
		Real YShift = 40;
		Real XPos = 0;
		Real YPos = 0;
		
		if( Global::AspectRatio < Real( 0.79 ) )
		{
			YPos = Global::HudH * 0.25;
		}
		int Color = Gfx::RGBA( 255, 255, 255, 255 );
		std::stringstream Temp;
		
		int SphereIdx = -1;
		for( size_t idx = 0; idx < DynObj->Body.SphereSize(); ++idx )
		{
			if( CurSelected[0] == DynObj->Body.Sphere( idx ).Index )
			{
				SphereIdx = idx;
				break;
			}
		}
		
		if( SphereIdx != -1 )
		{
			// Displays the current sphere number //
			// - ---------------------------------------------------------------------------------- - //
			cFonts::FlangeLight.Write(
				"Sphere#",
				Vector3D( Global::Left + XPos, Global::Bottom + YPos + YShift, 0.0 ),
				FontSize,
				Color
			);
			
			Temp << SphereIdx;
		
			cFonts::FlangeLight.Write(
				Temp.str(),
				Vector3D( Global::Left + XPos, Global::Bottom + YPos + Real( 6 ), 0.0 ),
				FontSize,
				Color
			);
			XPos += XShift;
			Temp.str(std::string());
			// Displays the sphere radius //
			// - ---------------------------------------------------------------------------------- - //
			cFonts::FlangeLight.Write(
				"Radius",
				Vector3D( Global::Left + XPos, Global::Bottom + YPos + YShift, 0.0 ),
				FontSize,
				Color
			);
			
			Temp << DynObj->Body.Sphere( SphereIdx ).Radius;
		
			cFonts::FlangeLight.Write(
				Temp.str(),
				Vector3D( Global::Left + XPos, Global::Bottom + YPos + Real( 6 ), 0.0 ),
				FontSize,
				Color
			);
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::DisplaySpringInfo()
{
	if( CurSelected.size() > 0 && DynObj->Body.SpringSize() > 0 )
	{
		Real FontSize = 0.5;
		Real XShift = 120;
		Real YShift = 40;
		Real XPos = 0;
		Real YPos = 0;
		
		if( Global::AspectRatio < Real( 0.79 ) )
		{
			YPos = Global::HudH * 0.25;
		}
		int Color = Gfx::RGBA( 255, 255, 255, 255 );
		std::stringstream Temp;
			
		int SpringNum = -1;
		for( size_t SpringIdx = 0; SpringIdx < DynObj->Body.SpringSize(); ++SpringIdx )
		{
			for( size_t idx = 0; idx < CurSelected.size(); ++idx )
			{
				for( size_t i = idx + 1; i < CurSelected.size(); ++i )
				{
					if( DynObj->Body.Spring( SpringIdx ).IndexA == CurSelected[idx] )
					{
						if( DynObj->Body.Spring( SpringIdx ).IndexB == CurSelected[i] )
						{
							SpringNum = SpringIdx;
							break;
						}
					}
					if( DynObj->Body.Spring( SpringIdx ).IndexB == CurSelected[idx] )
					{
						if( DynObj->Body.Spring( SpringIdx ).IndexA == CurSelected[i] )
						{
							SpringNum = SpringIdx;
							break;
						}
					}
					if( SpringNum != -1 )
						break;
				}
				if( SpringNum != -1 )
					break;
			}
		}		
		if( SpringNum != -1 )
		{
			// Displays current spring number //
			// - ---------------------------------------------------------------------------------- - //
			cFonts::FlangeLight.Write(
				"Spring#",
				Vector3D( Global::Left + XPos, Global::Bottom + YShift, 0.0 ),
				FontSize,
				Color
			);
			
			Temp << SpringNum;
		
			cFonts::FlangeLight.Write(
				Temp.str(),
				Vector3D( Global::Left + XPos, Global::Bottom + Real( 6 ), 0.0 ),
				FontSize,
				Color
			);
			XPos += XShift;
			Temp.str(std::string());
			// Displays current node A number //
			// - ---------------------------------------------------------------------------------- - //
			cFonts::FlangeLight.Write(
				"Node A",
				Vector3D( Global::Left + XPos, Global::Bottom + YShift, 0.0 ),
				FontSize,
				Color
			);
			
			Temp << DynObj->Body.Spring(SpringNum).IndexA;
		
			cFonts::FlangeLight.Write(
				Temp.str(),
				Vector3D( Global::Left + XPos, Global::Bottom + Real( 6 ), 0.0 ),
				FontSize,
				Color
			);
			XPos += XShift;
			Temp.str(std::string());
			// Displays current node B number //
			// - ---------------------------------------------------------------------------------- - //
			cFonts::FlangeLight.Write(
				"Node B",
				Vector3D( Global::Left + XPos, Global::Bottom + YShift, 0.0 ),
				FontSize,
				Color
			);
			
			Temp << DynObj->Body.Spring(SpringNum).IndexB;
		
			cFonts::FlangeLight.Write(
				Temp.str(),
				Vector3D( Global::Left + XPos, Global::Bottom + Real( 6 ), 0.0 ),
				FontSize,
				Color
			);
			XPos += XShift;
			Temp.str(std::string());
			// Displays current spring strength //
			// - ---------------------------------------------------------------------------------- - //
			cFonts::FlangeLight.Write(
				"Strength",
				Vector3D( Global::Left + XPos, Global::Bottom + YShift, 0.0 ),
				FontSize,
				Color
			);
			
			Temp << DynObj->Body.Spring(SpringNum).Strength;
		
			cFonts::FlangeLight.Write(
				Temp.str(),
				Vector3D( Global::Left + XPos, Global::Bottom + Real( 6 ), 0.0 ),
				FontSize,
				Color
			);
			XPos += XShift;
			Temp.str(std::string());
			// Displays current spring length //
			// - ---------------------------------------------------------------------------------- - //
			cFonts::FlangeLight.Write(
				"Length",
				Vector3D( Global::Left + XPos, Global::Bottom + YShift, 0.0 ),
				FontSize,
				Color
			);
			
			Temp << DynObj->Body.Spring(SpringNum).Length;
		
			cFonts::FlangeLight.Write(
				Temp.str(),
				Vector3D( Global::Left + XPos, Global::Bottom + Real( 6 ), 0.0 ),
				FontSize,
				Color
			);
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::DisplayMeshNodeInfo()
{
	if(	!DynObj->AnimationSet->Animation[ CurMeshAnim ].Frame.empty() && CurSelected.size() > 0 )
	{
		Real FontSize = 0.5;
		Real XShift = 120;
		Real YShift = 40;
		Real XPos = 0;
		Real YPos = 0;
		
		if( Global::AspectRatio < Real( 0.79 ) )
		{
			YPos = Global::HudH * 0.25;
		}
		int Color = Gfx::RGBA( 255, 255, 255, 255 );
		std::stringstream Temp;
		
		// Displays the current node number //
		// - ---------------------------------------------------------------------------------- - //
		cFonts::FlangeLight.Write(
			"Node #",
			Vector3D( Global::Left + XPos, Global::Bottom + YPos + YShift, 0.0 ),
			FontSize,
			Color
		);
		
		Temp << CurSelected[0];
	
		cFonts::FlangeLight.Write(
			Temp.str(),
			Vector3D( Global::Left + XPos, Global::Bottom + YPos + Real( 6 ), 0.0 ),
			FontSize,
			Color
		);
		XPos += XShift;
		Temp.str(std::string());
		// Displays the X location of the node //
		// - ---------------------------------------------------------------------------------- - //
		cFonts::FlangeLight.Write(
			"Node X",
			Vector3D( Global::Left + XPos, Global::Bottom + YPos + YShift, 0.0 ),
			FontSize,
			Color
		);
		
		Temp << DynObj->AnimationSet->MeshPose[ DynObj->AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].MeshPoseIndex ].Node[ CurSelected[0] ].Pos.x;
	
		cFonts::FlangeLight.Write(
			Temp.str(),
			Vector3D( Global::Left + XPos, Global::Bottom + YPos + Real( 6 ), 0.0 ),
			FontSize,
			Color
		);
		XPos += XShift;
		Temp.str(std::string());
		// Displays the Y location of the node //
		// - ---------------------------------------------------------------------------------- - //
		cFonts::FlangeLight.Write(
			"Node Y",
			Vector3D( Global::Left + XPos, Global::Bottom + YPos + YShift, 0.0 ),
			FontSize,
			Color
		);
		
		Temp << DynObj->AnimationSet->MeshPose[ DynObj->AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].MeshPoseIndex ].Node[ CurSelected[0] ].Pos.y;
	
		cFonts::FlangeLight.Write(
			Temp.str(),
			Vector3D( Global::Left + XPos, Global::Bottom + YPos + Real( 6 ), 0.0 ),
			FontSize,
			Color
		);
		XPos += XShift;
		Temp.str(std::string());
		// Displays the Pivot of the node //
		// - ---------------------------------------------------------------------------------- - //
		cFonts::FlangeLight.Write(
			"Pivot",
			Vector3D( Global::Left + XPos, Global::Bottom + YPos + YShift, 0.0 ),
			FontSize,
			Color
		);
		
		Temp << DynObj->AnimationSet->MeshPose[ DynObj->AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].MeshPoseIndex ].Node[ CurSelected[0] ].PivotIndex;
	
		cFonts::FlangeLight.Write(
			Temp.str(),
			Vector3D( Global::Left + XPos, Global::Bottom + YPos + Real( 6 ), 0.0 ),
			FontSize,
			Color
		);
		XPos += XShift;
		Temp.str(std::string());
		// Displays the Handle of the node //
		// - ---------------------------------------------------------------------------------- - //
		cFonts::FlangeLight.Write(
			"Handle",
			Vector3D( Global::Left + XPos, Global::Bottom + YPos + YShift, 0.0 ),
			FontSize,
			Color
		);
		
		Temp << DynObj->AnimationSet->MeshPose[ DynObj->AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].MeshPoseIndex ].Node[ CurSelected[0] ].HandleIndex;
	
		cFonts::FlangeLight.Write(
			Temp.str(),
			Vector3D( Global::Left + XPos, Global::Bottom + YPos + Real( 6 ), 0.0 ),
			FontSize,
			Color
		);
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::DisplayMode()
{
	// Displays the current edit mode //
	// - -------------------------------------------------------------------------------------- - //
	Real FontSize = 0.5;
	int Color = Gfx::RGBA( 255, 100, 100, 255 );
	Vector3D ModePos = Vector3D( Global::Right - Real( 250 ), Global::Top - Real( 30 ), 0.0 );
		
	switch( CurMode )
	{ 
		case NODE_MODE:
		{
			cFonts::FlangeLight.Write(
				"BodyNode Mode",
				ModePos,
				FontSize,
				Color
			);
			break;
		}
		case SPHERE_MODE:
		{
			cFonts::FlangeLight.Write(
				"Sphere Mode",
				ModePos,
				FontSize,
				Color
			);
			break;
		}
		case SPRING_MODE:
		{
			cFonts::FlangeLight.Write(
				"Spring Mode",
				ModePos,
				FontSize,
				Color
			);
			break;
		}
		case MESH_NODE_MODE:
		{
			cFonts::FlangeLight.Write(
				"MeshNode Mode",
				ModePos,
				FontSize,
				Color
			);
			break;
		}
		case PIVOT_HANDLE_MODE:
		{
			cFonts::FlangeLight.Write(
				"Pivot Handle Mode",
				ModePos,
				FontSize,
				Color
			);
			break;
		}
		case FACE_MODE:
		{
			cFonts::FlangeLight.Write(
				"Face Mode",
				ModePos,
				FontSize,
				Color
			);
			break;
		}
		case COMP_BODY_MODE:
		{
			cFonts::FlangeLight.Write(
				"CompBody Mode",
				ModePos,
				FontSize,
				Color
			);
			break;
		}
		case COMP_MESH_MODE:
		{
			cFonts::FlangeLight.Write(
				"CompMesh Mode",
				ModePos,
				FontSize,
				Color
			);
			break;
		}
		default:
		{
			break;	
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::DisplayComponentInfo()
{

	if( !IsSaved )
	{
		cFonts::FlangeLight.Write(
			"*",
			Vector3D( Global::Left + Real( 1 ), Global::Top - Real( 56 ), 0.0 ),
			Real( 1.0 ),
			Gfx::RGBA( 255, 255, 255, 255 )
		);
	}
	
	cFonts::FlangeLight.Write(
		"Component Editor",
		Vector3D( Global::Left + Real( 20 ), Global::Top - Real( 30 ), 0.0 ),
		Real( 0.5 ),
		Gfx::RGBA( 100, 100, 255, 255 )
	);

	std::stringstream Temp;

	cFonts::FlangeLight.Write(
		"Current Frame",
		Vector3D( Global::Right - Real( 600 ), Global::Top - Real( 30 ), 0.0 ),
		Real( 0.5 ),
		Gfx::RGBA( 100, 255, 100, 255 )
	);
	
	Temp << CurMeshFrame;

	cFonts::FlangeLight.Write(
		Temp.str(),
		Vector3D( Global::Right - Real( 400 ), Global::Top - Real( 30 ), 0.0 ),
		Real( 0.5 ),
		Gfx::RGBA( 100, 255, 100, 255 )
	);
	
	Temp.str(std::string());

	cFonts::FlangeLight.Write(
		"Component Dir",
		Vector3D( Global::Left + Real( 6 ), Global::Top - Real( 60 ), 0.0 ),
		Real( 0.5 ),
		Gfx::RGBA( 100, 100, 255, 255 )
	);

	cFonts::FlangeLight.Write(
		CompDirs[ CurDirIdx ],
		Vector3D( Global::Left + Real( 270 ), Global::Top - Real( 60 ), 0.0 ),
		Real( 0.5 ),
		Gfx::RGBA( 100, 100, 255, 255 )
	);

	Temp.str(std::string());

	int MyColor = Gfx::RGBA( 255, 255, 255, 255 );

	cFonts::FlangeLight.Write(
		"Current Animation",
		Vector3D( Global::Left + Real( 6 ), Global::Top - Real( 90 ), 0.0 ),
		Real( 0.5 ),
		MyColor
	);
	
	Temp << CurMeshAnim;

	cFonts::FlangeLight.Write(
		Temp.str(),
		Vector3D( Global::Left + Real( 270 ), Global::Top - Real( 90 ), 0.0 ),
		Real( 0.5 ),
		MyColor
	);
	
	Temp.str(std::string());
	
	if(	!DynObj->AnimationSet->Animation[ CurMeshAnim ].Frame.empty() )
	{

		if( CurMode == COMP_BODY_MODE )
		{
			MyColor = Gfx::RGBA( 255, 100, 100, 255 );
		}
	
		cFonts::FlangeLight.Write(
			"BodyPoseIndex",
			Vector3D( Global::Left + Real( 6 ), Global::Top - Real( 120 ), 0.0 ),
			Real( 0.5 ),
			MyColor
		);
		
		Temp << DynObj->AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].BodyPoseIndex;
	
		cFonts::FlangeLight.Write(
			Temp.str(),
			Vector3D( Global::Left + Real( 270 ), Global::Top - Real( 120 ), 0.0 ),
			Real( 0.5 ),
			MyColor
		);
	
		Temp.str(std::string());
		MyColor = Gfx::RGBA( 255, 255, 255, 255 );
		
		if( CurMode == COMP_MESH_MODE )
		{
			MyColor = Gfx::RGBA( 255, 100, 100, 255 );
		}
		
		cFonts::FlangeLight.Write(
			"MeshPoseIndex",
			Vector3D( Global::Left + Real( 6 ), Global::Top - Real( 150 ), 0.0 ),
			Real( 0.5 ),
			MyColor
		);
		
		Temp << DynObj->AnimationSet->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].MeshPoseIndex;
	
		cFonts::FlangeLight.Write(
			Temp.str(),
			Vector3D( Global::Left + Real( 270 ), Global::Top - Real( 150 ), 0.0 ),
			Real( 0.5 ),
			MyColor
		);
		
		Temp.str(std::string());
	
		Temp << TextureName[ AnimationGenerator->Animation[ CurMeshAnim ].Frame[ CurMeshFrame ].ImageIndex ];
	
		cFonts::FlangeLight.Write(
			Temp.str(),
			Vector3D( Global::Left + Real( 6 ), Global::Top - Real( 180 ), 0.0 ),
			Real( 0.5 ),
			MyColor
		);
	}

	int EqualNodeSizes = Pose->Node.size();
	int EqualSphereSizes = Pose->Sphere.size();
	int EqualSpringSizes = Pose->Spring.size();
	
	for( size_t idx = 0; idx < DynObj->AnimationSet->BodyPose.size(); ++idx )
	{
		if( EqualNodeSizes != int( DynObj->AnimationSet->BodyPose[idx].Node.size() ) )
		{
			EqualNodeSizes = -1;
		}
		if( EqualSphereSizes != int( DynObj->AnimationSet->BodyPose[idx].Sphere.size() ) )
		{
			EqualSphereSizes = -1;
		}
		if( EqualSpringSizes != int( DynObj->AnimationSet->BodyPose[idx].Spring.size() ) )
		{
			EqualSpringSizes = -1;
		}
	}
	if( EqualNodeSizes == -1 )
	{
		cFonts::FlangeLight.Write(
			"Unequal node sizes",
			Vector3D( Global::Right - Real( 600 ), Global::Top - Real( 110 ), 0.0 ),
			Real( 0.5 ),
			Gfx::RGBA( 255, 0, 0, 255 )
		);
	}
	if( EqualSphereSizes == -1 )
	{
		cFonts::FlangeLight.Write(
			"Unequal sphere sizes",
			Vector3D( Global::Right - Real( 600 ), Global::Top - Real( 150 ), 0.0 ),
			Real( 0.5 ),
			Gfx::RGBA( 255, 0, 0, 255 )
		);
	}
	if( EqualSpringSizes == -1 )
	{
		cFonts::FlangeLight.Write(
			"Unequal spring sizes",
			Vector3D( Global::Right - Real( 600 ), Global::Top - Real( 190 ), 0.0 ),
			Real( 0.5 ),
			Gfx::RGBA( 255, 0, 0, 255 )
		);
	}
}
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
