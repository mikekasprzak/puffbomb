gcc -c -I /Hammer/CodeExternal/BZip /Hammer/Code/External/BZip/bzlib.c -o bzlib.o
gcc -c -I /Hammer/CodeExternal/BZip /Hammer/Code/External/BZip/compress.c -o compress.o
gcc -c -I /Hammer/CodeExternal/BZip /Hammer/Code/External/BZip/decompress.c -o decompress.o
gcc -c -I /Hammer/CodeExternal/BZip /Hammer/Code/External/BZip/crctable.c -o crctable.o
gcc -c -I /Hammer/CodeExternal/BZip /Hammer/Code/External/BZip/blocksort.c -o blocksort.o
gcc -c -I /Hammer/CodeExternal/BZip /Hammer/Code/External/BZip/huffman.c -o huffman.o
gcc -c -I /Hammer/CodeExternal/BZip /Hammer/Code/External/BZip/randtable.c -o randtable.o
ar r bzip.a bzlib.o compress.o decompress.o crctable.o blocksort.o huffman.o randtable.o
del *.o