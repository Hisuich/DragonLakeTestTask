#pragma once

#include "GameObject.h"

class Shield : public GameObject
{
private:
	GameObject* protectedObject;

public:
	Shield(GameObject* protectedObject);
	virtual ~Shield();

	void destroy() override;
	void move(float dt) override;
	void update(float dt) override;
	void collision(GameObject* object) override;
};
