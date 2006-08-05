
#include <windows.h>

extern int GetTime();
int GetTime() {
	return timeGetTime();
}
