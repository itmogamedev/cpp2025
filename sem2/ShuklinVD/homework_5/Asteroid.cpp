#include "Asteroid.h"
#include "constants.h"

Asteroid::Asteroid()
    : GameObject(0.f, 0.f, ASTEROID_WIDTH, ASTEROID_HEIGHT),
      m_speed(ASTEROID_DEFAULT_SPEED)
{
}

Asteroid::Asteroid(float x, float y, float speed)
    : GameObject(x, y, ASTEROID_WIDTH, ASTEROID_HEIGHT),
      m_speed(speed)
{
}

void Asteroid::update(float deltaTime)
{
    move(0.f, m_speed * deltaTime);
}

void Asteroid::setSpeed(float speed) { m_speed = speed; }
float Asteroid::getSpeed() const { return m_speed; }
