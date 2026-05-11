#pragma once

#include "SFML/Graphics.hpp"

class Timer : public sf::Time {
 private:
  sf::Clock cl;

 public:
  Timer(sf::Time tm);

  int32_t getRemainingTimeAsMilliseconds();

  void start();

  void stop();

  void draw(sf::RenderWindow&);
};
