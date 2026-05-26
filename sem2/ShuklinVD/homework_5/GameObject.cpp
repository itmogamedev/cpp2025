#include "GameObject.h"

GameObject::GameObject()
    : x(0.f), y(0.f), width(0.f), height(0.f), alive(true) {}

GameObject::GameObject(float x, float y, float width, float height)
    : x(x), y(y), width(width), height(height), alive(true) {}

void GameObject::setPosition(float x, float y) {
  this->x = x;
  this->y = y;
}

void GameObject::move(float dx, float dy) {
  x += dx;
  y += dy;
}

float GameObject::getX() const { return x; }
float GameObject::getY() const { return y; }
float GameObject::getWidth() const { return width; }
float GameObject::getHeight() const { return height; }

sf::FloatRect GameObject::getBounds() const {
  return sf::FloatRect(x, y, width, height);
}

bool GameObject::collidesWith(const GameObject& other) const {
  return getBounds().intersects(other.getBounds());
}

void GameObject::setSprite(const sf::Texture& texture) {
  sprite.setTexture(texture);
  sf::Vector2u tex_size = texture.getSize();
  if (tex_size.x > 0 && tex_size.y > 0) {
    float scale_x = width / static_cast<float>(tex_size.x);
    float scale_y = height / static_cast<float>(tex_size.y);
    sprite.setScale(scale_x, scale_y);
  }
}

sf::Sprite& GameObject::getSprite() {
  sprite.setPosition(x, y);
  return sprite;
}

bool GameObject::isAlive() const { return alive; }
void GameObject::kill() { alive = false; }
void GameObject::revive() { alive = true; }
