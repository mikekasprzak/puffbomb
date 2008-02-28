
#include <SDL/SDL.h>

extern int GetTime();
int GetTime() {
	return SDL_GetTicks();
}
