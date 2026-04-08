#ifndef __GAME_H
#define __GAME_H

#include <SFML/Graphics.hpp>
#include <random>

class Game{
public:
	unsigned int screen_width;
	unsigned int screen_height;
	sf::RenderWindow window;
	std::random_device rd; 
    std::mt19937 gen;
	float timer;
	int score;

private:
	static Game *instance_ptr; 
	Game();
  
public:
	Game(const Game &obj) = delete; 

	static Game *getInstance() {
		if (instance_ptr == nullptr) {
			instance_ptr = new Game();
		}
		return instance_ptr; 
	}

	int randrange(int min, int max);
};

#endif