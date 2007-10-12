
// This should conceptually contain utilities for images. //

// Image type //

typedef Image {
	// Some sort of way to identify data found inside. //
	// LZMA or PNG compression is already passed.  This is raw data now, DXT, or Palette+Image.  //
	int ImageType;
	
	DataBlock* Data;
};

// Loaded image blocks point to these (Image* HamsterGraphic) //

