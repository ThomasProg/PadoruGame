#pragma once

#include <SFML/Graphics.hpp>
#include "vector2D.h"

struct Button
{
public:

	vector2D location{ 50, 50 };
	vector2D size{ 300, 100 };

	sf::Sprite sprite;

	void draw(sf::RenderWindow& window)
	{
		sprite.setPosition(location.x, location.y);
		const sf::Vector2u& texSize = sprite.getTexture()->getSize();
		sprite.setScale(size.x / texSize.x, size.y / texSize.y);
		window.draw(sprite);
	}

	bool isPressed(const vector2D& loc)
	{
		return loc.x > location.x && loc.y > location.y
			&& loc.x < location.x + size.x && loc.y < location.y + size.y;
	}
};