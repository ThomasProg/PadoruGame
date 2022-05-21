#include <random>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "macros.h"
#include "Player.h"
#include "projectile.h"
#include "background.h"

#include "inGame.h"
#include "menu.h"

bool addBackgroundTexture(const std::string& filename, std::vector<sf::Texture>& textures)
{
	textures.emplace_back(sf::Texture());
	sf::Image curImage;
	if (!curImage.loadFromFile(filename))
		return false;
	else
	{
		constexpr unsigned int margin = 100;
		constexpr float transition = 2.5;
		for (unsigned int y = 0; y < curImage.getSize().y; y++)
		{
			for (unsigned int x = 0; x < margin; x++)
			{
				sf::Color color = curImage.getPixel(x, y);
				unsigned int delta = static_cast<unsigned int> (float(margin - x) * transition);
				if (delta > 255)
					delta = 255;

				if (color.r < 255 - delta)
					color.r += delta;
				else
					color.r = 255;

				if (color.g < 255 - delta)
					color.g += delta;
				else
					color.g = 255;

				if (color.b < 255 - delta)
					color.b += delta;
				else
					color.b = 255;

				curImage.setPixel(x, y, color);
			}

			for (unsigned int x = curImage.getSize().x - margin; x < curImage.getSize().x; x++)
			{
				sf::Color color = curImage.getPixel(x, y);
				unsigned int delta = static_cast<unsigned int> (float(x - (curImage.getSize().x - margin)) * transition);
				if (delta > 255)
					delta = 255;

				if (color.r < 255 - delta)
					color.r += delta;
				else
					color.r = 255;

				if (color.g < 255 - delta)
					color.g += delta;
				else
					color.g = 255;

				if (color.b < 255 - delta)
					color.b += delta;
				else
					color.b = 255;

				curImage.setPixel(x, y, color);
			}
		}
		textures[textures.size() - 1].loadFromImage(curImage);
	}

	return true;
}

void addCharacter(std::string filename, std::vector<sf::Texture>& textures)
{
	for (char i = '1'; i <= '4'; i++)
	{
		textures.emplace_back(sf::Texture());
		if (!textures[textures.size() - 1].loadFromFile(filename + i + ".png"))
			return;
	}
}

int main(int argc, char** argv)
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "PADORU PADORU!");
	sf::Clock clock;
	float totalTime = 0.f;

	std::vector<sf::Texture> textures;
	constexpr unsigned int nbTextures = 20;
	textures.reserve(nbTextures);

	sf::Music padoruVoice;
	if (!padoruVoice.openFromFile("media/PadoruVoice.wav"))
		return -1; // error
	padoruVoice.setVolume(40);
	padoruVoice.play();

	textures.emplace_back(sf::Texture());
	if (!textures[0].loadFromFile("media/characters/padoru.png"))
		return EXIT_FAILURE;

	textures.emplace_back(sf::Texture());
	if (!textures[1].loadFromFile("media/characters/padoru2.png"))
		return EXIT_FAILURE;
	textures.emplace_back(sf::Texture());
	if (!textures[2].loadFromFile("media/characters/padoru3.png"))
		return EXIT_FAILURE;
	textures.emplace_back(sf::Texture());
	if (!textures[3].loadFromFile("media/characters/padoru4.png"))
		return EXIT_FAILURE;

	textures.emplace_back(sf::Texture());
	if (!textures[4].loadFromFile("media/snowball.png"))
		return EXIT_FAILURE;


	textures.emplace_back(sf::Texture());
	if (!textures[5].loadFromFile("media/present.jpg"))
		return EXIT_FAILURE;

	textures.emplace_back(sf::Texture());
	if (!textures[6].loadFromFile("media/Saintquartz.png"))
		return EXIT_FAILURE;

	addBackgroundTexture("media/winter1.jpg", textures);
	addBackgroundTexture("media/winter2.jpg", textures);
	addBackgroundTexture("media/winter3.jpg", textures);
	addBackgroundTexture("media/winter4.jpg", textures);
	addBackgroundTexture("media/winter5.jpg", textures);
	addBackgroundTexture("media/winter6.jpg", textures);
	addBackgroundTexture("media/winter7.jpg", textures);

	textures.emplace_back(sf::Texture());
	if (!textures[14].loadFromFile("media/padoruMenu.jpg"))
		return EXIT_FAILURE;

	textures.emplace_back(sf::Texture());
	if (!textures[15].loadFromFile("media/startButton.jpg"))
		return EXIT_FAILURE;

	textures.emplace_back(sf::Texture());						   
	if (!textures[16].loadFromFile("media/TruckKun.png"))
		return EXIT_FAILURE;

	textures.emplace_back(sf::Texture());
	if (!textures[17].loadFromFile("media/startButtonHard.jpg"))
		return EXIT_FAILURE;

	textures.emplace_back(sf::Texture());
	if (!textures[18].loadFromFile("media/ToBeContinued.png"))
		return EXIT_FAILURE;

	addCharacter("media/characters/player2_", textures); // 19 - 22
	addCharacter("media/characters/player3_", textures); // 23 - 26
	addCharacter("media/characters/player4_", textures); // 27 - 30
	addCharacter("media/characters/player5_", textures); // 31 - 34

	sf::Font font;
	if (!font.loadFromFile("media/LiberationSans-Regular.ttf"))
	{
		// error...
		return EXIT_FAILURE;
	}

	//InGame game(textures, font);

	Context* gameContext;
	//gameContext = new InGame(textures, font);
	gameContext = new Menu(textures, font, gameContext);

	while (window.isOpen())
	{
		sf::Time deltaTime = clock.restart();

		gameContext->ticks(totalTime, deltaTime, window);

		// draw
		window.clear();

		gameContext->draw(window);

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		gameContext->inputs(totalTime, deltaTime);

		window.display();
	}

	// delete gameContext;

	return 0;
}

