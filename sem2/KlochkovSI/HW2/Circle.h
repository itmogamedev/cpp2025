#ifndef CIRCLE_H_
#define CIRCLE_H_

#include <SFML/Graphics.hpp>

class Circle {
 public:
  Circle(float radius, sf::Color color);

  void randomize(float window_width, float window_height);
  void update(float delta_time, float window_width, float window_height);
  void draw(sf::RenderWindow& window) const;
  bool isClicked(sf::Vector2f mouse_pos) const;

 private:
  sf::CircleShape shape_;
  sf::Vector2f velocity_;
  float radius_;
};

#endif  // CIRCLE_H_
