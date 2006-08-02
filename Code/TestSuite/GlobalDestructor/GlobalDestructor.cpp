
// This is a test suite application for verifying that the current compiler supports global destructors //
// In fact, this test app also confirms that global constructors, and local ones, work. //
// It might be of best interest to improve this by testing namespaces, local classes, and other combinations //

#include <iostream>
#include <string>
using namespace std;

class Rubarb {
public:
	string Text;

	Rubarb( string _Text ) :
		Text( _Text )
	{
		cout << "Constructed " << Text << endl;
	}
	~Rubarb() {
		cout << "Destructed " << Text << endl;
	}
};

Rubarb GlobalInstance( "Global before main ****" );

int main( int argc, char* argv[] ) {
	Rubarb LocalInstance( "Main Local Before Start Of Main Text" );
	cout << "* Start of Main" << endl;
	Rubarb OtherLocalInstance( "Main Local After Start Of Main Text" );
	
	{
		Rubarb BracketLocalInstance( "Brackets Local Before Start Of Brackets Text" );
		cout << "* Start of Brackets" << endl;
		Rubarb OtherBracketLocalInstance( "Brackets Local After Start Of Brackets Text" );
		
		cout << "* End of Brackets" << endl;	
	}
	
	
	cout << "* End of Main" << endl;
	
	exit( 0 );
	return 0;
}

Rubarb OtherGlobalInstance( "Global after before main %%%%" );
