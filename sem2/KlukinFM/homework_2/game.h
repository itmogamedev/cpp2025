#pragma once
#include <SFML/Graphics.hpp>

class Game {
	sf::Font font;
	sf::Clock clock;
	float time;

public:
	char currChar;
	int score;

	Game();
	void enter(char key);
	void draw(sf::RenderTarget& target);
	char randChar();
};
