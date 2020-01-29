#include <Framework.h>
#include <Map.h>
#include <global.h>
#include <GameObject.h>
#include <Player.h>
#include <Asteroid.h>
#include <Cursor.h>
#include <iostream>
#include <string>

int w = 800;
int h = 600;
/* Test Framework realization */
class DragonLakeTestTask : public Framework {

public:
	Player* player;
	Map* map;
	Cursor* cursor;
	std::vector<GameObject*> gameObjects;
	global* global;
	float prevT, dt = 0;
	float fps = 60;

	virtual void PreInit(int& width, int& height, bool& fullscreen)
	{
		width = w;
		height = h;
		fullscreen = false;
	}

	virtual bool Init() {
		cursor = new Cursor();
		global = global::getInstance();
		global->reset();
		player = new Player();
		map = new Map(global->mapW, global->mapH);
		player->position = Point(global->mapW/2, global->mapH/2);
		map->player = player;
		global->gameObjects.push_back(player);
		gameObjects = global->gameObjects;
		showCursor(false);
		return true;
	}

	virtual void Close() {

	}

	virtual bool Tick() {
		if (player->needDestroy)
		{
			delete map;
			player->destroy();
			gameObjects.clear();
			Init();
		}
		dt = getTickCount() - prevT;
		dt /= fps;
		prevT = getTickCount();
		
		map->update(dt);
		
		gameObjects = global->gameObjects;
		for (auto object : gameObjects)
			object->update(dt);
		for (auto object : gameObjects)
			if (object->needDestroy && object->type != objectType::player) object->destroy();
		cursor->update(dt);
		return false;
	}

	virtual void onMouseMove(int x, int y, int xrelative, int yrelative) {
		
		player->shoot(Point(x,y));
		cursor->moveCursor(Point(x, y));
	}

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) {
		player->mouseClick(button, isReleased);
	}

	virtual void onKeyPressed(FRKey k) {
		player->keyPressed(k);
	}

	virtual void onKeyReleased(FRKey k) {
		player->keyReleased(k);
	}
	
	virtual const char* GetTitle() override
	{
		return "DragonLakeTestTask";
	}
};

std::vector<std::string> split(std::string str, char sym)
{
	std::vector<std::string> params;
	size_t cur, prev = 0;
	cur = str.find(sym);
	while (cur <= str.size())
	{
		params.push_back(str.substr(prev, cur - prev));
		prev = cur + 1;
		cur = str.find(sym, prev);
	}
	params.push_back(str.substr(prev, cur - prev));

	return params;
}

void setParams(std::string value, int& first, int& second)
{
	std::vector<int> params;
	try
	{
		std::vector<std::string> s = split(value, 'x');
		for (auto number : s)
			params.push_back(std::stoi(number));

		if (params.size() == 1) {
			first = params.at(0);
			second = params.at(0);
		}
		if (params.size() == 2) {
			first = params.at(0);
			second = params.at(1);
		}
	}
	catch (std::invalid_argument)
	{
		std::cout << "invalid_argument";
	}
}

void fsetParams(std::string value, float& first, float& second)
{
	std::vector<float> params;
	try
	{
		std::vector<std::string> s = split(value, 'x');
		for (auto number : s)
			params.push_back(std::stoi(number));

		if (params.size() == 1) {
			first = params.at(0);
			second = params.at(0);
		}
		if (params.size() == 2) {
			first = params.at(0);
			second = params.at(1);
		}
	}
	catch (std::invalid_argument)
	{
		std::cout << "invalid_argument";
	}
}

int main(int argc, char* argv[])
{
	global* global = global::getInstance();
	for (int i = 0; i != argc - 1; i++)
	{
		std::string option(argv[i]);
		if (option == "-window")
		{
			if (argv[i + 1][0] != '-')
			{
				setParams(argv[i + 1], w, h);
			}
		}
		if (option == "-map")
		{
			if (argv[i + 1][0] != '-')
			{
				setParams(argv[i + 1], global->mapW, global->mapH);
			}
		}
		if (option == "-num_asteroids")
		{
			if (argv[i + 1][0] != '-')
			{
				setParams(argv[i + 1], global->asteroidSpawn, global->asteroidSpawn);
			}
		}
		if (option == "-num_ammo")
		{
			if (argv[i + 1][0] != '-')
			{
				setParams(argv[i + 1], global->maxBullet, global->maxBullet);
			}
		}
		if (option == "-ability_probability")
		{
			if (argv[i + 1][0] != '-')
			{
				fsetParams(argv[i + 1], global->buffChance, global->buffChance);
			}
		}

	}
	return run(new DragonLakeTestTask);
}
