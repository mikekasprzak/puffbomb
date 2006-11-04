#ifdef EDITOR
// - ------------------------------------------------------------------------------------------ - //
#include "MapEdit.h"
#include <Input/Input.h>

// - ------------------------------------------------------------------------------------------ - //
using namespace Input;
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cMapEdit::SwitchDyn()
{
	if ( Button[ KEY_LEFT ].Pressed() ) 
	{
		if( !Mesh3DName.empty() )
		{
			if( CurMesh3D > 0 )
			{
				--CurMesh3D;
			}
			else
			{
				CurMesh3D = Mesh3DName.size() - 1;
			}
			
			UpdateMesh3DPreview();
		}
	}
	else if ( Button[ KEY_RIGHT ].Pressed() )
	{
		if( !Mesh3DName.empty() )
		{
			if( CurMesh3D < Mesh3DName.size() - 1 )
			{
				++CurMesh3D;
			}
			else
			{
				CurMesh3D = 0;	
			}
				
			UpdateMesh3DPreview();
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
#endif // Editor //
// - ------------------------------------------------------------------------------------------ - //
