// - ------------------------------------------------------------------------------------------ - //
// Assert //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Util_Assert_H__
#define __Util_Assert_H__
// - ------------------------------------------------------------------------------------------ - //
// Todo: Add makefile means to disable Harsh Assert Exiting //
// - ------------------------------------------------------------------------------------------ - //
#include <iostream>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#ifndef NDEBUG
// - ------------------------------------------------------------------------------------------ - //

// An important function we use to kill the game //
extern void QuitGame( int ReturnCode );

// __func__ is general purpose //
// __PRETTY_FUNCTION__ is GCC only //

// Assertion //
#define Assert( ___TEST, ___STR ) \
	if ( ___TEST ) { \
		std::cout << "- -------------------------------------------------------- - " << std::endl; \
		std::cout << "Assert Error: " << ___STR << std::endl << \
			"   Line: " << __LINE__ << "  File: " << __FILE__ << std::endl << \
			"   Func: " << __PRETTY_FUNCTION__ << std::endl; \
		std::cout << "- -------------------------------------------------------- - " << std::endl; \
		QuitGame( 1 ); \
	}

// Warnings //
#define Warning( ___TEST, ___STR ) \
	if ( ___TEST ) \
		std::cout << "Warning: " << ___STR << std::endl << \
			"   Line: " << __LINE__ << "  File: " << __FILE__ << std::endl << \
			"   Func: " << __PRETTY_FUNCTION__ << std::endl;

// - ------------------------------------------------------------------------------------------ - //
#else // NDEBUG //
// - ------------------------------------------------------------------------------------------ - //
#define Assert( ... ) ;
#define Warning( ... ) ;
// - ------------------------------------------------------------------------------------------ - //
#endif // NDEBUG //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Util_Assert_H__ //
// - ------------------------------------------------------------------------------------------ - //
