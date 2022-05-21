#include "menu.h"

#include "inGame.h"

Menu::Menu(std::vector<sf::Texture>& textures, sf::Font& font, Context*& gameContext)
	: textures(textures), font(font), gameContext(gameContext)
{
	background.setTexture(textures[14]);

	playButton.sprite.setTexture(textures[15]);
	playButtonHard.sprite.setTexture(textures[17]);
	playButtonHard.location = { 50, 200 };

	// select the font
	progzCopyright.setFont(font); // font is a sf::Font
	// set the string to display
	progzCopyright.setString("Game maker : Prog'z");
	// set the character size
	progzCopyright.setCharacterSize(20); // in pixels, not points!
	// set the color
	progzCopyright.setFillColor(sf::Color::White);
	// set the text style
	progzCopyright.setStyle(sf::Text::Bold);

	progzCopyright.setPosition(60, 10);
}

Menu::~Menu()
{

}

void Menu::ticks(float& totalTime, sf::Time& deltaTime, sf::RenderWindow& window)
{
	sf::Vector2i localPosition = sf::Mouse::getPosition(window);
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (playButton.isPressed(vector2D(localPosition.x, localPosition.y)))
		{
			InGame* game = new InGame(textures, font, gameContext);
			gameContext = game;
			game->difficulty = 1.f;
			delete this;
		}

		if (playButtonHard.isPressed(vector2D(localPosition.x, localPosition.y)))
		{
			InGame* game = new InGame(textures, font, gameContext);
			gameContext = game;
			game->difficulty = 1.9f;
			delete this;
		}
	}
}

void Menu::draw(sf::RenderWindow& window)
{
	window.draw(background);
	playButton.draw(window);
	playButtonHard.draw(window);
	window.draw(progzCopyright);
}

void Menu::inputs(float& totalTime, sf::Time& deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (!isRightPressed)
		{
			isRightPressed = true;
			nbPlayers++;
		}
	}
	else
		isRightPressed = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (!isLeftPressed)
		{
			isLeftPressed = true;
			nbPlayers--;
		}
	}
	else
		isLeftPressed = false;

	progzCopyright.setString("Game maker : Prog'z / score : " + std::to_string(nbPlayers));
}

