#pragma once

#include "GameObject.h"

enum class buffType
{
	none,
	shield,
	autoshoot,
	aim
};

class Buff : public GameObject
{
private:
	bool inSpace;
	float TimeToDestroy;

public:
	buffType bType;

	float buffTime;
	bool isBuffActive;

public:
	Buff(Point position, buffType bType);
	Buff(Point position);
	Buff(buffType bType);
	virtual ~Buff();

	void destroy() override;
	void move(float dt) override;
	void update(float dt) override;
	void collision(GameObject* object) override;
};