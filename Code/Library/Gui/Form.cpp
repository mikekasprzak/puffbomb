// - ------------------------------------------------------------------------------------------ - //
// Form //
// - ------------------------------------------------------------------------------------------ - //
#include "Form.h"
#include <Gui/Actions.h>
#include <Graphics/Gfx.h>
#include <Input/Input.h>
#include <Global.h>
#include <Animation/AnimationPool.h>
// - ------------------------------------------------------------------------------------------ - //
#include <sstream>
#include <fstream>
#include <iostream>
// - ------------------------------------------------------------------------------------------ - //
using namespace std;
// - ------------------------------------------------------------------------------------------ - //
cForm::cForm() :
	Pos( Vector2D( 0, 0 ) ),
	Size( Vector2D( 0, 0 ) ),
	Focus( 0 ),
	SuperFlowState( 1 ),
	IsVisible( true ),
	FormAlpha( 192 ),
	IsLabelsVisible( true )
{
	// Legacy //
	TextureID = TexturePool.Load( "DialogBox.tx" ).Id;
}
// - ------------------------------------------------------------------------------------------ - //
cForm::cForm( const std::string& File ) :
	Pos( Vector2D( 0, 0 ) ),
	Size( Vector2D( 0, 0 ) ),
	Focus( 0 ),
	SuperFlowState( 1 ),
	IsVisible( true ),
	FormAlpha( 192 ),
	IsLabelsVisible( true )
{
	// Legacy //
	TextureID = TexturePool.Load( "DialogBox.tx" ).Id;
	
	Load( File );
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
		IsVisible( true ),
		FormAlpha( 192 ),
		IsLabelsVisible( true )
{
	
}
// - ------------------------------------------------------------------------------------------ - //
void cForm::Load( const std::string &File )
{
	char Line[1024];
	
	ifstream InFile( File.c_str() );
	
	std::vector< Real > TempReals;
	
	int Group = 0;
	
	std::string TempString;
	std::string TempString2;
	
	int Align = 0;
	
	while( !InFile.eof() )
	{
		// Read a line from the file //
		InFile.getline( Line, sizeof( Line ) );
	
		// Populate and use a string stream to tokenize the data //
		stringstream Text;
		Text << Line;
						
		// Read all the tokens from that string //
		string Token;
		while( !Text.eof() )
		{
			// Read next token //
			Text >> Token;
			
			// Test to make sure this line/token isn't stupid and blank //
			if ( Token == "" ) {
				break;
			}
			// Test if a comment //
			else if ( Token[ 0 ] == '/' ) {
				break;
			}
			else if ( Token[ 0 ] == '#' ) {
				break;
			}
			// - ------------------------------------------------------------------------------ - //
			// Dialog Box //
			else if( Token == "DialogPos" )
			{
				Real TempNum;
				
				Text >> Token;
				
				TempNum = Anchor( Token );
				
				Text >> Token;
				
				std::string TempOperator = Token;
				
				Text >> Token;
				
				if( TempOperator[ 0 ] == '+' )
				{
					TempNum += atof( Token.c_str() );
				}
				else
				{
					TempNum -= atof( Token.c_str() );
				}
				TempReals.push_back( TempNum );
				
			}
			else if( Token == "Focus" )
			{
				Text >> Token;
				
				TempReals.push_back( atoi( Token.c_str() ) );
			}
			else if( Token == "Texture" )
			{
				Text >> Token;
				
				TempString = Token;
				
				TextureID = TexturePool.Load( TempString ).Id;

			}
			else if( Token == "CreateDialog" )
			{
				Pos = Vector2D( TempReals[ 0 ], TempReals[ 1 ] );
				Size = Vector2D( TempReals[ 2 ], TempReals[ 3 ] );
				Focus = TempReals[ 4 ];
					
				TempReals.clear();
				TempString.clear();
			}
			
			// - ------------------------------------------------------------------------------ - //
			else if( Token == "TextLabel" )
			{
				Text >> Token;
				
				TempReals.push_back( atof( Token.c_str() ) ); // 0

				Text >> Token;
				
				TempReals.push_back( atof( Token.c_str() ) ); // 1
			}
			// - ------------------------------------------------------------------------------ - //
			// Shared //
			else if( Token == "IsPassive" )
			{
				Text >> Token;
				
				TempReals.push_back( atof( Token.c_str() ) ); // 2
			}	
			else if( Token == "ActionID" )
			{
				Text >> Token;
				
				TempReals.push_back( atof( Token.c_str() ) ); // 3
			}	
			// - ------------------------------------------------------------------------------ - //
			else if( Token == "Text" )
			{
				TempString = Text.str().substr( 5, Text.str().size() - 1 );
			}	
			else if( Token == "Scale" )
			{
				Text >> Token;
				
				TempReals.push_back( atof( Token.c_str() ) ); // 4
			}	
			else if( Token == "Color" )
			{
				Text >> Token;
				
				TempReals.push_back( atof( Token.c_str() ) ); // 5

				Text >> Token;
				
				TempReals.push_back( atof( Token.c_str() ) ); // 6

				Text >> Token;
				
				TempReals.push_back( atof( Token.c_str() ) ); // 7

				Text >> Token;
				
				TempReals.push_back( atof( Token.c_str() ) ); // 8
			}	
			else if( Token == "SelColor" )
			{
				Text >> Token;
				
				TempReals.push_back( atof( Token.c_str() ) ); // 9

				Text >> Token;
				
				TempReals.push_back( atof( Token.c_str() ) ); // 10

				Text >> Token;
				
				TempReals.push_back( atof( Token.c_str() ) ); // 11

				Text >> Token;
				
				TempReals.push_back( atof( Token.c_str() ) ); // 12

			}
			else if( Token == "Align" )
			{
				Text >> Token;
				
				if( Token == "Left" )
				{
					Align = 0;
				}
				else if( Token == "Right" )
				{
					Align = 1;
				}
				else if( Token == "Center" )
				{
					Align = 2;
				}
			}
			else if( Token == "EndText" )
			{
				Labels.push_back(
					new cTextLabel(
						Vector2D( TempReals[ 0 ], TempReals[ 1 ] ),
						bool( TempReals[ 2 ] ),
						int( TempReals[ 3 ] ),
						TempString,
						TempReals[ 4 ],
						Gfx::RGBA( TempReals[ 5 ], TempReals[ 6 ], TempReals[ 7 ], TempReals[ 8 ] ),
						Align
					)
				);				
				
				Labels.back()->Group = Group;
				
				if( bool( TempReals[ 2 ] ) == false )
				{
					ActiveLabels.push_back(
						Labels.size() - 1
					);
				}
				
				if( TempReals.size() > 12 )
				{
					Labels.back()->SelColor = Gfx::RGBA( TempReals[ 9 ], TempReals[ 10 ], TempReals[ 11 ], TempReals[ 12 ] );
				}
				
				Group = 0;
				Align = 0;
				TempReals.clear();
				TempString.clear();
			}	
			// - ------------------------------------------------------------------------------ - //
			else if( Token == "AniLabel" )
			{
				Text >> Token;
				
				TempReals.push_back( atof( Token.c_str() ) ); // 0

				Text >> Token;
				
				TempReals.push_back( atof( Token.c_str() ) ); // 1
			}
			else if( Token == "Animation" )
			{
				Text >> Token;
				
				TempString = Token;
			}	
			else if( Token == "SelectAni" )
			{
				Text >> Token;
				
				TempString2 = Token;
			}	
			else if( Token == "CurrentFrame" )
			{
				Text >> Token;
				
				TempReals.push_back( atof( Token.c_str() ) ); // 4
			}	
			else if( Token == "EndAni" )
			{				
				Labels.push_back( 
					new cAniLabel(
						Vector2D( TempReals[ 0 ], TempReals[ 1 ] ),
						bool( TempReals[ 2 ] ),
						int( TempReals[ 3 ] ),
						AnimationPool.Load( TempString ),
						AnimationPool.Load( TempString2 ),
						int( TempReals[ 4 ] )
					)
				);
				
				Labels.back()->Group = Group;
				
				if( bool( TempReals[ 2 ] ) == false )
				{
					ActiveLabels.push_back(
						( Labels.size() - 1 )
					);
				}
				
				if( TempReals.size() > 8 )
				{
					Labels.back()->Color = Gfx::RGBA( TempReals[ 5 ], TempReals[ 6 ], TempReals[ 7 ], TempReals[ 8 ] );
				}
				if( TempReals.size() > 12 )
				{
					Labels.back()->SelColor = Gfx::RGBA( TempReals[ 9 ], TempReals[ 10 ], TempReals[ 11 ], TempReals[ 12 ] );
				}

				Group = 0;
				TempReals.clear();
				TempString.clear();
				TempString2.clear();
			}
			else if( Token == "DummyLabel" )
			{
				Text >> Token;
				
				TempReals.push_back( atof( Token.c_str() ) ); // 0

				Text >> Token;
				
				TempReals.push_back( atof( Token.c_str() ) ); // 1
			}
			else if( Token == "EndDummy" )
			{
				Labels.push_back(
					new cLabel( Vector2D( TempReals[ 0 ], TempReals[ 1 ] ), true, 0, Gfx::White(), Gfx::White() )
					);
					
				Labels.back()->Group = Group;
				
				Group = 0;
				TempReals.clear();
				TempString.clear();
				TempString2.clear();
			}
			else if( Token == "Group" )
			{
				Text >> Token;
				
				Group = atoi( Token.c_str() );
			}
			else if( Token == "EndDialog" )
			{
			}
			// - ------------------------------------------------------------------------------ - //
			// Extra Features //
			else if( Token == "IsVisible" )
			{
				Text >> Token;
				
				IsVisible = bool( atoi( Token.c_str() ) );
			}
			else if( Token == "IsLabelsVisible" )
			{
				Text >> Token;
				
				IsLabelsVisible = bool( atoi( Token.c_str() ) );
			}

		}
	}
	Log( LOG_HIGHEST_LEVEL, "Form Loaded" );
}
// - ------------------------------------------------------------------------------------------ - //
Real cForm::Anchor( const std::string &AnchorName )
{
	if( AnchorName == "Left" )
	{
		return Global::Left;
	}
	else if( AnchorName == "Right" )
	{
		return Global::Right;
	}
	else if( AnchorName == "Top" )
	{
		return Global::Top;
	}
	else if( AnchorName == "Bottom" )
	{
		return Global::Bottom;
	}
	else
	{
		return Real::Zero;	
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cForm::Step()
{
	SwitchFocus();

	Execute();
	
	if( IsLabelsVisible )
	{
		for( size_t idx = 0; idx < Labels.size(); ++idx )
		{
			Labels[ idx ]->Step();
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cForm::Draw( int _OverloadAlpha )
{
	if( IsVisible )
	{
		DrawBoxFrame();
	}
	
	if( IsLabelsVisible )
	{
		if( !ActiveLabels.empty() )
		{
			// Remove the + + Vector2D( 6, 0 ) when you get sick of the selected offset thing?
			if( Labels[ ActiveLabels[ Focus ] ]->Visible )
			{
				if( _OverloadAlpha != 255 )
				{
					int TempColor = ( Labels[ ActiveLabels[ Focus ] ]->SelColor & 0xffffff ) | ( _OverloadAlpha << 24 );
					Labels[ ActiveLabels[ Focus ] ]->Draw( Pos + Vector2D( 6, 0 ), TempColor );
				}
				else
				{
					Labels[ ActiveLabels[ Focus ] ]->Draw( Pos + Vector2D( 6, 0 ), Labels[ ActiveLabels[ Focus ] ]->SelColor );
				}
			}
		}
		
		for( size_t idx = 0; idx < Labels.size(); ++idx )
		{
			if( !ActiveLabels.empty() )
			{
				if( size_t( ActiveLabels[ Focus ] ) != idx )
				{
					if( Labels[ idx ]->Visible )
					{
						if( _OverloadAlpha != 255 )
						{
							int TempColor = ( Labels[ idx ]->Color & 0xffffff ) | ( _OverloadAlpha << 24 );
							Labels[ idx ]->Draw( Pos, TempColor );
						}
						else
						{
							Labels[ idx ]->Draw( Pos, Labels[ idx ]->Color );
						}
					}
				}
			}
			else
			{
				if( Labels[ idx ]->Visible )
				{
					if( _OverloadAlpha != 255 )
					{
						int TempColor = ( Labels[ idx ]->Color & 0xffffff ) | ( _OverloadAlpha << 24 );
						Labels[ idx ]->Draw( Pos, TempColor );
					}
					else
					{
						Labels[ idx ]->Draw( Pos, Labels[ idx ]->Color );
					}	
				}
			}
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cForm::DrawBoxFrame()
{
	if( IsVisible )
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
			Gfx::RGBA( 255, 255, 255, FormAlpha )
		);	
	}
}	
// - ------------------------------------------------------------------------------------------ - //
void cForm::SwitchFocus()
{
	if( Input::Button[ KEY_UP ].Pressed() || int( Input::Pad[0].Stick1.HarshKeyRepeat().y ) == 1 || int( Input::Pad[0].DPad.HarshKeyRepeat().y ) == 1 )
	{
		// Swaps the animation to off before it changes to the next focus //
		if( !ActiveLabels.empty() )
		{
			Labels[ ActiveLabels[ Focus ] ]->SelInit();
		}
		
		if( Focus > 0 )
		{
			--Focus;
		}
		else
		{
			Focus = ActiveLabels.size() - 1;	
		}
		// Swaps the animation to on the new focus //
		if( !ActiveLabels.empty() )
		{
			Labels[ ActiveLabels[ Focus ] ]->SelInit();
		}
	}
	if( Input::Button[ KEY_DOWN ].Pressed() || int( Input::Pad[0].Stick1.HarshKeyRepeat().y ) == -1 || int( Input::Pad[0].DPad.HarshKeyRepeat().y ) == -1 )
	{
		// Swaps the animation to off before it changes to the next focus //
		if( !ActiveLabels.empty() )
		{
			Labels[ ActiveLabels[ Focus ] ]->SelInit();
		}
		
		if( Focus < int( ActiveLabels.size() - 1 ) )
		{
			++Focus;
		}
		else
		{
			Focus = 0;	
		}
		// Swaps the animation to on the new focus //
		if( !ActiveLabels.empty() )
		{
			Labels[ ActiveLabels[ Focus ] ]->SelInit();
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cForm::Execute()
{
	if( Input::Button[ KEY_ENTER ].Pressed() || Input::Pad[0].Button[ PAD_A ].Pressed() || Input::Pad[0].Button[ PAD_START ].Pressed() )
	{
		if( !ActiveLabels.empty() )
		{
			SuperFlowState = cActions::ExecuteAction( Labels[ ActiveLabels[ Focus ] ]->ActionID );
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
cLabel& cForm::Group( const int GroupIdx, const int Index )
{
	int MyIndex = 0;
	for( size_t idx = 0; idx < Labels.size(); ++idx )
	{
		if( Labels[ idx ]->Group == GroupIdx )
		{
			if( Index == MyIndex )
			{
				return *Labels[ idx ];
			}
			MyIndex++;
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cForm::GroupPos( const int Group, const Vector2D& _Pos )
{
	for( size_t idx = 0; idx < Labels.size(); ++idx )
	{
		if( Labels[ idx ]->Group == Group )
		{
			Labels[ idx ]->Pos += _Pos;
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cForm::GroupPos( const int Group, const int Index, const Vector2D& _Pos )
{
	int MyIndex = 0;
	for( size_t idx = 0; idx < Labels.size(); ++idx )
	{
		if( Labels[ idx ]->Group == Group )
		{
			if( Index == MyIndex )
			{
				Labels[ idx ]->Pos += _Pos;
				return;
			}
			MyIndex++;
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cForm::GroupVisible( const int Group, const bool _Visible )
{
	for( size_t idx = 0; idx < Labels.size(); ++idx )
	{
		if( Labels[ idx ]->Group == Group )
		{
			Labels[ idx ]->Visible = _Visible;
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cForm::GroupVisible( const int Group, const int Index, const bool _Visible )
{
	int MyIndex = 0;
	for( size_t idx = 0; idx < Labels.size(); ++idx )
	{
		if( Labels[ idx ]->Group == Group )
		{
			if( Index == MyIndex )
			{
				Labels[ idx ]->Visible = _Visible;
				return;
			}
			MyIndex++;
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cForm::GroupColor( const int Group, const Gfx::Color _Color )
{
	for( size_t idx = 0; idx < Labels.size(); ++idx )
	{
		if( Labels[ idx ]->Group == Group )
		{
			Labels[ idx ]->Color = _Color;
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cForm::GroupColor( const int Group, const int Index, const Gfx::Color _Color )
{
	int MyIndex = 0;
	for( size_t idx = 0; idx < Labels.size(); ++idx )
	{
		if( Labels[ idx ]->Group == Group )
		{
			if( Index == MyIndex )
			{
				Labels[ idx ]->Color = _Color;
				return;
			}
			MyIndex++;
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cForm::GroupSelColor( const int Group, const Gfx::Color _Color )
{
	for( size_t idx = 0; idx < Labels.size(); ++idx )
	{
		if( Labels[ idx ]->Group == Group )
		{
			Labels[ idx ]->SelColor = _Color;
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cForm::GroupSelColor( const int Group, const int Index, const Gfx::Color _Color )
{
	int MyIndex = 0;
	for( size_t idx = 0; idx < Labels.size(); ++idx )
	{
		if( Labels[ idx ]->Group == Group )
		{
			if( Index == MyIndex )
			{
				Labels[ idx ]->SelColor = _Color;
				return;
			}
			MyIndex++;
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
