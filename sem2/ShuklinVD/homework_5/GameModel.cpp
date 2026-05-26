#include "GameModel.h"
#include "constants.h"
#include <cstdlib>

GameModel::GameModel(float screenWidth, float screenHeight)
    : m_screenWidth(screenWidth), m_screenHeight(screenHeight)
{
    reset();
}

void GameModel::reset()
{
    m_asteroids.clear();
    m_bullets.clear();

    float shipX = m_screenWidth / 2.f - SHIP_SPAWN_OFFSET_X;
    float shipY = m_screenHeight - SHIP_SPAWN_OFFSET_Y;
    m_ship = Ship(shipX, shipY);

    m_score = 0;
    m_state = GameState::Playing;

    m_shootTimer = 0.f;
    m_spawnTimer = 0.f;
    m_gameTime = 0.f;
    m_spawnInterval = SPAWN_INTERVAL_INIT;
}

float GameModel::currentCooldown() const
{
    float cd = SHOOT_COOLDOWN_BASE - static_cast<float>(m_score) * SHOOT_COOLDOWN_STEP;
    if (cd < SHOOT_COOLDOWN_MIN)
        cd = SHOOT_COOLDOWN_MIN;
    return cd;
}

void GameModel::update(float deltaTime)
{
    if (m_state != GameState::Playing)
        return;

    m_gameTime += deltaTime;
    m_shootTimer += deltaTime;
    m_spawnTimer += deltaTime;

    if (m_spawnTimer >= m_spawnInterval)
    {
        spawnAsteroid();
        m_spawnTimer = 0.f;
    }

    updateBullets(deltaTime);
    updateAsteroids(deltaTime);
    checkCollisions();
    cleanupDeadObjects();

    if (m_ship.isDead())
        m_state = GameState::GameOver;
}

void GameModel::spawnAsteroid()
{
    float x = static_cast<float>(rand() % static_cast<int>(m_screenWidth - ASTEROID_WIDTH));
    float speed = ASTEROID_BASE_SPEED + m_gameTime * ASTEROID_SPEED_ACCEL;
    Asteroid asteroid(x, ASTEROID_SPAWN_Y, speed);
    m_asteroids.push_back(asteroid);
}

void GameModel::moveShipLeft(float deltaTime)
{
    if (m_state == GameState::Playing)
        m_ship.moveLeft(deltaTime, m_screenWidth);
}

void GameModel::moveShipRight(float deltaTime)
{
    if (m_state == GameState::Playing)
        m_ship.moveRight(deltaTime, m_screenWidth);
}

void GameModel::shoot()
{
    if (m_state != GameState::Playing)
        return;

    if (m_shootTimer >= currentCooldown())
    {
        float bx = m_ship.getX() + m_ship.getWidth() / 2.f - BULLET_WIDTH / 2.f;
        float by = m_ship.getY() - BULLET_SPAWN_OFFSET_Y;
        m_bullets.push_back(Bullet(bx, by));
        m_shootTimer = 0.f;
    }
}

void GameModel::updateBullets(float deltaTime)
{
    for (size_t i = 0; i < m_bullets.size(); i++)
    {
        m_bullets[i].update(deltaTime);
        if (m_bullets[i].getY() + m_bullets[i].getHeight() < 0.f)
            m_bullets[i].kill();
    }
}

void GameModel::updateAsteroids(float deltaTime)
{
    for (size_t i = 0; i < m_asteroids.size(); i++)
    {
        m_asteroids[i].update(deltaTime);
        if (m_asteroids[i].getY() > m_screenHeight)
            m_asteroids[i].kill();
    }
}

void GameModel::checkCollisions()
{
    for (size_t b = 0; b < m_bullets.size(); b++)
    {
        if (!m_bullets[b].isAlive())
            continue;

        for (size_t a = 0; a < m_asteroids.size(); a++)
        {
            if (!m_asteroids[a].isAlive())
                continue;

            if (m_bullets[b].collidesWith(m_asteroids[a]))
            {
                m_bullets[b].kill();
                m_asteroids[a].kill();
                m_score += SCORE_PER_ASTEROID;
                break;
            }
        }
    }

    for (size_t a = 0; a < m_asteroids.size(); a++)
    {
        if (!m_asteroids[a].isAlive())
            continue;

        if (m_ship.collidesWith(m_asteroids[a]))
        {
            m_asteroids[a].kill();
            m_ship.loseLife();
        }
    }
}

void GameModel::cleanupDeadObjects()
{
    std::vector<Bullet> aliveBullets;
    for (size_t i = 0; i < m_bullets.size(); i++)
    {
        if (m_bullets[i].isAlive())
            aliveBullets.push_back(m_bullets[i]);
    }
    m_bullets = aliveBullets;

    std::vector<Asteroid> aliveAsteroids;
    for (size_t i = 0; i < m_asteroids.size(); i++)
    {
        if (m_asteroids[i].isAlive())
            aliveAsteroids.push_back(m_asteroids[i]);
    }
    m_asteroids = aliveAsteroids;
}

const Ship& GameModel::getShip() const { return m_ship; }
const std::vector<Asteroid>& GameModel::getAsteroids() const { return m_asteroids; }
const std::vector<Bullet>& GameModel::getBullets() const { return m_bullets; }
int GameModel::getScore() const { return m_score; }
int GameModel::getLives() const { return m_ship.getLives(); }
GameState GameModel::getState() const { return m_state; }
