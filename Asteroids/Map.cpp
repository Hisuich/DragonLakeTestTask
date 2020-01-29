#include <Map.h>

Map::Map(int width, int height)
{
	background = createSprite("data/background.png");
	getSpriteSize(background, spriteW, spriteH);
	this->width = width;
	this->height = height;
	col = ceil((float)width / spriteW);
	row = ceil((float)height / spriteH);
	playerTreshold.x = width / 2;
	playerTreshold.y = height / 2;

	int scrWidth;
	int scrHeight;
	getScreenSize(scrWidth, scrHeight);
	mapTreshold = Point((this->width - scrWidth) / 2, (this->height - scrHeight) / 2);
	mapOffset = mapOffset.subs(mapTreshold);



	global = global::getInstance();
}

Map::~Map()
{
	destroySprite(background);
}

void Map::update(float dt)
{
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
		{
			int x = ((spriteW * j) + mapOffset.x);
			int y = ((spriteH * i) + mapOffset.y);
			drawSprite(background, x, y);
		}
	checkColision();
	if (global->asteroidCount < global->asteroidSpawn/3)
		spawnAsteroids();
	
	while (global->bullets.size() > global->maxBullet)
	{
		global->bullets.front()->needDestroy = true;
		global->bullets.pop();
	}
	moveAround(player);
}

void Map::moveAround(GameObject* object)
{
	Point centerObjPos = Point(object->position.x + object->width / 2, object->position.y + object->height / 2);

	int scrWidth;
	int scrHeight;
	getScreenSize(scrWidth, scrHeight);

	for (auto _object : global->gameObjects)
	{
		_object->relativePosition.x = _object->position.x + mapOffset.x;
		_object->relativePosition.y = _object->position.y + mapOffset.y;
	}

	mapOffset.x = -(object->position.x - scrWidth/2);

	if (mapOffset.x > 0) mapOffset.x = 0;
	if (mapOffset.x < -mapTreshold.x * 2) mapOffset.x = -mapTreshold.x * 2;

	mapOffset.y = -(object->position.y - scrHeight/2);

	if (mapOffset.y > 0) mapOffset.y = 0;
	if (mapOffset.y < -mapTreshold.y * 2) mapOffset.y = -mapTreshold.y * 2;
}

void Map::checkColision()
{ 	

		for (auto object : global->gameObjects)
	{
		checkMapOutCollision(object);
		for (auto _object : global->gameObjects)
		{
			if (object == _object)
				continue;

			if (checkObjectsCollision(object, _object))
			{
				(object)->collision(_object);
				
			}
		}
	}
	
}

void Map::checkMapOutCollision(GameObject* object)
{
	
	if (object->position.x < 0)
		object->position.x += width - object->width;
	if (object->position.y < 0)
		object->position.y += height - object->height;
	if (object->position.x + object->width > width)
		object->position.x = fmod(object->position.x,width);
	if (object->position.y + object->height > height)
		object->position.y = fmod(object->position.y,height);;

}

bool Map::checkObjectsCollision(GameObject* object, GameObject* _object)
{
	Point centerObjectPosition = Point(object->position.x + object->width / 2, object->position.y + object->height / 2);
	Point center_ObjectPosition = Point(_object->position.x + _object->width / 2, _object->position.y + _object->height / 2);

	Point distance = centerObjectPosition.subs(center_ObjectPosition);

	Point fullDistance = Point(((object)->width + (_object)->width) / 2, ((object)->height + (_object)->height) / 2);
	
	Point fdistance = Point(fmodf(distance.x, width - object->width / 2 - _object->width / 2), fmodf(distance.y, height - object->height / 2 - _object->height / 2));

	if (fabs(fdistance.x) < fullDistance.x && fabs(fdistance.y) < fullDistance.y)
	{
		return true;
	}

	return false;
}

void Map::spawnAsteroids()
{
	for (int i = 0; i < global->asteroidSpawn; i++)
	{
		Point position = getAsteroidPosition();

		Point direction = Point(position.x - player->position.x, position.y - player->position.y).getNormalize();
		direction = direction.div(1);

		Asteroid* asteroid = new Asteroid((rand() % 2), position, direction);
		
		for (auto object : global->gameObjects)
		{
			while (object->type == objectType::asteroid && checkObjectsCollision(asteroid, object))
				asteroid->position = getAsteroidPosition();
		}

		global->gameObjects.push_back(asteroid);
	}
}

Point Map::getAsteroidPosition()
{
	Point position = Point(rand() % width + playerTreshold.x + player->position.x, rand() % height + playerTreshold.y + player->position.y);

	return position;
}