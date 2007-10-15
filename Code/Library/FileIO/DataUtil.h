// - ------------------------------------------------------------------------------------------ - //
// DataUtil - Data utility/reading/writing wrapping library //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_FileIO_DataUtil_H__
#define __Library_FileIO_DataUtil_H__
// - ------------------------------------------------------------------------------------------ - //
namespace IO {
// - ------------------------------------------------------------------------------------------ - //
// MemSET wrapper //
inline void set_Data( int _Value, void* _Data, size_t _Size ) {
	memset( _Value, (char*)_Data, _Size );
}
// - ------------------------------------------------------------------------------------------ - //
// MemCPY wrapper //
inline void copy_Data( void* _Src, void* _Dest, size_t _Size ) {
	memcpy( _Dest, _Src, _Size );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void read_Data( char* _FileName, void* Data, size_t _Size ) {
	
}
// - ------------------------------------------------------------------------------------------ - //
inline void write_Data( char* _FlieName, void* Data, size_t _Size ) {
	
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
inline void* new_Data( size_t _Size ) {
	return (void*)(new char[_Size]);
}
// - ------------------------------------------------------------------------------------------ - //
inline void delete_Data( void* _Data ) {
	
}
// - ------------------------------------------------------------------------------------------ - //
inline void* new_Data( char* _FileName ) {
	// allocate and load the data //
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
}; // namespace IO //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_FileIO_DataBlock_H__ //
// - ------------------------------------------------------------------------------------------ - //
