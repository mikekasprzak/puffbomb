// - ------------------------------------------------------------------------------------------ - //
// WindowManager //
// - ------------------------------------------------------------------------------------------ - //
#include "WindowManager.h"
#include <Graphics/Gfx.h>
#include <Input/Input.h>
#include <Global.h>
// - ------------------------------------------------------------------------------------------ - //
cWindowManager::cWindowManager()
{
	
}
// - ------------------------------------------------------------------------------------------ - //
cWindowManager::~cWindowManager()
{
	for( size_t idx = 0; idx < Form.size(); ++idx )
	{
		for( size_t idx2 = 0; idx2 < Form[ idx ].Labels.size(); ++idx2 )
		{
			delete Form[ idx ].Labels[ idx2 ];
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void cWindowManager::Load( const std::string& FileName )
{
	Form.push_back( cForm() );
	Form.back().Load( FileName );
}
// - ------------------------------------------------------------------------------------------ - //
