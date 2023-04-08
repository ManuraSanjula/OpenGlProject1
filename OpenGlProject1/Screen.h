#pragma once
#include "Screen.h"
#include <SDL.h>

class Screen {
public:
	static Screen* Instance();
	bool Initialize();
	void ClearScreen();
	void Present();
	void Shutdown();
private:
	Screen();
	Screen(const Screen&);
	Screen& operator=(Screen&);
private:
	SDL_Window* window;
	SDL_GLContext context;
};


