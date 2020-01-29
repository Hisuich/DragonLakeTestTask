#pragma once

#include <global.h>
#include <GameObject.h>

class Bullet : public GameObject
{
public:
	Bullet(Point currentSpeed, Point position);
	virtual ~Bullet();

	virtual void destroy() override;
	virtual void move(float dt) override;
	virtual void update(float dt) override;
	virtual void collision(GameObject* object) override;
};