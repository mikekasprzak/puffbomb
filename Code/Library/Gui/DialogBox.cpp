// - ------------------------------------------------------------------------------------------ - //
// DialogBox //
// - ------------------------------------------------------------------------------------------ - //
#include "DialogBox.h"
#include <Gui/Actions.h>
#include <Graphics/Gfx.h>
#include <Input/Input.h>
// - ------------------------------------------------------------------------------------------ - //
cDialogBox::cDialogBox() :
	Pos( Vector2D( 0, 0 ) ),
	Size( Vector2D( 0, 0 ) ),
	Focus( 0 ),
	SuperFlowState( 1 ),
	IsVisable( true ),
	IsLabelsVisable( true )
{
	TextureID = TexturePool.Load( "DialogBox.tx" );
}
// - ------------------------------------------------------------------------------------------ - //
cDialogBox::cDialogBox(
	const Vector2D& _Pos,
	const Vector2D& _Size,
	const int _Focus,
	const std::string& TextureLoc
	) :
		Pos( _Pos ),
		Size( _Size ),
		TextureID( TexturePool.Load( TextureLoc ) ),
		Focus( _Focus ),
		SuperFlowState( 1 ),
		IsVisable( true ),
		IsLabelsVisable( true )
{
	
}
// - ------------------------------------------------------------------------------------------ - //
void cDialogBox::Step()
{
	SwitchFocus();

	Execute();
	
	if( IsLabelsVisable )
	{
		for( size_t idx = 0; idx < TextLabel.size(); ++idx )
		{
			TextLabel[ idx ].Step();
		}
		for( size_t idx = 0; idx < AniLabel.size(); ++idx )
		{
			AniLabel[ idx ].Step();
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cDialogBox::Draw()
{
	if( IsVisable )
	{
		DrawBoxFrame();
	}
	
	if( IsLabelsVisable )
	{
		for( size_t idx = 0; idx < TextLabel.size(); ++idx )
		{
			TextLabel[ idx ].Draw();
		}
		for( size_t idx = 0; idx < AniLabel.size(); ++idx )
		{
			AniLabel[ idx ].Draw();
		}
		
		if( ActiveLabels[ Focus ] < 10000 )
		{
			TextLabel[ ActiveLabels[ Focus ] ].SelDraw();
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cDialogBox::DrawBoxFrame()
{
	if( IsVisable )
	{
		// Draw the Box //
		glColor4ub( 255, 255, 255, 192 );

		glBindTexture( GL_TEXTURE_2D, TextureID );
		
		gfx::Quad(
			Pos,
			Vector2D( Pos.x, Size.y ),
			Size,
			Vector2D( Size.x, Pos.y ),
			Vector2D( 0.001, 0.001 ),
			Vector2D( 0.001, 0.124 ),
			Vector2D( 0.124, 0.124 ),
			Vector2D( 0.124, 0.001 )
		);

		// Box Border //
		// Left //
		gfx::Quad(
			Vector2D( Pos.x - Real( 64 ), Pos.y ),
			Vector2D( Pos.x - Real( 64 ), Size.y ),
			Vector2D( Pos.x, Size.y ),
			Pos,
			Vector2D( 0.251, 0.001 ),
			Vector2D( 0.251, 0.124 ),
			Vector2D( 0.374, 0.124 ),
			Vector2D( 0.374, 0.001 )
		);
		
		// Right //
		gfx::Quad(
			Vector2D( Size.x + Real( 64 ), Size.y ),
			Vector2D( Size.x + Real( 64 ), Pos.y ),
			Vector2D( Size.x, Pos.y ),
			Size,
			Vector2D( 0.251, 0.001 ),
			Vector2D( 0.251, 0.124 ),
			Vector2D( 0.374, 0.124 ),
			Vector2D( 0.374, 0.001 )
		);
		
		// Top //
		gfx::Quad(
			Vector2D( Size.x, Pos.y + Real( 64 ) ),
			Vector2D( Pos.x, Pos.y + Real( 64 ) ),
			Pos,
			Vector2D( Size.x, Pos.y ),
			Vector2D( 0.251, 0.001 ),
			Vector2D( 0.251, 0.124 ),
			Vector2D( 0.374, 0.124 ),
			Vector2D( 0.374, 0.001 )
		);

		// Bottom //
		gfx::Quad(
			Vector2D( Pos.x, Size.y - Real( 64 ) ),
			Vector2D( Size.x, Size.y - Real( 64 ) ),
			Size,
			Vector2D( Pos.x, Size.y ),
			Vector2D( 0.251, 0.001 ),
			Vector2D( 0.251, 0.124 ),
			Vector2D( 0.374, 0.124 ),
			Vector2D( 0.374, 0.001 )
		);
		// Top Right //
		gfx::Quad(
			Vector2D( Size.x + Real( 64 ), Pos.y + Real( 64 ) ),
			Vector2D( Size.x, Pos.y + Real( 64 ) ),
			Vector2D( Size.x, Pos.y ),
			Vector2D( Size.x + Real( 64 ), Pos.y ),
			Vector2D( 0.376, 0.001 ),
			Vector2D( 0.376, 0.124 ),
			Vector2D( 0.499, 0.124 ),
			Vector2D( 0.499, 0.001 )
		);
		// Bottom Right //
		gfx::Quad(
			Vector2D( Size.x, Size.y ),
			Vector2D( Size.x, Size.y - Real( 64 ) ),
			Vector2D( Size.x + Real( 64 ), Size.y - Real( 64 ) ),
			Vector2D( Size.x + Real( 64 ), Size.y ),
			Vector2D( 0.499, 0.124 ),
			Vector2D( 0.499, 0.001 ),
			Vector2D( 0.376, 0.001 ),
			Vector2D( 0.376, 0.124 )
		);
		// Top Left //
		gfx::Quad(
			Vector2D( Pos.x, Pos.y ),
			Vector2D( Pos.x, Pos.y + Real( 64 ) ),
			Vector2D( Pos.x - Real( 64 ), Pos.y + Real( 64 ) ),
			Vector2D( Pos.x - Real( 64 ), Pos.y ),
			Vector2D( 0.499, 0.124 ),
			Vector2D( 0.499, 0.001 ),
			Vector2D( 0.376, 0.001 ),
			Vector2D( 0.376, 0.124 )
		);
		// Bottom Left //
		gfx::Quad(
			Vector2D( Pos.x - Real( 64 ), Size.y - Real( 64 ) ),
			Vector2D( Pos.x, Size.y - Real( 64 ) ),
			Vector2D( Pos.x, Size.y ),
			Vector2D( Pos.x - Real( 64 ), Size.y ),
			Vector2D( 0.376, 0.001 ),
			Vector2D( 0.376, 0.124 ),
			Vector2D( 0.499, 0.124 ),
			Vector2D( 0.499, 0.001 )
		);
	}
}	
// - ------------------------------------------------------------------------------------------ - //
void cDialogBox::CheckActive()  // Shouldn't need this anymore //
{
	/*for( size_t idx = 0; idx < TextLabel.size(); ++idx )
	{
		if( TextLabel[ idx ].IsPassive == false )
		{
			ActiveLabels.push_back( idx );
		}
	}
	for( size_t idx = 0; idx < AniLabel.size(); ++idx )
	{
		if( AniLabel[ idx ].IsPassive == false )
		{
			ActiveLabels.push_back( idx + 10000 );
		}
	}*/
}
// - ------------------------------------------------------------------------------------------ - //
void cDialogBox::SwitchFocus()
{
	if( Input::Button[ KEY_UP ].Pressed() )
	{
		// Swaps the animation to off before it changes to the next focus //
		if( ActiveLabels[ Focus ] < 20000 && ActiveLabels[ Focus ] >= 10000 )
		{
			AniLabel[ ActiveLabels[ Focus ] - 10000 ].SwapAnimation();
		}
	
		if( Focus > 0 )
		{
			--Focus;
		}
		else
		{
			Focus = ActiveLabels.size() - 1;	
		}
		// Swaps the animation to on before it changes to the next focus //
		if( ActiveLabels[ Focus ] < 20000 && ActiveLabels[ Focus ] >= 10000 )
		{
			AniLabel[ ActiveLabels[ Focus ] - 10000 ].SwapAnimation();
		}
	}
	if( Input::Button[ KEY_DOWN ].Pressed() )
	{
		// Swaps the animation to off before it changes to the next focus //
		if( ActiveLabels[ Focus ] < 20000 && ActiveLabels[ Focus ] >= 10000 )
		{
			AniLabel[ ActiveLabels[ Focus ] - 10000 ].SwapAnimation();
		}
		
		if( Focus < int( ActiveLabels.size() - 1 ) )
		{
			++Focus;
		}
		else
		{
			Focus = 0;	
		}
		// Swaps the animation to on before it changes to the next focus //
		if( ActiveLabels[ Focus ] < 20000 && ActiveLabels[ Focus ] >= 10000 )
		{
			AniLabel[ ActiveLabels[ Focus ] - 10000 ].SwapAnimation();
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cDialogBox::Execute()
{
	if( Input::Button[ KEY_ENTER ].Pressed() )
	{
		if( ActiveLabels[ Focus ] < 10000 )
		{
			SuperFlowState = cActions::ExecuteAction( TextLabel[ ActiveLabels[ Focus ] ].ActionID );
		}
		else if( ActiveLabels[ Focus ] < 20000 )
		{
			SuperFlowState = cActions::ExecuteAction( AniLabel[ ActiveLabels[ Focus ] - 10000 ].ActionID );
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
