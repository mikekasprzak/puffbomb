#ifdef EDITOR
// - ------------------------------------------------------------------------------------------ - //
#include "ComponentEdit.h"

#include <Graphics/Gfx.h>
#include <Font/Fonts.h>
#include <Util/String.h>
#include <Platform/Global.h>
// - ------------------------------------------------------------------------------------------ - //
#include <sstream>
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::DisplayText()
{
	if( !DynObj.empty() )
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
		
		if( Platform::AspectRatio < Real( 0.79 ) )
		{
			YPos = cGlobal::HudH * 0.25;
		}
		int Color = gfx::RGBA( 255, 255, 255, 255 );
		std::stringstream Temp;
		
		// Displays the current node number //
		// - ---------------------------------------------------------------------------------- - //
		cFonts::FlangeLight.Write(
			"Node #",
			Vector3D( cGlobal::Left + XPos, cGlobal::Bottom + YPos + YShift, 0.0 ),
			FontSize,
			Color
		);
		
		Temp << CurSelected[0];
	
		cFonts::FlangeLight.Write(
			Temp.str(),
			Vector3D( cGlobal::Left + XPos, cGlobal::Bottom + YPos + Real( 6 ), 0.0 ),
			FontSize,
			Color
		);
		XPos += XShift;
		Temp.str(std::string());
		// Displays the X location of the node //
		// - ---------------------------------------------------------------------------------- - //
		cFonts::FlangeLight.Write(
			"Node X",
			Vector3D( cGlobal::Left + XPos, cGlobal::Bottom + YPos + YShift, 0.0 ),
			FontSize,
			Color
		);
		
		Temp << Pose->Node[ CurSelected[0] ].Pos.x;
	
		cFonts::FlangeLight.Write(
			Temp.str(),
			Vector3D( cGlobal::Left + XPos, cGlobal::Bottom + YPos + Real( 6 ), 0.0 ),
			FontSize,
			Color
		);
		XPos += XShift;
		Temp.str(std::string());
		// Displays the Y location of the node //
		// - ---------------------------------------------------------------------------------- - //
		cFonts::FlangeLight.Write(
			"Node Y",
			Vector3D( cGlobal::Left + XPos, cGlobal::Bottom + YPos + YShift, 0.0 ),
			FontSize,
			Color
		);
		
		Temp << Pose->Node[ CurSelected[0] ].Pos.y;
	
		cFonts::FlangeLight.Write(
			Temp.str(),
			Vector3D( cGlobal::Left + XPos, cGlobal::Bottom + YPos + Real( 6 ), 0.0 ),
			FontSize,
			Color
		);
		XPos += XShift;
		Temp.str(std::string());
		// Displays the current mass //
		// - ---------------------------------------------------------------------------------- - //
		cFonts::FlangeLight.Write(
			"Mass",
			Vector3D( cGlobal::Left + XPos, cGlobal::Bottom + YPos + YShift, 0.0 ),
			FontSize,
			Color
		);
		
		Temp << Pose->Node[ CurSelected[0] ].Mass;
	
		cFonts::FlangeLight.Write(
			Temp.str(),
			Vector3D( cGlobal::Left + XPos, cGlobal::Bottom + YPos + Real( 6 ), 0.0 ),
			FontSize,
			Color
		);
		XPos += XShift;
		Temp.str(std::string());
		// Displays the total mass //
		// - ---------------------------------------------------------------------------------- - //
		cFonts::FlangeLight.Write(
			"Total Mass",
			Vector3D( cGlobal::Left + XPos, cGlobal::Bottom + YPos + YShift, 0.0 ),
			FontSize,
			Color
		);
		
		//Temp << Body2D[ CurBody ].Nodes.TotalMass;
		Temp << DynObj[ CurObj ].Body.Nodes.TotalMass;
	
		cFonts::FlangeLight.Write(
			Temp.str(),
			Vector3D( cGlobal::Left + XPos, cGlobal::Bottom + YPos + Real( 6 ), 0.0 ),
			FontSize,
			Color
		);

		
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::DisplaySphereInfo()
{
	if( CurSelected.size() > 0 && DynObj[ CurObj ].Body.SphereSize() > 0 )
	{
		Real FontSize = 0.5;
		Real XShift = 120;
		Real YShift = 40;
		Real XPos = 0;
		Real YPos = 0;
		
		if( Platform::AspectRatio < Real( 0.79 ) )
		{
			YPos = cGlobal::HudH * 0.25;
		}
		int Color = gfx::RGBA( 255, 255, 255, 255 );
		std::stringstream Temp;
		
		int SphereIdx = -1;
		for( size_t idx = 0; idx < DynObj[ CurObj ].Body.SphereSize(); ++idx )
		{
			if( CurSelected[0] == DynObj[ CurObj ].Body.Sphere( idx ).Index )
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
				Vector3D( cGlobal::Left + XPos, cGlobal::Bottom + YPos + YShift, 0.0 ),
				FontSize,
				Color
			);
			
			Temp << SphereIdx;
		
			cFonts::FlangeLight.Write(
				Temp.str(),
				Vector3D( cGlobal::Left + XPos, cGlobal::Bottom + YPos + Real( 6 ), 0.0 ),
				FontSize,
				Color
			);
			XPos += XShift;
			Temp.str(std::string());
			// Displays the sphere radius //
			// - ---------------------------------------------------------------------------------- - //
			cFonts::FlangeLight.Write(
				"Radius",
				Vector3D( cGlobal::Left + XPos, cGlobal::Bottom + YPos + YShift, 0.0 ),
				FontSize,
				Color
			);
			
			Temp << DynObj[ CurObj ].Body.Sphere( SphereIdx ).Radius;
		
			cFonts::FlangeLight.Write(
				Temp.str(),
				Vector3D( cGlobal::Left + XPos, cGlobal::Bottom + YPos + Real( 6 ), 0.0 ),
				FontSize,
				Color
			);
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::DisplaySpringInfo()
{
	if( CurSelected.size() > 0 && DynObj[ CurObj ].Body.SpringSize() > 0 )
	{
		Real FontSize = 0.5;
		Real XShift = 120;
		Real YShift = 40;
		Real XPos = 0;
		Real YPos = 0;
		
		if( Platform::AspectRatio < Real( 0.79 ) )
		{
			YPos = cGlobal::HudH * 0.25;
		}
		int Color = gfx::RGBA( 255, 255, 255, 255 );
		std::stringstream Temp;
			
		int SpringNum = -1;
		for( size_t SpringIdx = 0; SpringIdx < DynObj[ CurObj ].Body.SpringSize(); ++SpringIdx )
		{
			for( size_t idx = 0; idx < CurSelected.size(); ++idx )
			{
				for( size_t i = idx + 1; i < CurSelected.size(); ++i )
				{
					if( DynObj[ CurObj ].Body.Spring( SpringIdx ).IndexA == CurSelected[idx] )
					{
						if( DynObj[ CurObj ].Body.Spring( SpringIdx ).IndexB == CurSelected[i] )
						{
							SpringNum = SpringIdx;
							break;
						}
					}
					if( DynObj[ CurObj ].Body.Spring( SpringIdx ).IndexB == CurSelected[idx] )
					{
						if( DynObj[ CurObj ].Body.Spring( SpringIdx ).IndexA == CurSelected[i] )
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
				Vector3D( cGlobal::Left + XPos, cGlobal::Bottom + YShift, 0.0 ),
				FontSize,
				Color
			);
			
			Temp << SpringNum;
		
			cFonts::FlangeLight.Write(
				Temp.str(),
				Vector3D( cGlobal::Left + XPos, cGlobal::Bottom + Real( 6 ), 0.0 ),
				FontSize,
				Color
			);
			XPos += XShift;
			Temp.str(std::string());
			// Displays current node A number //
			// - ---------------------------------------------------------------------------------- - //
			cFonts::FlangeLight.Write(
				"Node A",
				Vector3D( cGlobal::Left + XPos, cGlobal::Bottom + YShift, 0.0 ),
				FontSize,
				Color
			);
			
			Temp << DynObj[ CurObj ].Body.Spring(SpringNum).IndexA;
		
			cFonts::FlangeLight.Write(
				Temp.str(),
				Vector3D( cGlobal::Left + XPos, cGlobal::Bottom + Real( 6 ), 0.0 ),
				FontSize,
				Color
			);
			XPos += XShift;
			Temp.str(std::string());
			// Displays current node B number //
			// - ---------------------------------------------------------------------------------- - //
			cFonts::FlangeLight.Write(
				"Node B",
				Vector3D( cGlobal::Left + XPos, cGlobal::Bottom + YShift, 0.0 ),
				FontSize,
				Color
			);
			
			Temp << DynObj[ CurObj ].Body.Spring(SpringNum).IndexB;
		
			cFonts::FlangeLight.Write(
				Temp.str(),
				Vector3D( cGlobal::Left + XPos, cGlobal::Bottom + Real( 6 ), 0.0 ),
				FontSize,
				Color
			);
			XPos += XShift;
			Temp.str(std::string());
			// Displays current spring strength //
			// - ---------------------------------------------------------------------------------- - //
			cFonts::FlangeLight.Write(
				"Strength",
				Vector3D( cGlobal::Left + XPos, cGlobal::Bottom + YShift, 0.0 ),
				FontSize,
				Color
			);
			
			Temp << DynObj[ CurObj ].Body.Spring(SpringNum).Strength;
		
			cFonts::FlangeLight.Write(
				Temp.str(),
				Vector3D( cGlobal::Left + XPos, cGlobal::Bottom + Real( 6 ), 0.0 ),
				FontSize,
				Color
			);
			XPos += XShift;
			Temp.str(std::string());
			// Displays current spring length //
			// - ---------------------------------------------------------------------------------- - //
			cFonts::FlangeLight.Write(
				"Length",
				Vector3D( cGlobal::Left + XPos, cGlobal::Bottom + YShift, 0.0 ),
				FontSize,
				Color
			);
			
			Temp << DynObj[ CurObj ].Body.Spring(SpringNum).Length;
		
			cFonts::FlangeLight.Write(
				Temp.str(),
				Vector3D( cGlobal::Left + XPos, cGlobal::Bottom + Real( 6 ), 0.0 ),
				FontSize,
				Color
			);
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::DisplayMeshNodeInfo()
{
	if( CurSelected.size() > 0 )
	{
		Real FontSize = 0.5;
		Real XShift = 120;
		Real YShift = 40;
		Real XPos = 0;
		Real YPos = 0;
		
		if( Platform::AspectRatio < Real( 0.79 ) )
		{
			YPos = cGlobal::HudH * 0.25;
		}
		int Color = gfx::RGBA( 255, 255, 255, 255 );
		std::stringstream Temp;
		
		// Displays the current node number //
		// - ---------------------------------------------------------------------------------- - //
		cFonts::FlangeLight.Write(
			"Node #",
			Vector3D( cGlobal::Left + XPos, cGlobal::Bottom + YPos + YShift, 0.0 ),
			FontSize,
			Color
		);
		
		Temp << CurSelected[0];
	
		cFonts::FlangeLight.Write(
			Temp.str(),
			Vector3D( cGlobal::Left + XPos, cGlobal::Bottom + YPos + Real( 6 ), 0.0 ),
			FontSize,
			Color
		);
		XPos += XShift;
		Temp.str(std::string());
		// Displays the X location of the node //
		// - ---------------------------------------------------------------------------------- - //
		cFonts::FlangeLight.Write(
			"Node X",
			Vector3D( cGlobal::Left + XPos, cGlobal::Bottom + YPos + YShift, 0.0 ),
			FontSize,
			Color
		);
		
		Temp << DynObj[ CurObj ].AnimationSet->MeshPose[ CurMeshPose ].Node[ CurSelected[0] ].Pos.x;
	
		cFonts::FlangeLight.Write(
			Temp.str(),
			Vector3D( cGlobal::Left + XPos, cGlobal::Bottom + YPos + Real( 6 ), 0.0 ),
			FontSize,
			Color
		);
		XPos += XShift;
		Temp.str(std::string());
		// Displays the Y location of the node //
		// - ---------------------------------------------------------------------------------- - //
		cFonts::FlangeLight.Write(
			"Node Y",
			Vector3D( cGlobal::Left + XPos, cGlobal::Bottom + YPos + YShift, 0.0 ),
			FontSize,
			Color
		);
		
		Temp << DynObj[ CurObj ].AnimationSet->MeshPose[ CurMeshPose ].Node[ CurSelected[0] ].Pos.y;
	
		cFonts::FlangeLight.Write(
			Temp.str(),
			Vector3D( cGlobal::Left + XPos, cGlobal::Bottom + YPos + Real( 6 ), 0.0 ),
			FontSize,
			Color
		);
		XPos += XShift;
		Temp.str(std::string());
		// Displays the Pivot of the node //
		// - ---------------------------------------------------------------------------------- - //
		cFonts::FlangeLight.Write(
			"Pivot",
			Vector3D( cGlobal::Left + XPos, cGlobal::Bottom + YPos + YShift, 0.0 ),
			FontSize,
			Color
		);
		
		Temp << DynObj[ CurObj ].AnimationSet->MeshPose[ CurMeshPose ].Node[ CurSelected[0] ].PivotIndex;
	
		cFonts::FlangeLight.Write(
			Temp.str(),
			Vector3D( cGlobal::Left + XPos, cGlobal::Bottom + YPos + Real( 6 ), 0.0 ),
			FontSize,
			Color
		);
		XPos += XShift;
		Temp.str(std::string());
		// Displays the Handle of the node //
		// - ---------------------------------------------------------------------------------- - //
		cFonts::FlangeLight.Write(
			"Handle",
			Vector3D( cGlobal::Left + XPos, cGlobal::Bottom + YPos + YShift, 0.0 ),
			FontSize,
			Color
		);
		
		Temp << DynObj[ CurObj ].AnimationSet->MeshPose[ CurMeshPose ].Node[ CurSelected[0] ].HandleIndex;
	
		cFonts::FlangeLight.Write(
			Temp.str(),
			Vector3D( cGlobal::Left + XPos, cGlobal::Bottom + YPos + Real( 6 ), 0.0 ),
			FontSize,
			Color
		);
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cComponentEdit::DisplayMode()
{
	// Displays the current mesh edit mode //
	// - -------------------------------------------------------------------------------------- - //
	Real FontSize = 0.5;
	int Color = gfx::RGBA( 255, 100, 100, 255 );
	Vector3D ModePos = Vector3D( cGlobal::Right - Real( 250 ), cGlobal::Top - Real( 30 ), 0.0 );
		
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
		case COMPONENT_MODE:
		{
			cFonts::FlangeLight.Write(
				"Component Mode",
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
void cComponentEdit::DisplayComponentInfo()
{
	cFonts::FlangeLight.Write(
		"Component Editor",
		Vector3D( cGlobal::Left + Real( 20 ), cGlobal::Top - Real( 30 ), 0.0 ),
		Real( 0.5 ),
		gfx::RGBA( 100, 100, 255, 255 )
	);

	cFonts::FlangeLight.Write(
		"Current Pose",
		Vector3D( cGlobal::Right - Real( 600 ), cGlobal::Top - Real( 30 ), 0.0 ),
		Real( 0.5 ),
		gfx::RGBA( 100, 255, 100, 255 )
	);
	
	std::stringstream Temp;

	Temp << CurPose;

	cFonts::FlangeLight.Write(
		Temp.str(),
		Vector3D( cGlobal::Right - Real( 400 ), cGlobal::Top - Real( 30 ), 0.0 ),
		Real( 0.5 ),
		gfx::RGBA( 100, 255, 100, 255 )
	);


	Temp.str(std::string());

	cFonts::FlangeLight.Write(
		"Current Frame",
		Vector3D( cGlobal::Right - Real( 600 ), cGlobal::Top - Real( 70 ), 0.0 ),
		Real( 0.5 ),
		gfx::RGBA( 100, 255, 100, 255 )
	);
	
	Temp << CurMeshPose;

	cFonts::FlangeLight.Write(
		Temp.str(),
		Vector3D( cGlobal::Right - Real( 400 ), cGlobal::Top - Real( 70 ), 0.0 ),
		Real( 0.5 ),
		gfx::RGBA( 100, 255, 100, 255 )
	);
	
	
	int EqualNodeSizes = Pose->Node.size();
	int EqualSphereSizes = Pose->Sphere.size();
	int EqualSpringSizes = Pose->Spring.size();
	
	
	for( size_t idx = 0; idx < DynObj[ CurObj ].AnimationSet->BodyPose.size(); ++idx )
	{
		if( EqualNodeSizes != int( DynObj[ CurObj ].AnimationSet->BodyPose[idx].Node.size() ) )
		{
			EqualNodeSizes = -1;
		}
		if( EqualSphereSizes != int( DynObj[ CurObj ].AnimationSet->BodyPose[idx].Sphere.size() ) )
		{
			EqualSphereSizes = -1;
		}
		if( EqualSpringSizes != int( DynObj[ CurObj ].AnimationSet->BodyPose[idx].Spring.size() ) )
		{
			EqualSpringSizes = -1;
		}
	}
	if( EqualNodeSizes == -1 )
	{
		cFonts::FlangeLight.Write(
			"Unequal node sizes",
			Vector3D( cGlobal::Right - Real( 600 ), cGlobal::Top - Real( 110 ), 0.0 ),
			Real( 0.5 ),
			gfx::RGBA( 255, 0, 0, 255 )
		);
	}
	if( EqualSphereSizes == -1 )
	{
		cFonts::FlangeLight.Write(
			"Unequal sphere sizes",
			Vector3D( cGlobal::Right - Real( 600 ), cGlobal::Top - Real( 150 ), 0.0 ),
			Real( 0.5 ),
			gfx::RGBA( 255, 0, 0, 255 )
		);
	}
	if( EqualSpringSizes == -1 )
	{
		cFonts::FlangeLight.Write(
			"Unequal spring sizes",
			Vector3D( cGlobal::Right - Real( 600 ), cGlobal::Top - Real( 190 ), 0.0 ),
			Real( 0.5 ),
			gfx::RGBA( 255, 0, 0, 255 )
		);
	}

}
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
