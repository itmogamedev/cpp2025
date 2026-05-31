#include "player.h"

#include <algorithm>

#include "resource_manager.h"

Player::Player(float window_width, float window_height)
    : window_width(window_width),
      speed(380.f),
      reload_timer(0.f),
      current_reload_time(0.45f),
      invulnerability_timer(0.f),
      lives(3) {
  sf::Texture& texture =
      ResourceManager::getInstance().getTexture("assets/player.png");
  sf::Vector2u tex_size = texture.getSize();
  if (tex_size.x > 0 && tex_size.y > 0) {
    sprite.setTexture(texture, true);
    // Масштабируем так, чтобы высота была ~90 пикселей.
    float scale = 90.f / static_cast<float>(tex_size.y);
    sprite.setScale(scale, scale);
    sprite.setOrigin(static_cast<float>(tex_size.x) / 2.f,
                     static_cast<float>(tex_size.y) / 2.f);
  }
  sprite.setPosition(window_width / 2.f, window_height - 70.f);
}

void Player::update(float delta_time) {
  if (reload_timer > 0.f) {
    reload_timer -= delta_time;
  }
  if (invulnerability_timer > 0.f) {
    invulnerability_timer -= delta_time;
    // Эффект мигания: чередуем альфа-канал.
    int blink = static_cast<int>(invulnerability_timer * 10.f);
    sprite.setColor(blink % 2 == 0 ? sf::Color(255, 255, 255, 120)
                                   : sf::Color::White);
  } else {
    sprite.setColor(sf::Color::White);
  }
}

void Player::draw(sf::RenderWindow& window) const { window.draw(sprite); }

void Player::moveLeft(float delta_time) {
  sf::Vector2f pos = sprite.getPosition();
  pos.x -= speed * delta_time;
  float half_width = sprite.getGlobalBounds().width / 2.f;
  if (pos.x < half_width) {
    pos.x = half_width;
  }
  sprite.setPosition(pos);
}

void Player::moveRight(float delta_time) {
  sf::Vector2f pos = sprite.getPosition();
  pos.x += speed * delta_time;
  float half_width = sprite.getGlobalBounds().width / 2.f;
  if (pos.x > window_width - half_width) {
    pos.x = window_width - half_width;
  }
  sprite.setPosition(pos);
}

bool Player::canShoot() const { return reload_timer <= 0.f; }

void Player::shoot() { reload_timer = current_reload_time; }

void Player::updateReloadTime(int score) {
  // 0.45с в начале, минимум 0.1с. Линейно уменьшается с очками.
  current_reload_time =
      std::max(0.1f, 0.45f - static_cast<float>(score) * 0.012f);
}

sf::FloatRect Player::getBounds() const {
  // Берём чуть уменьшенный bbox, чтобы коллизии были справедливее
  // (картинки не идеально вписаны в свои прямоугольники).
  sf::FloatRect bounds = sprite.getGlobalBounds();
  float shrink_x = bounds.width * 0.15f;
  float shrink_y = bounds.height * 0.15f;
  return sf::FloatRect(bounds.left + shrink_x, bounds.top + shrink_y,
                       bounds.width - 2.f * shrink_x,
                       bounds.height - 2.f * shrink_y);
}

sf::Vector2f Player::getPosition() const { return sprite.getPosition(); }

int Player::getLives() const { return lives; }

void Player::loseLife() {
  if (invulnerability_timer > 0.f) {
    return;  // Урон во время i-frames не засчитывается.
  }
  --lives;
  invulnerability_timer = 1.2f;
}

bool Player::isAlive() const { return lives > 0; }

bool Player::isInvulnerable() const { return invulnerability_timer > 0.f; }
