// - ------------------------------------------------------------------------------------------ - //
// String - Frontend and common C string functionality //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Data_String_Core_H__
#define __Library_Data_String_Core_H__
// - ------------------------------------------------------------------------------------------ - //
// String functions do not automatically include the null character in length calculations,
//   unless they are building a string. //
//
// TODO: 
// - ------------------------------------------------------------------------------------------ - //
//namespace Data {
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline const size_t length_String( const char* Str ) {
	return strlen( Str );	
}
// - ------------------------------------------------------------------------------------------ - //
// Note: strcpy needs enough room in Destination to hold the source string and a null character //
inline const char* copy_String( const char* Src, char* Dest ) {
	return strcpy( Dest, Src );
}
// - ------------------------------------------------------------------------------------------ - //
// Note: strcat needs enough room in Destination to hold both strings and a null character //
inline const char* cat_String( const char* Src, char* Dest ) {
	return strcat( Dest, Src );
}
// - ------------------------------------------------------------------------------------------ - //
inline const bool compare_String( const char* StrA, const char* StrB ) {
	// strcmp returns zero if a match, positive if mismatched character #1 is greater, else neg //
	return strcmp( StrA, StrB ) == 0;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Note: strcpy needs enough room in Destination to hold the source string and a null character //
inline const char* copyn_String( const char* Src, char* Dest, const size_t Number ) {
	return strncpy( Dest, Src, Number );
}
// - ------------------------------------------------------------------------------------------ - //
// Note: strcat needs enough room in Destination to hold both strings and a null character //
inline const char* catn_String( const char* Src, char* Dest, const size_t Number ) {
	return strncat( Dest, Src, Number );
}
// - ------------------------------------------------------------------------------------------ - //
inline const bool comparen_String( const char* StrA, const char* StrB, const size_t Number ) {
	return strncmp( StrA, StrB, Number ) == 0;
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
inline char* copy_String( const char* Src ) {
	char* Copy = new char[ length_String( Src ) + 1 ];
	
	copy_String( Src, Copy );
	
	return Copy;
}
// - ------------------------------------------------------------------------------------------ - //
inline char* new_String( const char* Src ) {
	return copy_String( Src );
}
// - ------------------------------------------------------------------------------------------ - //
inline void delete_String( char* Src ) {
	delete [] Src;	
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Create a new string by concatonating two strings together. //
inline char* new_String( const char* StrA, const char* StrB ) {
	size_t StrALen = length_String( StrA );
	size_t StrBLen = length_String( StrB );
	
	char* Str = new char[ StrALen + StrBLen + 1 ];
	copy_String( StrA, Str );
	cat_String( StrB, Str );
	
	return Str;
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// Returns a pointer to where in the string the pattern is found, otherwise a null pointer. //
inline const char* find_String( const char* Pattern, const char* Str ) {
	return strstr( Str, Pattern );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
//}; // namepsace Data //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_String_Core_H__ //
// - ------------------------------------------------------------------------------------------ - //
