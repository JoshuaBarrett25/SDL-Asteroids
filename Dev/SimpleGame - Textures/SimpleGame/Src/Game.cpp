#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"

#include "ECS.h"
#include "Components.h"

#include <map>

GameObject* player;
GameObject* largeAsteroid;
GameObject* mediumAsteroid;
GameObject* mediumAsteroid_var2;
GameObject* smallAsteroid;
GameObject* smallAsteroid_var2;
GameObject* projectile;

SDL_Renderer* Game::renderer = nullptr;

const Uint8* SDL_GetKeyboardState(int* numkeys);
const Uint8* state = SDL_GetKeyboardState(NULL);

bool fired;

Manager manager;
auto& newPlayer(manager.addEntity());

Game::Game()
{}

Game::~Game()
{}

void Game::init(const char* title, int screenWidth, int screenHeight, bool fullscreen)
{
	int flags = 0;


	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		}

		isRunning = true;
	}

	player = new GameObject("assets/ship.png", (screenWidth / 2), (screenHeight / 2));
	largeAsteroid = new GameObject("assets/largeAsteroid.png", 100, 100);
	mediumAsteroid = new GameObject("assets/mediumAsteroid.png", 200, 200);
	mediumAsteroid_var2 = new GameObject("assets/mediumAsteroid_var2.png", 300, 200);
	smallAsteroid = new GameObject("assets/smallAsteroid.png", 600, 600);
	smallAsteroid_var2 = new GameObject("assets/smallAsteroid_var2.png", 400, 400);
	projectile = new GameObject("assets/projectile.png", 500, 500);


	newPlayer.addComponent<PositionComponent>();
}

void Game::handleEvents()
{
	SDL_Event event;

	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT :
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game::update()
{
	SDL_PumpEvents();


	if ((state[SDL_SCANCODE_D]) || (state[SDL_SCANCODE_RIGHT]))
	{
		if (state[SDL_SCANCODE_LSHIFT])
		{
			player->Update(x_pos++, y_pos, screenWidth, screenHeight, "player", false);
		}
		player->Update(x_pos++, y_pos, screenWidth, screenHeight, "player", false);
	}

	if ((state[SDL_SCANCODE_A]) || (state[SDL_SCANCODE_LEFT]))
	{
		if (state[SDL_SCANCODE_LSHIFT])
		{
			player->Update(x_pos--, y_pos, screenWidth, screenHeight, "player", false);
		}
		player->Update(x_pos--, y_pos, screenWidth, screenHeight, "player", false);
	}

	if ((state[SDL_SCANCODE_W]) || (state[SDL_SCANCODE_UP]))
	{
		if (state[SDL_SCANCODE_LSHIFT])
		{
			player->Update(x_pos, y_pos--, screenWidth, screenHeight, "player", false);
		}
		player->Update(x_pos, y_pos--, screenWidth, screenHeight, "player", false);
	}

	if ((state[SDL_SCANCODE_S]) || (state[SDL_SCANCODE_DOWN]))
	{
		if (state[SDL_SCANCODE_LSHIFT])
		{
			player->Update(x_pos, y_pos++, screenWidth, screenHeight, "player", false);
		}
		player->Update(x_pos, y_pos++, screenWidth, screenHeight, "player", false);
	}

	if (state[SDL_SCANCODE_SPACE])
	{
		projectile->Update(player->destRect.x + (player->srcRect.w / 2 + 8), player->destRect.y, screenWidth, screenHeight, "projectile", false);
		fired = true;
	}

	if (fired == true)
	{
		projectile->Update(x_pos++, y++,)
	}

	if (x_pos < (screenWidth - screenWidth - 5))
	{
		x_pos = screenWidth - screenWidth - 5;
	}

	if (x_pos > (screenWidth - (player->srcRect.w * 2)))
	{
		x_pos = screenWidth - (player->srcRect.w * 2);
	}

	if (y_pos < (screenHeight - screenHeight - 5))
	{
		y_pos = screenHeight - screenHeight - 5;
	}

	if (y_pos > (screenHeight - (player->srcRect.h * 2)))
	{
		y_pos = screenHeight - (player->srcRect.h * 2);
	}


	largeAsteroid->Update(100, 100, screenWidth, screenHeight, "largeAsteroid", false);
	mediumAsteroid->Update(200, 200, screenWidth, screenHeight, "mediumAsteroid", false);
	mediumAsteroid_var2->Update(300, 200, screenWidth, screenHeight, "mediumAsteroid_var2", false);
	smallAsteroid->Update(600, 600, screenWidth, screenHeight, "smallAsteroid", false);
	smallAsteroid_var2->Update(700, 700, screenWidth, screenHeight, "smallAsteroid_var2", false);

	manager.update();
}

void Game::render()
{
	SDL_RenderClear(renderer);
	largeAsteroid->Render();
	mediumAsteroid->Render();
	mediumAsteroid_var2->Render();
	smallAsteroid->Render();
	smallAsteroid_var2->Render();
	projectile->Render();
	player->Render();
	SDL_RenderPresent(renderer);
}


void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}