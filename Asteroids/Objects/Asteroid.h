#pragma once
#include <global.h>
#include <GameObject.h>
#include <Buff.h>
#include <math.h>

class Asteroid : public GameObject
{
public:
	int size;
	Point maxSpeed;
	Point deceleration;
	Point minSpeed;

public:
	Asteroid(int size, Point position, Point maxSpeed);
	virtual ~Asteroid();

	void destroy() override;
	void move(float dt) override;
	void update(float dt) override;
	void collision(GameObject* object) override;
};