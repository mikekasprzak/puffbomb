// - ------------------------------------------------------------------------------------------ - //
// PackedFace //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Engine2D_Engine_DynamicComponent_Binary_PackedFace_H__
#define __Engine2D_Engine_DynamicComponent_Binary_PackedFace_H__
// - ------------------------------------------------------------------------------------------ - //
namespace Engine2D {
// - ------------------------------------------------------------------------------------------ - //
namespace DynamicComponent {
// - ------------------------------------------------------------------------------------------ - //
class cPackedFace {
public:
	unsigned int a:10;
	unsigned int b:10;
	unsigned int c:10;
		
private:
	// Adapt in to flags, if and when they exist //
	unsigned int Pad:2;
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace DynamicComponent //
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Engine2D //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Engine2D_Engine_DynamicComponent_Binary_PackedFace_H__ //
// - ------------------------------------------------------------------------------------------ - //
