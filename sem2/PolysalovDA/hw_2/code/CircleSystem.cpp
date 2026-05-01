#include "CircleSystem.h"

CircleSystem::CircleSystem(const sf::Vector2u& size)
    : window_size(size), score(START_SCORE) {}

void CircleSystem::initialize(unsigned int count) {
  circles.clear();

  for (int i = 0; i < count; ++i) {
    auto circle = std::make_unique<Circle>();
    trySetFreePosition(circle.get());
    circle->setRandomVelocity();
    circles.push_back(std::move(circle));
  }
}

bool CircleSystem::checkHit(const sf::Vector2i& mouse_pos) {
  for (auto& circle : circles) {
    if (circle->isActive() && circle->containsPoint(mouse_pos)) {
      score++;
      trySetFreePosition(circle.get());
      return true;
    }
  }
  return false;
}

bool CircleSystem::trySetFreePosition(Circle* circle) {
  for (int attempt = 0; attempt < FIND_FREE_POS_ATTEMPTS; ++attempt) {
    circle->setRandomPosition(window_size);
    if (isFreePosition(circle->getPosition(), circle)) {
      return true;
    }
  }
  return false;
}

bool CircleSystem::isFreePosition(const sf::Vector2f& pos,
                                  const Circle* exclude) const {
  for (const auto& circle : circles) {
    if (circle.get() != exclude && circle->isActive()) {
      Circle temp(circle->getRadius());
      temp.setPosition(pos);
      if (temp.isOverlapping(*circle)) {
        return false;
      }
    }
  }
  return true;
}

void CircleSystem::draw(sf::RenderTarget& target,
                        sf::RenderStates states) const {
  for (const auto& circle : circles) {
    target.draw(*circle, states);
  }
}

void CircleSystem::reset() {
  score = START_SCORE;
  initialize(CIRCLES_COUNT);
}

void CircleSystem::update(float delta_time, const sf::Vector2u& window_size) {
  for (auto& circle : circles) {
    if (circle->isActive()) {
      circle->update(delta_time, window_size);
    }
  }
}