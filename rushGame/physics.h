#pragma once

#include "vector2D.h"
#include "macros.h"

struct Physics
{
	vector2D location {0, 0};
	vector2D velocity {0, 0};
	vector2D acceleration {0, 0};

	void ticks(const sf::Time& deltaTime)
	{
		acceleration.y = gravityPower;

		velocity += acceleration * deltaTime.asSeconds();

		location += velocity * deltaTime.asSeconds();
	}
};

