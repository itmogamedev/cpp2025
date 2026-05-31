#pragma once

// Window dimensions
constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 800;

// Card grid
constexpr int GRID_SIZE = 4;
constexpr int CARD_COUNT = GRID_SIZE * GRID_SIZE;
constexpr int PAIRS_COUNT = CARD_COUNT / 2;

// Card dimensions and spacing
constexpr float CARD_WIDTH = 150.f;
constexpr float CARD_HEIGHT = 150.f;
constexpr float CARD_PADDING = 10.f;
constexpr float CARD_OUTLINE_THICKNESS = 2.f;

// Card colors
const sf::Color CARD_HIDDEN_COLOR(100, 100, 150);
const sf::Color CARD_REVEALED_COLOR(50, 50, 100);
const sf::Color CARD_OUTLINE_COLOR(sf::Color::White);

// Card symbols
constexpr int SYMBOL_CHARACTER_SIZE = 48;

// Grid centering offsets
constexpr float GRID_TOP_OFFSET = 50.f;
constexpr float GRID_OFFSET_X = (WINDOW_WIDTH - GRID_SIZE * (CARD_WIDTH + CARD_PADDING)) / 2.f;
constexpr float GRID_OFFSET_Y = (WINDOW_HEIGHT - GRID_SIZE * (CARD_HEIGHT + CARD_PADDING)) / 2.f + GRID_TOP_OFFSET;

// Game logic
constexpr float REVEAL_DELAY = 0.5f;
constexpr int CONSECUTIVE_MISSES_TO_SHUFFLE = 2;
constexpr int STARTING_MOVES = 0;
constexpr int STARTING_PAIRS_FOUND = 0;
constexpr int STARTING_CONSECUTIVE_MISSES = 0;

// UI text settings
constexpr int MOVES_TEXT_CHARACTER_SIZE = 24;
constexpr int GAME_OVER_TEXT_CHARACTER_SIZE = 48;
constexpr float MOVES_TEXT_X = 10.f;
constexpr float MOVES_TEXT_Y = 10.f;
const sf::Color MOVES_TEXT_COLOR(sf::Color::White);
const sf::Color GAME_OVER_TEXT_COLOR(sf::Color::Green);

// Background
const sf::Color BACKGROUND_COLOR(30, 30, 50);

// Font
constexpr const char* FONT_PATH = "arial.ttf";

// Card symbols array
constexpr const char* CARD_SYMBOLS[] = { "A", "B", "C", "D", "E", "F", "G", "H" };