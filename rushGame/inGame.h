#pragma once

#include <memory>
#include <vector>
#include <random>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "macros.h"
#include "Player.h"
#include "projectile.h"
#include "background.h"

#include "context.h"

class InGame : public Context
{
private:
	Background background;

	//sf::Text scoreText;

	//Player player;

	std::vector<Player> players;

	//int score = 0;

	std::vector<sf::Texture>& textures;
	sf::Font& font;
	Context*& gameContext;

	sf::Music music;
	bool bStart = true;

	bool isToBeContinuedPlaying = false;
	sf::Music toBeContinuedTrack;
	sf::Sprite toBeContinuedSprite;

	sf::RectangleShape rectangleFondu{ sf::Vector2f(WINDOW_SIZE_X, WINDOW_SIZE_Y) };

	std::vector<std::unique_ptr<Projectile>> snowballs;
	float snowballDelta = 0.f;
	unsigned int nbPresentsSpawned = 0;
	unsigned int nbPresentsMax = 5;

public:
	float difficulty = 1.9f;

private:
	float speed;
	float snowballDefaultSpeed = 450.f;// 300; //5000
	float snowballAcceleration = 0; // 5
	float snowballMaxHeight = WINDOW_SIZE_Y / 4;//snowballDefaultSpeed;
	float backgroundSpeed = 0.1f;

	sf::Sprite truckKun;

public:
	InGame(std::vector<sf::Texture>& textures, sf::Font& font, Context*& gameContext);
	~InGame() = default;

	void ticks(float& totalTime, sf::Time& deltaTime, sf::RenderWindow& window) override;
	void draw(sf::RenderWindow& window) override;
	void inputs(float& totalTime, sf::Time& deltaTime) override;
};