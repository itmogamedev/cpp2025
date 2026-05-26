#pragma once
#include "GameObject.h"

class Ship : public GameObject
{
public:
    Ship();
    Ship(float x, float y);

    void moveLeft(float deltaTime, float screenWidth);
    void moveRight(float deltaTime, float screenWidth);

    int getLives() const;
    void loseLife();
    void resetLives();
    bool isDead() const;

private:
    float m_speed;
    int m_lives;
};
