#ifndef _PROJECTILE_H_
#define _PROJECTILE_H_

#include "entity.h"

class Projectile : public Entity
{
private:

public:
	float speed = -500.f;
	int scoreAdded = -1;

	Projectile()
	{

	}

	~Projectile() = default;

	void ticks(const sf::Time& deltaTime) override 
	{
		Entity::ticks(deltaTime);

		const sf::Vector2u& textureSize = sprite.getTexture()->getSize();

		size = vector2D(50.f, 50.f * float(textureSize.y) / float(textureSize.x));

		sprite.setScale(size.x / float(textureSize.x), size.y / float(textureSize.y));

		//physics.velocity.x = speed * deltaTime.asSeconds();
		//physics.location.x += physics.velocity.x;
	}
};

#endif