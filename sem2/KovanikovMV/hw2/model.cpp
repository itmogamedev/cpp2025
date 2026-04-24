#include "model.h"

#include <cmath>
#include <cstdlib>
#include <ctime>

Model::Model(float windowWidth, float windowHeight)
    : windowWidth(windowWidth),
      windowHeight(windowHeight),
      score(0),
      timeLeft(initialTime),
      active(true) {
  std::srand(static_cast<unsigned>(std::time(nullptr)));
  reset();
}

void Model::initCircles() {
  circles.clear();
  for (int i = 0; i < circleCount; ++i) {
    Circle c;
    c.radius = circleRadius;
    randomizeCircle(c);
    circles.push_back(c);
  }
}

void Model::randomizeCircle(Circle& circle) {
  circle.position.x = circleRadius + static_cast<float>(std::rand()) /
                                         RAND_MAX *
                                         (windowWidth - 2 * circleRadius);
  circle.position.y = circleRadius + static_cast<float>(std::rand()) /
                                         RAND_MAX *
                                         (windowHeight - 2 * circleRadius);
  circle.velocity.x =
      -200.0f + static_cast<float>(std::rand()) / RAND_MAX * 400.0f;
  circle.velocity.y =
      -200.0f + static_cast<float>(std::rand()) / RAND_MAX * 400.0f;
}

void Model::clampPosition(Circle& circle) {
  if (circle.position.x - circle.radius < 0) {
    circle.position.x = circle.radius;
    circle.velocity.x = -circle.velocity.x;
  }
  if (circle.position.x + circle.radius > windowWidth) {
    circle.position.x = windowWidth - circle.radius;
    circle.velocity.x = -circle.velocity.x;
  }
  if (circle.position.y - circle.radius < 0) {
    circle.position.y = circle.radius;
    circle.velocity.y = -circle.velocity.y;
  }
  if (circle.position.y + circle.radius > windowHeight) {
    circle.position.y = windowHeight - circle.radius;
    circle.velocity.y = -circle.velocity.y;
  }
}

void Model::update(float deltaTime) {
  if (!active) return;
  for (auto& circle : circles) {
    circle.position += circle.velocity * deltaTime;
    clampPosition(circle);
  }
}

int Model::checkHit(const sf::Vector2i& mousePos) const {
  for (size_t i = 0; i < circles.size(); ++i) {
    float dx = mousePos.x - circles[i].position.x;
    float dy = mousePos.y - circles[i].position.y;
    float distSq = dx * dx + dy * dy;
    if (distSq <= circles[i].radius * circles[i].radius) {
      return static_cast<int>(i);
    }
  }
  return -1;
}

void Model::handleHit(int index) {
  if (!active) return;
  if (index >= 0 && index < static_cast<int>(circles.size())) {
    score++;
    randomizeCircle(circles[index]);
  }
}

void Model::handleMiss() {
  if (!active) return;
  timeLeft -= penalty;
  if (timeLeft <= 0.0f) {
    timeLeft = 0.0f;
    active = false;
  }
}

void Model::reset() {
  score = 0;
  timeLeft = initialTime;
  active = true;
  initCircles();
}

void Model::decreaseTime(float dt) {
  if (!active) return;
  timeLeft -= dt;
  if (timeLeft <= 0.0f) {
    timeLeft = 0.0f;
    active = false;
  }
}
