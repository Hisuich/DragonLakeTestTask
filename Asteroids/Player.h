#pragma once
#include "Framework.h"
#include "global.h"
#include "GameObject.h"
#include <math.h>
#include "Bullet.h"
#include "AimedBullet.h"
#include "Shield.h"
#include "Buff.h"

class Player : public GameObject
{
private:
	float autoshootTimer;

public:
	Point acceleration;
	float maxSpeed;
	float buffTime;

	bool canShoot;
	bool aim;

	Shield* shield;
	Buff* buff;	

public:
	Player();
	virtual ~Player();
	void shoot(Point destination);
	void mouseClick(FRMouseButton mb, bool isReleased);
	void keyPressed(FRKey k);
	void keyReleased(FRKey k);

	void destroy() override;
	void move(float dt) override;
	void update(float dt) override;
	void collision(GameObject* object) override;
};