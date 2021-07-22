#include "GameObject.h"
#include "TextureManager.h"



GameObject::GameObject(const char* texturesheet, int x, int y)
{
	objTexture = TextureManager::LoadTexture(texturesheet);

	x_pos = x;
	y_pos = y;
}

void GameObject::Update(int x_pos, int y_pos, int screenWidth, int screenHeight, const char* object, bool fired, bool hit)
{
	//Standard object will be initialised with these attributes
	srcRect.h = 32;
	srcRect.w = 32;
	srcRect.x = 0;
	srcRect.y = 0;

	//Specific objects are then changed to have custom attributes
	if (object == "projectile")
	{
		srcRect.h = 4;
		srcRect.w = 4;
	}

	if (object == "player")
	{
		srcRect.h = 24;
		srcRect.w = 24;
	}

	if ((object == "mediumAsteroid") || (object == "mediumAsteroid_var2"))
	{
		srcRect.h = 28;
		srcRect.w = 28;
	}

	if ((object == "smallAsteroid") || (object == "smallAsteroid_var2"))
	{
		srcRect.h = 12;
		srcRect.w = 12;
	}


	destRect.x = x_pos;
	destRect.y = y_pos;
	destRect.w = srcRect.w * 2;
	destRect.h = srcRect.h * 2;

	std::cout << destRect.x << ", " << destRect.y << std::endl;



	if (destRect.x < (screenWidth - screenWidth - 5))
	{
		destRect.x = screenWidth - screenWidth - 5;
	}

	if (destRect.x > (screenWidth - (srcRect.w * 2)))
	{
		destRect.x = screenWidth - (srcRect.w * 2);
	}

	if (destRect.y < (screenHeight - screenHeight - 5))
	{
		destRect.y = screenHeight - screenHeight - 5;
	}

	if (destRect.y > (screenHeight - (srcRect.h * 2)))
	{
		destRect.y = screenHeight - (srcRect.h * 2);
	}
}


void GameObject::Render()
{
	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}

GameObject::~GameObject()
{

}