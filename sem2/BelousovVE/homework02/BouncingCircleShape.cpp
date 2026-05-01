#include "BouncingCircleShape.h"

#include "Constants.h"

namespace SCREEN = Constants::SCREEN;
namespace NUMS = Constants::NUMS;

BouncingCircleShape::BouncingCircleShape(float r, size_t pointCnt)
    : CircleShape(r, pointCnt) {
  speedX = rand() % NUMS::modX + NUMS::minSpeedX;
  speedY = rand() % NUMS::modY + NUMS::minSpeedY;

  this->setOrigin(sf::Vector2f(r, r));

  moveDir =
      sf::Vector2<int>(rand() % 2 == 0 ? 1 : -1, rand() % 2 == 0 ? 1 : -1);

  int x = r + 1;
  this->setPosition(sf::Vector2f(rand() % (SCREEN::width - x) + x,
                                 rand() % (SCREEN::height - x) + x));
  this->setFillColor(sf::Color::Cyan);
}

void BouncingCircleShape::update(sf::RenderWindow& wn) {
  move();

  updateDirectionOnCollisionWithWindow(wn);
}

void BouncingCircleShape::move() {
  sf::Vector2f pos = this->getPosition();
  this->setPosition(
      sf::Vector2f(pos.x + speedX * moveDir.x, pos.y + speedY * moveDir.y));
}

void BouncingCircleShape::updateDirectionOnCollisionWithWindow(
    sf::RenderWindow& wn) {
  sf::Vector2u wnSize = wn.getSize();
  float r = this->getRadius();
  sf::Vector2f circlePos = this->getPosition();

  if (circlePos.x - r <= 0) {
    circlePos.x = r;
    moveDir.x *= -1;
  } else if (circlePos.x + r >= wnSize.x) {
    circlePos.x = wnSize.x - r;
    moveDir.x *= -1;
  }

  if (circlePos.y - r <= 0) {
    circlePos.y = r;
    moveDir.y *= -1;
  } else if (circlePos.y + r >= wnSize.y) {
    circlePos.y = wnSize.y - r;
    moveDir.y *= -1;
  }

  this->setPosition(circlePos);
}

void BouncingCircleShape::draw(sf::RenderWindow& wn) { wn.draw(*this); }

void BouncingCircleShape::increaseSpeedXY(float val) {
  speedX += val;
  speedY += val;
}
