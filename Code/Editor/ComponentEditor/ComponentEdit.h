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
#include <Math/Vector.h>
#include <Global.h>

#include <Graphics/Camera.h>
#include "Editor/Edit.h"

#include <DynamicComponent/Body2D/Body2D.h>
#include <DynamicComponent/DynamicComponent.h>

#include <DynamicComponent/AnimationGenerator/AnimationGenerator.h>
// - ------------------------------------------------------------------------------------------ - //
class cComponentEdit : public cEdit {
public:
	cCamera* UVCamera;
	cCamera* PreviewCamera;

public:
//	std::vector< Engine2D::cDynamicComponent > DynObj;
	Engine2D::cDynamicComponent* DynObj;
	Engine2D::cBody2DPose* Pose;
	
//	size_t CurObj;
	size_t CurMeshFrame;
	size_t CurMeshAnim;

	size_t CurTexPreview;
	
	Real NodeRadius;
	
	Real UVGridDepth[ 13 ];

	Vector3D PreviewTexVertex[ 4 ];
	
	Engine2D::cAnimationGenerator* AnimationGenerator;

	std::string BaseDirName;
		
	std::vector< std::string > CompDirs;
	size_t CurDirIdx;

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

	void LoadComp();
	void LoadCompTextures();
	void Save();
	std::string GetFileName();
	void FindCompDirs();
	void SwitchComp();
	void UpdatePreview();
	
	
public:
	// ComponentEditGlobal.cpp //
	Vector2D CalcMousePos();
	Vector2D CalcUVMousePos();
	
	void Undo();
	void ActiveAction();
	void SwitchMode();
	
	void BodyAddPose();
	void BodyDeletePose();
	void MeshAddPose();
	void MeshDeletePose();	
	
	void BodySwitchPose( size_t MyFrame );
	void MeshSwitchPose( size_t MyFrame );
	void MeshSwitchAnim();
	void MeshSwitchFrame();
	void ScaleAll();
	
public:
	// ComponentEditBodyNode.cpp //
	int BodySingleSelectNode();
	void BodySelectNode();
	void BodyMoveNode();
	void BodyAddNode();
	void BodyDeleteNode();
//	void BodyScaleNode();
	void BodyMass( const Real MassDiff );
	void BodyCalcTotalMass();

public:
	// ComponentEditBodySphere.cpp //
	void BodyAddSphere();
	void BodyDeleteSphere();
	void BodyRadius( const Real RadiusDiff );

public:
	// ComponentEditBodyAngle.cpp //
	void BodyAddAngle();
	void BodyDeleteAngle();
	void BodyAngleIndexes();
	
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
//	void MeshScaleNode();
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
