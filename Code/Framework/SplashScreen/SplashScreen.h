// - ------------------------------------------------------------------------------------------ - //
// SplashScreen //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Framework_SplashScreen_SplashScreen_H__
#define __Framework_SplashScreen_SplashScreen_H__
// - ------------------------------------------------------------------------------------------ - //
#include <MessageEntity.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Graphics/Camera.h>
#include <Graphics/Texture.h>
#include <Math/Vector.h>
// - ------------------------------------------------------------------------------------------ - //
#include <string>
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
	cSplashScreen( std::string TextureName, int EndTime = 3600, Real Scale = 1.0 );
	~cSplashScreen();
	
	void Draw();
	void Step();
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __Framework_SplashScreen_SplashScreen_H__ // 
// - ------------------------------------------------------------------------------------------ - //
