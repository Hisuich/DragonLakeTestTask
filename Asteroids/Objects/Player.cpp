#include <Player.h>

Player::Player()
	: GameObject()
{
	sprite = createSprite("data/spaceship.png");
	position.x = 320;
	position.y = 100;
	maxSpeed = 0.3 * speed;
	acceleration.x = 0;
	acceleration.y = 0;
	getSpriteSize(sprite, width, height);
	type = objectType::player;
	needDestroy = false;

	shield = new Shield(this);
	buff = new Buff(buffType::none);
}

Player::~Player()
{
	delete shield;
	delete buff;
}

void Player::keyPressed(FRKey k)
{
	switch (k)
	{
	case FRKey::LEFT:
		currentSpeed.x = -maxSpeed;
		acceleration.x = 0;
		break;
	case FRKey::RIGHT:
		currentSpeed.x = maxSpeed;
		acceleration.x = 0;
		break;
	case FRKey::UP:
		currentSpeed.y = -maxSpeed;
		acceleration.y = 0;
		break;
	case FRKey::DOWN:
		currentSpeed.y = maxSpeed;
		acceleration.y = 0;
		break;
	default:
		break;
	}
}
void Player::keyReleased(FRKey k)
{
	switch (k)
	{
	case FRKey::LEFT:
		acceleration.x = 0.003;
		break;
	case FRKey::RIGHT:
		acceleration.x = -0.003;
		break;
	case FRKey::UP:
		acceleration.y = 0.003;
		break;
	case FRKey::DOWN:
		acceleration.y = -0.003;
		break;
	default:
		break;
	}
}

void Player::shoot(Point destination)
{
	if (canShoot)
	{
		Point direction = destination.subs(this->relativePosition).getNormalize();
		Point curSpeed = direction.mult(speed);
		Point bPosition = Point(position.x + width * direction.x, position.y + height * direction.y);

		Bullet* bullet = new Bullet(curSpeed, bPosition);

		if (buff->isBuffActive && buff->bType == buffType::aim && aim)
		{
			for (auto object : global->gameObjects)
				if (destination.x < object->relativePosition.x + object->width &&
					destination.x > object->relativePosition.x &&
					destination.y < object->relativePosition.y + object->height &&
					destination.y > object->relativePosition.y)
				{
					bullet = new AimedBullet(object, curSpeed, bPosition);
					aim = false;
					break;
				}
		}

		global->gameObjects.push_back(bullet);
		global->bullets.push(bullet);
		canShoot = false;
	}
}

void Player::mouseClick(FRMouseButton mb, bool isReleased)
{
	if (mb == FRMouseButton::LEFT && !isReleased)
	{
		canShoot = true;
	}
	if (mb == FRMouseButton::RIGHT && !isReleased && buff->bType != buffType::none)
	{
		buff->isBuffActive = true;
	}
	if (mb == FRMouseButton::RIGHT && !isReleased && buff->bType == buffType::aim)
	{
		canShoot = true;
		aim = true;
	}

}

void Player::destroy()
{
	delete this;
}

void Player::move(float dt)
{
	currentSpeed.x += fabs(currentSpeed.x) <= maxSpeed  ? acceleration.x * fabs(currentSpeed.x) : 0;
	currentSpeed.y += fabs(currentSpeed.y) <= maxSpeed ? acceleration.y * fabs(currentSpeed.y) : 0;
	position.x += currentSpeed.x * dt;
	position.y += currentSpeed.y * dt;
	relativePosition.x += currentSpeed.x * dt;
	relativePosition.y += currentSpeed.y * dt;
}

void Player::update(float dt)
{
	buff->update(dt);

	if (buff->isBuffActive && buff->bType == buffType::shield)
		shield->update(dt);

	if (buff->isBuffActive && buff->bType == buffType::autoshoot)
	{
		autoshootTimer += dt;
		if (autoshootTimer >= 10)
		{
			autoshootTimer -= 10;
			for (auto object : global->gameObjects)
			{
				float distance = object->position.subs(position).getSqrMagnitude();
				if (distance < 250000 && object->type == objectType::asteroid)
				{
					canShoot = true;
					shoot(object->relativePosition);
					break;
				}
			}

		}
	}
	drawSprite(sprite, relativePosition.x, relativePosition.y);
	move(dt);
}

void Player::collision(GameObject* object)
{
	if (object->type == objectType::asteroid)
	{
		if (buff->bType == buffType::shield && buff->isBuffActive)
		{
			shield->collision(object);
			object->collision(shield);
		}
		else needDestroy = true;
	}

	if (object->type == objectType::buff)
	{
		this->buff->needDestroy = true;
		this->buff = ((Buff*)object);
	}
}
