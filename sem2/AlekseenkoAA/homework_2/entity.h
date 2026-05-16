#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>
#include <stdexcept>
#include <type_traits>

class Entity {
 private:
  std::unique_ptr<sf::Shape> shape;

  void ensureShape() const {
    if (!shape) {
      throw std::logic_error("Shape is not set");
    }
  }

 public:
  Entity() = default;

  bool hasShape() const { return static_cast<bool>(shape); }

  template <typename T>
  void setShape(const T& new_shape) {
    static_assert(std::is_base_of_v<sf::Shape, T>,
                  "T must derive from sf::Shape");

    shape = std::make_unique<T>(new_shape);
  }

  sf::Vector2f getPosition() const {
    ensureShape();
    return shape->getPosition();
  }

  void setPosition(sf::Vector2f new_position) {
    ensureShape();
    shape->setPosition(new_position);
  }

  sf::Vector2f getScale() const {
    ensureShape();
    return shape->getScale();
  }

  void setScale(sf::Vector2f factors) {
    ensureShape();
    shape->setScale(factors);
  }

  sf::Color getColor() const {
    ensureShape();
    return shape->getFillColor();
  }

  void setColor(sf::Color color) {
    ensureShape();
    shape->setFillColor(color);
  }

  sf::Shape& getShape() {
    ensureShape();
    return *shape;
  }

  const sf::Shape& getShape() const {
    ensureShape();
    return *shape;
  }
};