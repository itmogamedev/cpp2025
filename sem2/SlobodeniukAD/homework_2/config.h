#ifndef CONFIG_H
#define CONFIG_H

#include <SFML/Graphics.hpp>

// Настройки окна
constexpr unsigned int WINDOW_WIDTH = 800;
constexpr unsigned int WINDOW_HEIGHT = 600;
constexpr const char* WINDOW_TITLE = "OSU дома";

// Настройки кругов
constexpr int CIRCLES_COUNT = 5;
constexpr float CIRCLE_RADIUS = 25.0f;
constexpr int VELOCITY_RANGE = 400;
constexpr int VELOCITY_MIN = -200;
constexpr int VELOCITY_MAX = 200;

// Настройки игры
constexpr float INITIAL_TIME = 45.0f;
constexpr float TIME_PENALTY = 2.0f;
constexpr int SCORE_INCREMENT = 1;

// Настройки текста
constexpr unsigned int FONT_SIZE_SCORE = 24;
constexpr unsigned int FONT_SIZE_TIMER = 24;
constexpr unsigned int FONT_SIZE_GAME_OVER = 48;
constexpr float TEXT_POSITION_X = 10.0f;
constexpr float TEXT_POSITION_Y_SCORE = 10.0f;
constexpr float TEXT_POSITION_Y_TIMER = 40.0f;
constexpr float TEXT_POSITION_X_GAME_OVER = 180.0f;
constexpr float TEXT_POSITION_Y_GAME_OVER = 220.0f;

// Цвета
constexpr sf::Color BACKGROUND_COLOR = sf::Color::Black;
constexpr sf::Color CIRCLE_COLOR = sf::Color::Red;
constexpr sf::Color TEXT_COLOR = sf::Color::White;
constexpr sf::Color GAME_OVER_TEXT_COLOR = sf::Color::Yellow;

#endif
