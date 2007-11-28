
#include <Library/FileIO/DataUtil.h>
#include <Library/FileIO/DataUtilCompression.h>
#include <Library/FileIO/DataBlock.h>
#include <Library/FileIO/DataBlockCompression.h>
using namespace IO;

#include <iostream>
using namespace std;

int main( int argc, char* argv[] ) {

//  // C Style Reading //
//	{
//		DataBlock* Data = new_DataBlock( "Gravy.txt" );
//		DataBlock* Copy = copy_DataBlock( Data );
//	
//		Copy->Data[4] = 'm';
//	
//		cout << Data->Data << endl;
//		cout << Data->Size << endl;
//
//		cout << Copy->Data << endl;
//		cout << Copy->Size << endl;
//	
//		delete_DataBlock( Copy );
//		delete_DataBlock( Data );
//	}

//	// C++ Style Reading //
//	{
//		cDataBlock Data( "Gravy.txt" );
//		cDataBlock Copy( Data );
//		
//		Copy[4] = 'm';
//		
//		cout << Data.Data() << endl;
//		cout << Data.Size() << endl;
//	
//		cout << Copy.Data() << endl;
//		cout << Copy.Size() << endl;
//	}

	// LZMA Compression test //
	{
		cDataBlock Data( "GravyLZMA.pack" );
		cDataBlock Copy( cDataBlock::UnpackLZMA( Data ) );
		
		cout << "Compressed: " << Data.Size() << endl;
		cout << "Uncompressed: " << Copy.Size() << endl;
	
		cout << Copy.Data() << endl;
	}

	// BZIP Compression test //
	{
		cDataBlock Src( "Gravy.txt" );
		cDataBlock Dest( cDataBlock::PackBZIP( Src ) );
			
		Dest.Save( "GravyBZIP.pack" );
		
		cout << "Uncompressed: " << Src.Size() << endl;
		cout << "Compressed: " << Dest.Size() << endl;
	}
	
	// BZIP Uncompression test //
	{
		cDataBlock Src( "GravyBZIP.pack" );
		cDataBlock Dest( cDataBlock::UnpackBZIP( Src ) );
		
		cout << "Compressed: " << Src.Size() << endl;
		cout << "Uncompressed: " << Dest.Size() << endl;

		cout << Dest.Data() << endl;
	}


	// ZLIB Compression test //
	{
		cDataBlock Src( "Gravy.txt" );
		cDataBlock Dest( cDataBlock::PackZLIB( Src ) );
			
		Dest.Save( "GravyZLIB.pack" );
		
		cout << "Uncompressed: " << Src.Size() << endl;
		cout << "Compressed: " << Dest.Size() << endl;
	}
	
	// ZLIB Uncompression test //
	{
		cDataBlock Src( "GravyZLIB.pack" );
		cDataBlock Dest( cDataBlock::UnpackZLIB( Src ) );
		
		cout << "Compressed: " << Src.Size() << endl;
		cout << "Uncompressed: " << Dest.Size() << endl;

		cout << Dest.Data() << endl;
	}

	// Seems to be optional, but should require further investigation if I do decide to use it //
	//lzo_init();

	// LZO Compression test //
	{
		cDataBlock Src( "Gravy.txt" );
		cDataBlock Dest( cDataBlock::PackLZO( Src ) );
			
		Dest.Save( "GravyLZO.pack" );
		
		cout << "Uncompressed: " << Src.Size() << endl;
		cout << "Compressed: " << Dest.Size() << endl;
	}
	
	// LZO Uncompression test //
	{
		cDataBlock Src( "GravyLZO.pack" );
		cDataBlock Dest( cDataBlock::UnpackLZO( Src ) );
		
		cout << "Compressed: " << Src.Size() << endl;
		cout << "Uncompressed: " << Dest.Size() << endl;

		cout << Dest.Data() << endl;
	}	

	return 0;
}
