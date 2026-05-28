#include "asteroid.h"

#include <algorithm>

#include "resource_manager.h"

Asteroid::Asteroid(float x, float speed, const std::string& texture_path)
    : speed(speed) {
  sf::Texture& texture =
      ResourceManager::getInstance().getTexture(texture_path);
  sf::Vector2u tex_size = texture.getSize();
  if (tex_size.x > 0 && tex_size.y > 0) {
    sprite.setTexture(texture, true);
    // Сводим максимальную сторону к ~80 пикселей.
    float largest = static_cast<float>(std::max(tex_size.x, tex_size.y));
    float scale = 80.f / largest;
    sprite.setScale(scale, scale);
    sprite.setOrigin(static_cast<float>(tex_size.x) / 2.f,
                     static_cast<float>(tex_size.y) / 2.f);
  }
  sprite.setPosition(x, -50.f);
}

void Asteroid::update(float delta_time) {
  sprite.move(0.f, speed * delta_time);
}

void Asteroid::draw(sf::RenderWindow& window) const { window.draw(sprite); }

sf::FloatRect Asteroid::getBounds() const {
  // Чуть сжимаем хитбокс, иначе попасть/уворачиваться слишком сложно.
  sf::FloatRect bounds = sprite.getGlobalBounds();
  float shrink_x = bounds.width * 0.12f;
  float shrink_y = bounds.height * 0.12f;
  return sf::FloatRect(bounds.left + shrink_x, bounds.top + shrink_y,
                       bounds.width - 2.f * shrink_x,
                       bounds.height - 2.f * shrink_y);
}

bool Asteroid::isOffScreen(float window_height) const {
  return sprite.getPosition().y > window_height + 60.f;
}
