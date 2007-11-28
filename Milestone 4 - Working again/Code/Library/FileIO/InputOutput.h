// - ------------------------------------------------------------------------------------------ - //
// Input Output //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_FileIO_InputOutput_H__
#define __Library_FileIO_InputOutput_H__
// - ------------------------------------------------------------------------------------------ - //
#include <sstream>
#include <fstream>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
using namespace std;
// - ------------------------------------------------------------------------------------------ - //
class cEndianReader {
public:
	ifstream File;
	bool LittleEndian;

public:
	cEndianReader() :
		LittleEndian( true )
	{
	}
	
	cEndianReader( const std::string& _FileName, bool _LittleEndian = true ) :
		File( _FileName.c_str(), ios::binary | ios::in ),
		LittleEndian( _LittleEndian )	
	{
	}

public:
	template< class T >
	void Read( const T& Data ) {
		if ( LittleEndian )
			File.read( (char*)&Data, sizeof(Data) );
		else {
			
		}
	}

	template< class T >
	void Read( const T* Data, size_t Size ) {
		if ( LittleEndian )
			File.read( (char*)Data, Size );
		else {
			
		}
	}

	int Read() {
		if ( LittleEndian ) {
			int Data;
			File.read( (char*)&Data, sizeof(Data) );
			
			return Data;
		}
		else {
			
		}
		return 0;
	}
	bool Empty() {
		File.get();
		if( !File.good() )
		{
			return true;
		}
		File.unget();
		
		return false;
	}

};
// - ------------------------------------------------------------------------------------------ - //
class cEndianWriter {
public:
	ofstream File;
	bool LittleEndian;

public:
	cEndianWriter() :
		LittleEndian( true )
	{
	}
	
	cEndianWriter( const std::string& _FileName, bool _LittleEndian ) :
		File( _FileName.c_str(), ios::binary | ios::out ),
		LittleEndian( _LittleEndian )	
	{
	}

public:
	template< class T >
	void Write( const T& Data ) {
		if ( LittleEndian )
			File.write( (char*)&Data, sizeof(Data) );
		else {
			
		}
	}

	template< class T >
	void Write( const T* Data, size_t Size ) {
		if ( LittleEndian )
			File.write( (char*)Data, Size );
		else {
			
		}
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_FileIO_InputOutput_H__ //
// - ------------------------------------------------------------------------------------------ - //

