#pragma once
#include <SFML/Graphics.hpp>

constexpr unsigned int WINDOW_WIDTH = 800;
constexpr unsigned int WINDOW_HEIGHT = 900;

constexpr int GRID_SIZE = 4;
constexpr int CARD_COUNT = GRID_SIZE * GRID_SIZE;
constexpr int PAIR_COUNT = CARD_COUNT / 2;

constexpr float CARD_SIZE = 170.f;
constexpr float CARD_MARGIN = 20.f;
// Смещение поля по X — чтобы сетка карточек была по центру окна
constexpr float BOARD_OFFSET_X =
    ((float)WINDOW_WIDTH - (GRID_SIZE * CARD_SIZE + (GRID_SIZE - 1) * CARD_MARGIN)) / 2.f;
constexpr float BOARD_OFFSET_Y = 120.f;

constexpr int REVEAL_DELAY_MS = 900;

const sf::Color BG_COLOR(40, 40, 50);
const sf::Color BACK_COLOR(20, 40, 90);
const sf::Color OUTLINE_COLOR(255, 255, 255);
const sf::Color FACE_COLOR(245, 245, 245);
const sf::Color TEXT_COLOR(255, 255, 255);
