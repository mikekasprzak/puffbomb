// - ------------------------------------------------------------------------------------------ - //
#include <stdlib.h>
#include "Real.h"
// - ------------------------------------------------------------------------------------------ - //
// Regular constants //
// - ------------------------------------------------------------------------------------------ - //
const Real Real::Identity( 1.0 );
const Real Real::Zero( 0.0 );
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Other constants special to this type //
// - ------------------------------------------------------------------------------------------ - //
const Real Real::One( 1.0 );
const Real Real::Half( 0.5 );
const Real Real::Quarter( 0.25 );
const Real Real::SmallestUnit( 0.005 );
	
const Real Real::Pi( 3.1415926535897932384626433832795 );
const Real Real::TwoPi( Pi+Pi );
// - ------------------------------------------------------------------------------------------ - //
Real Real::Random() {
	return rand() / (double)RAND_MAX;
}
// - ------------------------------------------------------------------------------------------ - //
