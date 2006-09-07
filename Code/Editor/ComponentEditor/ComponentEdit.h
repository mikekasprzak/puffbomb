// - ------------------------------------------------------------------------------------------ - //
// ComponentEdit //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Editor_ComponentEdit_H__
#define __Editor_ComponentEdit_H__
#ifdef EDITOR
// - ------------------------------------------------------------------------------------------ - //
#include <string>
#include <vector>
// - ------------------------------------------------------------------------------------------ - //
#include <Geometry/Vector.h>
#include <Global.h>

#include <Graphics/Camera.h>
#include "Editor/Edit.h"

#include <Physics/Body2D.h>
#include <Engine/DynamicComponent.h>

#include <Engine2D/Graphics/AnimationGenerator.h>
// - ------------------------------------------------------------------------------------------ - //
class cComponentEdit : public cEdit {
public:
	cCamera* UVCamera;
	cCamera* PreviewCamera;

public:
	std::vector< Engine2D::cDynamicComponent > DynObj;
	Engine2D::cBody2DPose* Pose;
	
	size_t CurObj;
//	size_t CurPose;
//	size_t CurMeshPose;
	size_t CurMeshFrame;
	size_t CurMeshAnim;

	size_t CurTexPreview;
	
	Real NodeRadius;
	
	Real UVGridDepth[ 13 ];

	Vector3D PreviewTexVertex[4];
	
	Engine2D::cAnimationGenerator AnimationGenerator;

public:
	cComponentEdit();
	~cComponentEdit();

public:
	// ComponentEdit.cpp //
	void Draw();
	void HudDraw();
	void PreviewDraw();
	void UVDraw();
	void Step();
	
	Vector2D CalcMousePos();
	Vector2D CalcUVMousePos();
	
	void Undo();
	void ActiveAction();
	void SwitchMode();
	
	void BodyAddPose();
	void BodyDeletePose();
	void MeshAddPose();
	void MeshDeletePose();	
	
	void SwitchPose();
	void SwitchMeshAnim();
	void SwitchMeshPose();
	void SwitchMeshFrame();
	void SwitchTexture();
	void LoadComp();
	void LoadCompTextures();
	
public:
	// ComponentEditBodyNode.cpp //
	int BodySingleSelectNode();
	void BodySelectNode();
	void BodyMoveNode();
	void BodyAddNode();
	void BodyDeleteNode();
	void BodyScaleNode();
	void BodyMass( const Real MassDiff );
	void BodyCalcTotalMass();

public:
	// ComponentEditBodySphere.cpp //
	void BodyAddSphere();
	void BodyDeleteSphere();
	void BodyRadius( const Real RadiusDiff );
	
public:
	// ComponentEditBodySpring.cpp //
	void BodyAddSpring();
	void BodyDeleteSpring();
	
public:
	// ComponentEditMeshNode.cpp //
	int MeshSingleSelectNode();
	void MeshSelectNode();
	void MeshMoveNode();
	void MeshAddNode();
	void MeshDeleteNode();
	void MeshScaleNode();
	void MeshSetPivot();
	void MeshSetHandle();

public:
	// ComponentEditMeshFace.cpp //
	void MeshAddFace();
	void MeshDeleteFace();
	void MeshClockwise( ABCSet< unsigned int > &tempFace );
	void MeshGenerateUV();
		
public:
	// ComponentEditText.cpp //
	void DisplayText();
	void DisplayNodeInfo();
	void DisplaySphereInfo();
	void DisplaySpringInfo();
	void DisplayMeshNodeInfo();
	void DisplayMode();
	void DisplayComponentInfo();

};
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Editor_ComponentEdit_H__ //
// - ------------------------------------------------------------------------------------------ - //
