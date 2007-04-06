// - ------------------------------------------------------------------------------------------ - //
// DynamicCollection - A collection of Components //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Engine_DynamicCollection_H__
#define __Engine2D_Engine_DynamicCollection_H__
// - ------------------------------------------------------------------------------------------ - //
#include <vector>

#include "Linkage/Linkage.h"
#include "DynamicComponent/DynamicComponent.h"

#include <Impulse/Impulse.h>
#include <Zone/Zone.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
class cDynamicCollection {
public:
	// Components of this object //
	std::vector< cDynamicComponent > Component;	
	// Node Linkage in this object //
	std::vector< cNodeLink > NodeLink;
	// Anchoring (locking) points in this object //
	std::vector< cNodeAnchor > NodeAnchor;


	//#ifdef EDITOR
	std::vector< std::string > ComponentName;
	//#endif // Editor //
		
public:
	cDynamicCollection() {
	}
	
	cDynamicCollection( const std::string& FileName, const Vector2D& Offset = Vector2D::Zero ) {
		LoadBinary( FileName, Offset );
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
	virtual bool Work();

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
	inline bool IsActive() const {
		for ( size_t idx = 0; idx < Component.size(); idx++ ) {
			if ( Component[ idx ].IsActive() ) {
				return true;
			}
		}
		return false;
	}
	
	inline void SetActive() {
		for ( size_t idx = 0; idx < Component.size(); idx++ ) {
			Component[ idx ].Flags.SetActive();
		}
	}

	inline void SetInactive() {
		for ( size_t idx = 0; idx < Component.size(); idx++ ) {
			Component[ idx ].Flags.ResetActive();
		}
	}
	
	void SetPos( const Vector2D& _Pos ) {
		for ( size_t idx = 0; idx < Component.size(); idx++ ) {
			for ( size_t idx2 = 0; idx2 < Component[ idx ].Body.Nodes.Size(); idx2++ ) {
				Component[ idx ].Body.Nodes.Set( idx2, _Pos + Component[ idx ].Body.Pose->Node[ idx2 ].Pos );
			}
		}		
	}

public:
	// - -------------------------------------------------------------------------------------- - //
	// Messanging //
	virtual int Message( int Msg, cDynamicCollection* const Sender );
	virtual int Message( int Msg, class cPassiveObject* const Sender );
	virtual void Message( const cZone& Sender );
	virtual void Message( const cImpulse& Sender );

public:
	// - -------------------------------------------------------------------------------------- - //
	void LoadBinary( const std::string& FileName, const Vector2D& Offset = Vector2D::Zero );
	void SaveBinary( const std::string& FileName, bool LittleEndian = true );
		
	void UpdateAnchors();
	void CalcBoundingRect();
	
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Engine_DynamicCollection_H__ //
// - ------------------------------------------------------------------------------------------ - //
