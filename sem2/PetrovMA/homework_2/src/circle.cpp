
#include "circle.h"

#include <chrono>

#include <cstdint>
#include <iostream>

#include "game.h"

bool Circle::frameTick(Game *game) {
  int64_t time =
      std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch())
          .count();

  // 5s
  if (time - spawn_time > 5 * 1000L)
    return false;

  center.y += 25 * game->dt;
  shape.setPosition(center);

  return true;
}
