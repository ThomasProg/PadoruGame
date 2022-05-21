#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <queue>

#include <SFML/Graphics.hpp>

#include "vector2D.h"
#include "physics.h"

#include "entity.h"

extern unsigned int nbPlayers;

struct S_Inputs
{
public:
	sf::Keyboard::Key up, left, down, right;
};

class Player : public Entity
{
private:
	static constexpr float speed = 700.f;
	static constexpr float jumpSpeed = 400.f;

	static unsigned int playerID;

public:
	int score = 0;
	sf::Text scoreText;
	sf::Text finalScore;

	S_Inputs _inputs; 

public:
	unsigned int defaultTextureIndex = 0;
	std::queue<sf::Texture*> nextTextures;
	float delay = 0.2f;
	float cumTimeToNextTexture = 0.f;

public:
	Player(std::vector<sf::Texture>& textures, const sf::Font& font);
	~Player();

	void inputs(const sf::Time& deltaTime);

	void ticks(const sf::Time& deltaTime) override;
}; 

#endif