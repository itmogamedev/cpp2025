#pragma once
#include <SFML/Graphics.hpp>

class GameObject {
 public:
  GameObject();
  GameObject(float x, float y, float width, float height);

  void setPosition(float x, float y);
  void move(float dx, float dy);

  float getX() const;
  float getY() const;
  float getWidth() const;
  float getHeight() const;

  sf::FloatRect getBounds() const;
  bool collidesWith(const GameObject& other) const;

  void setSprite(const sf::Texture& texture);
  sf::Sprite& getSprite();

  bool isAlive() const;
  void kill();
  void revive();

 protected:
  float x;
  float y;
  float width;
  float height;
  bool alive;
  sf::Sprite sprite;
};
