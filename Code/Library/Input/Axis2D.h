// - ------------------------------------------------------------------------------------------ - //
// Axis2D //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Input_Axis2D_H__
#define __Input_Axis2D_H__
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include <Geometry/Vector.h>
#include <Util/ClassDesigner.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
namespace Input {
// - ------------------------------------------------------------------------------------------ - //
	class cAxis2D: public Vector2D {
	private:
		// 
		//Vector2D _Current;
		
		Vector2D _Last;
	
		// Digital Interpretation //
		Vector2D _Digital;
		int _BitMask;
		int _LastBitMask;
		
		int _KeyRepeat;
		
		enum {
			Left = bit0,
			Right = bit1,
			Down = bit2,
			Up = bit3
		};
	
	public:
		// - ---------------------------------------------------------------------------------- - //
		inline const Vector2D& Current() const {
			return *this;
		}
		// - ---------------------------------------------------------------------------------- - //
		inline const Vector2D& Last() const {
			return _Last;
		}
		// - ---------------------------------------------------------------------------------- - //
		inline const Vector2D Diff() const {
			return (_Last - *this);
		}
		// - ---------------------------------------------------------------------------------- - //
		inline const Vector2D& KeyRepeat() const {
			if ( _KeyRepeat == 0 )
				return *this;

			if ( _KeyRepeat >= 31 )
				if ( (_KeyRepeat & 7) == 0 )
					return *this;
			
			return Vector2D::Zero;
		}
		// - ---------------------------------------------------------------------------------- - //

		// - ---------------------------------------------------------------------------------- - //
		inline operator const Vector2D& () {
			return Current();
		}
		// - ---------------------------------------------------------------------------------- - //

		// - ---------------------------------------------------------------------------------- - //
		inline const Vector2D Digital() const {
			return _Digital;
		}
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
				if ( (_KeyRepeat & 7) == 0 )
					return _BitMask;
			
			return 0;
		}
		// - ---------------------------------------------------------------------------------- - //
	
	public:
		// - ---------------------------------------------------------------------------------- - //
		inline cAxis2D() {
		}	
		// - ---------------------------------------------------------------------------------- - //
		inline void Reset() {
			Set( Vector2D::Zero );
			_Last = Vector2D::Zero;
			_Digital = Vector2D::Zero;
			
			_BitMask = 0;
			_LastBitMask = 0;
			_KeyRepeat = 0;
		}
		// - ---------------------------------------------------------------------------------- - //		
		inline void Update( const Vector2D& NewState ) {
			_Last = *this;
			Set( NewState );
			
			// Calculate the axis as digital (no analog smoothness) //
			_Digital.x = ((x.Abs() > Real::Half )? Real::One : Real::Zero ) * x.Normal();
			_Digital.y = ((y.Abs() > Real::Half )? Real::One : Real::Zero ) * y.Normal();
				
			// Write a bitmask for input //
			int ThisBitMask = 0;
			
			if ( _Digital.x == Real::One ) {
				ThisBitMask |= bit0;
			}
			if ( _Digital.x == -Real::One ) {
				ThisBitMask |= bit1;
			}
			if ( _Digital.y == Real::One ) {
				ThisBitMask |= bit2;
			}
			if ( _Digital.y == -Real::One ) {
				ThisBitMask |= bit3;
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
};  // namespace Input //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Input_Axis2D_H__ //
// - ------------------------------------------------------------------------------------------ - //
