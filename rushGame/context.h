#pragma once

namespace sf 
{
	class RenderWindow;
	class Time;
};

class Context
{
private:
	
public:
	virtual void ticks(float& totalTime, sf::Time& clock, sf::RenderWindow& window) = 0;
	virtual void draw(sf::RenderWindow& window) = 0;
	virtual void inputs(float& totalTime, sf::Time& deltaTime) = 0;
};