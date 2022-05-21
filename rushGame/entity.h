#pragma once

#include <SFML/Graphics.hpp>
#include "physics.h"

namespace sf
{
	class RenderWindow;
	class Time;
};

class Entity
{
protected:
	sf::Sprite sprite;
	bool isOnGround = false;

public:
	Physics physics;
	vector2D size{ 100, 100 };

public:
	Entity() = default;
	virtual ~Entity() = default;

	void setSprite(const sf::Texture& texture)
	{
		sprite = sf::Sprite(texture);

		const sf::Vector2u& texSize = texture.getSize();
		physics.location.x = 0;
		physics.location.y = size.y;

		sprite.setScale(size.x / float(texSize.y), size.y / float(texSize.y));
	}

	void draw(sf::RenderWindow& window)
	{
		sprite.setPosition(physics.location.x, physics.location.y);
		window.draw(sprite);
	}

	bool isColliding(const Entity& entity)
	{
		return physics.location.x < entity.physics.location.x + entity.size.x
			&& entity.physics.location.x < physics.location.x + size.x
			&& physics.location.y < entity.physics.location.y + entity.size.y
			&& entity.physics.location.y < physics.location.y + size.y;
	}

	virtual void ticks(const sf::Time& deltaTime)
	{
		physics.ticks(deltaTime);

		// check bottom collision
		const float border = WINDOW_SIZE_Y - size.y;
		if (physics.location.y > border)
		{
			physics.location.y = border;
			physics.velocity.y = 0;
			isOnGround = true;
		}
	}
};