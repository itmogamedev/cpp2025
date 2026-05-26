#include "Entity.h"

#include <iostream>

Entity::Entity(const sf::Texture& texture)
    : texture_pointer(&texture), sprite(*texture_pointer) {}

void Entity::setPosition(const sf::Vector2f& position) {
  sprite.setPosition(position);
}

void Entity::setPosition(float x, float y) { sprite.setPosition({x, y}); }

sf::Vector2f Entity::getPosition() const { return sprite.getPosition(); }

sf::Vector2f Entity::getSize() const {
  return sf::Vector2f(
      static_cast<float>(texture_pointer->getSize().x) * sprite.getScale().x,
      static_cast<float>(texture_pointer->getSize().y) * sprite.getScale().y);
}

sf::FloatRect Entity::getGlobalBounds() const {
  return sprite.getGlobalBounds();
}

void Entity::move(const sf::Vector2f& offset) { sprite.move(offset); }

void Entity::setOrigin(const sf::Vector2f& origin) { sprite.setOrigin(origin); }

void Entity::setScale(float x, float y) { sprite.setScale({x, y}); }

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(sprite, states);
}