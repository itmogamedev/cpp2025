#pragma once

#include "SFML/Graphics.hpp"

class BouncingCircleShape : public sf::CircleShape {
private:
	float speedX;
	float speedY;

	sf::Vector2<int> moveDir;

	void move();

	void updateDirectionOnCollisionWithWindow(sf::RenderWindow& wn);

public:
	BouncingCircleShape(float r, size_t pointsCnt = 30Ui64);

	void update(sf::RenderWindow& wn);

	void draw(sf::RenderWindow& wn);

	void increaseSpeedXY(float val);
};