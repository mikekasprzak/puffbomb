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
inline const char* copy_String( const char* Src, char* Dest, const size_t Number ) {
	return strncpy( Dest, Src, Number );
}
// - ------------------------------------------------------------------------------------------ - //
// Note: strcat needs enough room in Destination to hold both strings and a null character //
inline const char* cat_String( const char* Src, char* Dest, const size_t Number ) {
	return strncat( Dest, Src, Number );
}
// - ------------------------------------------------------------------------------------------ - //
inline const bool compare_String( const char* StrA, const char* StrB, const size_t Number ) {
	return strncmp( StrA, StrB, Number ) == 0;
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// NOTE: Should this be removed, and replaced with just new?? //
inline char* copy_String( const char* Src ) {
	char* Copy = new char[ length_String( Src ) + 1 ];
	
	copy_String( Src, Copy );
	
	return Copy;
}
// - ------------------------------------------------------------------------------------------ - //
inline char* copy_String( const char* Src, const size_t Number ) {
	char* Copy = new char[ Number + 1 ];
	
	copy_String( Src, Copy, Number );
	
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
inline char* comma_String( const int Number ) {
	static char Text[32];
	char Sign[2];
	
	int AbsNumber = Number;
	if ( AbsNumber < 0 ) {
		AbsNumber = -AbsNumber;
		Sign[0] = '-';
		Sign[1] = 0;
	}
	else {
		Sign[0] = 0;
	}
	
	if ( AbsNumber < 1000 ) {
		sprintf( Text, "%s%i", Sign, AbsNumber );
	}
	else if ( AbsNumber < 1000000 ) {
		sprintf( Text, "%s%i,%003i", Sign, AbsNumber / 1000, AbsNumber % 1000 );
	}
	else if ( AbsNumber < 1000000000 ) {
		sprintf( Text, "%s%i,%003i,%003i", Sign, (AbsNumber/1000000), (AbsNumber / 1000) % 1000, AbsNumber % 1000 );
	}
	else {
		sprintf( Text, "%s%i,%003i,%003i,%003i", Sign, (AbsNumber/1000000000), (AbsNumber/1000000) % 1000, (AbsNumber / 1000) % 1000, AbsNumber % 1000 );
	}
	
	return Text;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
//}; // namepsace Data //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_String_Core_H__ //
// - ------------------------------------------------------------------------------------------ - //
