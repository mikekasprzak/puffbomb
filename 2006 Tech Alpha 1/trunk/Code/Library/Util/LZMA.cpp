// - ------------------------------------------------------------------------------------------ - //
// LZMA //
// - ------------------------------------------------------------------------------------------ - //
#include "LZMA.h"
// - ------------------------------------------------------------------------------------------ - //
#include <fstream>
// - ------------------------------------------------------------------------------------------ - //
#include <Util/Debug.h>
#include <Util/String.h>
#include <External/Lzma/LzmaDecode.h>
// - ------------------------------------------------------------------------------------------ - //
namespace LZMA {
// - ------------------------------------------------------------------------------------------ - //
	// Will unpack and return lzma file to bin //
	// If no .pack extension was found it will return the bin data with no extraction //
	char* UnPack( const std::string& FileName )
	{
		long FileSize;
		
		std::ifstream infile( FileName.c_str(), std::ifstream::binary );
		
		// Get the size of the file
		infile.seekg( 0, std::ifstream::end );
		FileSize=infile.tellg();
		infile.seekg( 0 );
	
		// allocate memory for file content
		char* buffer = new char [FileSize];
	
		infile.read( buffer, FileSize );

		infile.close();
		
		if( String::HasExtension( FileName, ".pack" ) )
		{
			unsigned char properties[LZMA_PROPERTIES_SIZE];

			*properties = buffer[0];
	
			unsigned long long int* tempUFileSize =  (unsigned long long int*)&buffer[LZMA_PROPERTIES_SIZE];
			unsigned long long int UFileSize = *tempUFileSize;
		
			CLzmaDecoderState state;
			
			if( LzmaDecodeProperties( &state.Properties, properties, LZMA_PROPERTIES_SIZE) != LZMA_RESULT_OK )
			{
				Log( LOG_MESH_INFO, "Incorrect stream properties (LZMA.h)" );
		 	  	return buffer;
		    }
			
			state.Probs = (CProb *)malloc(LzmaGetNumProbs(&state.Properties) * sizeof(CProb));
			if (state.Probs == 0)
			{
				Log( LOG_MESH_INFO, "state.Probs == 0 (LZMA.h)" );
				return buffer;
			}
			char* UBuffer = new char [UFileSize];
		
			size_t inProcessed = 0;
			size_t outProcessed = 0;
			int res = LzmaDecode( &state, ( unsigned char* )&buffer[ LZMA_PROPERTIES_SIZE + 8 ], FileSize, &inProcessed, ( unsigned char* )UBuffer, UFileSize, &outProcessed );
			
			delete[] buffer;
			
			return UBuffer;
		}
		else
		{
			return buffer;
		}
	}
	// - -------------------------------------------------------------------------------------- - //

// - ------------------------------------------------------------------------------------------ - //
}; // namespace LZMA //
// - ------------------------------------------------------------------------------------------ - //
