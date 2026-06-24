#include "Ship.h"

#include "constants.h"

Ship::Ship()
    : GameObject(0.f, 0.f, SHIP_WIDTH, SHIP_HEIGHT),
      speed(SHIP_SPEED),
      lives(SHIP_INITIAL_LIVES) {}

Ship::Ship(float x, float y)
    : GameObject(x, y, SHIP_WIDTH, SHIP_HEIGHT),
      speed(SHIP_SPEED),
      lives(SHIP_INITIAL_LIVES) {}

void Ship::moveLeft(float delta_time, float screen_width) {
  move(-speed * delta_time, 0.f);
  if (x < 0.f) x = 0.f;
}

void Ship::moveRight(float delta_time, float screen_width) {
  move(speed * delta_time, 0.f);
  if (x + width > screen_width) x = screen_width - width;
}

int Ship::getLives() const { return lives; }

void Ship::loseLife() {
  if (lives > 0) lives--;
}

void Ship::resetLives() { lives = SHIP_INITIAL_LIVES; }

bool Ship::isDead() const { return lives <= 0; }
