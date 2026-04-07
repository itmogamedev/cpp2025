#ifndef __CIRCLE_H
#define __CIRCLE_H

#include "object.h"
#include "color.h"
#include "vec.h"
#include "game.h"

class Circle : public Object {
private:
	sf::CircleShape shape;

public:
	int x, y;
	int radius;
	Color color;
	int speed;
	Vec2<int> direction;

	Circle(int x, int y, int radius, Color color, int speed=200, Vec2<int> direction = Vec2<int>(1, 1)) {
		this->x = x;
		this->y = y;
		this->radius = radius;
		this->color = color;

		this->speed = speed;
		this->direction = direction;
		this->shape = sf::CircleShape(radius);
		this->shape.setFillColor(color);
		this->shape.setOutlineColor(Color::White);
		this->shape.setOutlineThickness(2);
		this->shape.setOrigin(sf::Vector2f(radius, radius));
	}

	void update(float delta) override {
		this->x += (float)this->direction.x * delta * (float)this->speed;
		this->y += (float)this->direction.y * delta * (float)this->speed;

		int width = Game::getInstance()->screenWidth;
		int height = Game::getInstance()->screenHeight;
		if (this->x >= width - radius) {
			this->direction.x *= -1;
			this->x = width - radius - 1;
		}
		else if (this->x <= radius) {
			this->direction.x *= -1;
			this->x = radius + 1;
		}

		if (this->y >= height - radius) {
			this->direction.y *= -1;
			this->y = height - radius - 1;
		}
		else if (this->y <= radius) {
			this->direction.y *= -1;
			this->y = radius + 1;
		}
	}

	void draw() override {
		this->shape.setPosition(sf::Vector2f(this->x, this->y));
		this->shape.setFillColor(color);
		Game::getInstance()->window.draw(shape);
	}
};

#endif