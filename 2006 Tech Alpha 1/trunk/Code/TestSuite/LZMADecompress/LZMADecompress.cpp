// - ------------------------------------------------------------------------------------------ - //
// A test tool that will be used to try and decompress a LZMA or 7Zip file //
// - ------------------------------------------------------------------------------------------ - //
#include <iostream>
#include <fstream>
#include <External/Lzma/LzmaDecode.h>

using namespace std;
// - ------------------------------------------------------------------------------------------ - //

int main( int argc, char* argv[] ) {
	// Must have 2 or more arguments //
	if( argc < 3 )
		return -1;

	long size;
	unsigned char properties[LZMA_PROPERTIES_SIZE];

	std::cout << argv[1] << std::endl;
	
	ifstream infile( argv[1], ifstream::binary );
	
	// Get the size of the file
	infile.seekg( 0, ifstream::end );
	size=infile.tellg();
	infile.seekg( 0 );

	// allocate memory for file content
	char* buffer = new char [size];

	infile.read( buffer, size );
	
	*properties = buffer[0];
	
	unsigned long long int* tempUFileSize =  (unsigned long long int*)&buffer[LZMA_PROPERTIES_SIZE];
	unsigned long long int UFileSize = *tempUFileSize;

	CLzmaDecoderState state;
	
	if( LzmaDecodeProperties( &state.Properties, properties, LZMA_PROPERTIES_SIZE) != LZMA_RESULT_OK )
	{
 	  	std::cout << "Incorrect stream properties" << std::endl;
 	  	return -1;
    }

	state.Probs = (CProb *)malloc(LzmaGetNumProbs(&state.Properties) * sizeof(CProb));
	if (state.Probs == 0)
	{
		return -1;
	}
	unsigned char* UBuffer = new unsigned char [UFileSize];

	size_t inProcessed = 0;
	size_t outProcessed = 0;
	int res = LzmaDecode( &state, ( unsigned char* )&buffer[ LZMA_PROPERTIES_SIZE + 8 ], size, &inProcessed, UBuffer, UFileSize, &outProcessed );

	infile.close();
	
	std::ofstream outfile( argv[2], ofstream::binary );

	outfile.write( (char*)UBuffer, sizeof( unsigned char ) * UFileSize );
	
	outfile.close();

	delete[] buffer;
	delete[] UBuffer;
	
	return 0;
}
// - ------------------------------------------------------------------------------------------ - //
