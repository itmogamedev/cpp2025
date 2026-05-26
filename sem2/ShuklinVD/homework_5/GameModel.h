#pragma once
#include <vector>
#include "Ship.h"
#include "Asteroid.h"
#include "Bullet.h"

enum class GameState
{
    Playing,
    GameOver
};

class GameModel
{
public:
    GameModel(float screenWidth, float screenHeight);

    void reset();
    void update(float deltaTime);

    void moveShipLeft(float deltaTime);
    void moveShipRight(float deltaTime);
    void shoot();

    const Ship& getShip() const;
    const std::vector<Asteroid>& getAsteroids() const;
    const std::vector<Bullet>& getBullets() const;
    int getScore() const;
    int getLives() const;
    GameState getState() const;

private:
    void spawnAsteroid();
    void updateBullets(float deltaTime);
    void updateAsteroids(float deltaTime);
    void checkCollisions();
    void cleanupDeadObjects();
    float currentCooldown() const;

    float m_screenWidth;
    float m_screenHeight;

    Ship m_ship;
    std::vector<Asteroid> m_asteroids;
    std::vector<Bullet> m_bullets;

    int m_score;
    GameState m_state;

    float m_shootTimer;
    float m_spawnTimer;
    float m_gameTime;
    float m_spawnInterval;
};
