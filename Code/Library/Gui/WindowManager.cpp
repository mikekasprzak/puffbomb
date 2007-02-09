// - ------------------------------------------------------------------------------------------ - //
// WindowManager //
// - ------------------------------------------------------------------------------------------ - //
#include "WindowManager.h"
#include <Global.h>
#include <Animation/AnimationPool.h>
// - ------------------------------------------------------------------------------------------ - //
#include <sstream>
#include <fstream>
#include <iostream>
// - ------------------------------------------------------------------------------------------ - //
using namespace std;
// - ------------------------------------------------------------------------------------------ - //
void cWindowManager::Step()
{
	for( size_t idx = 0; idx < Form.size(); ++idx )
	{
		Form[ idx ].Step();
	}

}
// - ------------------------------------------------------------------------------------------ - //
void cWindowManager::Draw()
{
	for( size_t idx = 0; idx < Form.size(); ++idx )
	{
		Form[ idx ].Draw();
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cWindowManager::Load( const std::string &File )
{
	char Line[1024];
	
	ifstream InFile( File.c_str() );
	
	std::vector< Real > TempReals;
	
	int CurDialog = 0;
	int Group = 0;
	
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
				Form.push_back( cForm(
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
				
//				TempReals.push_back( atof( Token.c_str() ) + Form[ CurDialog ].Pos.x ); // 0
				TempReals.push_back( atof( Token.c_str() ) ); // 0

				Text >> Token;
				
//				TempReals.push_back( atof( Token.c_str() ) + Form[ CurDialog ].Pos.y ); // 1
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
			else if( Token == "EndText" )
			{
				Form[ CurDialog ].Labels.push_back(
					new cTextLabel(
						Vector2D( TempReals[ 0 ], TempReals[ 1 ] ),
						bool( TempReals[ 2 ] ),
						int( TempReals[ 3 ] ),
						TempString,
						TempReals[ 4 ],
						Gfx::RGBA( TempReals[ 5 ], TempReals[ 6 ], TempReals[ 7 ], TempReals[ 8 ] ) 
					)
				);				
				
				Form[ CurDialog ].Labels.back()->Group = Group;
				
				if( bool( TempReals[ 2 ] ) == false )
				{
					Form[ CurDialog ].ActiveLabels.push_back(
						Form[ CurDialog ].Labels.size() - 1
					);
				}
				
				if( TempReals.size() > 12 )
				{
					Form[ CurDialog ].Labels.back()->SelColor = Gfx::RGBA( TempReals[ 9 ], TempReals[ 10 ], TempReals[ 11 ], TempReals[ 12 ] );
				}
				
				Group = 0;
				TempReals.clear();
				TempString.clear();
			}	
			// - ------------------------------------------------------------------------------ - //
			else if( Token == "AniLabel" )
			{
				Text >> Token;
				
//				TempReals.push_back( atof( Token.c_str() ) + Form[ CurDialog ].Pos.x ); // 0
				TempReals.push_back( atof( Token.c_str() ) ); // 0

				Text >> Token;
				
//				TempReals.push_back( atof( Token.c_str() ) + Form[ CurDialog ].Pos.y ); // 1
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
				Form[ CurDialog ].Labels.push_back( 
					new cAniLabel(
						Vector2D( TempReals[ 0 ], TempReals[ 1 ] ),
						bool( TempReals[ 2 ] ),
						int( TempReals[ 3 ] ),
						AnimationPool.Load( TempString ),
						AnimationPool.Load( TempString2 ),
						int( TempReals[ 4 ] )
					)
				);
				
				Form[ CurDialog ].Labels.back()->Group = Group;
				
				if( bool( TempReals[ 2 ] ) == false )
				{
					Form[ CurDialog ].ActiveLabels.push_back(
						( Form[ CurDialog ].Labels.size() - 1 )
					);
				}
				
				if( TempReals.size() > 8 )
				{
					Form[ CurDialog ].Labels.back()->Color = Gfx::RGBA( TempReals[ 5 ], TempReals[ 6 ], TempReals[ 7 ], TempReals[ 8 ] );
				}
				if( TempReals.size() > 12 )
				{
					Form[ CurDialog ].Labels.back()->SelColor = Gfx::RGBA( TempReals[ 9 ], TempReals[ 10 ], TempReals[ 11 ], TempReals[ 12 ] );
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
				Form[ CurDialog ].Labels.push_back(
					new cLabel( Vector2D( TempReals[ 0 ], TempReals[ 1 ] ), true, 0, Gfx::White(), Gfx::White() )
					);
					
				Form[ CurDialog ].Labels.back()->Group = Group;
				
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
				++CurDialog;
			}
			// - ------------------------------------------------------------------------------ - //
			// Extra Features //
			else if( Token == "IsVisible" )
			{
				Text >> Token;
				
				Form[ CurDialog ].IsVisible = bool( atoi( Token.c_str() ) );
			}
			else if( Token == "IsLabelsVisible" )
			{
				Text >> Token;
				
				Form[ CurDialog ].IsLabelsVisible = bool( atoi( Token.c_str() ) );
			}

		}
	}
	Log( LOG_HIGHEST_LEVEL, Form.size() << " Dialog's Loaded" );
}
// - ------------------------------------------------------------------------------------------ - //
Real cWindowManager::Anchor( const std::string &AnchorName )
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
