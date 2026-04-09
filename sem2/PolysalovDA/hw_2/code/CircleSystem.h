#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <random>
#include <vector>

#include "Circle.h"
#include "Constants.h"

class CircleSystem : public sf::Drawable {
 private:
  std::vector<std::unique_ptr<Circle>> circles;
  unsigned int score;
  sf::Vector2u window_size;
  bool isFreePosition(const sf::Vector2f& pos, const Circle* exclude) const;
  bool trySetFreePosition(Circle* circle);

 public:
  CircleSystem(const sf::Vector2u& size);
  void initialize(unsigned int count);
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
  bool checkHit(const sf::Vector2i& mouse_pos);
  int getScore() const { return score; }
  void reset();
};