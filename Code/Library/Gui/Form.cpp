// - ------------------------------------------------------------------------------------------ - //
// Form //
// - ------------------------------------------------------------------------------------------ - //
#include "Form.h"
#include <Gui/Actions.h>
#include <Graphics/Gfx.h>
#include <Input/Input.h>
// - ------------------------------------------------------------------------------------------ - //
cForm::cForm() :
	Pos( Vector2D( 0, 0 ) ),
	Size( Vector2D( 0, 0 ) ),
	Focus( 0 ),
	SuperFlowState( 1 ),
	IsVisable( true ),
	IsLabelsVisable( true )
{
	TextureID = TexturePool.Load( "DialogBox.tx" ).Id;
}
// - ------------------------------------------------------------------------------------------ - //
cForm::cForm(
	const Vector2D& _Pos,
	const Vector2D& _Size,
	const int _Focus,
	const std::string& TextureLoc
	) :
		Pos( _Pos ),
		Size( _Size ),
		TextureID( TexturePool.Load( TextureLoc ).Id ),
		Focus( _Focus ),
		SuperFlowState( 1 ),
		IsVisable( true ),
		IsLabelsVisable( true )
{
	
}
// - ------------------------------------------------------------------------------------------ - //
void cForm::Step()
{
	SwitchFocus();

	Execute();
	
	if( IsLabelsVisable )
	{
		for( size_t idx = 0; idx < Labels.size(); ++idx )
		{
			Labels[ idx ]->Step();
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cForm::Draw()
{
	if( IsVisable )
	{
		DrawBoxFrame();
	}
	
	if( IsLabelsVisable )
	{
		// Remove the + + Vector2D( 6, 0 ) when you get sick of the selected offset thing?
		Labels[ ActiveLabels[ Focus ] ]->SelDraw( Pos + Vector2D( 6, 0 ) );
		
		for( size_t idx = 0; idx < Labels.size(); ++idx )
		{
			if( ActiveLabels[ Focus ] != idx )
			{	
				Labels[ idx ]->Draw( Pos );
			}
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cForm::DrawBoxFrame()
{
	if( IsVisable )
	{
		unsigned int IndicesSize = 9 * 4;
		
		Vector3D Vertex[ IndicesSize ];
		Vector2D TexCoord[ IndicesSize ];
	
		unsigned int Indices[ IndicesSize ];
		
		int VertexIdx = 0;
		
		// Draw the Box //
		Vertex[	VertexIdx ] = Pos.ToVector3D();
		TexCoord[ VertexIdx ] = Vector2D( 0.003, 0.003 );
		VertexIdx++;
		
		Vertex[	VertexIdx ] = Vector3D( Pos.x, Size.y, Real( 0.0 ) );
		TexCoord[ VertexIdx ] = Vector2D( 0.003, 0.121 );
		VertexIdx++;
		
		Vertex[	VertexIdx ] = Size.ToVector3D();
		TexCoord[ VertexIdx ] = Vector2D( 0.121, 0.121 );
		VertexIdx++;
		
		Vertex[	VertexIdx ] = Vector3D( Size.x, Pos.y, Real( 0.0 ) );
		TexCoord[ VertexIdx ] = Vector2D( 0.121, 0.003 );
		VertexIdx++;
		
		// Box Border //
		// Left //
		Vertex[	VertexIdx ] = Vector2D( Pos.x - Real( 64 ), Pos.y ).ToVector3D();
		TexCoord[ VertexIdx ] = Vector2D( 0.254, 0.003 );
		VertexIdx++;
		
		Vertex[	VertexIdx ] = Vector2D( Pos.x - Real( 64 ), Size.y ).ToVector3D();
		TexCoord[ VertexIdx ] = Vector2D( 0.254, 0.121 );
		VertexIdx++;
		
		Vertex[	VertexIdx ] = Vector2D( Pos.x, Size.y ).ToVector3D();
		TexCoord[ VertexIdx ] = Vector2D( 0.374, 0.121 );
		VertexIdx++;
		
		Vertex[	VertexIdx ] = Pos.ToVector3D();
		TexCoord[ VertexIdx ] = Vector2D( 0.374, 0.003 );
		VertexIdx++;
		
		// Right //
		Vertex[	VertexIdx ] = Vector2D( Size.x + Real( 64 ), Size.y ).ToVector3D();
		TexCoord[ VertexIdx ] = Vector2D( 0.254, 0.003 );
		VertexIdx++;
		
		Vertex[	VertexIdx ] = Vector2D( Size.x + Real( 64 ), Pos.y ).ToVector3D();
		TexCoord[ VertexIdx ] = Vector2D( 0.254, 0.121 );
		VertexIdx++;
		
		Vertex[	VertexIdx ] = Vector2D( Size.x, Pos.y ).ToVector3D();
		TexCoord[ VertexIdx ] = Vector2D( 0.374, 0.121 );
		VertexIdx++;
		
		Vertex[	VertexIdx ] = Size.ToVector3D();
		TexCoord[ VertexIdx ] = Vector2D( 0.374, 0.003 );
		VertexIdx++;
		
		// Top //
		Vertex[	VertexIdx ] = Vector2D( Size.x, Pos.y + Real( 64 ) ).ToVector3D();
		TexCoord[ VertexIdx ] = Vector2D( 0.254, 0.003 );
		VertexIdx++;
		
		Vertex[	VertexIdx ] = Vector2D( Pos.x, Pos.y + Real( 64 ) ).ToVector3D();
		TexCoord[ VertexIdx ] = Vector2D( 0.254, 0.121 );
		VertexIdx++;
		
		Vertex[	VertexIdx ] = Pos.ToVector3D();
		TexCoord[ VertexIdx ] = Vector2D( 0.374, 0.121 );
		VertexIdx++;
		
		Vertex[	VertexIdx ] = Vector2D( Size.x, Pos.y ).ToVector3D();
		TexCoord[ VertexIdx ] = Vector2D( 0.374, 0.003 );
		VertexIdx++;

		// Bottom //
		Vertex[	VertexIdx ] = Vector2D( Pos.x, Size.y - Real( 64 ) ).ToVector3D();
		TexCoord[ VertexIdx ] = Vector2D( 0.254, 0.003 );
		VertexIdx++;
		
		Vertex[	VertexIdx ] = Vector2D( Size.x, Size.y - Real( 64 ) ).ToVector3D();
		TexCoord[ VertexIdx ] = Vector2D( 0.254, 0.121 );
		VertexIdx++;
		
		Vertex[	VertexIdx ] = Size.ToVector3D();
		TexCoord[ VertexIdx ] = Vector2D( 0.374, 0.121 );
		VertexIdx++;
		
		Vertex[	VertexIdx ] = Vector2D( Pos.x, Size.y ).ToVector3D();
		TexCoord[ VertexIdx ] = Vector2D( 0.374, 0.003 );
		VertexIdx++;

		// Top Right //
		Vertex[	VertexIdx ] = Vector2D( Size.x + Real( 64 ), Pos.y + Real( 64 ) ).ToVector3D();
		TexCoord[ VertexIdx ] = Vector2D( 0.376, 0.003 );
		VertexIdx++;
		
		Vertex[	VertexIdx ] = Vector2D( Size.x, Pos.y + Real( 64 ) ).ToVector3D();
		TexCoord[ VertexIdx ] = Vector2D( 0.376, 0.121 );
		VertexIdx++;
		
		Vertex[	VertexIdx ] = Vector2D( Size.x, Pos.y ).ToVector3D();
		TexCoord[ VertexIdx ] = Vector2D( 0.497, 0.121 );
		VertexIdx++;
		
		Vertex[	VertexIdx ] = Vector2D( Size.x + Real( 64 ), Pos.y ).ToVector3D();
		TexCoord[ VertexIdx ] = Vector2D( 0.497, 0.003 );
		VertexIdx++;

		// Bottom Right //
		Vertex[	VertexIdx ] = Vector2D( Size.x, Size.y ).ToVector3D();
		TexCoord[ VertexIdx ] = Vector2D( 0.497, 0.121 );
		VertexIdx++;
		
		Vertex[	VertexIdx ] = Vector2D( Size.x, Size.y - Real( 64 ) ).ToVector3D();
		TexCoord[ VertexIdx ] = Vector2D( 0.497, 0.003 );
		VertexIdx++;
		
		Vertex[	VertexIdx ] = Vector2D( Size.x + Real( 64 ), Size.y - Real( 64 ) ).ToVector3D();
		TexCoord[ VertexIdx ] = Vector2D( 0.376, 0.003 );
		VertexIdx++;
		
		Vertex[	VertexIdx ] = Vector2D( Size.x + Real( 64 ), Size.y ).ToVector3D();
		TexCoord[ VertexIdx ] = Vector2D( 0.376, 0.121 );
		VertexIdx++;
		
	
		// Top Left //
		Vertex[	VertexIdx ] = Vector2D( Pos.x, Pos.y ).ToVector3D();
		TexCoord[ VertexIdx ] = Vector2D( 0.497, 0.121 );
		VertexIdx++;
		
		Vertex[	VertexIdx ] = Vector2D( Pos.x, Pos.y + Real( 64 ) ).ToVector3D();
		TexCoord[ VertexIdx ] = Vector2D( 0.497, 0.003 );
		VertexIdx++;
		
		Vertex[	VertexIdx ] = Vector2D( Pos.x - Real( 64 ), Pos.y + Real( 64 ) ).ToVector3D();
		TexCoord[ VertexIdx ] = Vector2D( 0.376, 0.003 );
		VertexIdx++;
		
		Vertex[	VertexIdx ] = Vector2D( Pos.x - Real( 64 ), Pos.y ).ToVector3D();
		TexCoord[ VertexIdx ] = Vector2D( 0.376, 0.121 );
		VertexIdx++;

		// Bottom Left //
		Vertex[	VertexIdx ] = Vector2D( Pos.x - Real( 64 ), Size.y - Real( 64 ) ).ToVector3D();
		TexCoord[ VertexIdx ] = Vector2D( 0.376, 0.003 );
		VertexIdx++;
		
		Vertex[	VertexIdx ] = Vector2D( Pos.x, Size.y - Real( 64 ) ).ToVector3D();
		TexCoord[ VertexIdx ] = Vector2D( 0.376, 0.121 );
		VertexIdx++;
		
		Vertex[	VertexIdx ] = Vector2D( Pos.x, Size.y ).ToVector3D();
		TexCoord[ VertexIdx ] = Vector2D( 0.497, 0.121 );
		VertexIdx++;
		
		Vertex[	VertexIdx ] = Vector2D( Pos.x - Real( 64 ), Size.y ).ToVector3D();
		TexCoord[ VertexIdx ] = Vector2D( 0.497, 0.003 );
		VertexIdx++;
		
		for( size_t idx = 0; idx < IndicesSize; ++idx )
		{
			Indices[ idx ] = idx;
		}
		
		Gfx::DrawQuads(
			Vertex,
			TexCoord,
			Indices,
			IndicesSize,
			TextureID,
			Gfx::RGBA( 255, 255, 255, 192 )
		);	
	}
}	
// - ------------------------------------------------------------------------------------------ - //
void cForm::SwitchFocus()
{
	if( Input::Button[ KEY_UP ].Pressed() || int( Input::Pad[0].Stick1.HarshKeyRepeat().y ) == 1 || int( Input::Pad[0].DPad.HarshKeyRepeat().y ) == 1 )
	{
		// Swaps the animation to off before it changes to the next focus //
		Labels[ ActiveLabels[ Focus ] ]->SelInit();
		
		if( Focus > 0 )
		{
			--Focus;
		}
		else
		{
			Focus = ActiveLabels.size() - 1;	
		}
		// Swaps the animation to on the new focus //
		Labels[ ActiveLabels[ Focus ] ]->SelInit();
	}
	if( Input::Button[ KEY_DOWN ].Pressed() || int( Input::Pad[0].Stick1.HarshKeyRepeat().y ) == -1 || int( Input::Pad[0].DPad.HarshKeyRepeat().y ) == -1 )
	{
		// Swaps the animation to off before it changes to the next focus //
		Labels[ ActiveLabels[ Focus ] ]->SelInit();
		
		if( Focus < int( ActiveLabels.size() - 1 ) )
		{
			++Focus;
		}
		else
		{
			Focus = 0;	
		}
		// Swaps the animation to on the new focus //
		Labels[ ActiveLabels[ Focus ] ]->SelInit();
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cForm::Execute()
{
	if( Input::Button[ KEY_ENTER ].Pressed() || Input::Pad[0].Button[ PAD_A ].Pressed() || Input::Pad[0].Button[ PAD_START ].Pressed() )
	{
		SuperFlowState = cActions::ExecuteAction( Labels[ ActiveLabels[ Focus ] ]->ActionID );
	}
}
// - ------------------------------------------------------------------------------------------ - //
