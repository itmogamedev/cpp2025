#include "GameModel.h"

#include <ctime>

void GameModel::reset() {
  timer = timerMax;
  balls.clear();

  for (int i = 0; i < ballsCount; ++i) {
    balls.push_back(getCircle());
  }
}

void GameModel::update(float deltaTime) {
  timer -= deltaTime;

  // update ball positions
  for (int i = 0; i < balls.size(); ++i) {
    balls[i].position.x += balls[i].velocity.x * deltaTime;
    balls[i].position.y += balls[i].velocity.y * deltaTime;

    // check bounds
    if (balls[i].position.y + (balls[i].radius * 2) >= height) {
      balls[i].velocity.y = -std::abs(balls[i].velocity.y);
    } else if (balls[i].position.y <= 0) {
      balls[i].velocity.y = std::abs(balls[i].velocity.y);
    }
    if (balls[i].position.x + (balls[i].radius * 2) >= width) {
      balls[i].velocity.x = -std::abs(balls[i].velocity.x);
    } else if (balls[i].position.x <= 0) {
      balls[i].velocity.x = std::abs(balls[i].velocity.x);
    }
  }
}

void GameModel::handleClick(float x, float y) {
  x -= ballRadius;
  y -= ballRadius;
  for (int i = 0; i < balls.size(); ++i) {
    float dx = x - balls[i].position.x;
    float dy = y - balls[i].position.y;
    if (dx * dx + dy * dy < ballRadius * ballRadius) {
      balls.erase(balls.cbegin() + i);
      balls.push_back(getCircle());
      timer += 1.f;
      return;
    }
  }
  timer -= 3.f;
}

Circle GameModel::getCircle() const {
  float randXPosition = (rand() % (width - 2 * ballRadius)) + ballRadius;
  float randYPosition = (rand() % (height - 2 * ballRadius)) + ballRadius;

  float randXVelocity = (rand() % 200) - 100;
  float randYVelocity = (rand() % 200) - 100;

  sf::Vector2f velocity(randXVelocity, randYVelocity);

  return Circle(ballRadius, {randXPosition, randYPosition},
                velocity.normalized() * ballSpeed);
}
