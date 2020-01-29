#pragma once


#include "Bullet.h"

class AimedBullet : public Bullet {
public:
	GameObject* aim;

public:
	AimedBullet(GameObject* aim, Point currentSpeed, Point position);
	virtual ~AimedBullet();

	void move(float dt) override;
};