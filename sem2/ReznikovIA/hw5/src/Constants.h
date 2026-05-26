#pragma once

constexpr int COLS = 4;
constexpr int ROWS = 4;
constexpr float CARD_W = 120.f;
constexpr float CARD_H = 160.f;
constexpr float GAP = 16.f;
constexpr float OFFSET_X = (1280.f - (COLS * CARD_W + (COLS - 1) * GAP)) / 2.f;
constexpr float OFFSET_Y = (720.f - (ROWS * CARD_H + (ROWS - 1) * GAP)) / 2.f;
