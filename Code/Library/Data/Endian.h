// - ------------------------------------------------------------------------------------------ - //
// Endian - Endian manipulation functions //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Data_Endian_H__
#define __Library_Data_Endian_H__
// - ------------------------------------------------------------------------------------------ - //

#include "Endian_Core.h"

#ifdef BIG_ENDIAN
	#include "Endian_Big.h"
#else
	#include "Endian_Little.h"
#endif // BIG_ENDIAN //

#include "Endian_Accessory.h"

// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_Endian_H__ //
// - ------------------------------------------------------------------------------------------ - //