#pragma once

#include <SFML/Graphics/Color.hpp>

// Окно
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

// Игровые параметры
#define INITIAL_TIME 30.0f
#define PENALTY_TIME 1.0f

// Шрифты и текст
#define SCORE_FONT_SIZE 30
#define TIMER_FONT_SIZE 30
#define CHAR_FONT_SIZE 120
#define GAME_OVER_FONT_SIZE 50
#define RESTART_FONT_SIZE 24
#define FINAL_SCORE_FONT_SIZE 36

// Позиции
#define SCORE_POS_X 10.0f
#define SCORE_POS_Y 10.0f
#define TIMER_POS_X 10.0f
#define TIMER_POS_Y 50.0f
#define GAME_OVER_POS_X (WINDOW_WIDTH / 2.0f)
#define GAME_OVER_POS_Y 250.0f
#define FINAL_SCORE_POS_X (WINDOW_WIDTH / 2.0f)
#define FINAL_SCORE_POS_Y 330.0f
#define RESTART_POS_X (WINDOW_WIDTH / 2.0f)
#define RESTART_POS_Y 400.0f

// Цвета
#define COLOR_SCORE sf::Color::White
#define COLOR_TIMER sf::Color::White
#define COLOR_CHAR sf::Color::Yellow
#define COLOR_GAME_OVER sf::Color::Red
#define COLOR_RESTART sf::Color::White
#define COLOR_FINAL_SCORE sf::Color::White
#define CLEAR_COLOR sf::Color::Black

// Прочее
#define FRAMERATE_LIMIT 60
