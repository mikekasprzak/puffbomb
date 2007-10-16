gcc -c -I /Hammer/CodeExternal/ZLib /Hammer/Code/External/ZLib/adler32.c
gcc -c -I /Hammer/CodeExternal/ZLib /Hammer/Code/External/ZLib/crc32.c
gcc -c -I /Hammer/CodeExternal/ZLib /Hammer/Code/External/ZLib/compress.c
gcc -c -I /Hammer/CodeExternal/ZLib /Hammer/Code/External/ZLib/deflate.c
gcc -c -I /Hammer/CodeExternal/ZLib /Hammer/Code/External/ZLib/gzio.c
gcc -c -I /Hammer/CodeExternal/ZLib /Hammer/Code/External/ZLib/inffast.c
gcc -c -I /Hammer/CodeExternal/ZLib /Hammer/Code/External/ZLib/inflate.c
gcc -c -I /Hammer/CodeExternal/ZLib /Hammer/Code/External/ZLib/inftrees.c
gcc -c -I /Hammer/CodeExternal/ZLib /Hammer/Code/External/ZLib/trees.c
gcc -c -I /Hammer/CodeExternal/ZLib /Hammer/Code/External/ZLib/uncompr.c
gcc -c -I /Hammer/CodeExternal/ZLib /Hammer/Code/External/ZLib/zutil.c
ar r zlib.a *.o
del *.o