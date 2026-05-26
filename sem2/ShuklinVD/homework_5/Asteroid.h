#pragma once
#include "GameObject.h"

class Asteroid : public GameObject
{
public:
    Asteroid();
    Asteroid(float x, float y, float speed);

    void update(float deltaTime);

    void setSpeed(float speed);
    float getSpeed() const;

private:
    float m_speed;
};
