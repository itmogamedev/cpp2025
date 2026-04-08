#include "game.h"

Game::Game() {
	gen = std::mt19937(rd());
	screen_width = 800;
	screen_height = 600;
	sf::ContextSettings settings;
	settings.antiAliasingLevel = 8;
	window = sf::RenderWindow( 
		sf::VideoMode( { screen_width, screen_height } ), 
		"Game", 
		sf::Style::Titlebar | sf::Style::Close, 
		sf::State::Windowed, 
		settings 
	);
	window.setFramerateLimit(0);

	timer = 60;
	score = 0;
}

int Game::randrange(int min, int max) {
	return std::uniform_int_distribution<>(min, max)(gen);
}

Game *Game::instance_ptr = nullptr;