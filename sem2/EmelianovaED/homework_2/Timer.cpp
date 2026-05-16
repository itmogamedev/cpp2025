#include "Timer.h"

Timer::Timer(float init_time) : remaining_time(init_time) {}
void Timer::resetTimer(float init_time) { remaining_time = init_time; }
void Timer::updateTimer(float delta_time) {
  if (remaining_time > 0) {
    remaining_time -= delta_time;
  } else if (remaining_time <= 0)
    remaining_time = 0;
}
void Timer::reduceTimer(float amount) {
  remaining_time -= amount;
  if (remaining_time <= 0) remaining_time = 0;
}
bool Timer::isExpired() const { return remaining_time <= 0.0f; }
float Timer::getRemainingTime() const { return remaining_time; }
