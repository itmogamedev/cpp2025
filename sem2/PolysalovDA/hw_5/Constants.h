#pragma once
#include <SFML/Graphics.hpp>
#include <string>

// Окно
const sf::Vector2u WINDOW_SIZE{800, 800};
constexpr const char* WINDOW_TITLE = "Space Shooter";
constexpr unsigned FRAMERATE_LIMIT = 60;

// Текстуры
const std::string SPACESHIP_TEXTURE = "../assets/spaceship.png";
const std::string ENEMY_TEXTURE = "../assets/asteroid.png";
const std::string BULLET_TEXTURE = "../assets/bullet.png";

// Корабль
constexpr float SPACESHIP_WIDTH = 50.f;
constexpr float SPACESHIP_HEIGHT = 30.f;
constexpr float SHIP_SPEED = 600.f;
const float SPACESHIP_START_POS_X = WINDOW_SIZE.x / 2.f;
const float SPACESHIP_START_POS_Y = WINDOW_SIZE.y - 100.f;

// Пули
const sf::Vector2f BULLET_SIZE{4.f, 15.f};
const sf::Color BULLET_COLOR = sf::Color::Yellow;
constexpr float BULLET_SPEED = 500.f;
const float BULLET_DESTROY_Y = -20.f;
const float BULLET_OFFSET_X = 2.f;
const float BULLET_OFFSET_Y = 15.f;

// Стрельба
constexpr float SHOOT_COOLDOWN_BASE = 0.5f;
constexpr float SHOOT_COOLDOWN_MIN = 0.1f;
constexpr float COOLDOWN_REDUCTION_PER_SCORE = 0.01f;

// Враги
constexpr float ENEMY_SPEED = 200.f;
constexpr float ASTEROID_BASE_SPEED = 200.f;
constexpr float ASTEROID_SPEED_INCREASE = 5.f;
constexpr float ENEMY_WIDTH = 50.f;
constexpr float ENEMY_HEIGHT = 50.f;
const unsigned ASTEROID_WIDTH = 50;
const float ASTEROID_SPAWN_Y = -50.f;
const int ASTEROID_SPAWN_MARGIN = 25;
constexpr float SPRITE_SIZE_MULTIPLIER = 0.5f;

// Спавн врагов
constexpr float ASTEROID_SPAWN_INTERVAL = 1.5f;
constexpr float ASTEROID_SPAWN_DECREASE = 0.02f;
constexpr float MIN_SPAWN_INTERVAL = 0.3f;

// UI
constexpr int STATS_TEXT_SIZE = 24;
const sf::Vector2f SCORE_TEXT_POSITION{10.f, 10.f};
constexpr int GAME_OVER_TEXT_SIZE = 48;
constexpr float WINDOW_PADDING = 50.f;

// Игровые правила
constexpr int MAX_LIVES = 3;
constexpr int START_SCORE = 0;
constexpr float SPEED_MULTIPLER = 0.1f;