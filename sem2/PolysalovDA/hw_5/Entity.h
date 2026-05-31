#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Entity : public sf::Drawable {
 protected:
  const sf::Texture* texture_pointer;
  sf::Sprite sprite;

 public:
  Entity(const sf::Texture& tex);

  void setPosition(const sf::Vector2f& position);
  void setPosition(float x, float y);
  sf::Vector2f getPosition() const;
  sf::Vector2f getSize() const;
  sf::FloatRect getGlobalBounds() const;
  void move(const sf::Vector2f& offset);
  void setOrigin(const sf::Vector2f& origin);
  void setScale(float x, float y);

  virtual void update(float dt) {}

 protected:
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};