#include <SFML/Graphics.hpp>
#include <string>
#include <cstdlib>
#include <math.h>
#include <iostream>


// Window settings
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define WINDOW_TITLE "OSU"
#define FRAME_RATE_LIMIT 60
#define GAME_DURATION 60
#define FONT_PATH "sem2/SamokhvalovAD/homework_2/pixel.otf"
#define TEXT_SIZE 24
#define TIMER_TEXT_OFFSET 30
#define SCORE_TEXT_OFFSET 30
#define BEFORE_TIMER_TEXT "Time: "
#define BEFORE_SCORE_TEXT "Score: "
#define GAME_OVER_TEXT "Game Over!"
#define FONT_ERROR_TEXT "Font error"


// Circle settings
#define CIRCLE_COUNT 5
#define CIRCLE_RADIUS_MIN 30
#define CIRCLE_RADIUS_MAX 60
#define CIRCLE_SPEED_MIN 2
#define CIRCLE_SPEED_MAX 5
#define POINTS_INCREASE 10
#define POINTS_DECREASE 5
#define INCREACE_TIME 4

// Color
#define MAX_COLOR_VALUE 255

#define RANDOM_NUMBER(min, max) (rand() % ((max) - (min) + 1)) + (min)
#define RANDOM_FLOAT(min, max) (float)RANDOM_NUMBER(min, max) + (float)(rand()) / (float)(RAND_MAX)