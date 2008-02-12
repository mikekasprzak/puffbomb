// - ------------------------------------------------------------------------------------------ - //
// Stream Core - Streams are standard interface for data sources, to share a common syntax. //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Data_Stream_Core_H__
#define __Library_Data_Stream_Core_H__
// - ------------------------------------------------------------------------------------------ - //
//namespace Data {
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Opening Stream (Need these for template specialization to work correctly) //
// - ------------------------------------------------------------------------------------------ - //
template<class T>
inline T open_Stream( const char* /*FileName*/ );
// - ------------------------------------------------------------------------------------------ - //
template<class T>
inline T open_Stream( const char* /*FileName*/, const char* /*OpenMask = "rb"*/ );
// - ------------------------------------------------------------------------------------------ - //
template<class T>
inline T open_readonly_Stream( const char* /*FileName*/ );
// - ------------------------------------------------------------------------------------------ - //
template<class T>
inline T open_writeonly_Stream( const char* /*FileName*/ );
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
//}; // namespace Data //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_Stream_Core_H__ //
// - ------------------------------------------------------------------------------------------ - //