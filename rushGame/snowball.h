#pragma once

#include "projectile.h"

class Snowball : public Projectile
{
private:

public:

	Snowball()
	{

	}

	void ticks(const sf::Time& deltaTime) override
	{
		Projectile::ticks(deltaTime);

		//const sf::Vector2u& textureSize = sprite.getTexture()->getSize();

		//size = vector2D(50.f, 50.f * float(textureSize.y) / float(textureSize.x));

		//sprite.setScale(size.x / float(textureSize.x), size.y / float(textureSize.y));
		//sprite.setRotation(sprite.getRotation() + 1 * deltaTime.asSeconds());

		////physics.velocity.x = speed * deltaTime.asSeconds();
		//physics.location.x += physics.velocity.x;
	}
};