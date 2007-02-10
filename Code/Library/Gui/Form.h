// - ------------------------------------------------------------------------------------------ - //
// Form //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Gui_Form_H__
#define __Gui_Form_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Graphics/TexturePool.h>
#include <vector>
#include <string>
// - ------------------------------------------------------------------------------------------ - //
#include "TextLabel.h"
#include "AniLabel.h"
// - ------------------------------------------------------------------------------------------ - //
class cForm
{
public:
	// Elements inside the form //
	std::vector< cLabel* > Labels;

	// Which labels can be selected by the controller and may have actions //
	std::vector< int > ActiveLabels;
	
	std::vector< int > DummyLabels;
	
	// Form position //
	Vector2D Pos;
	// Size of the form box //
	Vector2D Size;
	
	// For form border ( form box ) //
	unsigned int TextureID; 
	
	// Currently selected active label //
	int Focus;
	
	int SuperFlowState;
	
	// A variable to determine if the Form its self can be seen //
	bool IsVisible;
	
	// A variable to determine if the Form labels can be seen //
	bool IsLabelsVisible;

public:
	
	cForm();
	cForm(
		const Vector2D& _Pos,
		const Vector2D& _Size,
		const int _Focus,
		const std::string& TextureLoc
	);
	
	void Load( const std::string &File );
	Real Anchor( const std::string &AnchorName );
	
	void Step();
	
	void Draw();
	void DrawBoxFrame();

	void CheckActive();
	void SwitchFocus();
	void Execute();

	cLabel& Group( const int GroupIdx, const int Index );
	
	void GroupPos( const int Group, const Vector2D& _Pos );
	void GroupPos( const int Group, const int Index, const Vector2D& _Pos );
	
	void GroupVisible( const int Group, const bool _Visible = true );
	void GroupVisible( const int Group, const int Index, const bool _Visible = true );
	
	void GroupColor( const int Group, const Gfx::Color _Color );
	void GroupColor( const int Group, const int Index, const Gfx::Color _Color );
	void GroupSelColor( const int Group, const Gfx::Color _Color );
	void GroupSelColor( const int Group, const int Index, const Gfx::Color _Color );

};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Gui_Form_H__ //
// - ------------------------------------------------------------------------------------------ - //
