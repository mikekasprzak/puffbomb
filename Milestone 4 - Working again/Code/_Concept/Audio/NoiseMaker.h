
namespace Audio {
	class cNoiseMaker {
	public:
		// This should be a class to derive from.  It provides a mechanism to control sound //
		// playback on sounds associated with itself.  For cohesiveness, all sounds should be //
		// added to the derived class of this.  Sounds are then queue'd through this interface, //
		// so to give the control to stop and prioritize sound stoppings.  Positional information //
		// can also be included as an argument if there's interest in 2D/3D spacial placement. //
		
		// Sounds should also be activatable directly from a sound class, but they lack //
		// instancing information that allows us to stop them as a reactionary sound //
		
		
	}; // class cNoiseMaker //
}; // namespace Audio //
