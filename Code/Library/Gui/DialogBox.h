// - ------------------------------------------------------------------------------------------ - //
// DialogBox //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Gui_DialogBox_H__
#define __Gui_DialogBox_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Graphics/TexturePool.h>
#include <vector>
#include <string>
// - ------------------------------------------------------------------------------------------ - //
#include "TextLabel.h"
#include "AniLabel.h"
// - ------------------------------------------------------------------------------------------ - //
class cDialogBox
{
public:
	std::vector< cLabel* > Labels;

	// Which labels can be selected by the controller and may have actions //
	std::vector< int > ActiveLabels;
	
	Vector2D Pos;
	Vector2D Size;
	
	unsigned int TextureID;
	
	int Focus;
	
	int SuperFlowState;
	
	// A variable to determine if the Dialog Box its self can be seen //
	bool IsVisable;
	
	// A variable to determine if the Dialog Box labels can be seen //
	bool IsLabelsVisable;

public:
	
	cDialogBox();
	cDialogBox(
		const Vector2D& _Pos,
		const Vector2D& _Size,
		const int _Focus,
		const std::string& TextureLoc
	);
	
	void Step();
	
	void Draw();
	void DrawBoxFrame();

	void CheckActive();
	void SwitchFocus();
	void Execute();

};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Gui_DialogBox_H__ //
// - ------------------------------------------------------------------------------------------ - //
