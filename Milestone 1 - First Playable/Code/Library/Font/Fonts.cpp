// - ------------------------------------------------------------------------------------------ - //
#include <Font/Fonts.h>
// - ------------------------------------------------------------------------------------------ - //
//cFont cFonts::ComicSansMS;
cFont cFonts::FlangeLight;
// - ------------------------------------------------------------------------------------------ - //
#include <string>
// - ------------------------------------------------------------------------------------------ - //
cFonts::cFonts()
{

}
void cFonts::LoadFonts()
{
//	std::string FontLocation = "Content/PuffBOMB/2D/Fonts/ComicSansMS.font";
//	std::string FontLocation = "2D/Fonts/ComicSansMS.font";
//	ComicSansMS.Load( FontLocation );

//	FontLocation = "Content/PuffBOMB/2D/Fonts/FlangeLight.font";
	std::string FontLocation = "2D/Fonts/FlangeLight.font";
	FlangeLight.Load( FontLocation );

}
