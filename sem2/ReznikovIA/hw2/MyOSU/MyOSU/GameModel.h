#pragma once

#include <vector>

#include "Circle.h"

class GameModel {
 public:
  GameModel(int ballsCount, int ballRadius, float ballSpeed, int width,
            int height, float timerMax)
      : ballsCount(ballsCount),
        ballRadius(ballRadius),
        ballSpeed(ballSpeed),
        width(width),
        height(height),
        timerMax(timerMax) {};
  void update(float deltaTime);
  void reset();
  void handleClick(float x, float y);
  bool isGameOver() const { return timer <= 0.f; };
  const std::vector<Circle>& getBalls() const { return balls; };
  const float getTimer() const { return timer; }
  int getWidth() const { return width; }
  int getHeight() const { return height; }

 private:
  Circle getCircle() const;

  std::vector<Circle> balls;
  int ballsCount;
  int ballRadius;
  float ballSpeed;
  int width;
  int height;
  float timer;
  float timerMax;
};
