#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>


constexpr unsigned WINDOW_W = 800;
constexpr unsigned WINDOW_H = 600;
constexpr float PLAYER_SPEED = 300.f;
constexpr float BULLET_SPEED = 500.f;
constexpr float ASTEROID_BASE_SPEED = 120.f; 
constexpr float ASTEROID_SPEED_STEP = 15.f; // every 10
constexpr float RELOAD_BASE = 0.5f; // every 5
constexpr float RELOAD_MIN = 0.12f;
constexpr float RELOAD_STEP = 0.04f;
constexpr float ASTEROID_SPAWN_BASE = 1.4f; // seconds between spawns
constexpr float ASTEROID_SPAWN_MIN = 0.35f;
constexpr int MAX_LIVES = 3;


class Bullet {
public:
	sf::CircleShape shape;
    bool active = true;

    Bullet(sf::Vector2f pos);
    void update(float dt);
};

class Asteroid {
public:
	sf::CircleShape shape;
    float speed;
    bool active = true;

    Asteroid(float x, float spd);
    void update(float dt);
};


class Player {
public:
    Player(sf::Vector2f pos);

    void handleInput(float dt);
    bool tryShoot(float dt, int score);

    sf::Vector2f getPosition();
    sf::FloatRect getBounds();
    const sf::ConvexShape& getShape();

    int lives;

private:
    sf::ConvexShape shape;
    float reloadTimer;
};


class UI {
public:
    UI(const sf::Font& font);
    void draw(sf::RenderWindow& win, int score, int lives);
	void drawGameOver(sf::RenderWindow& win, int score);

private:
    const sf::Font& font;
    sf::Text scoreText;
    sf::Text livesText;
};


enum class GameState { 
	Playing, 
	GameOver 
};

class Game {
public:
    Game();
    void run();

private:
    void processEvents();
    void update(float dt);
    void render();
    void spawnAsteroid();
    void reset();

    sf::RenderWindow window;
    sf::Font font;

    Player player;
    std::vector<Bullet> bullets;
    std::vector<Asteroid> asteroids;
    UI ui;

    GameState state = GameState::Playing;
    int score = 0;
    float spawnTimer = 0.f;
    float spawnInterval = ASTEROID_SPAWN_BASE;
};


#endif