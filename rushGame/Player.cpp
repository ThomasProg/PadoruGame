#include <SFML/Graphics.hpp>

#include "Player.h"

unsigned int nbPlayers = 3;

unsigned int Player::playerID = 0;

Player::Player(std::vector<sf::Texture>& textures, const sf::Font& font)
{
	// INGAME SCORE

	// select the font
	scoreText.setFont(font); // font is a sf::Font
	// set the string to display
	scoreText.setString("0");
	// set the character size
	scoreText.setCharacterSize(40); // in pixels, not points!
	// set the color
	scoreText.setFillColor(sf::Color::Red);
	// set the text style
	scoreText.setStyle(sf::Text::Bold);


	// END SCORE

	// select the font
	finalScore.setFont(font); // font is a sf::Font
	// set the string to display
	finalScore.setString("");
	// set the character size
	finalScore.setCharacterSize(60); // in pixels, not points!
	// set the color
	finalScore.setFillColor(sf::Color::White);
	// set the text style
	finalScore.setStyle(sf::Text::Bold);

	// SET INPUTS

	switch (Player::playerID)
	{
	case 0 :
		defaultTextureIndex = 0;
		setSprite(textures[0]);
		_inputs = S_Inputs{ sf::Keyboard::Up, sf::Keyboard::Left, sf::Keyboard::Down, sf::Keyboard::Right};
		break;
	case 1:
		defaultTextureIndex = 19;
		setSprite(textures[19]);
		_inputs = S_Inputs{ sf::Keyboard::Z, sf::Keyboard::Q, sf::Keyboard::S, sf::Keyboard::D };
		break;
	case 2:
		defaultTextureIndex = 23;
		setSprite(textures[23]);
		_inputs = S_Inputs{ sf::Keyboard::Numpad8, sf::Keyboard::Numpad4, sf::Keyboard::Numpad5, sf::Keyboard::Numpad6 };
		break;
	case 3:
		defaultTextureIndex = 27;
		setSprite(textures[27]);
		_inputs = S_Inputs{ sf::Keyboard::I, sf::Keyboard::J, sf::Keyboard::K, sf::Keyboard::L };
		break;
	case 4:
		defaultTextureIndex = 31;
		setSprite(textures[31]);
		_inputs = S_Inputs{ sf::Keyboard::G, sf::Keyboard::H, sf::Keyboard::B, sf::Keyboard::N };
		break;

	default:
		break;
	}

	scoreText.setPosition(Player::playerID * 200 + 25, 0);

	Player::playerID++;
}


Player::~Player()
{
}

void Player::inputs(const sf::Time& deltaTime)
{
	if (sf::Keyboard::isKeyPressed(this->_inputs.right))
	{
		physics.location.x += speed * deltaTime.asSeconds();
	}

	if (sf::Keyboard::isKeyPressed(this->_inputs.left))
	{
		physics.location.x -= speed * deltaTime.asSeconds();
	}

	if (isOnGround)
	{
		if (sf::Keyboard::isKeyPressed(this->_inputs.up))
		{
			physics.velocity.y = - jumpSpeed;
			isOnGround = false;
		}
	}
	else
	{
		if (sf::Keyboard::isKeyPressed(this->_inputs.down))
		{
			physics.location.y += speed / 2.f * deltaTime.asSeconds();
			if (physics.velocity.y < 0)
				physics.velocity.y = 0;
		}
	}
}

void Player::ticks(const sf::Time& deltaTime)
{
	Entity::ticks(deltaTime);

	// on hit animation 
	cumTimeToNextTexture += deltaTime.asSeconds();
	if (nextTextures.size() != 0)
	{
		if (cumTimeToNextTexture > delay)
		{
			sprite.setTexture((*nextTextures.front()));
			nextTextures.pop();
			cumTimeToNextTexture = 0.f;
		}
	}	
	else
	{
		cumTimeToNextTexture = delay;
	}

	// border teleportation
	if (physics.location.x + size.x> WINDOW_SIZE_X)
		physics.location.x = 0;
	if (physics.location.x < 0)
		physics.location.x = 0;
		// physics.location.x = WINDOW_SIZE_X - size.x;
}