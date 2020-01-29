#include "Cursor.h"

Cursor::Cursor()
{
	sprite = createSprite("data/reticle.png");
}
Cursor::~Cursor()
{
	delete sprite;
}

void Cursor::moveCursor(Point position)
{
	this->position = position;
}

void Cursor::update(float dt)
{
	drawSprite(sprite, position.x, position.y);
}