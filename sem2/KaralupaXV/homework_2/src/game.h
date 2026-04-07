#ifndef __GAME_H
#define __GAME_H

#include <SFML/Graphics.hpp>
#include <random>

class Game{
public:
	unsigned int screenWidth;
	unsigned int screenHeight;
	sf::RenderWindow window;
	std::random_device rd; 
    std::mt19937 gen;
	float timer;
	int score;

private:
	static Game *instancePtr; 
	Game() {
		gen = std::mt19937(rd());
		screenWidth = 800;
		screenHeight = 600;
		sf::ContextSettings settings;
		settings.antiAliasingLevel = 8;
		window = sf::RenderWindow( 
			sf::VideoMode( { screenWidth, screenHeight } ), 
			"Game", 
			sf::Style::Titlebar | sf::Style::Close, 
			sf::State::Windowed, 
			settings 
		);
		window.setFramerateLimit(0);

		timer = 60;
		score = 0;
	}
  
public:
	Game(const Game &obj) = delete; 

	static Game *getInstance() {
		if (instancePtr == nullptr) {
			instancePtr = new Game();
		}
		return instancePtr; 
	}

	int randrange(int min, int max) {
		return std::uniform_int_distribution<>(min, max)(gen);
	}
};

Game *Game::instancePtr = nullptr;


#endif