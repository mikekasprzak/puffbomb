// - ------------------------------------------------------------------------------------------ - //
// DialogBox //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Gui_DialogBox_H__
#define __Gui_DialogBox_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Graphics/TexturePool.h>
#include <GL/gl.h>  // **Remove** //
#include <GL/glu.h> // **Remove** //
#include <vector>
#include <string>
// - ------------------------------------------------------------------------------------------ - //
#include "TextLabel.h"
#include "AniLabel.h"
//#include "CheckLabel.h"
//#include "ButtonLabel.h"
//#include "ComboLabel.h"
//#include "RadialLabel.h"
// - ------------------------------------------------------------------------------------------ - //
class cDialogBox
{
public:
	// Displayable objects // 	Active	Label - Subtract the First Number of each to get the index
	// Text // 					0 - 9999
	std::vector< cTextLabel > TextLabel;
	// Animation // 			10000 - 19999
	std::vector< cAniLabel > AniLabel;
	// Check Box // 			20000 - 29999
//	std::vector< cCheckLabel > CheckLabel;
	// Command Button // 		30000 - 39999
//	std::vector< cButtonLabel > ButtonLabel;
	// Combo Box // 			40000 - 49999
//	std::vector< cComboLabel > ComboLabel;
	// Radial Button // 		50000 - 59999
//	std::vector< cRadialLabel > RadialLabel;

	// Which labels can be selected by the controller and may have actions //
	std::vector< int > ActiveLabels;
	
	Vector2D Pos;
	Vector2D Size;
	
	unsigned int TextureID;
	
	int Focus;
	
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
