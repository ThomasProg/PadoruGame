#include "inGame.h"

#include <random>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "present.h"

#include "macros.h"
#include "Player.h"
#include "projectile.h"
#include "background.h"
#include "menu.h"

#include "snowball.h"

void addSnowball(std::vector<std::unique_ptr<Projectile>>& snowballs, sf::Texture& texture, vector2D velocity, float snowballHeight, Projectile* newProjectile)
{
	snowballs.emplace_back(newProjectile);
	std::unique_ptr<Projectile>& snowball = snowballs[snowballs.size() - 1];
	snowball->physics.velocity = velocity;

	snowball->setSprite(texture);
	snowball->physics.location.x = WINDOW_SIZE_X;
	snowball->physics.location.y = WINDOW_SIZE_Y - 100 - snowballHeight;
}

InGame::InGame(std::vector<sf::Texture>& textures, sf::Font& font, Context*& gameContext)
	: textures(textures), font(font), gameContext(gameContext)
{
	background.addSprite(sf::Sprite(textures[7]));
	background.addSprite(sf::Sprite(textures[8]));
	background.addSprite(sf::Sprite(textures[9]));
	background.addSprite(sf::Sprite(textures[10]));
	background.addSprite(sf::Sprite(textures[11]));
	background.addSprite(sf::Sprite(textures[12]));
	background.addSprite(sf::Sprite(textures[13]));

	truckKun.setTexture(textures[16]);

	for (unsigned int i = 0; i < nbPlayers; ++i)
		players.emplace_back(Player(textures, font));

	for (Player& player : players)
	{
		player.physics.location.x = -player.size.x;
		player.physics.location.y = WINDOW_SIZE_Y - player.size.y;
	}

	background.speed = 0.f;

	rectangleFondu.setFillColor(sf::Color(0, 0, 0, 0));

	toBeContinuedSprite.setTexture(textures[18]);
	toBeContinuedSprite.setPosition(WINDOW_SIZE_X, WINDOW_SIZE_Y);

	const sf::Vector2u& texSize = truckKun.getTexture()->getSize();
	truckKun.setPosition(WINDOW_SIZE_X - texSize.x, WINDOW_SIZE_Y - texSize.y);

	if (!music.openFromFile("media/padoru.wav"))
		return; // error
	music.play();
	// music.setLoop(true);

	if (!toBeContinuedTrack.openFromFile("media/toBeContinued.wav"))
		return; // error
}

void InGame::ticks(float& totalTime, sf::Time& deltaTime, sf::RenderWindow& window)
{
	if (bStart)
	{
		totalTime = 0.f;
		bStart = false;
	}

	if (totalTime < 3)
	{
		for (Player& player : players)
		{
			player.physics.location.x = -player.size.x + totalTime * player.size.x;
			player.physics.location.y = WINDOW_SIZE_Y - player.size.y;
		}

		const sf::Vector2u& texSize = truckKun.getTexture()->getSize();
		truckKun.setPosition(WINDOW_SIZE_X - texSize.x + totalTime * texSize.x / 2, WINDOW_SIZE_Y - texSize.y);
	}

	if (totalTime > 3)
	{
		background.speed = backgroundSpeed * speed;

		speed = 1.f;
	}

	if (totalTime > 20)
		speed = 1.3f;

	if (totalTime > 32)
		speed = 1.7f;

	if (totalTime > 43)
		speed = 1.f;

	if (totalTime > 54)
		speed = 1.7f;

	if (totalTime > 64.5)
		speed = 1.f;

	if (totalTime > 75)
		speed = 1.7f;

	if (totalTime > 86)
		speed = 1.3f;

	if (totalTime > 91)
		speed = 2.1f;

	if (totalTime > 110)
		speed = 3.0f;

	if (totalTime > 125)
		speed = 2.0f;

	if (totalTime > 129)
		speed = 1.0f;

	if (totalTime > 139)
	{
		if (!isToBeContinuedPlaying)
		{
			toBeContinuedTrack.play();
			isToBeContinuedPlaying = true;
		}
		speed = 0.0f;
	}

	if (totalTime > 142.f && totalTime < 142.5f)
	{
		const sf::Vector2u& texSize = truckKun.getTexture()->getSize();
		truckKun.setPosition(-float(texSize.x) + totalTime * float(texSize.x), WINDOW_SIZE_Y - texSize.y);
	}

	if (totalTime > 142.25f)
	{
		const sf::Vector2u& texSizeContinued = toBeContinuedSprite.getTexture()->getSize();
		toBeContinuedSprite.setPosition(WINDOW_SIZE_X - texSizeContinued.x * (totalTime - 142.25) * 4 - 10, WINDOW_SIZE_Y - texSizeContinued.y - 10);
	}

	if (totalTime > 142.5f)
	{
		const sf::Vector2u& texSize = truckKun.getTexture()->getSize();
		truckKun.setPosition(-float(texSize.x) + float(texSize.x) / 2.f, WINDOW_SIZE_Y - texSize.y);

		const sf::Vector2u& texSizeContinued = toBeContinuedSprite.getTexture()->getSize();
		toBeContinuedSprite.setPosition(WINDOW_SIZE_X - texSizeContinued.x * 0.25 * 4 - 10, WINDOW_SIZE_Y - texSizeContinued.y - 10);
	}

	if (totalTime > 148 && totalTime < 150)
	{
		float opacity = 255.f * (1 - ((150.f - totalTime) / 2.f));
		if (opacity > 255)
			opacity = 255;

		rectangleFondu.setFillColor(sf::Color(0, 0, 0, opacity));
	}
	if (totalTime > 150)
		rectangleFondu.setFillColor(sf::Color(0, 0, 0, 255));

	if (totalTime > 151)
	{
		for (unsigned int i = 0; i < players.size(); ++i)
		{
			Player& player = players[i];
			const float ratio = (float(i) / (float(players.size() - 1))) * 2 - 1; // between -1 and 1
			//ratio = 0;
			player.finalScore.setString("Score : " + std::to_string(player.score));
			player.finalScore.setOrigin(player.finalScore.getGlobalBounds().width / 2, player.finalScore.getGlobalBounds().height / 2);
			player.finalScore.setPosition(WINDOW_SIZE_X / 2, WINDOW_SIZE_Y / 2 + ratio * 200);
		}
	}

	if (totalTime > 156)
	{
		gameContext = new Menu(textures, font, gameContext);
		delete this;
	}
	
	speed *= difficulty;

	totalTime += deltaTime.asSeconds();

	for (std::unique_ptr<Projectile>& snowball : snowballs)
	{
		snowball->ticks(deltaTime);

		snowball->physics.location.x -= background.speed;

		for (Player& player : players)
		{
			if (snowball->isColliding(player))
			{
				if (player.nextTextures.size() == 0)
				{
					player.nextTextures.push(&textures[player.defaultTextureIndex + 1]);
					player.nextTextures.push(&textures[player.defaultTextureIndex + 2]);
					player.nextTextures.push(&textures[player.defaultTextureIndex + 3]);
					player.nextTextures.push(&textures[player.defaultTextureIndex]);
					player.score += snowball->scoreAdded;
					player.scoreText.setString(std::to_string(player.score));
				}
				// window.close();
			}
		}
	}
}

void InGame::inputs(float& totalTime, sf::Time& deltaTime)
{
	// inputs
	if (totalTime > 3)
	{
		float snowballDelay = (3.f/* - totalTime * 0.1*/) / (speed);
		if (snowballDelay < minimalSnowballDelay)
			snowballDelay = minimalSnowballDelay;

		if (snowballDelta > snowballDelay)
		{
			float speedY = (-snowballDefaultSpeed - snowballAcceleration * totalTime) * (float(std::rand() % 10) / 10.f) * 1.3f;
			speedY += speedY / 4.f;
			if (nbPresentsSpawned >= nbPresentsMax || std::rand() % 10 > 0)
			{
				addSnowball(snowballs, textures[4], vector2D((-snowballDefaultSpeed - snowballAcceleration * totalTime),
					speedY),
					float(std::rand() % int(snowballMaxHeight)), new Snowball);
			}
			else
			{
				addSnowball(snowballs, textures[6], vector2D((-snowballDefaultSpeed - snowballAcceleration * totalTime),
					speedY),
					float(std::rand() % int(snowballMaxHeight)), new Present);

				nbPresentsSpawned++;
			}


			snowballDelta = 0.f;
		}
		snowballDelta += deltaTime.asSeconds();

		for (Player& player : players)
		{
			player.ticks(deltaTime);
			player.inputs(deltaTime);
		}
	}
}

void InGame::draw(sf::RenderWindow& window)
{
	background.draw(window);

	window.draw(truckKun);

	for (Player& player : players)
		player.draw(window);

	for (std::unique_ptr<Projectile>& snowball : snowballs)
	{
		snowball->draw(window);
	}

	for (Player& player : players)
		window.draw(player.scoreText);

	window.draw(rectangleFondu);

	window.draw(toBeContinuedSprite);

	for (Player& player : players)
		window.draw(player.finalScore);
}

