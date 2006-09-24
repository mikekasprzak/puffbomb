
// This is a test program to determine the function of endianness combined with bitfields on //
// various compilers.  Obviously, it's unfinished, but I'll likely want to finish it one day, //
// especially when I get my grubby hands on a kit. //

#include <iostream>
using namespace std;

typedef long long int s64;
//typedef __int64 s64;

class cNormal {
public:
	int a;
	int b;
};

class cOverlap {
public:
	s64 a:28;
	s64 b:28;
	s64 c:8;
};


class cExplicit {
public:
	s64 a:32;
	s64 b:32;
};


int main( int argc, char* argv[] ) {
	
	cNormal Normal;
	Normal.a = 0x76543210;
	Normal.b = 0xFEDCBA98;
	unsigned char* pNormal = (unsigned char*)&Normal;
	cout << "Normal.a (int) = " << std::dec << Normal.a << std::hex << " (0x" << Normal.a << ")" << endl;
	cout << "Normal.b (int) = " << std::dec << Normal.b << std::hex << " (0x" << Normal.b << ")" << endl;
	cout << "Normal[0..7] = 0x" << std::hex <<
		(unsigned int)pNormal[0] << " " <<
		(unsigned int)pNormal[1] << " " <<
		(unsigned int)pNormal[2] << " " <<
		(unsigned int)pNormal[3] << "-" <<
		(unsigned int)pNormal[4] << " " <<
		(unsigned int)pNormal[5] << " " <<
		(unsigned int)pNormal[6] << " " <<
		(unsigned int)pNormal[7] << "" <<
		endl;
	cout << endl;

	cOverlap Overlap;
	Overlap.a = 0x6543210;
	Overlap.b = 0xDCBA987;
	Overlap.c = 0xFE;
	unsigned char* pOverlap = (unsigned char*)&Overlap;
	cout << "Overlap.a (int:24) = " << std::dec << Overlap.a << std::hex << " (0x" << Overlap.a << ")" << endl;
	cout << "Overlap.b (int:24) = " << std::dec << Overlap.b << std::hex << " (0x" << Overlap.b << ")" << endl;
	cout << "Overlap.c (int:8)  = " << std::dec << Overlap.c << std::hex << " (0x" << Overlap.c << ")" << endl;
	cout << "Overlap[0..7] = 0x" << std::hex <<
		(unsigned int)pOverlap[0] << " " <<
		(unsigned int)pOverlap[1] << " " <<
		(unsigned int)pOverlap[2] << " " <<
		(unsigned int)pOverlap[3] << "-" <<
		(unsigned int)pOverlap[4] << " " <<
		(unsigned int)pOverlap[5] << " " <<
		(unsigned int)pOverlap[6] << " " <<
		(unsigned int)pOverlap[7] << "" <<
		endl;
	cout << endl;

	cExplicit Exp;
	Exp.a = 0x76543210;
	Exp.b = 0xFEDCBA98;
	unsigned char* pExp = (unsigned char*)&Exp;
	cout << "Exp.a (int:32) = " << std::dec << Exp.a << std::hex << " (0x" << Exp.a << ")" << endl;
	cout << "Exp.b (int:32) = " << std::dec << Exp.b << std::hex << " (0x" << Exp.b << ")" << endl;
	cout << "Exp[0..7] = 0x" << std::hex <<
		(unsigned int)pExp[0] << " " <<
		(unsigned int)pExp[1] << " " <<
		(unsigned int)pExp[2] << " " <<
		(unsigned int)pExp[3] << "-" <<
		(unsigned int)pExp[4] << " " <<
		(unsigned int)pExp[5] << " " <<
		(unsigned int)pExp[6] << " " <<
		(unsigned int)pExp[7] << "" <<
		endl;
	cout << endl;

	cout << std::hex <<
		(unsigned int)pNormal[0] << " " <<
		(unsigned int)pNormal[1] << " " <<
		(unsigned int)pNormal[2] << " " <<
		(unsigned int)pNormal[3] << "-" <<
		(unsigned int)pNormal[4] << " " <<
		(unsigned int)pNormal[5] << " " <<
		(unsigned int)pNormal[6] << " " <<
		(unsigned int)pNormal[7] << "" <<
		endl;
	cout << std::hex <<
		(unsigned int)pOverlap[0] << " " <<
		(unsigned int)pOverlap[1] << " " <<
		(unsigned int)pOverlap[2] << " " <<
		(unsigned int)pOverlap[3] << "-" <<
		(unsigned int)pOverlap[4] << " " <<
		(unsigned int)pOverlap[5] << " " <<
		(unsigned int)pOverlap[6] << " " <<
		(unsigned int)pOverlap[7] << "" <<
		endl;
	cout << std::hex <<
		(unsigned int)pExp[0] << " " <<
		(unsigned int)pExp[1] << " " <<
		(unsigned int)pExp[2] << " " <<
		(unsigned int)pExp[3] << "-" <<
		(unsigned int)pExp[4] << " " <<
		(unsigned int)pExp[5] << " " <<
		(unsigned int)pExp[6] << " " <<
		(unsigned int)pExp[7] << "" <<
		endl;
			
	return 0;
}
