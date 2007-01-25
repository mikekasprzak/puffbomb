// - ------------------------------------------------------------------------------------------ - //
// Axis //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Input_Axis_H__
#define __Input_Axis_H__
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include <Geometry/Real.h>
#include <Util/ClassDesigner.h>
// - ------------------------------------------------------------------------------------------ - //

namespace Input {

// - ------------------------------------------------------------------------------------------ - //
	class cAxis: public Real {
	private:
		//Real _Current;
		
		Real _Last;
	
		// Digital Interpretation //
		Real _Digital;
		int _BitMask;
		int _LastBitMask;
		
		int _KeyRepeat;
		
		enum {
			Left = bit0,
			Right = bit1,
		};
		

	public:
		// - ---------------------------------------------------------------------------------- - //
		inline const Real Current() const {
			return *this;
		}
		// - ---------------------------------------------------------------------------------- - //
		inline const Real Last() const {
			return _Last;
		}
		// - ---------------------------------------------------------------------------------- - //
		inline const Real Diff() const {
			return (_Last - *this);
		}
		// - ---------------------------------------------------------------------------------- - //
		inline const Real& KeyRepeat() const {
			if ( _KeyRepeat == 0 )
				return _Digital;

			if ( _KeyRepeat >= 31 )
				if ( (_KeyRepeat & 3) == 0 )
					return _Digital;
			
			return Real::Zero;
		}
		// - ---------------------------------------------------------------------------------- - //

		// - ---------------------------------------------------------------------------------- - //
		inline operator Real () {
			return Current();
		}
		// - ---------------------------------------------------------------------------------- - //

		// - ---------------------------------------------------------------------------------- - //
		inline const Real Digital() const {
			return _Digital;
		}
		// - ---------------------------------------------------------------------------------- - //

		// - ---------------------------------------------------------------------------------- - //
		// Return the value of the axis as digital bitmask (bits for left,right,up,down) //
		inline int BitMask() const {
			return _BitMask;
		}
		// - ---------------------------------------------------------------------------------- - //
		// Return the value of the axis as digital bitmask (bits for left,right,up,down) //
		inline int BitMaskPressed() const {
			return (_BitMask ^ _LastBitMask) & _BitMask;
		}
		// - ---------------------------------------------------------------------------------- - //
		// Return the value of the axis as digital bitmask (bits for left,right,up,down) //
		inline int BitMaskReleased() const {
			return (_BitMask ^ _LastBitMask) & _LastBitMask;
		}
		// - ---------------------------------------------------------------------------------- - //
		// Return the value of the axis as digital bitmask (bits for left,right,up,down) //
		inline int BitMaskKeyRepeat() const {
			if ( _KeyRepeat == 0 )
				return _BitMask;

			if ( _KeyRepeat >= 31 )
				if ( (_KeyRepeat & 3) == 0 )
					return _BitMask;
			
			return 0;
		}
		// - ---------------------------------------------------------------------------------- - //

	
	public:
		// - ---------------------------------------------------------------------------------- - //
		inline cAxis() {
		}	
		// - ---------------------------------------------------------------------------------- - //
		inline void Reset() {
			Set( Real::Zero );
			_Last = Real::Zero;
			_Digital = Real::Zero;
			
			_BitMask = 0;
			_LastBitMask = 0;
			_KeyRepeat = 0;
		}
		// - ---------------------------------------------------------------------------------- - //		
		inline void Update( Real NewState ) {
			_Last = *this;
			Set( NewState );
			
			// Calculate the axis as digital (no analog smoothness) //
			_Digital = ((this->Abs() > Real::Half )? Real::One : Real::Zero ) * this->Normal();

			// Write a bitmask for input //
			int ThisBitMask = 0;
			
			if ( _Digital == Real::One ) {
				ThisBitMask |= bit0;
			}
			if ( _Digital == -Real::One ) {
				ThisBitMask |= bit1;
			}
			
			_LastBitMask = _BitMask;
			_BitMask = ThisBitMask;

			// Check for change //
			if ( _LastBitMask != _BitMask ) {
				_KeyRepeat = 0;
			}
			else {
				_KeyRepeat++;
			}			
		}
		// - ---------------------------------------------------------------------------------- - //
	};
// - ------------------------------------------------------------------------------------------ - //

};

// - ------------------------------------------------------------------------------------------ - //
#endif // __Input_Axis_H__ //
// - ------------------------------------------------------------------------------------------ - //
