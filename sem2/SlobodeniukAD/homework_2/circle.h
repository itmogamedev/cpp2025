#ifndef CIRCLE_H
#define CIRCLE_H

#include <SFML/Graphics.hpp>

#include "config.h"

class Circle {
public:
	Circle(float window_width, float window_height);
	void update(float dt, float window_width, float window_height);
	void draw(sf::RenderWindow& window) const;
	bool isClicked(const sf::Vector2i& mouse_pos) const;
	void reposition(float window_width, float window_height);

private:
	sf::CircleShape shape;
	sf::Vector2f velocity;
	float radius;
};

#endif