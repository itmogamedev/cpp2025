#pragma once
#include "GameObject.h"

class Asteroid : public GameObject {
 public:
  Asteroid();
  Asteroid(float x, float y, float speed);

  void update(float delta_time);

  void setSpeed(float speed);
  float getSpeed() const;

 private:
  float speed;
};
