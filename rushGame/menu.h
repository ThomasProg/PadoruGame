#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "context.h"

#include "button.h"

#include "context.h"

namespace sf
{
	class Texture;
	class Font;
};

class Menu : public Context
{
private:
	std::vector<sf::Texture>& textures;
	sf::Font& font;
	sf::Sprite background;

	Button playButton;

	Button playButtonHard;

	Context*& gameContext;

	sf::Text progzCopyright;
	bool isLeftPressed = false, isRightPressed = false;

public: 
	Menu(std::vector<sf::Texture>& textures, sf::Font& font, Context*& gameContext);
	~Menu();

	void ticks(float& totalTime, sf::Time& deltaTime, sf::RenderWindow& window) override;
	void draw(sf::RenderWindow& window) override;
	void inputs(float& totalTime, sf::Time& deltaTime) override;
};