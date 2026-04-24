#include "Counter.h"

Counter::Counter() : points(0) {};

void Counter::updateCounter(int win_point) { points += win_point; }
int Counter::getPoints() const { return points; }
void Counter::resetCounter() { points = 0; }
