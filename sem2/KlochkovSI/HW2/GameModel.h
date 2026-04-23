#ifndef GAME_MODEL_H_
#define GAME_MODEL_H_

#include <vector>

#include "Circle.h"
#include "Constants.h"

class GameModel {
 public:
  GameModel();

  void initCircles();
  void update(float delta_time);
  void handleHit(int index);
  void handleMiss();

  bool isGameOver() const;
  int getScore() const;
  float getTimeRemaining() const;
  const std::vector<Circle>& getCircles() const;
  std::vector<Circle>& getCircles();

 private:
  std::vector<Circle> circles_;
  float time_remaining_;
  int score_;
  bool game_over_;
};

#endif  // GAME_MODEL_H_
