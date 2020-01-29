#include "Shield.h"

Shield::Shield(GameObject* protectedObject)
{
	this->protectedObject = protectedObject;
	this->sprite = createSprite("data/circle.tga");
	getSpriteSize(this->sprite, width, height);

	this->position.x = protectedObject->position.x - ((this->width + protectedObject->width) / 2);
	this->position.y = protectedObject->position.y - ((this->height + protectedObject->height) / 2);
	this->relativePosition = protectedObject->position;

	this->type = objectType::shield;
}

Shield::~Shield()
{
}

void Shield::destroy()
{
	
	delete this;
}

void Shield::move(float dt)
{
	this->position.x = protectedObject->position.x - ((this->width + protectedObject->width) / 2);
	this->position.y = protectedObject->position.y - ((this->height + protectedObject->height) / 2);
	this->relativePosition = protectedObject->relativePosition;
}

void Shield::update(float dt)
{
	drawSprite(this->sprite, this->relativePosition.x, this->relativePosition.y);
	move(dt);
}

void Shield::collision(GameObject* object)
{
	if (object->type == objectType::asteroid)
	{ 
	}
}