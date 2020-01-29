#pragma once

#include <Framework.h>
#include <Point.h>
#include <global.h>

#include <string>

enum class objectType {
	player,
	bullet,
	asteroid,
	shield, 
	buff
};

class  GameObject {
protected:
	Sprite* sprite;

public:
	int width;
	int height;
	int id;

	int speed;
	
	bool needDestroy;

	Point currentSpeed;
	Point position;
	Point relativePosition;
	
	objectType type;
	global* global;

public:
	GameObject();
	virtual ~GameObject();

	virtual void move(float dt) = 0;
	virtual void update(float dt) = 0;
	virtual void collision(GameObject* object) = 0;
	virtual void destroy() = 0;
	
};