#pragma once
#include "global.h"
#include "GameObject.h"
#include "Player.h"
#include "Asteroid.h"
#include <math.h>
#include <vector>

class Map
{
private:
	int spriteW;
	int spriteH;

	int row;
	int col;

public:
	int width;
	int height;

	Point mapOffset;
	Point mapTreshold;
	Point playerTreshold;

	Player* player;
	Sprite* background;
	global* global;

public:
	Map(int width, int height);
	~Map();

	void update(float dt);
	void checkColision();
	void checkMapOutCollision(GameObject* object);
	void spawnAsteroids();
	void moveAround(GameObject* object);
	
	bool checkObjectsCollision(GameObject* object, GameObject* _object);

private:
	Point getAsteroidPosition();
};