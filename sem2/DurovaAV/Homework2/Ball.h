#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics.hpp>

class Ball {
public:
	explicit Ball(float radius);

	void setRandomSpawn(int maxWidth, int maxHeight);
	void setRandomMovement(float minSpeed, float maxSpeed);
	void move(float deltaTime, int boundaryX, int boundaryY);
	void draw(sf::RenderWindow& target);
	bool containsPoint(sf::Vector2i point);

private:
	sf::CircleShape body_;
	sf::Vector2f velocity_;
};

#endif