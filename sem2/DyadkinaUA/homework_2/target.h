#ifndef TARGET_H_
#define TARGET_H_

#include <SFML/Graphics.hpp>

class CircleTarget {
 public:
  CircleTarget(float radius, const sf::Color& color);

  void setPosition(const sf::Vector2f& position);
  void draw(sf::RenderWindow& window) const;
  bool contains(const sf::Vector2f& point) const;
  float getRadius() const;
  sf::Vector2f getPosition() const;

 private:
  sf::CircleShape shape;
};

#endif  // TARGET_H_
