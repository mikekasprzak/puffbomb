#include <string>

#include <Util/String.h>
#include <Util/Debug.h>

using namespace std;


int main( int argc, char* argv[] ) {
	// String Function Tests //
	{
		Log( 10, "String Function Tests" );
		
		string Chud = "src/Content.rome.paper/Experimental.mutant/SpiderPlayground.dig.me.a.life.map";
		
		Log( 10, "Input: " << Chud );

		// -------------------------------------------------------------------------------------- //
		
		// Munging functions //
		Log( 10, "Directory: " << String::Directory(Chud) );
		Log( 10, "FileName: " << String::FileName(Chud) );
		Log( 10, "BaseName: " << String::BaseName(Chud) );
		Log( 10, "Extension: " << String::Extension(Chud) );
		Log( 10, "LastExtension: " << String::LastExtension(Chud) );
		Log( 10, "NoLastExtension: " << String::NoLastExtension(Chud) );
		
		Log( 10, "SystemSlash: " << String::SystemSlash(Chud) );
		Log( 10, "NotSystemSlash: " << String::NotSystemSlash(Chud) );
		Log( 10, "UnixSlash: " << String::UnixSlash(Chud) );
		Log( 10, "WindowsSlash: " << String::WindowsSlash(Chud) );

		Log( 10, "UpperCase: " << String::UpperCase(Chud) );
		Log( 10, "LowerCase: " << String::LowerCase(Chud) );

		// -------------------------------------------------------------------------------------- //
		
		// Extension testing //
		if ( String::HasExtension( Chud, ".me" ) ) {
			Log( 10, ".me found in string" );
		}
		else {
			Log( 10, ".me not found in string" );
		}

		if ( String::HasExtension( Chud, ".m" ) ) {
			Log( 10, ".m found in string" );
		}
		else {
			Log( 10, ".m not found in string" );
		}
	
		if ( String::HasExtension( Chud, ".you" ) ) {
			Log( 10, ".you found in string" );
		}
		else {
			Log( 10, ".you not found in string" );
		}
	
		// -------------------------------------------------------------------------------------- //
	
		// Any Extension Testing //
		if ( String::HasAnyExtension( Chud, ".mutant" ) ) {
			Log( 10, ".mutant found in string" );
		}
		else {
			Log( 10, ".mutant not found in string" );
		}

		if ( String::HasAnyExtension( Chud, ".mutan" ) ) {
			Log( 10, ".mutan found in string" );
		}
		else {
			Log( 10, ".mutan not found in string" );
		}

		if ( String::HasAnyExtension( Chud, ".rome" ) ) {
			Log( 10, ".rome found in string" );
		}
		else {
			Log( 10, ".rome not found in string" );
		}
		
		// -------------------------------------------------------------------------------------- //
		
		// Directory testing //
		if ( String::HasDirectory( Chud, "src" ) ) {
			Log( 10, "src directory found in string" );
		}
		else {
			Log( 10, "src directory not found in string" );
		}

		if ( String::HasDirectory( Chud, "src/" ) ) {
			Log( 10, "src/ directory found in string" );
		}
		else {
			Log( 10, "src/ directory not found in string" );
		}

		if ( String::HasDirectory( Chud, "rc" ) ) {
			Log( 10, "rc directory found in string" );
		}
		else {
			Log( 10, "rc directory not found in string" );
		}

		if ( String::HasDirectory( Chud, "rc/" ) ) {
			Log( 10, "rc/ directory found in string" );
		}
		else {
			Log( 10, "rc/ directory not found in string" );
		}

		if ( String::HasDirectory( Chud, "Content" ) ) {
			Log( 10, "Content directory found in string" );
		}
		else {
			Log( 10, "Content directory not found in string" );
		}

		if ( String::HasDirectory( Chud, "Content/" ) ) {
			Log( 10, "Content/ directory found in string" );
		}
		else {
			Log( 10, "Content/ directory not found in string" );
		}

		if ( String::HasDirectory( Chud, "Playground" ) ) {
			Log( 10, "Playground directory found in string" );
		}
		else {
			Log( 10, "Playground directory not found in string" );
		}
		
	}
			
	return 0;	
}
