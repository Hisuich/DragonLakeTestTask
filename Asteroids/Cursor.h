#pragma once

#include <Point.h>
#include <Framework.h>

class Cursor
{
private:
	Sprite* sprite;
	Point position;

public:
	Cursor();
	~Cursor();
	void moveCursor(Point position);
	void update(float dt);
};