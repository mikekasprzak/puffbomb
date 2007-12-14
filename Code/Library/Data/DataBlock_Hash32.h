// - ------------------------------------------------------------------------------------------ - //
// DataBlock Hash32 - Data Hashing //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_FileIO_DataBlock_Hash32_H__
#define __Library_FileIO_DataBlock_Hash32_H__
// - ------------------------------------------------------------------------------------------ - //
//namespace Data {
// - ------------------------------------------------------------------------------------------ - //
// Taken from Gamedeveloper magazine's InnerProduct (Sean Barrett 2005-03-15)
// 
// circular shift hash -- produces good results if modding by a prime;
// longword at a time would be faster (need alpha-style "is any byte 0"),
// or just use the first longword
// - ------------------------------------------------------------------------------------------ - //
unsigned int hash32_DataBlock( const DataBlock* Data ) {
	if (!Data)
		return 0;
 
	unsigned char *n = (unsigned char *) Data->Data;
	unsigned int acc = 0x55555555;
	
	for ( size_t size = Data->Size; size; --size ) {
		acc = (acc >> 27) + (acc << 5) + *n++;
	}
	
	return acc;
}
// - ------------------------------------------------------------------------------------------ - //
//}; // namepsace Data //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_FileIO_DataBlock_Hash32_H__ //
// - ------------------------------------------------------------------------------------------ - //
