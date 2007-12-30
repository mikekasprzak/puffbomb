// - ------------------------------------------------------------------------------------------ - //
// EndianUtil - Endian manipulation functions //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Data_EndianUtil_H__
#define __Library_Data_EndianUtil_H__
// - ------------------------------------------------------------------------------------------ - //

#include "EndianUtil_Core.h"

#ifdef BIG_ENDIAN
	#include "EndianUtil_Big.h"
#else
	#include "EndianUtil_Little.h"
#endif // BIG_ENDIAN //

#include "EndianUtil_Accessory.h"

// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_EndianUtil_H__ //
// - ------------------------------------------------------------------------------------------ - //
