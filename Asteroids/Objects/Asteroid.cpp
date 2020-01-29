#include <Asteroid.h>


Asteroid::Asteroid(int size, Point position, Point maxSpeed)
	:GameObject()
{
	if (size > 1)
		this->size = 1;
	else if (size < 0)
		this->size = 0;
	this->size = size;

	if (this->size == 1)
		sprite = createSprite("data/big_asteroid.png");
	else
		sprite = createSprite("data/small_asteroid.png");

	this->maxSpeed = maxSpeed.mult(speed);
	minSpeed.x = this->maxSpeed.x / 2;
	minSpeed.y = this->maxSpeed.y / 2;
	this->deceleration = this->maxSpeed.getNormalize().div(100);
	currentSpeed.x = this->maxSpeed.x;
	currentSpeed.y = this->maxSpeed.y;
	this->position.x = position.x;
	this->position.y = position.y;
	getSpriteSize(sprite, width, height);

	type = objectType::asteroid;
	id = global->asteroidId++;
	global->asteroidCount++;
	needDestroy = false;
}

Asteroid::~Asteroid()
{
}

void Asteroid::destroy()
{
	for (auto i = global->gameObjects.begin(); i != global->gameObjects.end(); i++)
	{
		if ((*i)->type == this->type && (*i)->id == this->id)
		{
			global->gameObjects.erase(i);
			global->asteroidCount--;
			if ((global->buffChance * 100) > (rand() % 100))
				global->gameObjects.push_back(new Buff(this->position));
			break;
		}
	}	

	if (size == 1)
	{
		global->gameObjects.push_back(new Asteroid(0, this->position, this->maxSpeed.getNormalize().mult(0.5)));
		global->gameObjects.push_back(new Asteroid(0, this->position, this->maxSpeed.getNormalize().mult(-0.5)));
	}

		delete this;

}

void Asteroid::move(float dt)
{
	currentSpeed.x = (fabs(currentSpeed.x) >= fabs(minSpeed.x) ? currentSpeed.x - deceleration.x * currentSpeed.x : minSpeed.x) * dt;
	currentSpeed.y = (fabs(currentSpeed.y) >= fabs(minSpeed.y) ? currentSpeed.y - deceleration.y * currentSpeed.y : minSpeed.y) * dt;
	currentSpeed.x = fabs(currentSpeed.x) > fabs(maxSpeed.x) ? maxSpeed.x : currentSpeed.x;
	currentSpeed.y = fabs(currentSpeed.y) > fabs(maxSpeed.y) ? maxSpeed.y : currentSpeed.y;
	position.x += currentSpeed.x;
	position.y += currentSpeed.y;
	relativePosition.x += currentSpeed.x;
	relativePosition.y += currentSpeed.y;
}

void Asteroid::update(float dt)
{
	drawSprite(sprite, relativePosition.x, relativePosition.y);
	move(dt);
}

void Asteroid::collision(GameObject* object)
{
	if (object->type == objectType::bullet)
	{
		needDestroy = true;
	}

	if (object->type == objectType::shield)
	{

		this->currentSpeed = this->currentSpeed.mult(-1);
		this->maxSpeed = this->maxSpeed.mult(-1);
		this->minSpeed = this->minSpeed.mult(-1);
		this->deceleration = this->deceleration.mult(-1);

		this->move(1);
	}

	if (object->type == objectType::asteroid)
	{
		Point tempCurSpeed = this->currentSpeed;
		Point tempMaxSpeed = this->maxSpeed;
		Point tempMinSpeed = this->minSpeed;
		Point tempDeceleraion = this->deceleration;

		this->currentSpeed = object->currentSpeed;
		this->maxSpeed = ((Asteroid*)object)->maxSpeed;
		this->minSpeed = ((Asteroid*)object)->minSpeed;
		this->deceleration = ((Asteroid*)object)->deceleration;

		((Asteroid*)object)->currentSpeed = tempCurSpeed;
		((Asteroid*)object)->maxSpeed = tempMaxSpeed;
		((Asteroid*)object)->minSpeed = tempMinSpeed;
		((Asteroid*)object)->deceleration = tempDeceleraion;
		
		this->move(0.1);
		object->move(0.1);
		
	}
}
