#ifndef RENDERER_H
#define RENDERER_H
#include <SFML/Graphics.hpp>
class Renderer {
	sf::RenderWindow& window;
	const sf::Font& font;
public:
	Renderer(sf::RenderWindow& window, const sf::Font& font);
	void drawGame(char symbol_current, int counter, float reamining_time);
	void drawGameOver(int final_counter);
};
#endif  // !RENDERER_H
