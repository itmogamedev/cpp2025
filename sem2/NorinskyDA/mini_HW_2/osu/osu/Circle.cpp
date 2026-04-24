#include "Circle.h"

#include <SFML/Graphics.hpp>
#include <random>

Circle::Circle(float r) : radius(r) {
  shape.setRadius(radius);
  shape.setFillColor(sf::Color::Cyan);
  shape.setOutlineColor(sf::Color::White);
  shape.setOutlineThickness(2);
  shape.setOrigin(sf::Vector2f(radius, radius));  // Центрируем круг
}

void Circle::setPosition(float x, float y) {
  shape.setPosition(sf::Vector2f(x, y));
}

void Circle::draw(sf::RenderWindow& window) { window.draw(shape); }

bool Circle::contains(float x, float y) {
  // Проверяем, попал ли клик в круг
  sf::Vector2f pos = shape.getPosition();
  float dx = x - pos.x;
  float dy = y - pos.y;
  return (dx * dx + dy * dy) <= (radius * radius);
}
