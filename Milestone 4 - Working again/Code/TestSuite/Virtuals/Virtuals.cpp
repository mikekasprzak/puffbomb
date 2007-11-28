
#include <stdio.h>


class Bole {
public:
	int Cat;
	int Dog;

	virtual void Yuke() {
	}

	virtual void pyuke() {
	}
};

class Yole: public Bole {
public:
	int Carp;
	int Parp;

	virtual void pyuke() {
		printf("aotnshu\n");
	}

};

class Robe {
public:
	int tim;
	
	//virtual void Mute() {}
	
};


int main( int argc, char* argv[] ) {

	int Cam;
	Bole b;
	Yole t;
	int Sam;
	Robe c;
	
	printf("Bole %i\n", sizeof( b ) );
	printf("Yole %i\n", sizeof( t ) );
	printf("Robe %i\n", sizeof( c ) );
}
