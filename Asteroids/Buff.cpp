#include "Buff.h"

Buff::Buff(Point position, buffType bType)
{
	this->position = position;
	this->relativePosition = position;

	this->bType = bType;
	if (bType == buffType::shield) this->sprite = createSprite("data/shield_icon.png");
	else if (bType == buffType::autoshoot) this->sprite = createSprite("data/autoshoot_icon.png");
	else 
		this->sprite = createSprite("data/aim_icon.png");
	getSpriteSize(sprite, width, height);
	this->id = global->buffId++;
	this->type = objectType::buff;
	inSpace = true;
}

Buff::Buff(Point position) : Buff(position, buffType((rand() % 3) + 1))
{
}

Buff::Buff(buffType bType) : Buff(Point(-1000, -1000), bType)
{
}

Buff::~Buff()
{
}

void Buff::destroy()
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

void Buff::move(float dt)
{

}

void Buff::update(float dt)
{
	if (inSpace)
		TimeToDestroy += dt;
	if (TimeToDestroy >= 250)
		this->needDestroy = true;

	drawSprite(sprite, this->relativePosition.x, this->relativePosition.y);
	move(dt);

	if (isBuffActive) buffTime += dt;
	if (buffTime >= 100)
	{
		isBuffActive = false;
		bType = buffType::none;
	}
}

void Buff::collision(GameObject* object)
{
	if (object->type == objectType::player)
	{
		inSpace = false;
		this->position.x = -1000;
		this->position.y = -1000;
		this->relativePosition = this->position;
	}
}