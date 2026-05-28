#include "meteor.h"

#include <algorithm>
#include <cstdlib>
#include <stdexcept>

static float RandomFloat(float min_value, float max_value) {
  return min_value + static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX) *
                         (max_value - min_value);
}

Meteor::Meteor(float screen_width, float screen_height)
    : screen_width(screen_width), screen_height(screen_height) {
  if (!meteor_texture.loadFromFile("C:/Users/Admin/Desktop/meow/cpp2sem/miniHw5/Images/kam5.png")) {
    throw std::runtime_error("Failed to load meteor texture.");
  }

  meteor_sprite.setTexture(meteor_texture);
  Restart();
}

void Meteor::Move(float delta_time, float speed_boost) {
  meteor_sprite.move(0.f, (fall_speed + speed_boost) * delta_time);

  if (meteor_sprite.getPosition().y > screen_height + meteor_sprite.getGlobalBounds().height) {
    Restart();
  }
}

void Meteor::Draw(sf::RenderWindow& window) const {
  window.draw(meteor_sprite);
}

bool Meteor::Collision(const sf::FloatRect& object) const {
  return meteor_sprite.getGlobalBounds().intersects(object);
}

void Meteor::Restart() {
  const float scale = RandomFloat(0.2f, 0.5f);
  meteor_sprite.setScale(scale, scale);

  const float max_spawn_x = std::max(0.f, screen_width - meteor_sprite.getGlobalBounds().width);
  const float spawn_x = RandomFloat(0.f, max_spawn_x);
  const float spawn_y = RandomFloat(-screen_height, -80.f);

  meteor_sprite.setPosition(spawn_x, spawn_y);
  fall_speed = RandomFloat(80.f, 120.f);
}

sf::FloatRect Meteor::GetMeteorBounds() const {
  return meteor_sprite.getGlobalBounds();
}
