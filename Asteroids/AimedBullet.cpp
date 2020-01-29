#include "AimedBullet.h"

AimedBullet::AimedBullet(GameObject* aim, Point currentSpeed, Point position)
	: Bullet(currentSpeed, position)
{
	this->aim = aim;
}

AimedBullet::~AimedBullet()
{
}

void AimedBullet::move(float dt)
{
	currentSpeed = aim->position.subs(this->position).getNormalize().mult(speed);
	position.x += currentSpeed.x * dt;
	position.y += currentSpeed.y * dt;
	relativePosition.x += currentSpeed.x * dt;
	relativePosition.y += currentSpeed.y * dt;
}
