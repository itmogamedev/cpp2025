#include "Utils.h"

#include <cstdlib>

char getRandomChar() { return static_cast<char>('A' + (std::rand() % 26)); }
