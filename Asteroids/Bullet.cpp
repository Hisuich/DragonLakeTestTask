#include "Bullet.h"

Bullet::Bullet(Point currentSpeed, Point position) 
	: GameObject()
{
	sprite = createSprite("data/bullet.png");
	this->currentSpeed = currentSpeed;
	this->position = position;
	getSpriteSize(sprite, width, height);
	type = objectType::bullet;
	needDestroy = false;
		
	id = global->bulletId++;
}

Bullet::~Bullet()
{
}

void Bullet::destroy()
{
	for (auto i = global->gameObjects.begin(); i != global->gameObjects.end(); i++)
	{
		if ((*i)->type == this->type && (*i)->id == this->id)
		{ 
			global->gameObjects.erase(i);
			break;
		}
	}
		delete this;
}

void Bullet::move(float dt)
{
	position.x += currentSpeed.x * dt;
	position.y += currentSpeed.y * dt;
	relativePosition.x += currentSpeed.x * dt;
	relativePosition.y += currentSpeed.y * dt;
}

void Bullet::update(float dt)
{
	drawSprite(sprite, relativePosition.x, relativePosition.y);

	move(dt);
}

void Bullet::collision(GameObject* object)
{
	if (object->type == objectType::asteroid)
	{
		needDestroy = true;
	}
	
}

