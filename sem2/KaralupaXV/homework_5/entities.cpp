#include "game.h"
#include <cmath>
#include <cstdlib>
#include <ctime>


Bullet::Bullet(sf::Vector2f pos) {
    shape.setRadius(4.f);
    shape.setOrigin({4.f, 4.f});
    shape.setPosition(pos);
    shape.setFillColor(sf::Color::Yellow);
}

void Bullet::update(float dt) {
    if (!active) {
		return;
	}
	
	shape.move({0.f, -BULLET_SPEED * dt});
    if (shape.getPosition().y < -10.f) {
        active = false;
	}
}


Asteroid::Asteroid(float x, float spd) : speed(spd) {
    float radius  = 22 + (std::rand() % 18);
    shape = sf::CircleShape(radius);
    shape.setFillColor(sf::Color(110, 90, 70));
    shape.setPosition({x, -40.f});
}

void Asteroid::update(float dt) {
    shape.move({0.f, speed * dt});
    if (shape.getPosition().y > WINDOW_H + 40) {
        active = false;
	}
}
