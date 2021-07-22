#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int screenWidth, int ScreenHeight, bool fullscreen);

	void handleEvents();
	void update();
	bool running() { return isRunning; }
	void render();
	void clean();

	static SDL_Renderer* renderer;

	int screenWidth = 1000;
	int screenHeight = 800;

	

	int x_pos = screenWidth / 2 - 16;
	int y_pos = screenHeight / 2 - 16;


private:
	bool isRunning = false;
	int cnt = 0;
	SDL_Window* window;
};