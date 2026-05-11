// Circle.h
// Класс игрового круга: хранит позицию, скорость и визуальное представление,
// умеет двигаться с отскоком от границ поля, проверять попадание мыши и
// респавниться в новой случайной точке с новой скоростью. Поддерживает
// опциональную текстуру: если задана, отрисовывается внутри круглой формы.

#ifndef HOMEWORK_2_CIRCLE_H
#define HOMEWORK_2_CIRCLE_H

#include <SFML/Graphics.hpp>

class Circle {
 public:
  Circle(float radius, float field_width, float field_height, float top_offset);

  void update(float dt);
  void draw(sf::RenderWindow& window);
  bool contains(float mx, float my) const;
  void respawn();
  void setTexture(const sf::Texture* texture);

 private:
  void randomize();
  void applyTexture();

  float radius;
  float field_width;
  float field_height;
  float top_offset;
  float x;
  float y;
  float vx;
  float vy;
  sf::CircleShape shape;
  const sf::Texture* texture;
};

#endif  // HOMEWORK_2_CIRCLE_H
