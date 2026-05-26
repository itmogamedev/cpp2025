#ifndef CONST_H
#define CONST_H

#define GRID_SIZE 4
#define TOTAL_CARDS 16
#define TOTAL_PAIRS 8
#define CARD_WIDTH 90.f
#define CARD_HEIGHT 90.f
#define FIELD_MARGIN 20.f
#define WAIT_SECONDS 0.5f
#define MAX_CONSECUTIVE_ERRORS 2

#define WINDOW_WIDTH (GRID_SIZE * CARD_WIDTH + GRID_SIZE * FIELD_MARGIN + 25.f)
#define WINDOW_HEIGHT (GRID_SIZE * CARD_HEIGHT + GRID_SIZE * FIELD_MARGIN + 80.f)
#define WINDOW_TITLE "memo memo memo memo"
#define FONT_MAIN "fonts/ofont.ru_Uncage.ttf"

#define COLOR_BG sf::Color(255, 240, 245)
#define COLOR_CARD_OPEN sf::Color(255, 200, 220)
#define COLOR_CARD_CLOSED sf::Color(230, 180, 200)
#define COLOR_TEXT sf::Color(120, 60, 80)

#define TEXT_SIZE_SYMBOL 50
#define TEXT_SIZE_INFO 24
#define INFO_OFFSET 10

#endif