#include <SFML/Graphics.hpp>
#include <string>
#include <cstdlib>
#include <math.h>
#include <iostream>


// Window settings
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

// Circle settings
#define CIRCLE_COUNT 5
#define CIRCLE_RADIUS_MIN 30
#define CIRCLE_RADIUS_MAX 60
#define CIRCLE_SPEED_MIN 2
#define CIRCLE_SPEED_MAX 5

// Color
#define MAX_COLOR_VALUE 255

#define RANDOM_NUMBER(min, max) (rand() % ((max) - (min) + 1)) + (min)
#define RANDOM_FLOAT(min, max) (float)RANDOM_NUMBER(min, max) + (float)(rand()) / (float)(RAND_MAX)