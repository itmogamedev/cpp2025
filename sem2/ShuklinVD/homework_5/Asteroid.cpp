#include "Asteroid.h"

#include "constants.h"

Asteroid::Asteroid()
    : GameObject(0.f, 0.f, ASTEROID_WIDTH, ASTEROID_HEIGHT),
      speed(ASTEROID_DEFAULT_SPEED) {}

Asteroid::Asteroid(float x, float y, float speed)
    : GameObject(x, y, ASTEROID_WIDTH, ASTEROID_HEIGHT), speed(speed) {}

void Asteroid::update(float delta_time) { move(0.f, speed * delta_time); }

void Asteroid::setSpeed(float speed) { this->speed = speed; }
float Asteroid::getSpeed() const { return speed; }
