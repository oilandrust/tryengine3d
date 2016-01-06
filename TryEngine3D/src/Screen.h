#ifndef SCREEN_H_INCLUDED
#define SCREEN_H_INCLUDED

#include <SDL.h>

class Screen{
	public:
		static float width;
		static float height;
		static SDL_Window* windowHandle;

		Screen();
		~Screen();
};

#endif
