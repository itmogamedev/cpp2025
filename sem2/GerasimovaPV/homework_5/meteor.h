#ifndef MINIHW5_METEOR_H
#define MINIHW5_METEOR_H

#include <SFML/Graphics.hpp>

class Meteor {
 public:
  Meteor(float screen_width, float screen_height);

  void Move(float delta_time, float speed_boost);
  void Draw(sf::RenderWindow& window) const;
  bool Collision(const sf::FloatRect& object) const;
  void Restart();
  sf::FloatRect GetMeteorBounds() const;

 private:
  sf::Sprite meteor_sprite;
  sf::Texture meteor_texture;
  float screen_width;
  float screen_height;
  float fall_speed = 0.f;
};

#endif  // MINIHW5_METEOR_H
