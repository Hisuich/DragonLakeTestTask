#include <global.h>

global* global::instance = nullptr;

global::global()
{
	asteroidSpawn = 7;
	maxBullet = 3;
	
	scrW = 800;
	scrH = 600;

	mapW = 1200;
	mapH = 1200;

	buffChance = 0.2;
}

global* global::getInstance()
{
	if (instance == nullptr)
	{
		instance =  new global();
	}
	return instance;
}

void global::reset()
{
	this->gameObjects.clear();
	std::queue<GameObject*> empty;
	std::swap(this->bullets, empty);

	asteroidCount = 0;

	bulletId = 0;
	asteroidId = 0;
	buffId = 0;
}



