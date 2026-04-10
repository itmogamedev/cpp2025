#include "game.h"
#include <iostream>
#include <algorithm>

std::string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789[]-=;'\,./";
const int maxTime = 300;

Game::Game() {
	font.openFromFile("fonts/Comic Sans MS.ttf");
	time = maxTime;
	score = 0;
	currChar = randChar();
}

char Game::randChar() {
	currChar = chars[std::rand() % chars.length()];
	return currChar;
}

void Game::enter(char key) {
	if (time - int(clock.getElapsedTime().asSeconds()) <= 0) return;
	if (key == currChar || key >= 'a' && key <= 'z' && currChar >='A' && currChar <= 'Z' && key == currChar + ('a' - 'A')) {
		score += 5;
		randChar();
	}
	else {
		time = std::max(0.0f, time - 5);
		randChar();
	}
}

void Game::draw(sf::RenderTarget& target) {
	sf::Text textTimer(font);
	sf::Text textScore(font);
	sf::Text textChar(font);
	if ((time - int(clock.getElapsedTime().asSeconds())) <= 0) {
		sf::Text textGameOver(font, "GAME OVER", 80);
		textGameOver.setFillColor(sf::Color::Red);
		textGameOver.setPosition(sf::Vector2f({ 305, 255 }));

		textScore.setString("Your Score " + std::to_string(score));
		textScore.setCharacterSize(80);
		textScore.setPosition(sf::Vector2f({ 305, 355 }));
		target.draw(textGameOver);
		target.draw(textScore);
		return;
	}
	textTimer.setString(std::to_string(int(std::max(0.0f, time - int(clock.getElapsedTime().asSeconds())))));
	textTimer.setCharacterSize(48);
	textTimer.setFillColor(sf::Color::White);
	target.draw(textTimer);

	textScore.setString("YOUR SCORE " + std::to_string(score));
	textScore.setCharacterSize(48);
	textScore.setFillColor(sf::Color::White);
	textScore.setPosition(sf::Vector2f({ 0, 50 }));
	target.draw(textScore);

	textChar.setString(currChar);
	textChar.setCharacterSize(80);
	textChar.setFillColor(sf::Color::Yellow);
	textChar.setPosition(sf::Vector2f({ 525,285 }));
	target.draw(textChar);
}