// - ------------------------------------------------------------------------------------------ - //
// DynamicCollection - A collection of Components //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Engine_DynamicCollection_H__
#define __Engine2D_Engine_DynamicCollection_H__
// - ------------------------------------------------------------------------------------------ - //
#include <vector>

#include "Linkage/Linkage.h"
#include "DynamicComponent/DynamicComponent.h"
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cDynamicCollection {
public:
	// Components of this object //
	std::vector< cDynamicComponent > Component;
	
	#ifdef EDITOR
	std::vector< std::string > ComponentName;
	#endif // Editor //
		
	// Node Linkage in this object //
	std::vector< cNodeLink > NodeLink;
	// Anchoring (locking) points in this object //
	std::vector< cNodeAnchor > NodeAnchor;

public:
	cDynamicCollection() {
	}
	
	virtual ~cDynamicCollection() {
	}
	
public:
	// - -------------------------------------------------------------------------------------- - //
	// Do physics, as a self sustaining object //
	void Step();
	// Step the mass body linkage (node links and anchors) //
	void StepLinkage();

	// Do any work (control/AI) I may have.  This is commonly overloaded to provide control. //
	virtual void Work();

public:
	// - -------------------------------------------------------------------------------------- - //
	// Draw this object, and all it's Meshes transformed by it's Bodies //
	void Draw();

public:
	// - -------------------------------------------------------------------------------------- - //
	// Debug Drawing Functions //
	void DebugDraw() const;
	
	void DrawComponent( const size_t Index, const bool Selected = false ) const;
	void DrawNodeLink( const size_t Index, const bool Selected = false ) const;
	void DrawNodeAnchor( const size_t Index, const bool Selected = false ) const;

	void DrawComponents( const std::vector< size_t >& SelectionVector = std::vector< size_t >() ) const;
	void DrawNodeLinks( const std::vector< size_t >& SelectionVector = std::vector< size_t >() ) const;
	void DrawNodeAnchors( const std::vector< size_t >& SelectionVector = std::vector< size_t >() ) const;

	void DrawBoundingRect( const bool Selected = false ) const;

public:
	// - -------------------------------------------------------------------------------------- - //
	// Query if this object is, at all, enabled //
	inline bool IsActive() {
		return true;
	}

public:
	// - -------------------------------------------------------------------------------------- - //
	// Messanging //

public:
	// - -------------------------------------------------------------------------------------- - //
	void LoadBinary( const std::string& FileName );
	void SaveBinary( const std::string& FileName, bool LittleEndian = true );	
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Engine_DynamicCollection_H__ //
// - ------------------------------------------------------------------------------------------ - //
