
// This is a test program to determine the function of endianness combined with bitfields on //
// various compilers.  Obviously, it's unfinished, but I'll likely want to finish it one day, //
// especially when I get my grubby hands on a kit. //

#include <iostream>
using namespace std;

class cNormal {
public:
	int a;
	int b;
};

class cOverlap {
public:
	int a:28;
	int b:28;
	int c:8;
};


class cExplicit {
public:
	int a:32;
	int b:32;
};


int main( int argc, char* argv[] ) {
	
	cNormal Normal;
	Normal.a = 0x76543210;
	Normal.b = 0xFEDCBA98;
	char* pNormal = (char*)&Normal;
	cout << "Normal.a (int) = " << Normal.a << std::hex << " (0x" << Normal.a << ")" << endl;
	cout << "Normal.b (int) = " << Normal.b << std::hex << " (0x" << Normal.b << ")" << endl;
	cout << "Normal[0..3] = \"" <<
		pNormal[0] << "\" \"" <<
		pNormal[1] << "\" \"" <<
		pNormal[2] << "\" \"" <<
		pNormal[3] << "\"" <<
		endl;
	cout << endl;

	cOverlap Overlap;
	Overlap.a = 0x6543210;
	Overlap.b = 0xDCBA987;
	Overlap.c = 0xFE;
	char* pOverlap = (char*)&Overlap;
	cout << "Overlap.a (int:24) = " << Overlap.a << std::hex << " (0x" << Overlap.a << ")" << endl;
	cout << "Overlap.b (int:24) = " << Overlap.b << std::hex << " (0x" << Overlap.b << ")" << endl;
	cout << "Overlap.c (int:8)  = " << Overlap.c << std::hex << " (0x" << Overlap.c << ")" << endl;
	cout << "Overlap[0..3] = \"" <<
		pOverlap[0] << "\" \"" <<
		pOverlap[1] << "\" \"" <<
		pOverlap[2] << "\" \"" <<
		pOverlap[3] << "\"" <<
		endl;
	cout << endl;

	cExplicit Exp;
	Exp.a = 0x76543210;
	Exp.b = 0xFEDCBA98;
	char* pExp = (char*)&Exp;
	cout << "Exp.a (int:32) = " << Exp.a << std::hex << " (0x" << Exp.a << ")" << endl;
	cout << "Exp.b (int:32) = " << Exp.b << std::hex << " (0x" << Exp.b << ")" << endl;
	cout << "Exp[0..3] = \"" <<
		pExp[0] << "\" \"" <<
		pExp[1] << "\" \"" <<
		pExp[2] << "\" \"" <<
		pExp[3] << "\"" <<
		endl;
	cout << endl;
	
	return 0;
}
