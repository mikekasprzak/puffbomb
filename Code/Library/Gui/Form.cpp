// - ------------------------------------------------------------------------------------------ - //
// Form //
// - ------------------------------------------------------------------------------------------ - //
#include "Form.h"
#include <Game/Global.h>
#include <Animation/AnimationPool.h>
// - ------------------------------------------------------------------------------------------ - //
#include <sstream>
#include <fstream>
#include <iostream>
// - ------------------------------------------------------------------------------------------ - //
using namespace std;
// - ------------------------------------------------------------------------------------------ - //
void cForm::Step()
{
	for( size_t idx = 0; idx < DialogBox.size(); ++idx )
	{
		DialogBox[ idx ].Step();
	}

}
// - ------------------------------------------------------------------------------------------ - //
void cForm::Draw()
{
	for( size_t idx = 0; idx < DialogBox.size(); ++idx )
	{
		DialogBox[ idx ].Draw();
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cForm::Load( const std::string &File )
{
	char Line[1024];
	
	ifstream InFile( File.c_str() );
	
	std::vector< Real > TempReals;
	
	int CurDialog = 0;
	
	std::string TempString;
	std::string TempString2;
	
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
			}
			else if( Token == "CreateDialog" )
			{
				DialogBox.push_back( cDialogBox(
					Vector2D( TempReals[ 0 ], TempReals[ 1 ] ),
					Vector2D( TempReals[ 2 ], TempReals[ 3 ] ),
					int( TempReals[ 4 ] ),
					TempString )
				);
				TempReals.clear();
				TempString.clear();
			}
			
			// - ------------------------------------------------------------------------------ - //
			else if( Token == "TextLabel" )
			{
				Text >> Token;
				
				TempReals.push_back( atof( Token.c_str() ) + DialogBox[ CurDialog ].Pos.x ); // 0

				Text >> Token;
				
				TempReals.push_back( atof( Token.c_str() ) + DialogBox[ CurDialog ].Pos.y ); // 1
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

			}	
			else if( Token == "Alpha" )
			{
				Text >> Token;
				
				TempReals.push_back( atof( Token.c_str() ) ); // 8
			}	
			else if( Token == "EndText" )
			{
				DialogBox[ CurDialog ].TextLabel.push_back(
					cTextLabel(
						Vector2D( TempReals[ 0 ], TempReals[ 1 ] ),
						bool( TempReals[ 2 ] ),
						int( TempReals[ 3 ] ),
						TempString,
						TempReals[ 4 ],
						gfx::RGBA( TempReals[ 5 ], TempReals[ 6 ], TempReals[ 7 ], TempReals[ 8 ] ) 
					)
				);
				
				if( bool( TempReals[ 2 ] ) == false )
				{
					DialogBox[ CurDialog ].ActiveLabels.push_back(
						DialogBox[ CurDialog ].TextLabel.size() - 1
					);
				}
				
				TempReals.clear();
				TempString.clear();
			}	
			// - ------------------------------------------------------------------------------ - //
			else if( Token == "AniLabel" )
			{
				Text >> Token;
				
				TempReals.push_back( atof( Token.c_str() ) + DialogBox[ CurDialog ].Pos.x ); // 0

				Text >> Token;
				
				TempReals.push_back( atof( Token.c_str() ) + DialogBox[ CurDialog ].Pos.y ); // 1
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
				DialogBox[ CurDialog ].AniLabel.push_back(
					cAniLabel(
						Vector2D( TempReals[ 0 ], TempReals[ 1 ] ),
						bool( TempReals[ 2 ] ),
						int( TempReals[ 3 ] ),
						AnimationPool.Load( TempString ),
						AnimationPool.Load( TempString2 ),
						int( TempReals[ 4 ] )
					)
				);
				
				if( bool( TempReals[ 2 ] ) == false )
				{
					DialogBox[ CurDialog ].ActiveLabels.push_back(
						( DialogBox[ CurDialog ].AniLabel.size() - 1 ) + 10000
					);
				}
				
				TempReals.clear();
				TempString.clear();
				TempString2.clear();
			}	
			else if( Token == "EndDialog" )
			{
				++CurDialog;
			}
			// - ------------------------------------------------------------------------------ - //
			// Extra Features //
			else if( Token == "IsVisable" )
			{
				Text >> Token;
				
				DialogBox[ CurDialog ].IsVisable = bool( atoi( Token.c_str() ) );
			}
			else if( Token == "IsLabelsVisable" )
			{
				Text >> Token;
				
				DialogBox[ CurDialog ].IsLabelsVisable = bool( atoi( Token.c_str() ) );
			}

		}
	}
	Log( LOG_HIGHEST_LEVEL, DialogBox.size() << " Dialog's Loaded" );
}
// - ------------------------------------------------------------------------------------------ - //
Real cForm::Anchor( const std::string &AnchorName )
{
	if( AnchorName == "Left" )
	{
		return cGlobal::Left;
	}
	else if( AnchorName == "Right" )
	{
		return cGlobal::Right;
	}
	else if( AnchorName == "Top" )
	{
		return cGlobal::Top;
	}
	else if( AnchorName == "Bottom" )
	{
		return cGlobal::Bottom;
	}
	else
	{
		return Real::Zero;	
	}
}
// - ------------------------------------------------------------------------------------------ - //
