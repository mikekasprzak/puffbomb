// - ------------------------------------------------------------------------------------------ - //
// SplashScreen //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __FlowElements_SplashScreen_SplashScreen_H__
#define __FlowElements_SplashScreen_SplashScreen_H__
// - ------------------------------------------------------------------------------------------ - //
#include <MessageEntity.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Graphics/Camera.h>
#include <Graphics/Texture.h>
#include <Geometry/Vector.h>
// - ------------------------------------------------------------------------------------------ - //
class cSplashScreen : public cMessageEntity { 
private:
	cCamera* Camera;
	int Color;
	
	Vector3D TexVertex[ 4 ];
	Vector2D TexUV[ 4 ];
	unsigned int TexIndices[ 4 ];
	cTexture Tex;
	
public:
	cSplashScreen();
	~cSplashScreen();
	
	void Draw();
	void Step();
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __FlowElements_SplashScreen_SplashScreen_H__ // 
// - ------------------------------------------------------------------------------------------ - //
