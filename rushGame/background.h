#pragma once

#include <vector>
#include <SFML/Graphics.hpp>

class Background
{
private:
	std::vector<sf::Sprite> sprites;
public:
	float speed = 0.1f;

public:
	Background() = default;
	~Background() = default;

	void addSprite(sf::Sprite newSprite)
	{
		if (sprites.size() != 0)
		{
			newSprite.setPosition(sprites[sprites.size() - 1].getPosition().x + sprites[sprites.size() - 1].getTexture()->getSize().x - 20,
				sprites[sprites.size() - 1].getPosition().y);
		}
		sprites.emplace_back(newSprite);
	}

	void draw(sf::RenderWindow& window)
	{
		for (unsigned int spriteID = 0; spriteID < sprites.size(); spriteID++)
		{
			sf::Sprite& sprite = sprites[spriteID];

			sprite.setPosition(sprite.getPosition().x - speed, sprite.getPosition().y);
			if (sprite.getPosition().x + sprite.getTexture()->getSize().x < 0)
			{
				unsigned int prevID;
				if (spriteID == 0)
					prevID = sprites.size() - 1;
				else
					prevID = spriteID - 1;

				if (prevID < sprites.size())
				{
					sprite.setPosition(sprites[prevID].getPosition().x + sprites[prevID].getTexture()->getSize().x - 20,
						sprites[prevID].getPosition().y);
				}
			}

			window.draw(sprite);
		}
	}
};