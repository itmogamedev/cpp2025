#pragma once
#include "GameObject.h"

class Bullet : public GameObject
{
public:
    Bullet();
    Bullet(float x, float y);

    void update(float deltaTime);

private:
    float m_speed;
};
