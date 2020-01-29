#pragma once
#include <vector>
#include <queue>
class GameObject;
class Bullet;

class global
{
private:
	static global* instance;


private:
	global();

public:
	static global* getInstance();

	std::queue<GameObject*> bullets;
	std::vector<GameObject*> gameObjects;

	int asteroidCount;

	int bulletId;
	int asteroidId;
	int buffId;

	int scrW;
	int scrH;

	int mapW;
	int mapH;

	int asteroidSpawn;
	int maxBullet;

	float buffChance;
	
public:
	void reset();
};

