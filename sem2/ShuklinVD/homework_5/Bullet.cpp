#include "Bullet.h"
#include "constants.h"

Bullet::Bullet()
    : GameObject(0.f, 0.f, BULLET_WIDTH, BULLET_HEIGHT),
      m_speed(BULLET_SPEED)
{
}

Bullet::Bullet(float x, float y)
    : GameObject(x, y, BULLET_WIDTH, BULLET_HEIGHT),
      m_speed(BULLET_SPEED)
{
}

void Bullet::update(float deltaTime)
{
    move(0.f, -m_speed * deltaTime);
}
