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

	Circle(int x, int y, int radius, Color color, int speed=200, Vec2<int> direction = Vec2<int>(1, 1));

	void update(float delta) override;
	void draw() override;
};

#endif