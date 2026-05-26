#pragma once
#include "GameObject.h"

class Ship : public GameObject {
 public:
  Ship();
  Ship(float x, float y);

  void moveLeft(float delta_time, float screen_width);
  void moveRight(float delta_time, float screen_width);

  int getLives() const;
  void loseLife();
  void resetLives();
  bool isDead() const;

 private:
  float speed;
  int lives;
};
