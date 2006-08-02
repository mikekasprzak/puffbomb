// - ------------------------------------------------------------------------------------------ - //
// A tool that converts model or text based mesh3d data to bin mesh3d data //
// - ------------------------------------------------------------------------------------------ - //
#include "Model.h"
#include <iostream>
int main( int argc, char* argv[] ) {
	// Must have 2 or more arguments //
	if( argc < 3 )
		return -1;
	if( ( argc - 1 ) % 2 )
	{
		std::cout << "Un-even amount of args!!!" << std::endl;
		return -1;
	} 

	for( int idx = 1; idx < argc; ++idx )
	{
		std::cout << argv[idx] << " < Converted to > ";
		
		// even arguments are the infiles and locations //
		cModel TempModel;
		TempModel.Load( argv[idx] );
		++idx;
		// odd arguments are the outfiles and locations //
		TempModel.SaveBin( argv[idx] );
		
		std::cout << argv[idx] << std::endl;

	}
	
	return 0;
}
// - ------------------------------------------------------------------------------------------ - //
