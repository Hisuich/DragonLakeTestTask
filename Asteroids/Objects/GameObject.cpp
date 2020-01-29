#include <GameObject.h>

GameObject::GameObject()
{
	speed = 20;
	global = global::getInstance();
}

GameObject::~GameObject()
{
		destroySprite(sprite);
}