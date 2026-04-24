#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

struct Circle {
  sf::Vector2f position;
  sf::Vector2f velocity;
  float radius;
};

class Model {
 public:
  Model(float windowWidth, float windowHeight);

  void update(float deltaTime);
  void handleHit(int index);
  void handleMiss();
  void reset();
  void decreaseTime(float dt);
  int checkHit(const sf::Vector2i& mousePos) const;
  const std::vector<Circle>& getCircles() const { return circles; }
  int getScore() const { return score; }
  float getTimeLeft() const { return timeLeft; }
  bool isActive() const { return active; }

 private:
  std::vector<Circle> circles;
  int score;
  float timeLeft;
  bool active;

  float windowWidth;   // это не во view, потому что круги при перемещении не
  float windowHeight;  // должны выйти за рамки экрана

  const float penalty = 1.0f;
  const float initialTime = 30.0f;
  const int circleCount = 5;
  const float circleRadius = 30.0f;

  void initCircles();
  void clampPosition(Circle& circle);
  void randomizeCircle(Circle& circle);
};
