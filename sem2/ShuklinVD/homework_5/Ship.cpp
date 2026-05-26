#include "Ship.h"
#include "constants.h"

Ship::Ship()
    : GameObject(0.f, 0.f, SHIP_WIDTH, SHIP_HEIGHT),
      m_speed(SHIP_SPEED), m_lives(SHIP_INITIAL_LIVES)
{
}

Ship::Ship(float x, float y)
    : GameObject(x, y, SHIP_WIDTH, SHIP_HEIGHT),
      m_speed(SHIP_SPEED), m_lives(SHIP_INITIAL_LIVES)
{
}

void Ship::moveLeft(float deltaTime, float screenWidth)
{
    move(-m_speed * deltaTime, 0.f);
    if (m_x < 0.f)
        m_x = 0.f;
}

void Ship::moveRight(float deltaTime, float screenWidth)
{
    move(m_speed * deltaTime, 0.f);
    if (m_x + m_width > screenWidth)
        m_x = screenWidth - m_width;
}

int Ship::getLives() const { return m_lives; }

void Ship::loseLife()
{
    if (m_lives > 0)
        m_lives--;
}

void Ship::resetLives() { m_lives = SHIP_INITIAL_LIVES; }

bool Ship::isDead() const { return m_lives <= 0; }
